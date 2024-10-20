
void rgb_blink(int dTime){
  digitalWrite(LED_R_pin, HIGH);
  delay(dTime);
  digitalWrite(LED_R_pin, LOW);
  delay(dTime);
  digitalWrite(LED_G_pin, HIGH);
  delay(dTime);
  digitalWrite(LED_G_pin, LOW);
  delay(dTime);
  digitalWrite(LED_B_pin, HIGH);
  delay(dTime);
  digitalWrite(LED_B_pin, LOW);
  delay(dTime);
}

void rgb_on(){
  digitalWrite(LED_R_pin, HIGH);
  digitalWrite(LED_G_pin, HIGH);
  digitalWrite(LED_B_pin, HIGH);   
}

void rgb_off(){
  digitalWrite(LED_R_pin, LOW);
  digitalWrite(LED_G_pin, LOW);
  digitalWrite(LED_B_pin, LOW);   
}
