void cds_read(){
  float cdsValue = analogRead(CDS_pin);             // cds값 읽기
  float cdsVoltage = cdsValue * (5.0 / 1023.0);     // cds값을 변환
 
  // print out the Variable resistor value you read:
  Serial.print("[A1]cds value : "); Serial.print(cdsValue);
  Serial.print("\tcds Voltage : "); Serial.println(cdsVoltage);
  //delay(500);
  
}
