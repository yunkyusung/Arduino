// 적외선 리모컨 신호 수신
// 라이브러리 https://github.com/z3t0/Arduino-IRremote
// 참고 http://www.geeetech.com/wiki/index.php/Arduino_IR_Remote_Control
/* 리모컨 모델에 따라 코드 수정하여 사용
   ------------------
 /                    \
|  CH-    CH     CH+   |
| FFA25D FF629D FFE21D |
|                      |
|  |<<     >>|   |>||  |
| FF22DD FF02FD FFC23D |
|                      |
|   -       +     EQ   |
| FFE01F FFA857 FF906F |
|                      |
|   0      100+  200+  |
| FF6897 FF9867 FFB04F |
|                      |
|   1       2     3    |
| FF30CF FF18E7 FF7A85 |
|                      |
|   4       5     6    |
| FF10EF FF38C7 FF5AA5 |
|                      |
|   7       8     9    |
| FF42BD FF4AB5 FF52AD |
|                      |
|       Car mp3        |
 \                    /
   ------------------
(FFFFFFFF 버튼을 계속 누르고 있을 때)
버튼:     0      1      2      3      4      5      6      7      8      9  
  값:  FF6897 FF30CF FF18E7 FF7A85 FF10EF FF38C7 FF5AA5 FF42BD FF4AB5 FF52AD
*/
// ir수신 키값 출력
void ir_recv(){
  if (irrecv.decode(&results)) {
    Serial.print("decode_type : "); Serial.print(results.decode_type);
    Serial.print("\tvalue : ");     Serial.print(results.value, HEX);
    Serial.print("\tbits : ");      Serial.println(results.bits);

    irrecv.resume(); // 다음값 수신
  }
  //delay(100);
}

// 수신 키값 출력 및 LED 제어
// ir 1,2,3,4,5,6,7,8,9,0으로
void ir_recv_and_ctrl(){
  if (irrecv.decode(&results)) {
    // 수신 키값 출력
    Serial.print("decode_type : "); Serial.print(results.decode_type);
    Serial.print("\tvalue : ");     Serial.print(results.value, HEX);
    Serial.print("\tbits : ");      Serial.println(results.bits);

    // LED 제어
// 버튼:     0      1      2      3      4      5      6      7      8      9    계속누름
//   값:  FF6897 FF30CF FF18E7 FF7A85 FF10EF FF38C7 FF5AA5 FF42BD FF4AB5 FF52AD FFFFFFFF
    switch(results.value){
      case 0xFFFFFFFF:
        break;  //아무것도 하지 않음

      case 0x00FF6897: //'0'
        led_toggle(0);
        break;

      case 0x00FF30CF: //'1'
        led_toggle(9);
        break;
        
      case 0x00FF18E7: //'2'
        led_toggle(10);
        break;
        
      case 0x00FF7A85: //'3'
        led_toggle(11);
        break;
        
      case 0x00FF10EF: //'4'
        led_toggle(12);
        break;
        
      case 0x00FF38C7: //'5'
        led_toggle(13);
        break;
    }
    
    irrecv.resume(); // 다음값 수신
  }
  //delay(100);
}
