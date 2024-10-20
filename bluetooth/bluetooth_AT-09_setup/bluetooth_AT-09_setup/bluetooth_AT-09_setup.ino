/* AT-09 bluetooth
 serial 모니터에서 "Both NL & CR"로 설정한 후, (\r\n)(\12\15)
 "AT" 명령을 보내고 OK를 확인한다.
 [AT명령어]
- 버젼 확인: AT+VERSION
- ADDR확인: AT+LADDR
- 역할 확인/설정: AT+ROLE   *마스터:1, 슬레이브:0 
- 이름 확인/설정: AT+NAME, AT+NAMEAT09_74D2
- BAUD 확인/설정: AT+BAUD, AT+BAUD4    참고)4:9600bps  5:19200, 6:38400, 7:57600
- 비번 확인/설정: AT+PIN, AT+PIN123456  *기본값: 123456
*/

#include <SoftwareSerial.h> // 0,1번핀 제외하고 Serial 통신을 하기 위해 선언

//#define EN_PIN ?   // 블루투스 en핀, HC05의 경우 AT 모드 진입에 사용됨
#define TX_PIN 3   // [ARDUINO TX:3] ----- [AT-09 RX]
#define RX_PIN 2   // [ARDUINO RX:2] ----- [AT-09 TX]

SoftwareSerial BTSerial(RX_PIN, TX_PIN); // BTSerial(Rx, Tx)

void setup()
{
  Serial.begin(9600);     // 통신 속도 9600bps로 PC와 시리얼 통신 시작
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial Start!");
  BTSerial.begin(9600);   // AT09의 디폴트 속도 9600bps
  Serial.println("BTSerial Start!");
  Serial.println("Select [Both NL & CR]");
}

//PC_USB ←(Serial)→ USB_Arduino_PINS 2, 3 ←(BTSerial)→ 
//       TDX, RXD_AT-09BLE chip (CC254x) ← Characteristic → BLE central
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

void sendCommand(const char * command){
  Serial.print("Command send :");
  Serial.println(command);
  BTSerial.println(command);
  //wait some time
  delay(100);
  
  char reply[100];
  int i = 0;
  while (BTSerial.available()) {
    reply[i] = BTSerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  Serial.print(reply);
  Serial.println("Reply end");
}
