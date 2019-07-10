void getData(){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   if (client.connect(URL, 80)){
    Serial.println("Getting current water");
      client.print("GET /sema/water-ops/pgwc/");
      client.print(DEVICE_ID);
      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(URL);
      client.println("Content-type:application/json");
      client.println("Connection: close");
      client.println();
   }else{
    Serial.println("Error connecting to server");
   }
  }
}

//check for the response to the HTTP GET
void checkResponse(){
  //hold the JSON results
  String deviceString;
  String maxWaterString;
  //find the nested objects using this
  int bracketCount = 0;
  
  //read from the API response
   while (client.available()) {
    char c = (char)client.read();
    //wait for the JSON
    if (c == '{'){
      bracketCount++;
    }
    //start building the response string
    if (bracketCount == 2){
      deviceString += c;
    }else if (bracketCount == 3){
      maxWaterString +=c;
    }
  }
  if (maxWaterString != "" && deviceString != ""){
    //Serial.print("response string: " + responseString);
    //deserialize
    DeserializationError error1 = deserializeJson(jsonDoc1, deviceString);
    DeserializationError error2 = deserializeJson(jsonDoc2, maxWaterString);
    long currentWaterChar = jsonDoc1["current_water_amount"];
    long maxWaterChar = jsonDoc2["value"];
    if (currentWaterChar > 0){
      //set the water variable
      currentWaterAmount = currentWaterChar;
      Serial.print("currrent water char ");
      Serial.println(currentWaterChar);
    }
  
    if(maxWaterChar > 0){
      //set the max water variable
      maxWaterAmount = maxWaterChar;
      Serial.print("max water char ");
      Serial.println(maxWaterChar);
    }
  }
}

void postData(String body){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   if (client.connect(URL, 80)){
      Serial.println("Body");
      Serial.println(body);
      client.print("POST /sema/water-ops/pgwc/");
      client.print(DEVICE_ID);
      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(URL);
      client.println("Content-type:application/json");
      client.println("Connection: close");
      client.println();
      client.println(body);
   }else{
    Serial.println("Error connecting to server");
   }
  }

}
