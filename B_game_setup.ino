
void DrawRoad(){
  // bg road
  tft.fillRect(0,50,WIDTH,220,TFT_BLACK);

}

void Lanes(){
  //lane animation
   // Clear the previous positions of the rectangles
  for (int i = 0; i < 24; i++) {
    tft.fillRect(rect_x[i], rect_y[0], 5, 2, TFT_BLACK);
    tft.fillRect(rect_x[i], rect_y[1], 5, 2, TFT_BLACK);
    tft.fillRect(rect_x[i], rect_y[2], 5, 2, TFT_BLACK);
    tft.fillRect(rect_x[i], rect_y[3], 5, 2, TFT_BLACK);
  }

  // Update the positions of the rectangles
  for (int i = 0; i < 24; i++) {
    rect_x[i] -= 5;
    if (rect_x[i] < 0) {
      rect_x[i] = WIDTH;
    }
  }

  // Draw the rectangles at their new positions
  for (int i = 0; i < 24; i++) {
    tft.fillRect(rect_x[i], rect_y[0], 5, 2, TFT_WHITE);
    tft.fillRect(rect_x[i], rect_y[1], 5, 2, TFT_WHITE);
    tft.fillRect(rect_x[i], rect_y[2], 5, 2, TFT_WHITE);
    tft.fillRect(rect_x[i], rect_y[3], 5, 2, TFT_WHITE);
  }
}


void Pause(){
  tft.fillRect(20,20,440,280,TFT_DARKGREY);
  tft.fillRect(110,110,10,20,TFT_WHITE);
  tft.fillRect(120,110,10,20,TFT_WHITE);
  //(+smthn to save score?)
}


