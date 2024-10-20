
#define BtnOffPin     2
#define BtnOnPin      3
#define BtnBlinkPin   4
#define LedPin       13
#define INTERVAL    500       // interval at which to blink (milliseconds)

uint8_t lastMode = 0;
uint8_t ledState;

unsigned long previousMillis = 0;       // will store last time LED was updated

uint8_t cnt = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BtnOffPin, INPUT_PULLUP);
  pinMode(BtnOnPin, INPUT_PULLUP);
  pinMode(BtnBlinkPin, INPUT_PULLUP);
  pinMode(LedPin, OUTPUT);
}

void loop() {
  uint8_t Mode = readBtns(BtnOffPin, BtnOnPin, BtnBlinkPin);  //mode 0:Off, 1:On, 2:Blink
  static uint8_t blinkTimes = 10;
  unsigned long currentMillis = millis();

  if (Mode != lastMode) {
    switch (Mode) {
      case 0:
        digitalWrite(LedPin, LOW);
        break;
      case 1:
        digitalWrite(LedPin, HIGH);
        break;
      case 2:
        digitalWrite(LedPin, LOW);
        blinkTimes = 10;
        break;
    }
    lastMode = Mode;
  }
  
  if (Mode == 2 ) {
    if (currentMillis - previousMillis >= INTERVAL) {
      previousMillis = currentMillis;   // save the last time you blinked the LED
      ledState = !ledState;             // if the LED is off turn it on and vice-versa:
      digitalWrite(LedPin, ledState);   // set the LED with the ledState of the variable:
      blinkTimes--;
      if (blinkTimes == 0)
        lastMode = 0;
    }
  }

}

int readBtns(uint8_t BtnOFF, uint8_t BtnON, uint8_t BtnBlink) {
  if (digitalRead(BtnOFF) == LOW)
    return 0;
  else if (digitalRead(BtnON) == LOW)
    return 1;
  else if (digitalRead(BtnBlink) == LOW)
    return 2;
  else
    return lastMode;
}
