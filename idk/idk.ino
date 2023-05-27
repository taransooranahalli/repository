#include <ESP8266WiFi.h>
#include <espnow.h>
#define SensorPin 14

#define WIFI_CHANNEL 1
boolean SendingConfirmation = false;

uint8_t remoteMac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x36};
// struct of sending data
struct __attribute__((packed)) SENSOR_DATA {
  int SwitchID = 1;
} sensorData;


void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Start Program");
  pinMode(SensorPin,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  WiFi.mode(WIFI_AP);
  Serial.print("This node AP mac: "); Serial.println(WiFi.softAPmacAddress());

 
  esp_now_init();
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_add_peer(remoteMac, ESP_NOW_ROLE_COMBO, WIFI_CHANNEL, NULL, 0);
//************************************************************
  esp_now_register_send_cb([](uint8_t *sendingMac, uint8_t sendStatus) {
    Serial.print("SendingStatus:  ");
    Serial.println(sendStatus);
    if (sendStatus == 0) {
      SendingConfirmation = true;
    } else {
      SendingConfirmation = false;
    }
  });
//************************************************************
}

void loop() {
  if(digitalRead(SensorPin)){
    Serial.println("Motion Dectected");
    uint8_t bs[sizeof(sensorData)];
   
    memcpy(bs, &sensorData, sizeof(sensorData));
    esp_now_send(NULL, bs, sizeof(sensorData)); // NULL means send to all peers

    digitalWrite(LED_BUILTIN,LOW);
    delay(1000);
  }else{
    digitalWrite(LED_BUILTIN,HIGH);    
  }
}