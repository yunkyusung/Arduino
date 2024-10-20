// 스위치로 LED 제어
// sw1 --> led1 제어
// sw2 --> led2 제어

void sw_led(){
  if(digitalRead(SW1_pin) == LOW){    // pull-up, 스위치 누르면 LOW
    digitalWrite(LED1_pin, HIGH);
  }else{
    digitalWrite(LED1_pin, LOW);
  }
  if(digitalRead(SW2_pin) == LOW){
    digitalWrite(LED2_pin, HIGH);
  }else{
    digitalWrite(LED2_pin, LOW);
  }
}

void sw_test(){
  while(1){
    // 스위치를 둘 다 누르면 종료
    if(digitalRead(SW1_pin) == LOW && digitalRead(SW2_pin) == LOW)
      return;
      
    // SW1 누름
    if(digitalRead(SW1_pin) == LOW){    // pull-up, 스위치 누르면 LOW
      digitalWrite(LED1_pin, HIGH);
      rgb_blink(50);
    }else{
      digitalWrite(LED1_pin, LOW);
    }
    // SW2 누름
    if(digitalRead(SW2_pin) == LOW){
      digitalWrite(LED2_pin, HIGH);
      rgb_blink(50);
    }else{
      digitalWrite(LED2_pin, LOW);
    }
  }
}
