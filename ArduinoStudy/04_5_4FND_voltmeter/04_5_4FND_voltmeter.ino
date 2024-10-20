/* - subj: 4 digits 7 segment voltmeter
   - pin connecting
      pin_no  : 1   2   3   4   5   6   7   8   9   10  11  12
     (segment)  e   d   dp  c   g   D1  b   D2  D3  f   a   D4
      Arduino : 6   5   9   4   8   10  3   11  12  7   2   13  A0
      POT pin :                                                 2(center)
   - KNUE OSlab 2019 study 2019.4.25.
*/

// sements data (Comman Anode)
const byte segmentCA[][8] = {
  //{a, b, c, d, e, f, g, dp }
  {0, 0, 0, 0, 0, 0, 1, 1}, //0
  {1, 0, 0, 1, 1, 1, 1, 1}, //1
  {0, 0, 1, 0, 0, 1, 0, 1}, //2
  {0, 0, 0, 0, 1, 1, 0, 1}, //3
  {1, 0, 0, 1, 1, 0, 0, 1}, //4
  {0, 1, 0, 0, 1, 0, 0, 1}, //5
  {0, 1, 0, 0, 0, 0, 0, 1}, //6
  {0, 0, 0, 1, 1, 1, 1, 1}, //7
  {0, 0, 0, 0, 0, 0, 0, 1}, //8
  {0, 0, 0, 0, 1, 0, 0, 1}, //9
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

bool isCA = true;  //Change value to match you usings (true: Common Anode, false: Common Cathod)

const uint8_t digitPins[4] = { 10, 11, 12, 13 }; //digit pin: 10-D1, 11-D2, 12-D3, 13-D4

const unsigned long delayT = 5;        //delay time for active display

//time interval for reading analog values
unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  //set segment and digit pins to OUTPUT mode
  for (byte i = 2; i < 14 ; i++)  {   //2-a, 3-b, 4-c, 5-d, 6-e, 7-f, 8-g, 9-dp
    pinMode(i, OUTPUT);               //10-D1, 11-D2, 12-D3, 13-D4
  }
}

void loop() {
  /* [test] display 0,1,2,3
    for (byte i = 0; i < 4; i++) {
    displayNUM(i, i);               // USAGE: displayNUM(byte digitPinNo i, byte number)
    delay(delayT);
    }
  */

  unsigned long currentMillis = millis();
  int readVal = 0;                  // read value from analog port
  static float Volt = 0.0;

  //Reading voltage values at intervals
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    readVal = analogRead(A0);
    Volt = (readVal * 5.0) / 1024.0;
  }
  displayValue(Volt);               //display valtage value
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

// display value on FNDs
void displayValue(float value) {
  int val;
  int dpDigitNo = 3;                //position fo decimal point
  int digitNum[4];                  //Numeric storage to display at each digit

  // making float value to 4digits integer number
  while (value < 1000 && dpDigitNo > 0) {
    value = value * 10.0;
    dpDigitNo--;
  }

  val = value;
  digitNum[0] = val / 1000;         //1000's digit
  digitNum[1] = val % 1000 / 100;   //100's digit
  digitNum[2] = val % 100 / 10;     //10's digit
  digitNum[3] = val % 10;           //1's digit

  for (int i = 0; i < 4; i++) {
    //Determine whether a digit contains a decimal point
    if (dpDigitNo == i) {
      displayNUM(i, digitNum[i] + 16);
    } else {
      displayNUM(i, digitNum[i]);
    }
    delay(delayT);                  //for active display
  }
}
