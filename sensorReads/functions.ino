String getFirebaseReads(String topic){
  if(Firebase.getString(fbdo, topic)){             
     return fbdo.to<String>();             
  }
  else   {
    Serial.println(fbdo.errorReason());    
    return fbdo.errorReason();
  }            

}

void setFirebaseReads(String topic, float data){
  Firebase.setFloat(fbdo, topic, data);
}

void LDR(){
  if (analogRead(A0) < threshold)        
    setFirebaseReads("office/LDR", analogRead(A0));
  delay(100);
}

void LED(int pin, String action){
  if(action == "on")
    digitalWrite(pin, HIGH);
  else
    digitalWrite(pin, LOW);

}

void DHT11Senor(){
  delay(2000);  
  setFirebaseReads("DHT/temp", dht.readTemperature());                                     
  setFirebaseReads("DHT/hum", dht.readHumidity());                                     
}