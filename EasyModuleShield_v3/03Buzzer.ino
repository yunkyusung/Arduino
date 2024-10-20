/* 이 쉴드의 부저는 수동타입. 즉, tone 신호로 소리를 내야함(주파수를 생성해서 공급)
  아두이노 기본 라이브러리 tone()을 사용하면 Ir과 충돌함(동일한 내장 타이머를 사용함)
  따라서, 타이머를 사용하지 않는 TimerFreeTone() 라이브러리를 사용함.
  https://bitbucket.org/teckel12/arduino-timer-free-tone/wiki/Home
*/

/* 아두이노의 PWM 과 TIMER
  http://www.hardcopyworld.com/gnuboard5/bbs/board.php?bo_table=lecture_pract&wr_id=12
  타이머와 PWM 핀은 밀접하게 연관되어 있습니다. 프로세서의 핀아웃 문서나 데이터 시트를 보면 OCRxA, OCRxB, OCRxC 로 표기된 PWM 핀이 있습니다.
  (x는 타이머 숫자 0~5) Mega를 제외한 일반적인 아두이노는 3개의 타이머와 6개의 PWM 핀이 있으며 아래와 같이 연관되도록 설정되어 있습니다.
  Pin 5, 6  : timer0 에 의해 컨트롤
  Pin 9, 10 : timer1 에 의해 컨트롤   <---> 서보는 timer1 사용
  Pin 11, 3 : timer2 에 의해 컨트롤   <---> tone(), IRremote 는 timer2 사용

  서보 라이브러리(Timer1)를 사용할 경우, 9번, 10번 핀의 PWM 은 사용할 수 없습니다.
  tone(),IRremote() 함수(Timer2)를 사용할 경우, 3번, 11번 핀의 PWM은 사용할 수 없습니다
*/

// 간격으로 beepCnt회 울림
void buzz_beep(int beepCnt) {
  for (int i = beepCnt; i > 0; i--) {
    TimerFreeTone(BUZZ_pin, 1000, 50); //TimerFreeTone(TONE_PIN, freq[Hz], duration[ms])
    delay(50);  // beep 음 간격
  }
}

// ON 신호음
void buzz_beep_on() {
  for (int i = 1; i < 5; i++) {
    TimerFreeTone(BUZZ_pin, 500 * i, 40); //TimerFreeTone(TONE_PIN, freq[Hz], duration[ms])
    delay(40);
  }
}

// OFF 신호음
void buzz_beep_off() {
  for (int i = 4; i > 0; i--) {
    TimerFreeTone(BUZZ_pin, 500 * i, 40); //TimerFreeTone(TONE_PIN, freq[Hz], duration[ms])
    delay(40);
  }
}

/*
  // IR과 충돌하므로 tone()은 IR을 쓰지않을 때만 사용할 것
  void buzz_play(int freq, int dTime){
  //tone(BUZZ_pin, freq, dTime);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
  //delay(dTime*2);
  //tone(BUZZ_pin, freq);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
  //delay(dTime);
  //noTone(BUZZ_pin);
  //delay(dTime);
  }
*/
