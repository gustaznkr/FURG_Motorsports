void Display() {
  
  SPI.setModule(2);
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(3);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(8);
  tft.println("FURG MOTORSPORT!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(3);
  tft.println("27/07/2020");

}

