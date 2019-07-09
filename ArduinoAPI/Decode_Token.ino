void Decode_Token(){
  encodedJWT=TOKEN;
  String testDecoded = "x";
  for(int i=0 ; i<100 ; i++) testDecoded[i] += 'x';
  boolean decodedToken = jwt.decodeJWT(encodedJWT, testDecoded);
  Serial.println();
    
  //jwt.decodeJWT(encodedJWT, decodedPayload);
 // Serial.println("5) testDecoded: ");
 // Serial.println(testDecoded);
  LoginPayload=testDecoded;

//Getting Login Payload.Device

  LoginPayload_Device= LoginPayload.substring(LoginPayload.indexOf("device\":{")+8);
   Serial.print("LoginPayload.Device: ");
   Serial.println(LoginPayload_Device);

  ID=LoginPayload_Device.substring(LoginPayload_Device.indexOf("id")+4,LoginPayload_Device.indexOf(",\"name\""));
  NAME= LoginPayload_Device.substring(LoginPayload_Device.indexOf("name")+6,LoginPayload_Device.indexOf(",\"serial"));
  SERIAL_NUMBER= LoginPayload_Device.substring(LoginPayload_Device.indexOf("serial_number")+15,LoginPayload_Device.indexOf(",\"ip_address"));
  IP_ADDRESS=LoginPayload_Device.substring(LoginPayload_Device.indexOf("ip_address")+12,LoginPayload_Device.indexOf(",\"firmware"));
  FIRMWARE= LoginPayload_Device.substring(LoginPayload_Device.indexOf("firmware")+10,LoginPayload_Device.indexOf(",\"kiosk_id"));
  KIOSK_ID=LoginPayload_Device.substring(LoginPayload_Device.indexOf("kiosk_id")+10,LoginPayload_Device.indexOf(",\"user_id"));
  USER_ID=LoginPayload_Device.substring(LoginPayload_Device.indexOf("user_id")+9,LoginPayload_Device.indexOf(",\"created_at"));
  CREATED=LoginPayload_Device.substring(LoginPayload_Device.indexOf("created_at")+12,LoginPayload_Device.indexOf(",\"updated_at"));
  UPDATED=LoginPayload_Device.substring(LoginPayload_Device.indexOf("updated_at")+12,LoginPayload_Device.indexOf(",\"current_water_amount"));
  CURRENT_WATER_AMOUNT=LoginPayload_Device.substring(LoginPayload_Device.indexOf("current_water_amount")+22,LoginPayload_Device.indexOf(",\"active"));
  ACTIVE=LoginPayload_Device.substring(LoginPayload_Device.indexOf("active")+8,LoginPayload_Device.indexOf(",\"sensors"));

String PayLoad= LoginPayload_Device.substring(LoginPayload_Device.indexOf("sensors"));
SENSOR_ID=PayLoad.substring(PayLoad.indexOf("id")+4,PayLoad.indexOf(",\"name"));
SENSOR_NAME=PayLoad.substring(PayLoad.indexOf("name")+6,PayLoad.indexOf(",\"sampling_site_id"));
SAMPLING_SITE=PayLoad.substring(PayLoad.indexOf("sampling_site_id")+18,PayLoad.indexOf(",\"parameter_id"));
PARAMETER_ID=PayLoad.substring(PayLoad.indexOf("parameter_id")+14,PayLoad.indexOf(",\"device_id"));
DEVICE_ID=PayLoad.substring(PayLoad.indexOf("device_id")+11,PayLoad.indexOf(",\"created_at"));
CREATED_AT=PayLoad.substring(PayLoad.indexOf("created_at")+12,PayLoad.indexOf(",\"updated_at"));
UPDATED_AT=PayLoad.substring(PayLoad.indexOf("updated_at")+12,PayLoad.indexOf("},{\"id\""));

String PyLoad=PayLoad.substring(PayLoad.indexOf("},{\"id"));
SENSOR2_ID=PyLoad.substring(PyLoad.indexOf("id")+4,PyLoad.indexOf(",\"name"));
SENSOR2_NAME=PyLoad.substring(PyLoad.indexOf("name")+6,PyLoad.indexOf(",\"sampling_site_id"));
SAMPLING_SITE2=PyLoad.substring(PyLoad.indexOf("sampling_site_id")+18,PyLoad.indexOf(",\"parameter_id"));
PARAMETER_ID2=PyLoad.substring(PyLoad.indexOf("parameter_id")+14,PyLoad.indexOf(",\"device_id"));
DEVICE_ID2=PyLoad.substring(PyLoad.indexOf("device_id")+11,PyLoad.indexOf(",\"created_at"));
CREATED_AT2=PyLoad.substring(PyLoad.indexOf("created_at")+12,PyLoad.indexOf(",\"updated_at"));
UPDATED_AT2=PyLoad.substring(PyLoad.indexOf("updated_at")+12,PyLoad.indexOf("}],\"max_water_amount"));


String PyLd=PayLoad.substring(PayLoad.indexOf("max_water_amount"));
VALUE=PyLd.substring(PyLd.indexOf("value")+6,PyLd.indexOf(",\"created_at"));
CREATED_AT3=PyLd.substring(PyLd.indexOf("created_at")+6,PyLd.indexOf("\"}},"));


IAT=PyLd.substring(PyLd.indexOf("iat")+5,PyLd.indexOf(",\"exp"));
String EXp=PyLd.substring(PyLd.indexOf("exp")+5,-2);
EXP=EXp.substring(0,EXp.indexOf("}"));
//Serial.print("firmware: ");
//Serial.println(CREATED);

}
