void oled_initialization(){
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_128x64_i2c_init();
    ssd1306_clearScreen();
    ssd1306_printFixed(40,0 , "Wildtrack", STYLE_NORMAL);
    ssd1306_printFixed(0,32 , "GPS: ", STYLE_NORMAL);
    ssd1306_printFixed(0,40 , "LoRa: ", STYLE_NORMAL);
    ssd1306_printFixed(0,48 , "Send: ", STYLE_NORMAL);
}

void printOled(){

  char ore [10];
  char minuti [10];
  char secondi [10];
  
  sprintf (ore, "%d", int(act_time.hour));
  sprintf (minuti, "%d", int(act_time.minute));
  sprintf (secondi, "%d", int(act_time.second));


  ssd1306_printFixed(0,16 , "                    ", STYLE_NORMAL);
  ssd1306_printFixed(0,16 , "ora: ", STYLE_NORMAL);
  ssd1306_printFixed(25,16 , ore, STYLE_NORMAL);
  ssd1306_printFixed(40,16 , minuti, STYLE_NORMAL);
  ssd1306_printFixed(55,16 , secondi, STYLE_NORMAL);
  
  if (isGPShour){
    ssd1306_printFixed(40,32 , "   ", STYLE_NORMAL);
    ssd1306_printFixed(40,32 , "ON", STYLE_NORMAL);
  }
  else {
     ssd1306_printFixed(40,32 , "  ", STYLE_NORMAL);
     ssd1306_printFixed(40,32 , "OFF", STYLE_NORMAL);
  }

  if (isLORAhour){
    ssd1306_printFixed(40,40 , "   ", STYLE_NORMAL);
    ssd1306_printFixed(40,40 , "ON", STYLE_NORMAL);
  }
  else {
     ssd1306_printFixed(40,40 , "  ", STYLE_NORMAL);
     ssd1306_printFixed(40,40 , "OFF", STYLE_NORMAL);
  }

  if (LORA_interval){
    ssd1306_printFixed(40,48 , "   ", STYLE_NORMAL);
    ssd1306_printFixed(40,48 , "ON", STYLE_NORMAL);
  }
  else {
     ssd1306_printFixed(40,48 , "  ", STYLE_NORMAL);
     ssd1306_printFixed(40,48 , "OFF", STYLE_NORMAL);
  }
  
}
