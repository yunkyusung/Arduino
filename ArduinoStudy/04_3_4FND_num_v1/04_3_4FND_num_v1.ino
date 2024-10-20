/*        d2
 *       ====  
 *  d7 ||    || d3
 *    d8 ==== 
 *  d6 ||    || d4
 *       ====  *
 *        d5    d9
 *  Common Anode
 */
byte digitsCA[][8] = { // 공통 양극(CA)
//  {a,b,c,d,e,f,g,dp}
    {0,0,0,0,0,0,1,1}, //0
    {1,0,0,1,1,1,1,1}, //1
    {0,0,1,0,0,1,0,1}, //2
    {0,0,0,0,1,1,0,1}, //3
    {1,0,0,1,1,0,0,1}, //4
    {0,1,0,0,1,0,0,1}, //5
    {0,1,0,0,0,0,0,1}, //6
    {0,0,0,1,1,1,1,1}, //7
    {0,0,0,0,0,0,0,1}, //8
    {0,0,0,0,1,0,0,1}, //9
    {0,0,0,1,0,0,0,1}, //a
    {1,1,0,0,0,0,0,1}, //b
    {0,1,1,0,0,0,1,1}, //c
    {1,0,0,0,0,1,0,1}, //d
    {0,1,1,0,0,0,0,1}, //e
    {0,1,1,1,0,0,0,1}  //f
  };
//{a,b,c,d,e,f,g,dp}
byte digitsCC[][8] = { // 공통 음극(CC)
    {1,1,1,1,1,1,0,0}, //0
    {0,1,1,0,0,0,0,0}, //1
    {1,1,0,1,1,0,1,0}, //2
    {1,1,1,1,0,0,1,0}, //3
    {0,1,1,0,0,1,1,0}, //4
    {1,0,1,1,0,1,1,0}, //5
    {1,0,1,1,1,1,1,0}, //6
    {1,1,1,0,0,0,0,0}, //7
    {1,1,1,1,1,1,1,0}, //8
    {1,1,1,1,0,1,1,0}, //9
    {1,1,1,0,1,1,1,0}, //a
    {0,0,1,1,1,1,1,0}, //b
    {1,0,0,1,1,1,0,0}, //c
    {0,1,1,1,1,0,1,0}, //d
    {1,0,0,1,1,1,1,0}, //e
    {1,0,0,0,1,1,1,0}  //f
  };

const uint8_t digitPins[4] = { 10, 11, 12, 13 }; //digit 선택 핀 10-D1, 11-D2, 12-D3, 13-D4 

int delayT = 100;

void setup() {
  for(byte i = 2; i < 10 ; i++)  { //2-a, 3-b, 4-c, 5-d, 6-e, 7-f, 8-g, 9-dp
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);      // CA: HIGH-OFF  LOW-ON
  }
  for(byte i = 0; i < 4 ; i++)  { //10-D1, 11-D2, 12-D3, 13-D4 
    pinMode(i, OUTPUT);
    digitalWrite(digitPins[i], LOW);  // CA: LOW-OFF  HIGH-ON
  }
}

void loop() {
//  for(int digit=0; digit<4; digit++){
    digitalWrite(13,HIGH);   //digit 선택
    displayFND(8);
    delay(delayT);
    digitalWrite(13,LOW);   //digit 해제
    delay(delayT*3);
    
//  }
}

void clearFND()  {
  for(byte i = 2 ; i < 10 ; i++)  {
    digitalWrite(i, HIGH); // CA: HIGH-OFF  LOW-ON
  }
}

void displayFND(byte num)  {
  for(byte i = 2 ; i < 10 ; i++)  {
    digitalWrite(i, digitsCA[num][i-2]);
  }
}
