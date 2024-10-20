// 스위치로 led 제어

// led
void led_blink(int dTime) {
  digitalWrite(LED1_pin, HIGH);
  delay(dTime);
  digitalWrite(LED1_pin, LOW);
  delay(dTime);
  digitalWrite(LED2_pin, HIGH);
  delay(dTime);
  digitalWrite(LED2_pin, LOW);
  delay(dTime);
}

void led_on() {
  digitalWrite(LED1_pin, HIGH);
  digitalWrite(LED2_pin, HIGH);
}

void led_off() {
  digitalWrite(LED1_pin, LOW);
  digitalWrite(LED2_pin, LOW);
}

/* 디지털 pin의 값을 반전함
  DDRx : 입출력 방향 설정(R/W), PORTx : 출력 및 상태 설정(R/W), PINx : 핀 상태 읽기(R)
  x : B (crystal 2~1, digital pin 13~8), C (analog pins 5~0), D (digital pin 7~0)
  *레지스터 구조
         7   6   5   4   3   2   1   0           7   6   5   4   3   2   1   0
  DDRB: cr2 cr1 D13 D12 D11 D10 D9  D8    DDRD: D7  D6  D5  D4  D3  D2  D1  D0
  *레지스터 입출력 설정
  DDRD = DDRD | B00100000;    // set PORTD (digital 5) to output
  DDRD = DDRD & B10100011;    // set PORTD (digital 6,4,3,2) to input
  DDRB = DDRD | B00111110;    // set PORTD (digital 13~9) to output

*/
void led_toggle(int pin) {
  switch(pin){
    case 9:
      PORTB ^= B00000010;  // D9만 토글
      break;
    case 0:
      PORTB ^= B00111111;  // D13~D8 모두 토글
      break;
    case 10:
      PORTB ^= B00000100;  // D10만 토글
      break;
    case 11:
      PORTB ^= B00001000;  // D11만 토글
      break;
    case 12:
      PORTB ^= B00010000;  // D12만 토글
      break;
    case 13:
      PORTB ^= B00100000;  // D13만 토글
      break;
  }
  
}
