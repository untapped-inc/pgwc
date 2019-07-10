#include <ArduinoJson.h>
#include <SD.h>
#include <WiFiNINA.h>
#include "WiFiCredentials.h"


#define FLOWMETER_PIN A0
#define ORP_PIN A1
#define RELAY_PIN 13
//this is how many units the analog read must differ between readings in order to be considered a rising or falling edge
#define FLOWMETER_THRESHOLD 100
#define URL "pgw.semawater.org"
#define DEVICE_ID 1

//used for SD Card - Arduino digital pin being used for the SD Card Reader's clock pin
const char *ORP_FILENAME =  "SensorB.txt";
const char *FLOWMETER_FILENAME = "SensorA.txt";

const int CS_PIN = 4;
//the number of milliliters that have been detected by the sensor per pulse (rising and falling edge)
const int ML_PER_PULSE = 500;

//variable to store the flowmeter readings for future comparison
float previousFlowmeter = -9999;

WiFiClient client;
int status = WL_IDLE_STATUS;

long startTime = 0;
long startingMillis;

long previousORPSampleTime;
long previousWifiTime;
//total milliseconds per ORP sample 5 minutes
const long ORP_SAMPlE_MILLIS = 300000;
// interval at which to communicate (milliseconds)
const int WIFI_INTERVAL = 1000;

//track whether we are off or on
bool waterIsFlowing = false;

//set to true when it's time to send new sensor data up
bool newDataExists = false;

//the current water unit left for the device since the last currentMaxWaterAmount was set. It’s set during first connection 
//and changes either locally, through local calculations and after a sync/connection, from the remote calculation.
int currentWaterAmount = -1;
//the current max water unit set for the device, it’s set during first connection and changes on subsequent connections or synchronizations. 
//The controller CANNOT start retrieving data from sensors without this value. THIS VALUE DOES NOT CHANGE, IT’S ONLY USED FOR REFERENCE.
int maxWaterAmount = -1;

//used for JSON Deserilization
StaticJsonDocument<1024> jsonDoc1;
StaticJsonDocument<1024> jsonDoc2;

void setup() {
  Serial.begin(9600);
  pinMode(FLOWMETER_PIN, INPUT_PULLUP);
  pinMode(ORP_PIN, INPUT);
  Serial.println("Starting");
  status = WiFi.begin(WifiSSID, WifiPassword);

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
  
  initTimekeeping();
  initSDCard();
  pinMode(RELAY_PIN, OUTPUT);
  //make sure that the water is off when we start
  turnWaterOff();
  //track time to make sure we only sample once per 5 minutes
  previousORPSampleTime = millis();
  previousWifiTime = previousORPSampleTime;
}

void loop() {
  long loopTime = millis();
  
  //this logic deals with  measurement - check that water is flowing and that appropriate variables have been set first!
  if (waterIsFlowing && maxWaterAmount != -1 && currentWaterAmount != -1){
    int flowmeterReading = getFlowmeterReading(); //in milliliters
    //decrement the water from the current water amount
    currentWaterAmount -= flowmeterReading;
    //Serial.println(totalFlowmeter);
    //write to SD Card
    appendSensor(flowmeterReading, true);
    newDataExists = true;
    //turn off the motor when enough water has been delivered
   if(currentWaterAmount <= 0){
      //turn off relay
      turnWaterOff();
   }
  }else{
    //this deals with communication when the water is not flowing
    //check to make sure that enough time has elapsed before attempting communication
    if (loopTime - previousWifiTime > WIFI_INTERVAL){
      previousWifiTime = loopTime;
      //if there is new data, send it, otherwise check the API
      if (!newDataExists){
        //sends the GET HTTP request
        getData();
      }else{
        //todo: send the data - this needs to be implemented in future versions
        //String flowmeterData = readFile(FLOWMETER_FILENAME);
        //String orpData = readFile(ORP_FILENAME);
        /*Serial.print("flowmeter Data: ");
        Serial.println(flowmeterData);
        */

        //orpData.trim();

        String orpData = "";
               
        unsigned long createdAtTime = getCurrentTime();
        
        String requestBody = 
        "{\"clientReadings\":{\"sensorA\": [],\"sensorB\": [ " + orpData + "] },\"clientDevice\":{ \"id\": "
        + String(DEVICE_ID) +
        ",\"current_water_amount\": " + currentWaterAmount +
        ",\"max_water_amount\":{ \"value\": " + maxWaterAmount + ", \"created_at\": " + createdAtTime + " }}}";
        
       // Serial.print("request body: ");
        //Serial.println(requestBody);
        postData(requestBody);

        //clean up the old data
        SD.remove(FLOWMETER_FILENAME);
        //July 10, 2019: this file isn't being overwritten because we can't send it up to the endpoint yet
        //SD.remove(ORP_FILENAME);
        newDataExists = false;
      }
    }
    //check for the response to the HTTP GET Request - this sets the max water and current water variables
    checkResponse();

    //decide if we should turn the water on
    if (currentWaterAmount > 0){
      turnWaterOn();
    }
  }  

  //ORP readings every 5 minutes
  if (loopTime - previousORPSampleTime > ORP_SAMPlE_MILLIS){
    int ORPReading = getORPReading(); //in mv
    previousORPSampleTime = loopTime;
    //grab reading from ORP Sensor
    appendSensor(ORPReading, false);
    newDataExists = true;
  }

  delay(100);
}


