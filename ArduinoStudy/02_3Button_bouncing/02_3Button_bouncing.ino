static uint8_t pushButtonPin = 2;
static uint8_t LedPin = 13;
int cnt = 0;
int BtnReading = HIGH;
int lastBtnState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(pushButtonPin,INPUT_PULLUP);
  pinMode(LedPin,OUTPUT);
}

void loop() {
  BtnReading = digitalRead(pushButton);
  if(BtnReading != lastBtnState){
    if(BtnReading == HIGH){
      cnt++;
      Serial.println(String(cnt) + "회 눌렀습니다.");
    }
  }
  lastBtnState = BtnReading;
  //delay(1);
}
