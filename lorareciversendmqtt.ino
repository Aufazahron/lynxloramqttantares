#include <LoRa.h>
#include <AntaresESPMQTT.h>

#define SS_PIN 5
#define RST_PIN 0
#define DI0_PIN 2
#define BAND 915E6

#define ACCESSKEY "e08e0b16b2add3a1:ce17ab4326d9d010"       // Antares account access key
#define WIFISSID "azrniot"         // Wi-Fi SSID to connect to
#define PASSWORD "wkwkwkwk"     // Wi-Fi password

#define projectName "iotedgecomputing"   // Name of the application created in Antares
#define deviceName "Lynx-receiver"     // Name of the device created in Antares

AntaresESPMQTT antares(ACCESSKEY);

void setup() {
  Serial.begin(9600);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
  while (!Serial);

  LoRa.setPins(SS_PIN, RST_PIN, DI0_PIN);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");

  // Mengatur pin DIO0 sebagai input
  pinMode(DI0_PIN, INPUT);
}

void loop() {
  antares.checkMqttConnection();
  // Menunggu sampai paket diterima
  if (LoRa.parsePacket()) {
    // Membaca pesan yang diterima
    
    String dataReceived = "";
    while (LoRa.available()) {
      dataReceived += (char)LoRa.read();
    }
    float suhu, kelembapan;
    int commaIndex = dataReceived.indexOf(',');
    if (commaIndex != -1) {
      suhu = dataReceived.substring(0, commaIndex).toFloat();
      kelembapan = dataReceived.substring(commaIndex + 1).toFloat();
      antares.add("suhu", suhu);
      antares.add("kelembapan", kelembapan);
      antares.publish(projectName, deviceName);

    Serial.println(); // Pindah baris setelah selesai membaca pesan
  }}
}
