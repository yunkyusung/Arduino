/*   - 주제: 4자리 7세그먼트 시계
     - 참고: https://steemit.com/kr-arduino/@codingman/6vertu-millis
     - 회로 연결
        핀번호   : 1   2   3   4   5   6   7   8   9   10  11  12
       (세그먼트)  e   d   dp  c   g   D1  b   D2  D3  f   a   D4
        아두이노 : 6   5   9   4   8   10  3   11  12  7   2   13
     - KNUE OSlab 2019 study 2019.4.25.
*/

// 세그먼트 숫자 비트 패턴 (공통 양극 기준)
byte segmentCA[][8] = {
  //{a, b, c, d, e, f, g, dp }
  {0, 0, 0, 0, 0, 0, 1, 1}, //0   0
  {1, 0, 0, 1, 1, 1, 1, 1}, //1   1
  {0, 0, 1, 0, 0, 1, 0, 1}, //2   2
  {0, 0, 0, 0, 1, 1, 0, 1}, //3   3
  {1, 0, 0, 1, 1, 0, 0, 1}, //4   4
  {0, 1, 0, 0, 1, 0, 0, 1}, //5   5
  {0, 1, 0, 0, 0, 0, 0, 1}, //6   6
  {0, 0, 0, 1, 1, 1, 1, 1}, //7   7
  {0, 0, 0, 0, 0, 0, 0, 1}, //8   8
  {0, 0, 0, 0, 1, 0, 0, 1}, //9   9
  {0, 0, 0, 1, 0, 0, 0, 1}, //a  10
  {1, 1, 0, 0, 0, 0, 0, 1}, //b  11
  {0, 1, 1, 0, 0, 0, 1, 1}, //c  12
  {1, 0, 0, 0, 0, 1, 0, 1}, //d  13
  {0, 1, 1, 0, 0, 0, 0, 1}, //e  14
  {0, 1, 1, 1, 0, 0, 0, 1}, //f  15
  {0, 0, 0, 0, 0, 0, 1, 0}, //0. 16
  {1, 0, 0, 1, 1, 1, 1, 0}, //1. 17
  {0, 0, 1, 0, 0, 1, 0, 0}, //2. 18
  {0, 0, 0, 0, 1, 1, 0, 0}, //3. 19
  {1, 0, 0, 1, 1, 0, 0, 0}, //4. 20
  {0, 1, 0, 0, 1, 0, 0, 0}, //5. 21
  {0, 1, 0, 0, 0, 0, 0, 0}, //6. 22
  {0, 0, 0, 1, 1, 1, 1, 0}, //7. 23
  {0, 0, 0, 0, 0, 0, 0, 0}, //8. 24
  {0, 0, 0, 0, 1, 0, 0, 0}  //9. 25
};

bool isCA = true;  //사용하는 부품에 따라 설정 변경(true: 공통양극, false: 공통음극)

const uint8_t digitPins[4] = { 10, 11, 12, 13 }; //digit 선택 핀 10-D1, 11-D2, 12-D3, 13-D4
const unsigned long delayT = 5;   //active display 지연 시간

extern volatile unsigned long timer0_millis;       //외부 시스템 타이머변수
int hh, mm, ss;         //시각 저장 변수

//시간 측정용
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(115200);

  //포트 설정(세그먼트 8개, 자리수 4개, )
  for (byte i = 2; i < 14 ; i++)  {   //세그먼트: 2-a, 3-b, 4-c, 5-d, 6-e, 7-f, 8-g, 9-dp
    pinMode(i, OUTPUT);               //자리수:  10-D1, 11-D2, 12-D3, 13-D4
  }

  Serial.println("set time(hh:mm:ss) : ");
}

void loop() {
  unsigned long currentMillis = millis();

  if (Serial.available()) {
    String inString = Serial.readStringUntil('\n');
    int index1 = inString.indexOf(':');
    int index2 = inString.indexOf(':', index1 + 1);
    int index3 = inString.length();

    hh = inString.substring(0, index1).toInt();
    mm = inString.substring(index1 + 1, index2).toInt();
    ss = inString.substring(index2 + 1, index3).toInt();

    timer0_millis = ((long)hh * 3600 + mm * 60 + ss) * 1000;
    previousMillis = millis();
    Serial.println("updated time is : " + String(hh) + ":" + String(mm) + ":" + String(ss));
    Serial.println("reset time(hh:mm:ss)? ");
  }

  // 1초 마다 시간 업데이트
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    currentMillis = millis() / 1000;

    if (millis() >= 86400000) {
      timer0_millis = 0;
    }
    ss = currentMillis % 60;
    mm = (currentMillis / 60) % 60;
    hh = (currentMillis / (60 * 60)) % 24;
  }

  //현재 시각 표시
  displayNUM(0, mm/10);
  delay(delayT);
  displayNUM(1, mm%10+16);
  delay(delayT);
  displayNUM(2, ss/10);
  delay(delayT);
  displayNUM(3, ss%10);
  delay(delayT);
}

// display the number on each digit
void displayNUM(byte dgtNo, byte num) {
  // all digits OFF
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], !isCA);
  }
  // dgtNo digit ON
  digitalWrite(digitPins[dgtNo], isCA);

  // display segments
  for (byte i = 2; i < 10; i++) {   //2-a, 3-b, 4-c, 5-d, 6-e, 7-f, 8-g, 9-dp
    if (isCA) {
      digitalWrite(i, segmentCA[num][i - 2]);
    } else {
      digitalWrite(i, !segmentCA[num][i - 2]);
    }
  }
}
