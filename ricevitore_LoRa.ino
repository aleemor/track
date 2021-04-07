#include <LoRa.h>
#include <SPI.h>

#define preamb 77

struct dati{ 
  uint8_t preambolo;
  uint8_t n_reboot;
  uint8_t batt;
  uint8_t h_dop;
  uint16_t sec;
  uint16_t id;      
  uint16_t lat_1;     // int16_t
  uint16_t lon_1;
  uint16_t lat_2;     // int16_t
  uint16_t lon_2;
  uint16_t lat_3;     // int16_t
  uint16_t lon_3;
} pacchetto;

byte buffer_pack[20];

int packetSize;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  LORA_initialization();

  delay(1000);
  Serial.println("Ricevitore LoRa");
  
}

void loop() {
  packetSize = LoRa.parsePacket();
  if (packetSize==20) {
    while ( LoRa.available() ) {
      for(int i = 0; i<20; i++) {
        buffer_pack[i] = LoRa.read();
      }
      memcpy(&pacchetto,buffer_pack,20);
    }
    if (pacchetto.preambolo==preamb){
      //Serial.write((byte *)&buffer_pack, 20); 
      displayInfo();
    }
  }
}

void  LORA_initialization() {
  if (!LoRa.begin(915E6)) {                                   // verifico collegamenti LoRa
    Serial.println("Starting LoRa Failed");
    while (1);
  }
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(67.5E3);
  LoRa.setTxPower(0, 1);
}

void displayInfo() {
  Serial.print("preamb: ");
  Serial.print(pacchetto.preambolo);
  Serial.print(" reboot: ");
  Serial.print(pacchetto.n_reboot);
  Serial.print(" batt: ");
  Serial.print(pacchetto.batt);
  Serial.print(" hdop: ");
  Serial.print(pacchetto.h_dop);
  Serial.print(" sec: ");
  Serial.print(pacchetto.sec);
  Serial.print(" id: ");
  Serial.print(pacchetto.id);
  Serial.print(" lat_1: ");
  Serial.print(pacchetto.lat_1);
  Serial.print(" lon_1: ");
  Serial.print(pacchetto.lon_1);
  Serial.print(" lat_2: ");
  Serial.print(pacchetto.lat_2);
  Serial.print(" lon_2: ");
  Serial.print(pacchetto.lon_2);
  Serial.print(" lat_3: ");
  Serial.print(pacchetto.lat_3);
  Serial.print(" lon_3: ");
  Serial.print(pacchetto.lon_3);  
  Serial.print(" size: ");
  Serial.print(packetSize);  
  Serial.print(" RSSI:");
  Serial.print(LoRa.packetRssi());

  Serial.println();
  
}
