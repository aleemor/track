void displayInfo(){

  printOled();
  
 // Serial.print(millis());
 // Serial.print(" ");
  oraRTC();
  Serial.print(F(" "));
  oraGPS();
  Serial.print(" CHAR:");
  Serial.print(gps.charsProcessed());
  //Serial.print(F(" fixLoc: "));
  //Serial.print(gps.location.isUpdated());
  //Serial.print(F(" fixTime: "));
  //Serial.print(gps.time.isUpdated());
  Serial.print(F(" SAT: "));
  Serial.print(gps.satellites.value());
  Serial.print(F(" LoRa:"));
  Serial.print(isLORAhour);
  Serial.print(F(" GPS:"));
  Serial.print(isGPShour);
  Serial.print(F(" SEND: "));
  Serial.print(LORA_interval);
  Serial.print(F(" n_packSent: "));
  Serial.print(pacchetto.n_packSent);
  Serial.print(F(" lat_1: "));
  Serial.print(pacchetto.lat_1);
  Serial.print(F(" lon_1: "));
  Serial.print(pacchetto.lon_1);
  Serial.print(F(" lat_2: "));
  Serial.print(pacchetto.lat_2);
  Serial.print(F(" lon_2: "));
  Serial.print(pacchetto.lon_2);
  Serial.print(F(" lat_3: "));
  Serial.print(pacchetto.lat_3);
  Serial.print(F(" lon_3: "));
  Serial.print(pacchetto.lon_3);     
  /*     
  Serial.print(F(" ID: "));
  Serial.print(pacchetto.id);
  Serial.print(F(" batteria: "));
  Serial.print(pacchetto.batt);
  Serial.print(F(" h_dop: "));
  Serial.print(pacchetto.h_dop);
  Serial.print(F(" count_reboot: "));
  Serial.println(count_reboot); */

  Serial.println();
}

void oraRTC() {
  Serial.print(F("RTC: "));
  Serial.print(act_time.hour);   Serial.print(F(":"));
  Serial.print(act_time.minute); Serial.print(F(":"));
  Serial.print(act_time.second); 
}

void oraGPS() {
  Serial.print(F("ora GPS: "));
  Serial.print(gps.time.hour());    Serial.print(F(":"));
  Serial.print(gps.time.minute());  Serial.print(F(":"));
  Serial.print(gps.time.second());  
}

void aggiorna_count_reboot() {

  EEPROM.get(12,count_reboot);
  count_reboot++;
  EEPROM.put(12,count_reboot);
  pacchetto.n_reboot = count_reboot;
}
