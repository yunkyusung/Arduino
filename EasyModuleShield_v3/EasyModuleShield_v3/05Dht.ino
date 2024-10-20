// DHT11 센서값 읽기
void dht_read(){
  //센서값 읽기
  float h = dht.readHumidity();         // 습도를 측정합니다.
  float t = dht.readTemperature();      // 온도를 측정합니다.
  float f = dht.readTemperature(true);  // 화씨 온도를 측정합니다.
  
  // 값 읽기에 오류가 있으면 오류를 출력
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // 체감 온도값(화씨) 계산
  float hif = dht.computeHeatIndex(f, h);
  // 체감 온도값(섭씨) 계산
  float hic = dht.computeHeatIndex(t, h, false);

  // Serial로 결과를 출력
  Serial.print("[D4]DHT11 - ");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");  // 
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
