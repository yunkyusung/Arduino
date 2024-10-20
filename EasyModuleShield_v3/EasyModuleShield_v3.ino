/* 아두이노 이지모듈쉴드 테스트 프로그램 ver.3
 *  Easy Module Shield For Arduino 핀맵
  ----------------------------------------------------------------------------
                  ~         ~    ~              ~     ~     ~
  D0   D1   D2   D3   D4    D5   D6   D7   D8   D9   D10   D11   D12   D13
  Rx   Tx   SW1  SW2 dht11 buzz  IR           --R     B     G--  LED2  LED1
  ----------------------------------------------------------------------------
  A0   A1   A2   A3   A4   A5
  VR  CDS  LM35
  -------------------------------
  YunKyuSung@KNUE. 2020.7.23. GNU.
*/

#include <DHT.h>
#include <IRremote.h>
#include <TimerFreeTone.h>

#define SW1_pin      2
#define SW2_pin      3
#define DHT_pin      4
#define BUZZ_pin     5
#define IR_pin       6
#define LED_R_pin    9
#define LED_B_pin   10
#define LED_G_pin   11
#define LED2_pin    12
#define LED1_pin    13
#define VR_pin      A0
#define CDS_pin     A1
#define LM35_pin    A2

#define DHTTYPE DHT11   // DHT 11(DHT시리즈중 11을 선택)

DHT dht(DHT_pin, DHTTYPE);    // DHT11 객체 선언

IRrecv irrecv(IR_pin);        // 적외선 수신기 객체 선언
decode_results results;       // 적외선 수신데이터 저장 객체 선언

void setup() {
  Serial.begin(9600);           // 시리얼 통신 시작

  // 포트 입출력 설정
  pinMode( SW1_pin,   INPUT );    // sw1 스위치1
  pinMode( SW2_pin,   INPUT );    // sw2 스위치2
  pinMode( DHT_pin,   INPUT );    // dht11 온습도
  pinMode( BUZZ_pin,  OUTPUT);    // buzzer 부저
  pinMode( IR_pin,    INPUT );    // IR 적외선 수신
  pinMode( LED_R_pin, OUTPUT);    // RGB-Red
  pinMode( LED_G_pin, OUTPUT);    // RGB-Green
  pinMode( LED_B_pin, OUTPUT);    // RGB-Blue
  pinMode( LED2_pin,  OUTPUT);    // LED2
  pinMode( LED1_pin,  OUTPUT);    // LED1

  dht.begin();                  // DHT11 시작
  irrecv.enableIRIn();          // 적외선 수신 시작
  //analogReference(INTERNAL);    // LM35용
}

void loop() {
  // 부품별 테스트
  // LED
  //led_blink(500);     // LED1, LED2 깜빡이기, 파라미터: delay 속도(ms)

  // RGB LED
  //rgb_blink(100);     // RGB 차례로 깜빡이기, 파라미터: delay 속도(ms)

  // 스위치
  //sw_led();           // SW1, SW2 스위치 누르면 LED 켜짐

  // 온습도(dht11)
  //dht_read();         // dht11 값 읽어서 출력하기
  //delay(1500);        // 1.5초 간격으로

  //부저
  //buzz_beep(2);       // buzz_beep(beep횟수)
  //delay(1000);
  //buzz_beep_on();     // ON 신호음
  //delay(1000);
  //buzz_beep_off();    // OFF 신호음
  //delay(1000);

  //적외선
  //ir_recv();            // 적외선 수신 , buzzer의 tone()과 충돌함, 둘 중 하나를 코멘트 처리해야함
  //ir_recv_and_ctrl();
  //delay(300);

  // 가변저항 VR
  //vr_read();            // 가변저항의 전압 읽기
  //delay(500);

  // 조도센서 cds
  //cds_read();             // 조도(cds) 읽기
  //delay(500);

  // 온도센서(LM35)
  //lm35_read();            // 온도(lm35) 읽기
  //delay(1000);


  // 보드 테스트
#if 1   // 여기를 1로 바꾸면 보트 테스트 실행

  //SW로 LED, RGB-LED 테스트를 계속 실행, SW 2개를 동시에 누르면 다음으로 진행
  sw_test();

  // VR(가변저항), cds(조도), dht11(온습도), lm35(온도) 를 Serial로 전송
  led_on();  rgb_on();  // 셀프 테스트 모드 표시
  while (1) { // 아무 스위치나 누를 때까지 Self Test 계속 실행
    Serial.println("Testing... ******");
    dht_read();           // dht11(온습도)값 읽어서 Serial로 출력하기
    vr_read();            // VR(가변저항)의 전압 읽어서 Serial로 출력하기
    cds_read();           // cds(조도)값 읽어서 Serial로 출력하기
    lm35_read();          // lm35(온도)값 읽어서 Serial로 출력하기

    if (digitalRead(SW1_pin) == LOW || digitalRead(SW2_pin) == LOW) // 아무 스위치나 누르면 Self Test 종료
      break;

    buzz_beep(1); // IR 수신 대기
    for (int i = 0; i < 5; i++) {
      ir_recv_and_ctrl();            // Ir(적외선) 수신
      delay(300);
    }
  }
  led_off();  rgb_off();  // 셀프 테스트 종료 표시

#endif

}
