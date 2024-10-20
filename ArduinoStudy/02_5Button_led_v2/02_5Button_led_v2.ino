/* 2019 OS lab study 도전 과제 (2019.4.11.)
 * [수행 조건]
 * 버튼은 한번에 하나만 누른다.
 * 버튼을 누를 때 다음 동작을 수행한다.
 *  1. 버튼(D2)를 누르면(LOW) LED(D13)은 켜진다(ON).
 *  2. 버튼(D3)를 누르면(LOW) LED(D13)은 꺼진다(OFF).
 *  3. 버튼(D4)를 누르면(LOW) LED(D13)은 5회 점멸(1초 간격)한다.
 */
 
#define BtnOffPin     2       // OFF 모드 버튼 연결 핀번호
#define BtnOnPin      3       // ON 모드 버튼 연결 핀번호
#define BtnBlinkPin   4       // Blink 모드 버튼 연결 핀번호
#define LedPin       13       // 표시 LED 연결 핀번호
#define INTERVAL    500       // 점멸 시간 간격(milliseconds)

uint8_t lastMode = 0;                   // 이전 모드
unsigned long previousMillis = 0;       // 이전 시각 

void setup() {
  pinMode(BtnOffPin, INPUT_PULLUP);     // OFF 모드 버튼 입력 모드(Pull-Up) 설정
  pinMode(BtnOnPin, INPUT_PULLUP);      // ON 모드 버튼 입력 모드(Pull-Up)  설정
  pinMode(BtnBlinkPin, INPUT_PULLUP);   // Blink 모드 버튼 입력 모드(Pull-Up) 설정 
  pinMode(LedPin, OUTPUT);              // LED 표시 출력 모드(Pull-Up)  설정
}

void loop() {
  static uint8_t ledState = LOW;                              // LED 상태
  static uint8_t blinkTimes = 10;                             // 점멸 횟수
  static unsigned long currentMillis;                         // 현재 시각
  static uint8_t Mode = 0;                                    // Mode 0:Off, 1:On, 2:Blink
  
  Mode = readBtns(BtnOffPin, BtnOnPin, BtnBlinkPin);          // 버튼 상태 읽기
  currentMillis = millis();                                   // 현재 시각 읽기

  // 이전 모드와 다른 모드 선택 처리 루틴 =====
  if (Mode != lastMode) {   
    switch (Mode) {
      case 0:
        digitalWrite(LedPin, LOW);
        break;
      case 1:
        digitalWrite(LedPin, HIGH);
        break;
      case 2:
        digitalWrite(LedPin, LOW);  // 점멸 준비(LED Off)
        blinkTimes = 10;            // 점멸 준비(점멸 횟수 세팅)
        break;
    }
    lastMode = Mode;                // 바뀐 모드 저장
  }
  // 이전 모드와 다른 모드 선택 처리 루틴 ===== end
  
  // blink 모드 처리 루틴  ====
  if (Mode == 2 ) {                     
    if (currentMillis - previousMillis >= INTERVAL) {     // 점멸 시간이 되면
      previousMillis = currentMillis;   // save the last time you blinked the LED
      ledState = !ledState;             // if the LED is off turn it on and vice-versa:
      digitalWrite(LedPin, ledState);   // set the LED with the ledState of the variable:
      blinkTimes--;
      if (blinkTimes == 0)
        lastMode = 0;                   // 점멸이 끝나면 OFF모드로 전환, 다시 점멸 모드 기동 가능토록함
    }
  }
  // blink 모드 처리 루틴  ==== end
}

// 버튼 값 읽기
int readBtns(uint8_t BtnOFF, uint8_t BtnON, uint8_t BtnBlink) {
  if (digitalRead(BtnOFF) == LOW)
    return 0;
  else if (digitalRead(BtnON) == LOW)
    return 1;
  else if (digitalRead(BtnBlink) == LOW)
    return 2;
  else
    return lastMode;    // 아무 버튼도 누르지 않았으면 이전 모드 반환 
}
