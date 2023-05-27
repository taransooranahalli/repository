#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Adafruit_NeoPixel.h>


#define WIFI_CHANNEL 1
#define LED_PIN    13
#define LED_COUNT 60
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
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  wifi_set_macaddr(SOFTAP_IF, &mac_addr[0]);
  esp_now_init();
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_recv_cb([](uint8_t *mac_addr, uint8_t *data, uint8_t len) {
    Serial.println("DataReceived");
    ReceivedData = true;    
  });
}

/*void loop() {
  if(ReceivedData == true){
    ReceivedData = false;    
    theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
    strip.clear();
    strip.show();            // Turn OFF all pixels ASAP


    Serial.println("Motion Dectected");
    digitalWrite(LED_BUILTIN,LOW);
    delay(1000);
  }else{
    digitalWrite(LED_BUILTIN,HIGH);    
  }
}
// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }*/
}
