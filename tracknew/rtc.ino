void clock_initialization() {
  Wire.beginTransmission(0x68);
  if (0)   // which=false -> 0x0e, true->0x0f.
    Wire.write(0x0f);
  else
    Wire.write(0x0e);
  Wire.write(0b11110111);
  Wire.endTransmission();

  clock.armAlarm1(false);           // Inizializzo le sveglie.
  clock.armAlarm2(false);           //          "
  clock.clearAlarm1();              //          "
  clock.clearAlarm2();              //          "
}

void setTime() {                                             // Confronta l'ora del GPS con quella dell'RTC. Se la differenza è maggiore di
  if (aggiornaOra){
    if ( abs(act_time.minute - gps.time.minute())) {           // un minuto aggiorna l'ora dell' RTC.
      Serial.println(F("Aggiorno orario!!!"));
      clock.setDateTime(2014, 4, 25, gps.time.hour(), gps.time.minute(), gps.time.second());
      act_time = clock.getDateTime();
      interruttori(); 
      delay(10);
    }
  }
}
