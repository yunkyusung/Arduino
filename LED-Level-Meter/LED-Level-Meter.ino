// LED level meter : 가변저항에 따라 led 켜지는 개수 제어

int L[12] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13}; // D7은 공통GND용
int readValue;

void setup() {
  for (int i = 1; i < 14; i++) {  // 핀모드 셋업
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  readValue = analogRead(A0);
  LevelMeter(readValue);
}

// 입력값에 따라 LED 켜지는 개수 제어
void LevelMeter(int val) {
  int Level = int(val / 79);  // 1023/13 = 78.7(약79)
  
  allClear(); // LED 모두 끄기
  
  for (int i = 0; i < Level; i++) // 레벨만큼 켜기
    digitalWrite(L[i], HIGH);
}

// LED 모두 끄기
void allClear(){
   for (int i = 0; i < 12; i++)
    digitalWrite(L[i], LOW);
}
