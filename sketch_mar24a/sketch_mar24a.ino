#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Adafruit_NeoPixel.h>


#define WIFI_CHANNEL 1
#define LED_PIN    13
#define LED_COUNT 125
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

boolean ReceivedData = false;

uint8_t mac_addr[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x36};
// struct of sending data
struct __attribute__((packed)) SENSOR_DATA {
  int SwitchID ;
} sensorData;


void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Start Program");
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_AP);
  Serial.print("This node AP mac: ");
  Serial.println(WiFi.softAPmacAddress());

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)   
 
  wifi_set_macaddr(SOFTAP_IF, &mac_addr[0]);
  esp_now_init();
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_recv_cb([](uint8_t *mac_addr, uint8_t *data, uint8_t len) {
    Serial.println("DataReceived");
    ReceivedData = true;    
  });
}

void loop() {
  if(ReceivedData == true){
    ReceivedData = false;    
  colorWipe(strip.Color(255,   0,   0), 20); // Red
  delay(3000);
  colorWipe2(strip.Color(0,   0,   0), 20); // Red
  delay(250);
  colorWipe(strip.Color(255,   0,   0), 20); // Red
  delay(3000);
  colorWipe2(strip.Color(0,   0,   0), 20); // Red
  delay(250);
    strip.clear();
    strip.show();            // Turn OFF all pixels ASAP
    Serial.println("Motion Dectected");
    digitalWrite(LED_BUILTIN,LOW);
    delay(1000);
  }else{
    digitalWrite(LED_BUILTIN,HIGH);    
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=8; i<=26; i++) { // For each pixel in strip...
    int j =54 - i;
    int k = i + 44;
    int l =97 - i;
    strip.setPixelColor(i, color);         //  String 1  Set pixel's color (in RAM)
    strip.setPixelColor(j, color);         //  String 2  Set pixel's color (in RAM)
    strip.setPixelColor(k, color);         //  String 3  Set pixel's color (in RAM)
    strip.setPixelColor(l, color);         //  String 4  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}  

void colorWipe2(uint32_t color, int wait) {
  for(int i=8; i<=26; i++) { // For each pixel in strip...
    int j =54 - i;
    int k = i + 44;
    int l =97 - i;
    strip.setPixelColor(i, color);         //  String 1  Set pixel's color (in RAM)
    strip.setPixelColor(j, color);         //  String 2  Set pixel's color (in RAM)
    strip.setPixelColor(k, color);         //  String 3  Set pixel's color (in RAM)
    strip.setPixelColor(l, color);         //  String 4  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}  