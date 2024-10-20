// https://m.blog.naver.com/PostView.nhn?blogId=damtaja&logNo=220448940594&proxyReferer=https%3A%2F%2Fwww.google.com%2F

const uint8_t digitPins[4] = { 5, 6, 7, 8 }; //4 common anode pins of the display
#define clockPin   11  //74HC595 Pin 11(SRCLK)
#define latchPin   12  //74HC595 Pin 12(RCLK)
#define dataPin    13  //74HC595 Pin 14(SER)
#define clockDotPin 9  //4 FND Pin 4 시계 도트(Hign on)
#define delayTime   5  //FND digits display interval

// clock
extern volatile unsigned long timer0_millis; // 시스템의 타이머변수
unsigned long timeVal; //이전시간
unsigned long readTime; //현재타이머시간
uint8_t Hour, Min, Sec;

bool timeDotState = true;

const byte digit[10] = {     //seven segment digits in bits
  B11000000, //0
  B11111001, //1
  B10100100, //2
  B10110000, //3
  B10011001, //4
  B10010010, //5
  B10000010, //6
  B11111000, //7
  B10000000, //8
  B10010000  //9
};

void setup() {
  Serial.begin(115200);
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  pinMode(clockDotPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.println("Input now time to set clock hh:mm:ss");
}

void loop() {
  // 시각 입력 (형식 hh:mm:ss)
  setNowTime();

  // 현재 시각 업데이트
  nowTimeUpdate();

  // 현재 시각을 FND에 표시
  nowTimDisplayFND();
}


// 현재 시간을 FND에 표시
void nowTimDisplayFND() {
  updateDisplayOne(0, Hour/10);
  delay(delayTime);
  updateDisplayOne(1, Hour%10);
  delay(delayTime);
  updateDisplayOne(2, Min/10);
  delay(delayTime);
  updateDisplayOne(3, Min%10);
  delay(delayTime);
  digitalWrite(clockDotPin, timeDotState);

}
// 현재 시각 업데이트
void nowTimeUpdate() {
  if (millis() - timeVal >= 500 & timeDotState) { //0.5초 간격으로 타임도트 점멸
    timeDotState = false;
  }

  if (millis() - timeVal >= 1000) { //1초 단위 출력
    readTime = millis() / 1000;

    timeDotState = true;
    if (millis() >= 86400000) {
      timer0_millis = 0;
    }
    timeVal = millis();

    Sec = readTime % 60;
    Min = (readTime / 60) % 60;
    Hour = (readTime / (60 * 60)) % 24;
  }
}
// 시간 입력
void setNowTime() {
  if (Serial.available()) {
    String inString = Serial.readStringUntil('\n');
    uint8_t index1 = inString.indexOf(':');
    uint8_t index2 = inString.indexOf(':', index1 + 1);
    uint8_t index3 = inString.length();

    Hour = inString.substring(0, index1).toInt();
    Min = inString.substring(index1 + 1, index2).toInt();
    Sec = inString.substring(index2 + 1, index3).toInt();

    // 시스템의 타임을 입력한 시간으로 설정
    timer0_millis = ((long)Hour * 3600 + Min * 60 + Sec) * 1000;
    timeVal = millis();

    Serial.println("Now time is");
    Serial.print(Hour/10);
    Serial.print(Hour%10);
    Serial.print(":");
    Serial.print(Min/10);
    Serial.print(Min%10);
    Serial.print(":");
    Serial.print(Sec/10);
    Serial.println(Sec%10);
  }
}

void updateDisplayOne(uint8_t idx, uint8_t num) {
  // all FNDs disable
  for (uint8_t i = 0; i < 4; i++)  {
    digitalWrite(digitPins[i], LOW);
  }
  // write data to a FND
  digitalWrite(digitPins[idx], HIGH);
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, LOW);
  // clear display
  shiftOut(dataPin, clockPin, MSBFIRST, B00000000);  //shiftOut(dataPin, clockPin, bitOrder, value)
  // write a data
  shiftOut(dataPin, clockPin, MSBFIRST, digit[num]);  //shiftOut(dataPin, clockPin, bitOrder, value)
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(digitPins[idx], HIGH);
}

void updateDisplay() {
  // all FNDs disable
  for (uint8_t i = 0; i < 4; i++)  {
    digitalWrite(digitPins[i], LOW);
  }
  // write data to a FND
  for (uint8_t i = 0; i < 4; i++)  {
    digitalWrite(digitPins[i], HIGH);
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    // clear display
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);  //shiftOut(dataPin, clockPin, bitOrder, value)
    // write a data
    shiftOut(dataPin, clockPin, MSBFIRST, digit[5]);  //shiftOut(dataPin, clockPin, bitOrder, value)
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(digitPins[i], HIGH);
  }
}
