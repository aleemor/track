#include <LoRa.h>
#include <SPI.h>

#define serialBaud 115200

#define preamb 77

#define frequency 915E6
#define BW 125E3
#define SF 12

struct dati{ 
  uint8_t  preambolo;
  uint8_t  n_reboot;
  uint8_t  batt;
  uint8_t  h_dop;
  uint16_t n_packSent;
  uint16_t sec;
  uint16_t id;      
  uint16_t lat_1;     
  uint16_t lon_1;
  uint16_t lat_2;     
  uint16_t lon_2;
  uint16_t lat_3;     
  uint16_t lon_3;
} pacchetto;

byte buffer_pack[sizeof(pacchetto)];

int counterLoop=0;

int Rssi;
uint32_t Snr;
int packetSize;
uint16_t n_packReceived = 0;
uint16_t n_packSent;
float PDR;

void setup() {
  Serial.begin(serialBaud);
  while (!Serial);

  LORA_initialization();

  delay(1000);
  
}

void loop() {
  counterLoop++;
  packetSize = LoRa.parsePacket();
  Serial.print(" packetSize: ");
  Serial.print(packetSize);
  Serial.print(" [");
  Serial.print(counterLoop);  
  Serial.println("]");  
  delay(10);
  
  if (packetSize==sizeof(pacchetto)) {
    while ( LoRa.available() ) {
      for(int i = 0; i<sizeof(pacchetto); i++) {
        buffer_pack[i] = LoRa.read();
      }
      Rssi=LoRa.packetRssi();
      Snr=LoRa.packetSnr();
      memcpy(&pacchetto,buffer_pack,sizeof(pacchetto));     
    }
    
    if (pacchetto.preambolo==preamb){
      n_packReceived++;
      n_packSent=pacchetto.n_packSent;
      PDR=((float)n_packReceived/n_packSent)*100; 
      //displayInfo();
      serialWrite();
    }
  }
  delay(1000); 
  
}

void  LORA_initialization() {
  if (!LoRa.begin(frequency)) {                                  
    Serial.println("Starting LoRa Failed");
    while (1);
  }

  LoRa.setSpreadingFactor(SF);
  LoRa.setSignalBandwidth(BW);
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
  Serial.print(" n_packSent: ");
  Serial.print(pacchetto.n_packSent);  
  Serial.print(" n_packReceived: ");
  Serial.print(n_packReceived);
  Serial.print(" PDR: ");
  Serial.print(PDR);    
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
  Serial.print(Rssi);
  Serial.print(" SNR:");
  Serial.print(Snr);
  
  Serial.println();
  
}

void serialWrite() {
      Serial.write((byte *)&buffer_pack, sizeof(pacchetto)); 
      Serial.write((byte *)&Rssi,2);
      Serial.write((byte *)&Snr,4);  
      Serial.write((byte *)&PDR,4);
  }
