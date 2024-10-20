void lm35_read(){
    int reading = analogRead(LM35_pin);
    //float temperature = ( 5.0 * reading *100. ) / 1024. ;
    float temperature = reading/2.048;      // (1.5/5.0)*1023./150. = 2.048, 1.5V for 150'C
    //float temperature = reading/9.31;    // setup()에 analogReference(INTERNAL); 로 설정해야함 (1.1V 의 Vref)
    
    Serial.print("[A2]LM35 temperature : ");  Serial.println(temperature);
    //delay(500);
}
