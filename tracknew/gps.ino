void GPS_action() {
  if ( isGPShour ) {
    LoRa.sleep();
    gpsON();                        
    getGPS();
    if (gps.location.isUpdated()) {
      setTime();
      delay(10);
      if (gps.satellites.value() >= num_sats_min ) {
        dataToPack(gps.location.lat(), gps.location.lng());
        gpsOFF();
        TurnOFF();
      }
      else {
        if (act_time.minute >= minute_fix_sat) {
          Serial.println(F("Troppo tempo per ottenere il numero di satelliti che voglio."));
          dataToPack(gps.location.lat(), gps.location.lng());
          gpsOFF();
          TurnOFF();
        }
      }
    }
    else {
      if (act_time.minute >= minute_fix_pos) {
        Serial.println(F("Troppo tempo per fixare la posizione."));
        dataToPack(NO_FIX_POS, NO_FIX_POS);
        Serial.print(pacchetto.lat_1);
        gpsOFF();
        TurnOFF();
      }
    }
  }
}

void getGPS() {
  while (GPS_serial.available() > 0) {
    if (gps.encode(GPS_serial.read())) {
    }
  }
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS detected: check wiring."));
    pacchetto.batt = GPS_ROTTO;
    digitalWrite(GPS_EN_pin, LOW);
    isGPShour = false;
    TurnOFF();
  }
}

void gpsON(){
  digitalWrite(GPS_EN_pin, HIGH);  
}

void gpsOFF(){
  digitalWrite(GPS_EN_pin, LOW);
  isGPShour = false;
}

void dataToPack(float lat_f, float lon_f) {
  pacchetto.h_dop = (int)(gps.hdop.hdop()) * 10;
  switch (act_time.hour) {
    case FIX_1:
      pacchetto.lat_1 = (int)(lat_f * 1000);
      pacchetto.lon_1 = (int)(lon_f * 1000);
      EEPROM.put(0,pacchetto.lat_1);
      EEPROM.put(2,pacchetto.lon_1);
      
      break;
    case FIX_2:
      pacchetto.lat_2 = (int)(lat_f * 1000);
      pacchetto.lon_2 = (int)(lon_f * 1000);
      EEPROM.put(4,pacchetto.lat_2);
      EEPROM.put(6,pacchetto.lon_2);
      break;
    case FIX_3:
      pacchetto.lat_3 = (int)(lat_f * 1000);
      pacchetto.lon_3 = (int)(lon_f * 1000);
      EEPROM.put(8,pacchetto.lat_3);
      EEPROM.put(10,pacchetto.lon_3);
      break;
  }
}

void canc_pack_daEEPROM() {
  EEPROM.put(0,0);
  EEPROM.put(2,0);
  EEPROM.put(4,0);
  EEPROM.put(6,0);  
  EEPROM.put(8,0);
  EEPROM.put(10,0);
  }
