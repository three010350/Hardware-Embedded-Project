#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <TridentTD_LineNotify.h>

#define SSID        "Minda"   // ชื่อ Wifi
#define PASSWORD    "asronarom"   // รหัส Wifi
#define LINE_TOKEN  "bJvVeb0l3fZ5GhaIMMmhrah0PejRBcF3tq6xdWpzvVr"   // TOKEN

#include <SoftwareSerial.h>
SoftwareSerial NodeSerial(D2, D3); // RX | TX
void setup() {
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  NodeSerial.begin(57600);
  Serial.begin(9600);
  Serial.println();
  Serial.println("NodeMCU/ESP8266 Run");
  ///////////////////////
  //Serial.begin(115200);
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting ",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
}

void loop() {
  while (NodeSerial.available() > 0)
  {
    //Serial.println("test");
    float mq_7 = NodeSerial.parseFloat();
    float mq_4 = NodeSerial.parseFloat();
    int mh_z14a = NodeSerial.parseInt();
    if (NodeSerial.read() == '\n')
    {
      Serial.print("values of mq135 = ");
      Serial.println(mq_7);
      Serial.print("values of mq_4 = ");
      Serial.println(mq_4);
      Serial.print("values of mh_z14a = ");
      Serial.println(mh_z14a);
      Serial.print('\n');
      ///////////////////////////////
      if(mq_7 > 100 || mh_z14a >1200 || mq_4>500)
      {
        LINE.notify("ขยะเป็นมลพิษเร่งจัดการ");
        LINE.notify("CO2 CH4 CO");
        LINE.notify(mh_z14a);
        LINE.notify(mq_4);
        LINE.notify(mq_7);
        LINE.notify("ตามลำดับ");
      }
    }
  }

}