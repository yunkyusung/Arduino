void pot_read(){
  Serial.print("Potentiometer reading: ");
  Serial.println(analogRead(POT_PIN));
}

// pot값에 따라 LED 켜짐
// 0~250:L1, ~500:L1L2, ~750:L1L2L3, ~1023:L1L2L3
void pot_led(){
  int PotValue = analogRead(POT_PIN);
  Serial.println(analogRead(POT_PIN));
  led_level_meter(PotValue);
}
