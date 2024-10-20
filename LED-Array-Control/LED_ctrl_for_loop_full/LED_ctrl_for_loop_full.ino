// 제어,반복문 학습 예제
// 회로 구성 : D0~D13까지 14개 LED bar module 연결
// https://www.mcuboard.com:14063/shop/goods/goods_view.php?goodsno=1378335
// 2020.9.15. yunkyusng@KNUE.  GNU.

int dTime = 50;

void setup() {
  for (int i = 0; i < 14; i++)  // 핀모드 셋업
    pinMode(i, OUTPUT);
}

void loop() {

  //[과제1] 위/아래로 쌓기
  upStack();      // 0 -> 13 위로 쌓기(up stack)
  allClear();
  downStack();    // 0 <- 13 아래로 쌓기(down stack)
  allClear();

  //[과제2]위/아래로 하나씩 점멸(2회 반복)
  for (int k = 0; k < 2; k++) {
    upBlink();    // 0 -> 13 위로 하나씩 점멸(up blink)
    downBlink();  // 0 <- 13 아래로 하나식 점멸(down blink)
  }

  //[과제3-1] 안으로/밖으로 하나씩 점멸(2회 반복)
  for (int k = 0; k < 2; k++) {
    innerBlink();   // 0 -> 6  7 <- 13 밖에서 안으로 하나씩 점멸(to center blink)
    outerBlink();   // 0 <- 6  7 -> 13 안에서 밖으로 하나씩 점멸(to outer blink)
  }

  //[과제3-2] 안으로 쌓고,밖으로 하나씩 끄기(2회 반복)
  for (int k = 0; k < 2; k++) {
    innerStack();   // 0 -> 6  7 <- 13 밖에서 안으로 하나씩 쌓기(stack to inner)
    outerOff();     // 0 <- 6  7 -> 13 안에서 밖으로 하나씩 끄기(off to outer)
  }

  //[과제3-3] 밖으로 쌓고,안으로 하나씩 끄기(2회 반복)
  for (int k = 0; k < 2; k++) {
    outerStack();   // 0 -> 6  7 <- 13 안에서 밖으로 하나씩 쌓기(stack to outer)
    innerOff();     // 0 <- 6  7 -> 13 밖에서 안으로 하나씩 끄기(off to inner)
  }
  

  //[과제4] 아래로/위로 날아가서 쌓기
  flyDownStack(14);  // 아래로 날아가서 14개 쌓기(fly down stack)
  delay(500);  allClear();
  flyUpStack();       // 위로 날아가서 쌓기(fly up stack)
  delay(500);  allClear();

  //[과제5] 홀/짝 번갈아 점멸(10회)
  alterBlink(10);     // 홀,짝 번갈아 10회 점멸(odd even alternating blink)
  allClear();

  //[추가1] 7개 쌓고 하나씩 위로 데려가기
  flyDownStack(7);    // 아래로 날아가서 7개 쌓기(fly down stack)
  delay(500); 
  takeOutUp(6);       // 6부터 하나씩 위로 데려가기(take out upward)


  delay(1000);

}//loop

// 0 -> 13 위로 쌓기(up stack)
void upStack() {
  for (int i = 0; i < 14; i++) {
    digitalWrite(i, HIGH);
    delay(dTime);
  }
}

// 0 <- 13 아래로 쌓기(down stack)
void downStack() {
  for (int i = 13; i >= 0; i--) {
    digitalWrite(i, HIGH);
    delay(dTime);
  }
}

// 0 -> 13 위로 하나씩 점멸(up blink)
void upBlink() {
  for (int i = 0; i < 14; i++) {
    digitalWrite(i, HIGH);
    delay(dTime);
    digitalWrite(i, LOW);
  }
}

// 0 <- 13 아래로 하나씩 점멸(down blink)
void downBlink() {
  for (int i = 13; i >= 0; i--) {
    digitalWrite(i, HIGH);
    delay(dTime);
    digitalWrite(i, LOW);
  }
}

// 0 -> 6  7 <- 13 밖에서 안으로 하나씩 점멸(to center blink)
void innerBlink() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(i, HIGH);
    digitalWrite(13 - i, HIGH);
    delay(dTime);
    digitalWrite(i, LOW);
    digitalWrite(13 - i, LOW);
  }
}

// 0 <- 6  7 -> 13 안에서 밖으로 하나씩 점멸(to outer blink)
void outerBlink() {
  for (int i = 6; i >= 0; i--) {
    digitalWrite(i, HIGH);
    digitalWrite(13 - i, HIGH);
    delay(dTime);
    digitalWrite(i, LOW);
    digitalWrite(13 - i, LOW);
  }
}

// 0 -> 6  7 <- 13 밖에서 안으로 하나씩 쌓기(stack to inner)
void innerStack() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(i, HIGH);
    digitalWrite(13 - i, HIGH);
    delay(dTime);
  }
}

// 0 <- 6  7 -> 13 안에서 밖으로 하나씩 쌓기(stack to ouitr)
void outerStack() {
  for (int i = 6; i >= 0; i--) {
    digitalWrite(i, HIGH);
    digitalWrite(13 - i, HIGH);
    delay(dTime);
  }
}
// 0 <- 6  7 -> 13 안에서 밖으로 하나씩 끄기(off to outer)
void outerOff() {
  for (int i = 6; i >= 0; i--) {
    digitalWrite(i, LOW);
    digitalWrite(13 - i, LOW);
    delay(dTime);
  }
}

// 0 -> 6  7 <- 13 밖에서 안으로 하나씩 끄기(off to inner)
void innerOff() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(i, LOW);
    digitalWrite(13 - i, LOW);
    delay(dTime);
  }
}

// 아래로 날아가서 쌓기(fly down stack)
void flyDownStack(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 13; j > i; j--) {
      digitalWrite(j, HIGH);
      delay(10 * (i + 1));
      digitalWrite(j, LOW);
    }
    digitalWrite(i, HIGH);
    delay(dTime);
  }
}

// 위로 날아가서 쌓기(fly up stack)
void flyUpStack() {
  for (int i = 13; i >= 0; i--) {
    for (int j = 0; j < i; j++) {
      digitalWrite(j, HIGH);
      delay(130 - 10 * i);
      digitalWrite(j, LOW);
    }
    digitalWrite(i, HIGH);
    delay(dTime);
  }
}

// 홀,짝 번갈아 cnt회 점멸(odd even alternating blink)
void alterBlink(int cnt) {
  for (int i = 0; i < (cnt * 2); i++) {
    for (int j = 0; j < 13; j += 2) {
      digitalWrite(j, i % 2);
      digitalWrite(j + 1, !(i % 2));
    }
    delay(dTime * 2);
  }
}

// 하나씩 위로 데려가기(take out upward)
void takeOutUp(int n) {
  for (int j = n; j >= 0; j--) {
    for (int k = 13; k > j; k--) { // 데리러 가기
      digitalWrite(k, HIGH);
      delay(dTime);
      digitalWrite(k, LOW);
    }

    for (int l = j; l < 13; l++) { // 데리고 가기
      digitalWrite(l, HIGH);
      digitalWrite(l + 1, HIGH);
      delay(10*(j+1));
      digitalWrite(l, LOW);
      digitalWrite(l + 1, LOW);
    }
    digitalWrite(13, HIGH);    // 사라질 때 마지막 LED 보이기
    delay(dTime);
    digitalWrite(13, LOW);
    delay(dTime * 4);
  }
}

// 모든 LED 끄기(all LEDs off)
void allClear() {
  for (int i = 0; i < 14; i++) {
    digitalWrite(i, LOW);
  }
}
