void Get_Token(){
   if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
   HTTPClient http;    //Declare object of class HTTPClient
   http.begin("http://pgw.semawater.org/sema/login");      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header
   int httpCode = http.POST("{ \"usernameOrEmail\": \"pgwc\",\"password\": \"pgwc\" }");   //Send the request

   String payload = http.getString();                  //Get the response payload
   int Strarttoken= payload.indexOf("token");
   String Token = payload.substring(Strarttoken+8);
   Serial.println(httpCode);   //Print HTTP return code
 //  Serial.println(payload);    //Print request response payload
   TOKEN= Token.substring(0,Token.indexOf("\""));
 // Serial.println("");
 // Serial.print("Token is: ");
 // Serial.println(TOKEN);
   http.end();  //Close connection
 }else{
 
    Serial.println("Error in WiFi connection");   
 }
  
  
  }
