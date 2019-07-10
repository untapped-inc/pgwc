void wifiCommunication(const char *body){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   if (client.connect(URL, 80)){
      Serial.println("connected to server");
      Serial.println(body);
      client.println("GET /todos/1"); ///sema/water-ops/pgwc/");
      client.print("Host: ");
      client.println(URL);
      client.println("Content-type:application/json");
      client.println("Connection: close");
      client.println();
      //client.println(body);      
   }else{
    Serial.println("Error connecting to server");
   }
  }
}