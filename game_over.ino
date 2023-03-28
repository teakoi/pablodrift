void GameOver(){
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(46,20);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(6);
  tft.println("GAME OVER");
  
  tft.setCursor(26, 50);
  tft.setTextSize(4);
  tft.println("Press the Right button to try again")
  tft.setCursor(26,60);
  tft.println("Press the Left button to return to main menu");
   
  finished=millis();
  elapsed=finished-start;
  lcd.setCursor(0,7);
  lcd.print( (elapsed)//1000);
  
  if (digitalRead (ButtonDOWN) == LOW){
    MainMenuState = true;
    GameOverState = false;
  } 
  
  if (digitalRead(ButtonUP)==HIGH) {
    GameState = true;
    GameOverState = false;
  }
}
