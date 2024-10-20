/* - subj: 4 digits 7 segment voltmeter
   - pin connecting
      pin_no  : 1   2   3   4   5   6   7   8   9   10  11  12
     (segment)  e   d   dp  c   g   D1  b   D2  D3  f   a   D4
      Arduino : 6   5   9   4   8   10  3   11  12  7   2   13  A0
      POT pin :                                                 2(center)
   - KNUE OSlab 2019 study 2019.4.25.
*/

#include "SevSeg.h"

SevSeg sevseg; //Instantiate a seven segment controller object

unsigned long previousMillis = 0;
const long interval = 500;    //전압 측정 시간 간격

void setup() {
  //Serial.begin(115200);
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
  bool resistorsOnSegments = true;   // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options  cf) COMMON_CATHODE
  bool updateWithDelays = false;      // Default 'false' is Recommended
  bool leadingZeros = true;           // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false;       // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}


void loop() {
  unsigned long currentMillis = millis();
  int readVal = 0;                  // read value from analog port
  static float Volt = 0.0;
  static int dotPos = 0;

  //interval 시간 간격으로 전압 읽기
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    readVal = analogRead(A0);
    Volt = (readVal * 5.0) / 1024.0;
    
    // 4자리 유효숫자로 취하고 소수점 넣기
    dotPos = 0;
    while (Volt < 1000 && dotPos < 3) {
      Volt = Volt * 10.0;
      dotPos++;
    }
    //Serial.println("volt:"+String(Volt)+" , dotpos: "+String(dotPos));
  }

  //전압 표시
  sevseg.setNumber((int)Volt, dotPos);
  sevseg.refreshDisplay(); // Must run repeatedly
}
