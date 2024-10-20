/*
  HC-05 bluetooth
  https://m.blog.naver.com/PostView.nhn?blogId=nkkh159&logNo=220872249304&proxyReferer=https:%2F%2Fwww.google.com%2F
*/

// serial 모니터에서 "Both NL & CR"로 설정한 후,
// "AT" 명령을 보내고 OK를 확인한다.
// 그 외, AT+VERSION, AT+NAME?, AT+NAME="HC-05(74D2)"
// AT+BAUD4     4:9600bsp  5:19200, 6:38400, 7:57600

#include <SoftwareSerial.h> 

// Serial 통신핀으로 D2번핀을 Rx로, D3번핀을 Tx로 선언
SoftwareSerial BTSerial(2, 3); // HC-05 TX <-> arduino 2번핀 , HC-05 RX <-> arduino 3번핀 연결
// D4번 핀은 EN에 연결

void setup()
{
  pinMode(4, OUTPUT);       // en- HIGH(AT모드), LOW(일반모드)
  digitalWrite(4, HIGH);    // AT모드 진입
  Serial.begin(9600);       // 통신 속도 9600bps로 PC와 시리얼 통신 시작
  BTSerial.begin(38400);    // HC-05는 디폴트 38400bps으로 통신
  Serial.println("Serial Start!");
  Serial.println("BT Module AT Mode!");
  Serial.println("select [Both NL & CR]");
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
