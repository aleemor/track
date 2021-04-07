//  Alessandro Moretti
//
// Connessioni:
//             GPS ----- Arduino           RFM9x ----- Arduino               DS3231 ----- Arduino
//
//             VIN ----- 5V                VIN   ----- ICSP 2  ( 5V )          VCC  ----- 5V
//             GND ----- GND               GND   ----- ICSP 6  ( GND )         GND  ----- GND
//             TX  ----- D9                SCK   ----- ICSP 3  ( D13 )         SDA  ----- SDA
//             RX  ----- D8                MISO  ----- ICSP 1  ( D12 )         SCL  ----- SCL
//             EN  ----- D7                MOSI  ----- ICSP 4  ( D11 )         SQW  ----- D2
//                                         CS    ----- D10
//

#include "track.h"

void setup() {
  Serial.begin(115200);
  clock.begin();
  GPS_serial.begin(9600);

  aggiorna_count_reboot();
  
  //canc_pack_daEEPROM();

  pacchetto.id = ID;


  pinMode(GPS_EN_pin, OUTPUT);                              // Enable pin del GPS.
  pinMode(wakePin, INPUT);                                  // Il pin 2 è utlizzato per l'interrupt.

  clock_initialization();
  LORA_initialization();
  oled_initialization();

  clock.setDateTime(2016, 9, 30, setStartHour, setStartMin, setStartSec);
  
  delay(100);
  
  Serial.println(F("\nRTC_SLEEP_GPS_LORA\n"));
  
}

void loop() {
  act_time = clock.getDateTime();                           // Prendo l'orario dall'RTC
  interruttori();                                           // Controllo se è ora di accendere GPS e LoRa;
  clock.setAlarm2(0, 0, wake_minute,  DS3231_MATCH_M);      // Attivo l' interrupt al primo minuto di ogni ora.
  info_every_sec();                                         // Stampo informazioni ogni secondo
  GPS_action();
  LORA_action();
  TurnOFF();
  delay(10);
}

void info_every_sec() {
  if ( millis() >= prev_info + 1000) {
    prev_info = millis();
    displayInfo();
  }
}


void interruttori() {
  if ( (act_time.hour == FIX_1) || (act_time.hour == FIX_2) || (act_time.hour == FIX_3) ) {
    isGPShour = true;
  }
  else {
    isGPShour = false;
  }
  

  if ( (act_time.hour == LORA_start_hour) || (act_time.hour == LORA_stop_hour)  ) {    
    isLORAhour = true;

    if (LORA_start_hour == LORA_stop_hour) {
      if ((act_time.minute >= LORA_start_minute) && (act_time.minute < LORA_stop_minute)) {
        LORA_interval = true;
      }
      else {
        LORA_interval = false;
      }
    }

    else {
      if ( (act_time.hour == LORA_start_hour) && ( act_time.minute >= LORA_start_minute ) ) {
        LORA_interval = true;
      }
      else if ( (act_time.hour == LORA_stop_hour) && ( act_time.minute < LORA_stop_minute ) ) {
        LORA_interval = true;
      }
      else {
        LORA_interval = false;
      }

    }
  }
}

void TurnOFF() {
  if (!isGPShour && !isLORAhour ) {
    gpsOFF();
    Serial.println(F("Dormo."));
    displayInfo();
    delay(100);
    sleep_enable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);                              // Configuro la modalità "power down" che massimizza il risparmio di energia
    attachInterrupt(digitalPinToInterrupt(2), WakeUP, FALLING);       // Gestione dell'interrupt.
    sleep_cpu();                             // Addormento la CPU.
    //
    //*****Da qui arduino ricomincia quando si sveglia*****
    //

    clock.clearAlarm2();                                              // elimina l'allarme (per evitare ulteriori indesiderati interrupt)
    act_time = clock.getDateTime();
    interruttori(); 
    displayInfo();
  }
}

void WakeUP() {                                                       // disabilita la modalità sleep
  Serial.println(F("Sveglio"));
  sleep_disable();
  //detachInterrupt(0);
}
