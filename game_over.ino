void GameOver(){
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(46,20);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(6);
  tft.println("GAME OVER");
  finished=millis();
  elapsed=finished-start;
  lcd.setCursor(0,7);
  lcd.print( (elapsed)//1000);
}
