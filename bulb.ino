#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#define TRIG D6
#define ECHO D7
String str;

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(9600);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();
   pinMode(TRIG,OUTPUT);
   pinMode(ECHO,INPUT);
// pinMode(led,OUTPUT);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("SSAAN", "yahooindia");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;
    //long n = 458766;
    
    //float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    //float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    //float f = dht.readTemperature(true);
//    Serial.print("Humidity: ");
//    Serial.print(h);
//    Serial.print(" %\t");
//    Serial.print("Temperature: ");
//    Serial.print(t);
//    Serial.print(" *C ");
//    Serial.print(f);
//    Serial.print(" *F\t");
//  
      long distance,duration;
    digitalWrite(TRIG,HIGH);
    delayMicroseconds(1000);
    digitalWrite(TRIG,LOW);
    duration=pulseIn(ECHO,HIGH);
    distance=(duration/2)/29.1;
    Serial.print(distance);
    Serial.println("CM");
    delay(10);

    
    String dis = (String) distance;
    
    String str = "http://kumarsaket.ml/Project_02/saket1.php?distance="+dis +"&submit=Submit";
    //String str = "http://user.cisar.in/page1.php?name="+my_name+"&humid="+hum+"&temp="+tem+"&faren="+far;
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, str)) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(10000);

}
