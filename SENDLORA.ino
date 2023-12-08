#include <LoRa.h>
#include <TiyGPS++.h>
#include <SoftwareSerial.h>

#define ss 10    // LoRa SS pin
#define dio0 2   // LoRa DIO0 pin

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
  while (!Serial);

  LoRa.setPins(ss, dio0);

  while (!LoRa.begin(868E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}


void sendMessage(String message) {
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  Serial.println("Message sent: " + message);
}
void loop() {
  
      // Prepare the data to transmit
      String data = "TEMPERATURE: " + String(TEMPERATURE , 6) + ", HUMIDITY: " + String(HUMIDITY, 6);
 // Send the data via LoRa
      sendMessage(data);

      // Adjust the delay based on your requirements
      delay(10000);  // 10 seconds delay between messages


}
