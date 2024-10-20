void led_blink(){
  digitalWrite(LED1_PIN, LOW);  // ON [Common Anode. 즉, Low이면 켜짐]
  delay(1000);
  digitalWrite(LED1_PIN, HIGH); // OFF
  delay(1000);
}

void all_led_blink(){
  all_led_off();
  delay(1000);
  all_led_on();
  delay(1000);
}

void led_level_meter(int value){
  all_led_on();
  if(value<750){
    digitalWrite(LED4_PIN, HIGH);
  }
  if(value<500){
    digitalWrite(LED3_PIN, HIGH);
  }
  if(value<250){
    digitalWrite(LED2_PIN, HIGH);
  }
}

void all_led_off(){
  digitalWrite(LED1_PIN, HIGH); // OFF
  digitalWrite(LED2_PIN, HIGH);
  digitalWrite(LED3_PIN, HIGH);
  digitalWrite(LED4_PIN, HIGH);  
}

void all_led_on(){
  digitalWrite(LED1_PIN, LOW);  // ON
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(LED4_PIN, LOW);  
}
