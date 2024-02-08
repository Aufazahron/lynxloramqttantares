#include <LoRa.h>

#define SS_PIN 5
#define RST_PIN 0
#define DI0_PIN 2
#define BAND 915E6

void setup() {
  Serial.begin(9600);
  while (!Serial);

  LoRa.setPins(SS_PIN, RST_PIN, DI0_PIN);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // Menyiapkan data suhu dan kelembapan
  float suhu = 20.20;
  float kelembapan = 50.02;

  // Membuat string yang berisi data suhu dan kelembapan
  String data = String(suhu, 2) + "," + String(kelembapan, 2);

  Serial.print("Sending data: ");
  Serial.println(data);

  // Mengirim data
  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();

  delay(5000); // Delay 5 detik sebelum mengirim data lagi
}
