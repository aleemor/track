#include <DS3231.h>
#include <Wire.h>
#include <avr/sleep.h>
#include <TinyGPS++.h>
#include <AltSoftSerial.h>
#include <SPI.h>
#include <LoRa.h>
#include <EEPROM.h>

#include "ssd1306.h"



DS3231 clock;
RTCDateTime act_time;
TinyGPSPlus gps;
AltSoftSerial GPS_serial;

uint16_t ID = 1;                               // Identificativo.
uint16_t GPS_ROTTO = 55555;                    // Messaggio di errore per GPS rotto.
const float NO_FIX_POS = 33.333;               // Messaggio di errore per fix della posizione.

int count_reboot;

uint16_t n_packSent = 0;

bool isGPShour;                                // isGPStime = true se è ora di usare il GPS.
bool isLORAhour;                               // isGPStime = true se è ora di usare il LoRa.                            
bool LORA_interval;                            // timeOfSendig = true se sono nell'intervallo di visibilità


#define preamb 77
#define FREQUENZA_INVIO  3000                  // In millisecondi 

#define num_sats_min  5                        // Numero di satelliti che voglio per prendere la posizione
#define wake_minute  0                         // Minuto dell'ora in cui sveglio Arduino.
#define GPS_EN_pin  7                          // Enable pin del GPS.
#define wakePin  2                             // Il pin 2 è utlizzato per l'interrupt.

#define  LORA_start_hour  14                    // Intervallo invio pacchetto: 
#define  LORA_stop_hour  14                     // ( ORA_LORA_1 : MINUTE_INF ---- ORA_LORA_2 : MINUTE_SUP )
#define  LORA_start_minute 3                 
#define  LORA_stop_minute  23    

#define frequency 915E6
#define SF 12                                   // Spreading Factor
#define BW 125E3                                // Bandwith
#define codingRateDenominator  5            
#define txPwr 5

#define aggiornaOra 1
#define UTC 1

#define setStartHour 14
#define setStartMin  59
#define setStartSec  50


#define FIX_1  15                              // Ora in cui raccolgo la prima posizione.
#define FIX_2  17                              // Ora in cui raccolgo la seconda posizione.
#define FIX_3  19                              // Ora in cui raccolgo la terza posizione.
#define minute_fix_sat   7                     // Minuti massimi per ottenere NUM_SATS satelliti.
#define minute_fix_pos   5                     // Minuti massimi per ottenere la posizione dal satellite.

uint64_t prev_info;                            // Mi serve per stampare a seriale.
uint64_t prev_send;                            // Mi serve per inviare.

struct dati{ 
  uint8_t preambolo;
  uint8_t n_reboot;
  uint8_t batt;
  uint8_t h_dop;
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
