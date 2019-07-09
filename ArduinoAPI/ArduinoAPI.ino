#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJWT.h>
String dev_key = "jfbnve98rh394nr9u";
ArduinoJWT jwt = ArduinoJWT(dev_key);
String encodedJWT;
String TOKEN;
String SynchPayload;
String LoginPayload;
String LoginPayload_Device;
String ID,NAME,SERIAL_NUMBER,IP_ADDRESS,FIRMWARE,KIOSK_ID,USER_ID,CREATED,UPDATED,IAT,EXP;
String CURRENT_WATER_AMOUNT,ACTIVE;
String SENSOR_ID,SENSOR_NAME,SAMPLING_SITE,PARAMETER_ID,DEVICE_ID,CREATED_AT,UPDATED_AT,
       MAX_WATER_AMOUNT,SENSOR2_ID,SENSOR2_NAME,SAMPLING_SITE2,PARAMETER_ID2,DEVICE_ID2,CREATED_AT2,
       UPDATED_AT2,VALUE,CREATED_AT3;
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)

void setup() {
Serial.begin(115200);
 WiFi.begin("Etisalat-iModem-ETB2", "4d5r19y0");   //WiFi connection
//   WiFi.beFrgin("uits.Solutions", "Fruits@55@Fruits");   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
    unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      Synch();
      if(SynchPayload.indexOf("Successfully synchronized")<0){
        Get_Token();
        delay(1000);
       // Serial.println(TOKEN);
        delay(1000);
        Decode_Token();
       // Serial.print("Login Payload: ");
      //  Serial.println(LoginPayload);
          }
}


}
