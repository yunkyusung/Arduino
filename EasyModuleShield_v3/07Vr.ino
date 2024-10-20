// A0(VR_pin)에 연결된 가변저항(포텐쇼미터, VR)의 전압을 읽음
// 10bit ADC이므로 아날로그 0~5V입력을 디지털 0~1023의 값으로 읽음

void vr_read(){
  float VRvalue = analogRead(VR_pin);           // VR값 읽기
  float VRvoltage = VRvalue * (5.0 / 1023.0);   // VR값을 변환 5[V]:1023 = VR전압[V]:ADC값 
 
  // print out the Variable resistor value you read:
  Serial.print("[A0]VR : ");
  Serial.println(VRvoltage);
  //delay(500);
}
