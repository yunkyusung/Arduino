static uint8_t pushButtonPin = 2;
static uint8_t LedPin = 13;
int cnt = 0;
int BtnState = HIGH;
int lastBtnState = HIGH;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(115200);
  pinMode(pushButtonPin,INPUT_PULLUP);
  pinMode(LedPin,OUTPUT);
}

void loop() {
  int BtnReading = digitalRead(pushButtonPin);

  // 버튼 상태가 바뀌면 타이머 새로 시작
  if (BtnReading != lastBtnState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  // 디바운스 타임이 지났으면(스위치가 안정화 되었으면)
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (BtnReading != BtnState) {
      if (BtnState == LOW) {
        cnt++;
        Serial.println(String(cnt) + "회 눌렀습니다.");
        //BtnState != BtnState;
      }
      BtnState = BtnReading;
    }
  }
  lastBtnState = BtnReading;
  //delay(1);
}
