// 제어,반복문 학습 예제
// 회로 구성 : D1~D13까지 LED bar module 연결 D7은 GND
// 2020.9.15. yunkyusng@KNUE.  GNU.

int L[12] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13}; // D7은 공통GND용
int dTime = 50;

void setup() {
  for (int i = 1; i < 14; i++) {  // 핀모드 셋업
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {

#if 1
  //[과제1] 위/아래로 쌓기
  upStack();      // 1 -> 13 위로 쌓기(up stack)
  allClear();
  downStack();    // 1 <- 13 아래로 쌓기(down stack)
  allClear();

  //[과제2]위/아래로 하나씩 점멸(2회 반복)
  for (int k = 0; k < 2; k++) {
    upBlink();    // 1 -> 13 위로 하나씩 점멸(up blink)
    downBlink();  // 1 <- 13 아래로 하나식 점멸(down blink)
  }

  //[과제3] 안으로/밖으로 하나씩 점멸(2회 반복)
  for (int k = 0; k < 2; k++) {
    innerBlink();   // 1 -> 6  8 <- 13 밖에서 안으로 하나씩 점멸(to center blink)
    outerBlink();   // 1 <- 6  8 -> 13 안에서 밖으로 하나씩 점멸(to outer blink)
  }

  ////[과제4] 아래로/위로 날아가서 쌓기
  flyDownStack(12);  // 아래로 날아가서 12개 쌓기(fly down stack)
  delay(500);  allClear();
  flyUpStack();     // 위로 날아가서 쌓기(fly up stack)
  delay(500);  allClear();

  //[과제5] 홀/짝 번갈아 점멸(10회)
  alterBlink(10);   // 홀,짝 번갈아 10회 점멸(odd even alternating blink)
  allClear();

#endif

#if 1
  //[추가1] 6개 쌓고 하나씩 위로 데려가기
  flyDownStack(6);  // 아래로 날아가서 12개 쌓기(fly down stack)
  delay(500); 
  takeOutUp();      // 하나씩 위로 데려가기(take out upward)
#endif

  delay(1000);

}//loop

// 1 -> 13 위로 쌓기(up stack)
void upStack() {
  for (int i = 0; i < 12; i++) {
    digitalWrite(L[i], HIGH);
    delay(dTime);
  }
}

// 1 <- 13 아래로 쌓기(down stack)
void downStack() {
  for (int i = 11; i >= 0; i--) {
    digitalWrite(L[i], HIGH);
    delay(dTime);
  }
}

// 1 -> 13 위로 하나씩 점멸(up blink)
void upBlink() {
  for (int i = 0; i < 12; i++) {
    digitalWrite(L[i], HIGH);
    delay(dTime);
    digitalWrite(L[i], LOW);
  }
}

// 1 <- 13 아래로 하나씩 점멸(down blink)
void downBlink() {
  for (int i = 11; i >= 0; i--) {
    digitalWrite(L[i], HIGH);
    delay(dTime);
    digitalWrite(L[i], LOW);
  }
}

// 1 -> 6  8 <- 13 밖에서 안으로 하나씩 점멸(to center blink)
void innerBlink() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(L[i], HIGH);
    digitalWrite(L[11 - i], HIGH);
    delay(dTime);
    digitalWrite(L[i], LOW);
    digitalWrite(L[11 - i], LOW);
  }
}

// 1 <- 6  8 -> 13 안에서 밖으로 하나씩 점멸(to outer blink)
void outerBlink() {
  for (int i = 5; i >= 0; i--) {
    digitalWrite(L[i], HIGH);
    digitalWrite(L[11 - i], HIGH);
    delay(dTime);
    digitalWrite(L[i], LOW);
    digitalWrite(L[11 - i], LOW);
  }
}

// 아래로 날아가서 쌓기(fly down stack)
void flyDownStack(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 11; j > i; j--) {
      digitalWrite(L[j], HIGH);
      delay(10 * i);
      digitalWrite(L[j], LOW);
    }
    digitalWrite(L[i], HIGH);
    delay(dTime);
  }
}

// 위로 날아가서 쌓기(fly up stack)
void flyUpStack() {
  for (int i = 11; i >= 0; i--) {
    for (int j = 0; j < i; j++) {
      digitalWrite(L[j], HIGH);
      delay(110 - 10 * i);
      digitalWrite(L[j], LOW);
    }
    digitalWrite(L[i], HIGH);
    delay(dTime);
  }
}

// 홀,짝 번갈아 cnt회 점멸(odd even alternating blink)
void alterBlink(int cnt) {
  for (int i = 0; i < (cnt * 2); i++) {
    for (int j = 0; j < 11; j += 2) {
      digitalWrite(L[j], i % 2);
      digitalWrite(L[j + 1], !(i % 2));
    }
    delay(dTime * 2);
  }
}

// 하나씩 위로 데려가기(take out upward)
void takeOutUp() {
  for (int j = 5; j >= 0; j--) {
    for (int k = 11; k > j; k--) { // 데리러 가기
      digitalWrite(L[k], HIGH);
      delay(dTime);
      digitalWrite(L[k], LOW);
    }

    for (int l = j; l < 11; l++) { // 데리고 가기
      digitalWrite(L[l], HIGH);
      digitalWrite(L[l + 1], HIGH);
      delay(dTime);
      digitalWrite(L[l], LOW);
      digitalWrite(L[l + 1], LOW);
    }
    digitalWrite(L[11], HIGH);    // 사라질 때 마지막 LED 보이기
    delay(dTime);
    digitalWrite(L[11], LOW);
    delay(dTime * 4);
  }
}

// 모든 LED 끄기(all LEDs off)
void allClear() {
  for (int i = 0; i < 12; i++) {
    digitalWrite(L[i], LOW);
  }
}
