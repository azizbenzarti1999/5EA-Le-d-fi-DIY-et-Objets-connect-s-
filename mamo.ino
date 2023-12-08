#define BLYNK_TEMPLATE_ID "TMPL2cwWYxZJ8"
#define BLYNK_TEMPLATE_NAME "serre intelligent"
#define BLYNK_AUTH_TOKEN "WZm4zl9HnTWD-YQoCDwlPX1wMJ_I1NVl"
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "mahmoud";  // type your wifi name
char pass[] = "hmila466";  // type your wifi password


#define DHTPIN 32
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

#define soil 25
#define ventilateur 33
#define pompe_PIN  13

int pompeState = LOW;
#define Gauge_DHT    V0
#define Gauge_SOL    V1
#define LED_pompe    V2
#define LED_vent     V3
#define LED_vent     V4

void setup() {
  Serial.begin(9600);
  pinMode(pompe_PIN, OUTPUT);
  digitalWrite(pompe_PIN, LOW);
  pinMode(ventilateur, OUTPUT);
  digitalWrite(ventilateur, LOW);
  
  Blynk.begin(auth, ssid, pass);
  dht.begin();

  timer.setInterval(100L, soilMoistureSensor);
  timer.setInterval(100L, DHT22sensor);
}

void loop() {

  Blynk.run();
  timer.run();

}

void DHT22sensor() {
  float t = dht.readTemperature(); 

  if ( isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t);
  Serial.print("Temperature: ");
  Serial.print(t);
    

  if (t < 45) {
    digitalWrite(ventilateur, HIGH);
    Blynk.virtualWrite(LED_vent, HIGH);

  } else if (t >= 25) {
    digitalWrite(ventilateur, LOW);
    Blynk.virtualWrite(LED_vent, LOW);
  }
}

bool pompeActive = false;

void soilMoistureSensor() {
  int value = analogRead(soil);
  value = map(value, 0, 1023, 0, 100);
  Blynk.virtualWrite(V1, value);

  if (value < 20 && !pompeActive) {
    digitalWrite(pompe_PIN, HIGH);
    Blynk.virtualWrite(LED_pompe, HIGH);
    pompeActive = true;  
  } else if (value >= 100 && pompeActive) {
    digitalWrite(pompe_PIN, LOW);
    Blynk.virtualWrite(LED_pompe, LOW);
    pompeActive = false;  
  }
}
