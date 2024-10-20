/*
  A simple program designed to setup and demonstrate the 3 Traffic Light LED module - BBAA100043
 
  The program simulates a simple pedestrian crossing.
  
  modified 21 June 2019
  by Sebastian Karam - Flux Workshop
*/
 
int redLEDpin = 13; // pin number for the red LED
int amberLEDpin = 12; // pin number for the amber LED
int greenLEDpin = 11; // pin number for the green LED
 
int amberDelay = 5; // pause in seconds to maintain the amber light
int redDelay = 10; // pause in seconds to maintain the red light
 
void setup() {
  pinMode(redLEDpin, OUTPUT); // set the R signal pin as an output
  pinMode(amberLEDpin, OUTPUT); // set the Y signal pin as an output
  pinMode(greenLEDpin, OUTPUT); // set the G signal pin as an output
 
  digitalWrite(redLEDpin,LOW); // set the red LED to off by default
  digitalWrite(amberLEDpin,LOW); // set the amber LED to off by default
  digitalWrite(greenLEDpin,HIGH); // set the green LED to on by default
  
  Serial.begin(9600); // launch the serial monitor
  Serial.println("Flux Workshop Traffic Light Example");
  Serial.println("Enter P to Cross");  
}
 
void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) { // check if data is available on the serial input
    char input = Serial.read(); // store the serial data in a variable
    if (input == 'P'){ // check if the incoming data is the letter 'P'
      Serial.println("--- BUTTON HAS BEEN PRESSED ---");
      Serial.println("--- GOING TO AMBER ---");  
      for (int count = 0; count <= amberDelay; count++){ // Loop through the amber sequence
        digitalWrite(amberLEDpin,HIGH); // set the amber LED to on
        digitalWrite(greenLEDpin,LOW); // set the green LED to off
        delay(1000);
      }
      Serial.println("--- GOING TO RED ---"); 
      for (int count = 0; count <= redDelay; count++){ // Loop through the amber sequence
        digitalWrite(amberLEDpin,LOW); // set the amber LED to off
        digitalWrite(redLEDpin,HIGH); // set the red LED to on
        delay(1000);
      }
      Serial.println("--- GOING TO FLASHING AMBER ---"); 
      for (int count = 0; count <= amberDelay*2; count++){ // Loop through the flashing amber sequence
        digitalWrite(amberLEDpin,!digitalRead(amberLEDpin)); // toggle the amber LED
        digitalWrite(redLEDpin,LOW); // set the red LED to off
        delay(500); // this is a shortened delay for it to flash faster
      }
      Serial.println("--- GOING TO BACK TO GREEN ---"); 
      digitalWrite(amberLEDpin,LOW); // set the amber LED to off
      digitalWrite(greenLEDpin,HIGH); // set the green LED to on
      delay(1000);
      Serial.println("Enter P to Cross"); // resend the instruction
    }
  }
}