/***Helper Functions***/

String readFile(const char *filename){
  Serial.println(filename);
  String fileContents;
  File sensorFile = SD.open(filename);
  if (sensorFile){
    while(sensorFile.available()){
     fileContents += (char)sensorFile.read();
      //Serial.write(sensorFile.read());
    }
    sensorFile.close();
  }else{
    Serial.println("Failed to open for read");
  }
  return fileContents;
}

void appendSensor(unsigned long value, bool isSensorA){
  //todo: in future versions, allow the ORP to be appended
  File sensorFile;
  if (isSensorA){
    sensorFile =  SD.open(FLOWMETER_FILENAME, FILE_WRITE);
  }else{
    sensorFile = SD.open(ORP_FILENAME, FILE_WRITE);
  }
  if (sensorFile){
    char buffer[1000];
    long unixTime = getCurrentTime();
    sprintf(buffer, "{\"created_at\": %lu, \"value\": %lu }", unixTime, value); 
    sensorFile.println(buffer);
  }else{
    Serial.println("Failed to open for print");
  }
  sensorFile.close();
}


long getCurrentTime(){
  return startTime + ( millis()-startingMillis);
}

void initTimekeeping(){
  //get the starting time
  while(startTime == 0){
    Serial.println("Getting Time");
    startTime = WiFi.getTime();
  }
  startingMillis = millis();
}

//helper function to setup SD Card
void initSDCard(){
  File sensorAFile; 
  File sensorBFile;
  //setup pin for SD Card 
  pinMode(CS_PIN, OUTPUT);
  Serial.println("Starting SD Card initialization");

  if (!SD.begin(CS_PIN)){
    Serial.println("SD Card initialiation failed!");
    return;
  }

  Serial.println("Successfully initialized SD Card");

  //setup flowmeter file
  if (!SD.exists(FLOWMETER_FILENAME)){
    sensorAFile = SD.open(FLOWMETER_FILENAME, FILE_WRITE);
    if (sensorAFile){
      Serial.println("creating file a");
      sensorAFile.close();
    }else{
      Serial.println("file a creation failed");
    }
  
  }

  //orp file
  if(!SD.exists(ORP_FILENAME)){
    sensorBFile = SD.open(ORP_FILENAME, O_RDWR | O_CREAT);
    sensorBFile.close();
  }
}

//flowmeter reading in mL
int getFlowmeterReading(){
  int milliliters = 0;
  //read from the flowmeter
  float currentFlowmeter = analogRead(FLOWMETER_PIN);
  //Serial.println(currentFlowmeter);
  //check for either rising or falling edge
  if (previousFlowmeter != -9999 && (abs(currentFlowmeter - previousFlowmeter) > FLOWMETER_THRESHOLD)){
    milliliters = ML_PER_PULSE;
  }
  //the current reading is saved for comparison next time
  previousFlowmeter = currentFlowmeter;
  return milliliters;
}

//returns the ORP meter's reading in millivolts
float getORPReading(){
  //it's just an analog read
  return analogRead(ORP_PIN);
}

void turnWaterOff(){
  digitalWrite(RELAY_PIN, HIGH);
  waterIsFlowing = false;
}

void turnWaterOn(){
  digitalWrite(RELAY_PIN, LOW);
  waterIsFlowing = true;
}
