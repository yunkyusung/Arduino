/* HC-06 bluetooth
 serial 모니터에서 "Both NL & CR"로 설정한 후, (\r\n)(\12\15)
 "AT" 명령을 보내고 OK를 확인한다.
 [참고]
 - 버젼 확인: AT+VERSION
 - 이름 확인/바꾸기: AT+NAME?, AT+NAME="HC-06(74D2)"
 - mac addr. 확인/바꾸기: AT+ADDR?, AT+ADDR:12:34:56:ab:cd:ef 
 - BR바꾸기: AT+BAUD4  참고)4:9600bps  5:19200, 6:38400, 7:57600
 - 비번 확인/바꾸기: AT+PSWD?, AT+PSWD=1234
*/

#include <SoftwareSerial.h> // 0,1번핀 제외하고 Serial 통신을 하기 위해 선언

// Serial 통신핀으로 D2번핀을 Rx로, D3번핀을 Tx로 선언
SoftwareSerial BTSerial(2, 3); // BTSerial(Rx, Tx): Adu-Rx(2)<->BT(Tx), Adu-Tx(3)<->BT(Rx) 연결

void setup()
{
  Serial.begin(9600); // 통신 속도 9600bps로 PC와 시리얼 통신 시작
  BTSerial.begin(9600); // 통신 속도 9600bps로 블루투스 시리얼 통신 시작
  Serial.write("SERIAL START!");
  Serial.println("BT Module AT Mode!");
  //Serial.println("select [Both NL & CR]");   // ver3.0
  Serial.println("select [line ending 없음]");  // DX_smartv2.0
  
}

void loop()
{
  // BTSerial 핀에 입력이 들어오면, 바이트단위로 읽어서 PC로 출력
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  // Serial 핀에 입력이 들어오면, 바이트단위로 읽어서 블루투스로 출력
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}
