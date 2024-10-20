/*   - 주제: 4자리 7세그먼트 시계(SevSeg 라이브러리 이용)
     - 기능: 라이브러리 이용, 초 도트 점멸, 시간 입력(hh:mm:ss), hh:mm 혹은 mm:ss 표시 가능
     - 참고: https://playground.arduino.cc/Main/SevenSegmentLibrary/
     - 회로 연결
         핀번호   : 1   2   3   4   5   6   7   8   9   10  11  12
        (세그먼트)  e   d   dp  c   g   D1  b   D2  D3  f   a   D4
         아두이노 : 6   5   9   4   8   10  3   11  12  7   2   13
     - KNUE OSlab 2019 study 2019.4.25.
*/

#include "SevSeg.h"
SevSeg sevseg;          //7세그먼트 제어 오브젝트의 인스턴스 생성

extern volatile unsigned long timer0_millis;       //외부 시스템 타이머변수(아두이노 system 변수)
byte hh, mm, ss;                                   //시각 저장 변수

//초 도트 점멸과 1초를 세기 위하여 
unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  Serial.begin(115200);

  byte numDigits = 4;                   //자리(FND) 갯수
                    //D1, D2, D3, D4
  byte digitPins[] = {10, 11, 12, 13};  //자리수(digit) 선택 핀
                      //A, B, C, D, E, F, G, DP
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};    //세그먼트 출력 핀
  bool resistorsOnSegments = false;     // 'false'는 자리수 핀(공통 극)에 저항이 연결됨을 의미
  byte hardwareConfig = COMMON_ANODE;   // 공통 음극은 'COMMON_CATHODE'
  bool updateWithDelays = false;        // 'false' 를 권장함(active delay값)
  bool leadingZeros = true;             // 'true'는 숫자 앞의 빈자리를 0으로 채운다는 의미 ex) 0001
  bool disableDecPoint = false;         // 'true'는 소수점이 없는 숫자이거나, 회로에서 연결하지 않았음을 의미

  //7세그먼트 초기화
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  Serial.println("set time(hh:mm:ss)? ");   //현재시각 입력 방법 안내
}

void loop() {
  unsigned long currentMillis = millis();
  static int nowTime = 0;     //현재 시각
  static int dotPos = 2;      //초 도트 위치

  //현재시각 설정을 기다림
  if (Serial.available()) {
    //입력된 현재시각 문자열을 의미 단위로 분해(파싱)
    String inString = Serial.readStringUntil('\n');
    int index1 = inString.indexOf(':');
    int index2 = inString.indexOf(':', index1 + 1);
    int index3 = inString.length();
    
    //입력한 시:분:초 저장
    hh = inString.substring(0, index1).toInt();
    mm = inString.substring(index1 + 1, index2).toInt();
    ss = inString.substring(index2 + 1, index3).toInt();
    
    //시스템의 시간을 입력한 시간으로 변경
    timer0_millis = ((long)hh * 3600 + mm * 60 + ss) * 1000;
    
    //입력한 시간 확인 및 시간세팅 입력 안내
    Serial.println("updated time is : " + String(hh) + ":" + String(mm) + ":" + String(ss));
    Serial.println("set time(hh:mm:ss)? ");

    previousMillis = millis();
  }

  // 1초 마다 시간 업데이트
  if (currentMillis - previousMillis >= interval) {
    dotPos *= -1;
    previousMillis = currentMillis;
    currentMillis = millis() / 1000;
    if (millis() >= 86400000) {     //시스템 시계 오버플로 리셋
      timer0_millis = 0;
    }
    ss = currentMillis % 60;
    mm = (currentMillis / 60) % 60;
    hh = (currentMillis / (60 * 60)) % 24;
    nowTime = ss + mm * 100;    //분:초 표시
    //nowTime = mm + hh * 100;  //시:분 표시
  }

  //시간 표시
  sevseg.setNumber(nowTime, dotPos);
  sevseg.refreshDisplay();          //계속 반복 실행되어야 함
}
