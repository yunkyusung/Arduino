// Multifunction Expansion Board Adapter For Arduino
//----------------------------------------------------------------------------
//                  ~        ~    ~              ~     ~     ~
// D0     D1   D2   D3   D4    D5   D6   D7   D8   D9   D10   D11   D12   D13
// └APC220┘ IR소켓 BUZZ LATCH  -    -   CLK  DATA  -   LED4  LED3  LED2  LED1  
//----------------------------------------------------------------------------
//  A0   A1   A2   A3   A4      A5        
//  VR   SW1  SW2  SW3 LM35소켓  -
//----------------------------------
// Free pins (pwm) : 5, 6, 9, A5
// J1: LM35 enable, J2: SW1~3 enable

#define LED1_PIN  13
#define LED2_PIN  12
#define LED3_PIN  11
#define LED4_PIN  10
#define DATA_PIN   8    // 7Segment display
#define CLK_PIN    7    // 7Segment display
#define LATCH_PIN  4    // 7Segment display
#define BUZZER_PIN 3
#define POT_PIN   A0
#define SW1_PIN   A1
#define SW2_PIN   A2
#define SW3_PIN   A3
#define LM35_PIN  A4

void setup()
{
  Serial.begin(9600);
  pinMode(LED1_PIN, OUTPUT);  // D1
  pinMode(LED2_PIN, OUTPUT);  // D2
  pinMode(LED3_PIN, OUTPUT);  // D3
  pinMode(LED4_PIN, OUTPUT);  // D4
  //pinMode(SW1_PIN, INPUT);  // A1
  //pinMode(SW2_PIN, INPUT);  // A2
  //pinMode(SW3_PIN, INPUT);  // A3
  all_led_off();
  /* Set DIO pins to outputs */
  pinMode(LATCH_PIN,OUTPUT);
  pinMode(CLK_PIN,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
}


void loop()
{
  //led_blink();
  //all_led_blink();
  //SW_led_OnOff();
  //pot_read();
  //delay(500);
  //pot_led();
  //delay(50);
  
  /* Update the display with the current counter value */
  //WriteNumberToSegment(0 , 0); // segNO, value
  //WriteNumberToSegment(1 , 1);
  //WriteNumberToSegment(2 , 2);
  //WriteNumberToSegment(3 , 3);

  // pot값을 세그먼트에 표시하고, Led에도 표시, 500넘으면 부저도
  int PotValue = analogRead(POT_PIN);
  WriteNumberToSegment(0 , PotValue / 1000);
  WriteNumberToSegment(1 , (PotValue / 100) % 10);
  WriteNumberToSegment(2 , (PotValue / 10) % 10);
  WriteNumberToSegment(3 , PotValue % 10);
  led_level_meter(PotValue);
  if(PotValue>=500){
    digitalWrite(BUZZER_PIN, LOW);
  }
  
}
