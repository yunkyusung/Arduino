// switches are pull-down mode.

void SW_led_OnOff()
{
  if(digitalRead(SW1_PIN) == LOW){  //SW1누르면 모두 켜기 
    digitalWrite(LED1_PIN, LOW);    // Common Anode. 즉, Low이면 켜짐
    digitalWrite(LED2_PIN, LOW);    // ON
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(LED4_PIN, LOW);
  }
  if(digitalRead(SW2_PIN) == LOW){  //SW2누르면 모두 끄기
    digitalWrite(LED1_PIN, HIGH);   // OFF
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
    digitalWrite(LED4_PIN, HIGH);
  }
  if(digitalRead(SW3_PIN) == LOW){  //SW3누르면 짝수 켜기
    digitalWrite(LED1_PIN, HIGH);   // OFF
    digitalWrite(LED2_PIN, LOW);    // ON
    digitalWrite(LED3_PIN, HIGH);   // OFF
    digitalWrite(LED4_PIN, LOW);    // ON
  }
}
