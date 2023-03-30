int button_D_clicked = 0; // only perform action when button is clicked, and wait until another press
int button_U_clicked = 0; // same as above

int item_selected = 0; // which item in the menu is selected
int item_sel_previous; // previous item - item before the sleceted one
int item_sel_next; // next item - item ater the selected one

int menuX[2] = {158,250};
int menuY = 72;

// ' item_selected_background', 72x24px
const unsigned char item_selected_background [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x10, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x08, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x04, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const int NUM_ITEMS = 2;
char menu_items[NUM_ITEMS] [7] = {
  {"START"},
  {"?????"}
};

void Menu(){

  MainMenuState=true;
  tft.fillScreen(TFT_CYAN);
  
  //title:
  tft.fillRect(38,10,404,50,TFT_DARKCYAN);
  tft.drawRect(36,8,408,54,TFT_BLACK);
  tft.setCursor(46,14);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(6);
  tft.println("PABLO DRIFT");

  tft.setCursor(200,120);
  tft.setTextColor(TFT_DARKCYAN);
  tft.setTextSize(3);
  tft.println("LITE");
  

  //grass:
  tft.fillRect(0,168,480,152,TFT_GREEN);

  //PABLO:
  tft.fillRect(90,280,60,20,TFT_ORANGE);
  tft.fillRect(96,112,10,20,TFT_NAVY);
  tft.fillTriangle(129, 180, 130, 200, 180, 190, TFT_ORANGE);
  tft.fillEllipse(100,210,30,80,TFT_BLUE);
  tft.fillEllipse(110,170,10,20,TFT_WHITE);
  tft.fillEllipse(115,178,5,10,TFT_BLACK);


  //menu stuff:
  tft.fillRect(menuX[0],menuY,72,24,TFT_BLACK);
  tft.fillRect(menuX[1],menuY,72,24,TFT_BLACK);

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  tft.setCursor(menuX[0]+7, menuY+5);
  tft.println(menu_items[0]);

  tft.setCursor(menuX[1]+7, menuY+5);
  tft.println(menu_items[1]);

  tft.drawBitmap(menuX[0],menuY,item_selected_background,72,24,TFT_WHITE);

  //Music();

  while (MainMenuState = true) {

    if ((digitalRead(ButtonDOWN) == LOW) && (button_D_clicked == 0)) { // down button clicked - jump to next menu item
    item_selected = item_selected + 1; // select next item
    button_D_clicked = 1; // set button to clicked to only perform the action once

    tft.drawBitmap(menuX[0],menuY,item_selected_background,72,24,TFT_BLACK);
    tft.drawBitmap(menuX[1],menuY,item_selected_background,72,24,TFT_WHITE);

    if (item_selected >= NUM_ITEMS) { // last item was selected, jump to first menu item
      item_selected = 0;

      tft.drawBitmap(menuX[0], menuY, item_selected_background,72,24,TFT_WHITE);
      tft.drawBitmap(menuX[1], menuY, item_selected_background,72,24,TFT_BLACK);

      }
    } 

    if ((digitalRead(ButtonDOWN) == HIGH) && (button_D_clicked == 1)) { // unclick 
    button_D_clicked = 0;
    }


    if ((digitalRead(ButtonUP) == LOW) && (button_U_clicked == 0)) { // select button clicked
     button_U_clicked = 1; // set button to clicked to only perform the action once
     if (item_selected == 0) {
       //*****insert what happens when the start option is chosen*****
       initiateGame();
       break;
       //tft.fillScreen(TFT_BLUE);
     }
     else if (item_selected == 1) {
       //****insert what happens when the 2nd option is choses****
       tft.fillScreen(TFT_YELLOW);
       } 
    }
    if ((digitalRead(ButtonUP) == HIGH) && (button_U_clicked == 1)) { // unclick
    button_U_clicked = 0;
    }


    // set correct values for the previous and next items
    item_sel_previous = item_selected - 1;
    if (item_sel_previous < 0) {item_sel_previous = NUM_ITEMS - 1;} // previous item would be below first = make it the last
    item_sel_next = item_selected + 1;  
    if (item_sel_next >= NUM_ITEMS) {item_sel_next = 0;} // next item would be after last = make it the first

    }
}