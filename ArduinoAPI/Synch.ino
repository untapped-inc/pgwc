void Synch(){
  
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
   HTTPClient http;    //Declare object of class HTTPClient
   http.begin("http://pgw.semawater.org/sema/water-ops/pgwc/");      //Specify request destination
   
   http.addHeader("Content-Type", "application/json");  //Specify content-type header
  // http.addHeader("Authorization", "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyIjp7ImlkIjo4LCJlbWFpbCI6InBnd2NAdW50YXBwZWQtaW5jLmNvbSIsInVzZXJuYW1lIjoicGd3YyIsImZpcnN0TmFtZSI6IlBHVyIsImxhc3ROYW1lIjoiQ29udHJvbGxlciIsImFjdGl2ZSI6dHJ1ZSwicm9sZSI6W3siY29kZSI6ImRldmljZSIsImF1dGhvcml0eSI6IkRldmljZSJ9XX0sImRldmljZSI6eyJpZCI6MSwibmFtZSI6IlBHV0MiLCJzZXJpYWxfbnVtYmVyIjpudWxsLCJpcF9hZGRyZXNzIjpudWxsLCJmaXJtd2FyZSI6bnVsbCwia2lvc2tfaWQiOjEsInVzZXJfaWQiOjgsImNyZWF0ZWRfYXQiOiIyMDE5LTA2LTEzVDE4OjQxOjI5LjAwMFoiLCJ1cGRhdGVkX2F0IjoiMjAxOS0wNy0wNVQxODozMjoxMS4wMDBaIiwiY3VycmVudF93YXRlcl9hbW91bnQiOjc4NDMxLCJhY3RpdmUiOnRydWUsInNlbnNvcnMiOlt7ImlkIjoxLCJuYW1lIjoiRnJlcXVlbmN5IENvdW50ZXIiLCJzYW1wbGluZ19zaXRlX2lkIjozLCJwYXJhbWV0ZXJfaWQiOjEsImRldmljZV9pZCI6MSwiY3JlYXRlZF9hdCI6IjIwMTktMDYtMTNUMTg6NDg6MDMuMDAwWiIsInVwZGF0ZWRfYXQiOiIyMDE5LTA3LTAxVDE0OjU1OjA5LjAwMFoifSx7ImlkIjoyLCJuYW1lIjoiT1JQIE1ldGVyIiwic2FtcGxpbmdfc2l0ZV9pZCI6MSwicGFyYW1ldGVyX2lkIjoxNywiZGV2aWNlX2lkIjoxLCJjcmVhdGVkX2F0IjoiMjAxOS0wNy0wMVQxNTowOTo0NS4wMDBaIiwidXBkYXRlZF9hdCI6IjIwMTktMDctMDFUMTU6MDk6NDUuMDAwWiJ9XSwibWF4X3dhdGVyX2Ftb3VudCI6eyJ2YWx1ZSI6ODAwMDAsImNyZWF0ZWRfYXQiOiIyMD⸮⸮LTEzVDE5OjExOjUzLjAwMFoifX0sImlhdCI6MTU2MjM1MjE2MSwiZXhwIjoxNTYyNDM4NTYxfQ.N7nxvB0ENkEq_J4MnI70BVWPkDaPHJwyq10mbSh7iOA");
   //String Data = "{ \"clientReadings\": [{ \"created_at\": \"2019-06-28T20:25:20.69-04:00\",\"parameter_id\": \"1\",\"sampling_site_id\": \"3\",\"value\": \"1320\",\"user_id\": \"8\",\"kiosk_id\": \"1\"},{\"created_at\": \"2019-06-28T20:25:20.69-04:00\",\"parameter_id\": \"1\",\"sampling_site_id\": \"3\",\"value\": \"289\",\"user_id\": \"8\",\"kiosk_id\": \"1\"}],\"clientDevice\":{\"id\":\""+ID+"\",\"name\":"+NAME+",\"serial_number\": \""+SERIAL_NUMBER+"\",\"ip_address\": \""+IP_ADDRESS+"\",\"firmware\": \""+FIRMWARE+"\",\"kiosk_id\": \""+KIOSK_ID+"\",\"user_id\": \""+USER_ID+"\",\"created_at\": "+CREATED+",\"updated_at\": "+UPDATED+",\"current_water_amount\": \""+CURRENT_WATER_AMOUNT+"\",\"active\": \""+ACTIVE+"\",\"sensors\":[{ \"id\":\""+SENSOR_ID+"\",\"name\":"+SENSOR_NAME+",\"sampling_site_id\":\""+SAMPLING_SITE+"\",\"parameter_id\":\""+PARAMETER_ID+"\",\"device_id\":\""+DEVICE_ID+"\",\"created_at\":"+CREATED_AT+",\"updated_at\":"+UPDATED_AT+"},{\"id\":\""+SENSOR2_ID+"\",\"name\":"+SENSOR2_NAME+",\"sampling_site_id\":\""+SAMPLING_SITE2+"\",\"parameter_id\":\""+PARAMETER_ID2+"\",\"device_id\":\""+DEVICE_ID2+"\",\"created_at\":"+CREATED_AT2+",\"updated_at\":"+UPDATED_AT2+"}],\"max_water_amount\":{\"value\":\""+VALUE+"\",\"created_at\":"+CREATED_AT+"}},\"iat\":\""+IAT+"\",\"exp\":\""+EXP+"\"}" ;
   String Data = "{\"clientReadings\":{\"sensorA\":[{\"created_at\":\"2018-11-21 12:04:50\",\"value\":\"234\"},{\"created_at\":\"2018-11-21 12:6:50\",\"value\":\"289\"}],\"sensorB\":[{\"created_at\":\"2018-11-21 12:04:50\",\"value\":\"234\"},{\"created_at\":\"2018-11-21 12:6:50\",\"value\":\"289\"}]},\"clientDevice\":{\"id\":\""+ID+"\",\"name\":"+NAME+",\"serial_number\": \""+SERIAL_NUMBER+"\",\"ip_address\": \""+IP_ADDRESS+"\",\"firmware\": \""+FIRMWARE+"\",\"kiosk_id\": \""+KIOSK_ID+"\",\"user_id\": \""+USER_ID+"\",\"created_at\": "+CREATED+",\"updated_at\": "+UPDATED+",\"current_water_amount\": \""+CURRENT_WATER_AMOUNT+"\",\"active\": \""+ACTIVE+"\",\"sensors\":[{ \"id\":\""+SENSOR_ID+"\",\"name\":"+SENSOR_NAME+",\"sampling_site_id\":\""+SAMPLING_SITE+"\",\"parameter_id\":\""+PARAMETER_ID+"\",\"device_id\":\""+DEVICE_ID+"\",\"created_at\":"+CREATED_AT+",\"updated_at\":"+UPDATED_AT+"},{\"id\":\""+SENSOR2_ID+"\",\"name\":"+SENSOR2_NAME+",\"sampling_site_id\":\""+SAMPLING_SITE2+"\",\"parameter_id\":\""+PARAMETER_ID2+"\",\"device_id\":\""+DEVICE_ID2+"\",\"created_at\":"+CREATED_AT2+",\"updated_at\":"+UPDATED_AT2+"}],\"max_water_amount\":{\"value\":\""+VALUE+"\",\"created_at\":"+CREATED_AT+"}},\"iat\":\""+IAT+"\",\"exp\":\""+EXP+"\"}" ;

   Serial.print("BODY: ");
   Serial.println(Data);
   int httpCode = http.POST(Data);   //Send the request

   String payload = http.getString();                  //Get the response payload
   int Strarttoken= payload.indexOf("token");
   String Token = payload.substring(Strarttoken+8);
   Serial.println(httpCode);   //Print HTTP return code
   SynchPayload=payload;
   Serial.println(SynchPayload);    //Print request response payload
   http.end();  //Close connection
   CURRENT_WATER_AMOUNT=SynchPayload.substring(SynchPayload.indexOf("current_water_amount")+22,SynchPayload.indexOf(",\"active"));
Serial.print("Current water amount: ");
Serial.println(CURRENT_WATER_AMOUNT);
String pyld = SynchPayload.substring(SynchPayload.indexOf("max_water_amo nt"));
Serial.print("pyld: ");
Serial.println(pyld);
VALUE=pyld.substring(pyld.indexOf("value")+6,pyld.indexOf(",\"created_at"));
 Serial.print("Maximum water amount: ");
Serial.println(VALUE);
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
  
  
  }
