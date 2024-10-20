/* 날씨 API 정보를 받아온 후 LED 매트릭스에 기온을 표시하는 예제
Arduino_LED_Matrix(기본설치), Arduino_JSON, WiFiS3(기본설치) 라이브러리를 추가
https://m.blog.naver.com/no1_devicemart/223267576032
*/

// WiFiWeatherStation.ino
#include "Arduino_LED_Matrix.h" // led 매트릭스 사용을 위한 라이브러리
#include "numbers.h" // 0~9 숫자 + 모래시계 아이콘

ArduinoLEDMatrix matrix; // led 매트릭스 객체 생성

#include "WiFiS3.h" // WiFi 사용을 위한 라이브러리
#include <Arduino_JSON.h> // Arduino 스케치에서 JSON 처리 위한 라이브러리
#include <assert.h> // 에러 검출용 헤더파일

#include "arduino_secrets.h" // WiFi ID/PASSWORD 정보를 담고 있는 헤더파일

unsigned long lastConnectionTime = 0;               // 마지막으로 서버에 연결한 시간(밀리초)
const unsigned long postingInterval = 10L * 1000L;  // 업데이트 사이의 지연 시간(밀리초)
JSONVar myObject;
unsigned char frame[8][12];
int temperature = 0;
// arduino_secrets.h에 SSID, password 저장
char ssid[] = SECRET_SSID;  // network SSID (name)
char pass[] = SECRET_PASS;  // network password (use for WPA, or use as key for WEP)
int keyIndex = 0;           // network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// DNS를 사용하지 않으려는 경우(그리고 스케치 크기를 줄이려면)
// 서버 이름 대신 숫자 IP를 사용
//IPAddress server(202,61,229,161);  // numeric IP for api.open-meteo.com (no DNS)
char server[] = "api.open-meteo.com";  // name address for api.open-meteo.com (using DNS)
// https://api.open-meteo.com/v1/forecast?latitude=41.6561&longitude=-0.8773&current_weather=true&timezone=Europe%2FBerlin

// 서버의 IP 주소와 포트로 이더넷 클라이언트 라이브러리 초기화
// 연결하려는 포트(포트 80은 HTTP의 기본값)
WiFiClient client;

void displayDec(int number) {
  int decs = (number / 10) % 10;
  int units = number % 10;  //
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j<6 > 0; ++j) {
      frame[i][j] = numbers[decs][i][j];
    }
    for (int j = 0; j<6 > 0; ++j) {
      frame[i][j + 6] = numbers[units][i][j];
    }
  }

  matrix.renderBitmap(frame, 8, 12);
}

/* -------------------------------------------------------------------------- */
void setup() {
  /* -------------------------------------------------------------------------- */
  //시리얼을 초기화하고 포트가 열릴 때까지 기다림
  Serial.begin(9600);
  while (!Serial) {
    ;  // 직렬 포트가 연결될 때까지 기다림
  }

  matrix.begin(); // led 매트릭스 시작

  matrix.loadFrame(clock_animation[0]);
  // WiFi 모듈 확인
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // WiFi 네트워크에 연결 시도
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // WPA/WPA2 네트워크에 연결. 개방형 또는 WEP 네트워크를 사용하는 경우 이 줄을 변경
    status = WiFi.begin(ssid, pass);

    // 연결을 위해 10초 대기
    //delay(10000);
  }
  // 연결 완료, 상태 출력
  printWifiStatus();
}

/* just wrap the received data up to 80 columns in the serial print*/
/* -------------------------------------------------------------------------- */
void read_response() {
  /* -------------------------------------------------------------------------- */
  uint32_t received_data_num = 0;
  uint32_t data_num = 0;
  bool jsonDetected = false;
  char data[500];
  while (client.available() && data_num < 500) {
    /* 실제 데이터 수신 */
    char c = client.read();
    // 
    if ('{' == c) {
      jsonDetected = true;
    }
    if (jsonDetected) {
      data[data_num++] = c;
    }
  }
  //data[received_data_num] = 0;
  if (jsonDetected) {
    Serial.println(data);
    myObject = JSON.parse(data);
    Serial.print("Temperature C: ");
    if (myObject.hasOwnProperty("current_weather")) {

      temperature = (double)myObject["current_weather"]["temperature"];
      Serial.println(temperature);
      displayDec(temperature);
    }
  }
}

/* -------------------------------------------------------------------------- */
void loop() {
  // 네트워크 연결에서 들어오는 데이터가 있는 경우
  // 시리얼 포트로 보냄. 이는 디버깅 목적으로만 사용됨
  read_response();
  // 마지막 연결 이후 10초가 지나면 다시 연결하고 데이터를 보냄
  if (millis() - lastConnectionTime > postingInterval) {
    http_request();
  }
}

/* -------------------------------------------------------------------------- */
void printWifiStatus() {
  /* -------------------------------------------------------------------------- */
  // 연결된 네트워크의 SSID 출력
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // IP 주소 출력
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // 수신된 신호 강도 출력
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void http_request() {
  matrix.loadFrame(clock_animation[0]);
  client.stop();
  Serial.println("\nStarting connection to server...");
  // 연결되면 시리얼 모니터에 출력
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // HTTP 요청을 수행
    client.println("GET /v1/forecast?latitude=37.566&longitude=126.9784&current_weather=true&timezone=Asia%2FSeoul HTTP/1.1");
    client.println("Host: api.open-meteo.com");
    client.println("Connection: close");
    client.println();
    lastConnectionTime = millis();
  } else {
    // 연결을 할 수 없다면
    Serial.println("connection failed");
  }
}