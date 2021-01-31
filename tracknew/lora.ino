void LORA_action() {
  if (isLORAhour) {
  LoRa.sleep();
  if (LORA_interval) {
    if (millis() >= prev_send + FREQUENZA_INVIO) {
      pacchetto.batt = analogRead(A0);                                 // aggiungi controllo
      pacchetto.sec = millis()/1000;
      pacchetto.preambolo = preamb;
      recupera_da_EEPROM();
      LORA_send();
      LoRa.sleep();
      prev_send = millis();
    }
  }
  else {
    if ( (act_time.hour == LORA_stop_hour) && (act_time.minute >= LORA_stop_minute) ) {
      Serial.println(F("Ho fatto, dormo"));
      isLORAhour = false;
      TurnOFF();
    }
  }
}
}

void LORA_send() {
  Serial.println(F("Invio"));
  LoRa.beginPacket();
  LoRa.write((byte *)&pacchetto, sizeof(pacchetto));
  LoRa.endPacket();
  //LoRa.sleep();
}

void  LORA_initialization() {
  if (!LoRa.begin(frequency)) {                                   // verifico collegamenti LoRa
    Serial.println("Starting LoRa Failed");
    while (1);
  }
  LoRa.setSpreadingFactor(SF);
  LoRa.setSignalBandwidth(BW);
  LoRa.setCodingRate4(codingRateDenominator);
  LoRa.setTxPower(0, 1);
}

void recupera_da_EEPROM() {
  EEPROM.get(0,pacchetto.lat_1);
  EEPROM.get(2,pacchetto.lon_1);
  EEPROM.get(4,pacchetto.lat_2);
  EEPROM.get(6,pacchetto.lon_2);  
  EEPROM.get(8,pacchetto.lat_3);
  EEPROM.get(10,pacchetto.lon_3);
}
