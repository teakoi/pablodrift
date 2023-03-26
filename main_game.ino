#include <TFT_eSPI.h>
#include "carbitmap.h"
#include "pitches.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite img = TFT_eSprite(&tft);
TFT_eSprite under = TFT_eSprite(&tft);
TFT_eSprite enemy = TFT_eSprite(&tft);

#include <LiquidCrystal.h> 

int Contrast=75;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);  


#define WIDTH  480
#define HEIGHT 320

int carw = 34;
int carh = 30;

#define truckh 21
#define truckw 34

int angle = 0;

#define extra_y_space 6 
/* this is the extra TRANSPARENT space that
I've left above and below the car's bitmap//art.
This is the max speed that the car can move up and down without the car's body leaving a trail*/
int PlayerSpeed = extra_y_space; //max player speed incriment (+-y) is = to extxra y space


int PlayerX = (WIDTH/2) - (carw/2);
int PlayerY = (HEIGHT/2 - (carh/2));

const int ButtonUP = 2 ;
const int ButtonDOWN = 3 ;


const unsigned long HOLD_TIME = 5000; // hold time in milliseconds

unsigned long ButtonUPStartTime = 0;
unsigned long ButtonDOWNStartTime = 0;

bool ButtonUPPressed = false;
bool ButtonDOWNPressed = false;


int rect_x[24] = {480, 460, 440, 420, 400, 380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 40, 20};
int rect_y[4] = {94,138,182,226};


int EnemyX = 480;
int EnemyY[4] = {94, 138, 182, 226};
int EnemySpeed = 1;

bool MainMenuState = false;
/*when main menu is true, display main menu
when false, hide main menu*/
bool GameState = false;
/*when gamestate is true, start game
when false, save and display the losing game screen
end game*/

bool PauseState = false;
/* when pause is true, save and pause game, display pause screen
when false, game runs*/

//Add code for main menu to run while menu state = 1

void setup() {

  pinMode(ButtonUP, INPUT_PULLUP);
  pinMode(ButtonDOWN, INPUT_PULLUP);
  
  tft.begin();
  tft.setRotation(1);
  analogWrite(13,Contrast);
  lcd.begin(16, 7);

  Menu();

  if (GameState = true){
    MainMenuState = false;

    img.createSprite(carw, carh);
    under.createSprite(carw, carh);
    enemy.createSprite(truckw, truckh);

    //Draws the bg:
    DrawRoad();
    tft.fillRect(0,0,WIDTH,50,TFT_DARKGREEN);
    tft.fillRect(0,270,WIDTH,50,TFT_DARKGREEN);

    tft.fillRect(0,46,WIDTH,4,TFT_RED);
    tft.fillRect(0,270,WIDTH,4,TFT_RED);

    //So I can see where the center of the screen is:
    /*tft.drawFastVLine ( tft.width()/2, 0, HEIGHT, TFT_BLUE );
    tft.drawFastHLine ( 0,tft.height()/2, WIDTH, TFT_BLUE );*/

    //rotation (drifting)
    tft.setPivot(240, (tft.height()/2));
    /* rotation works but leaves bits of car trail at corners*/

  }

}







/*dont do under set swap bytes when bitmap is 16bit colour
when bitmap is 16bit colour, you can leave transparent as transparent in the pixel art, 
and no need to call colour with the function, nor to fill sprite. both do nothing*/

void loop(){

  while (GameState = true){
    bool ButtonUPState = digitalRead(ButtonUP) == LOW;
    bool ButtonDOWNState = digitalRead(ButtonDOWN) == LOW;

    Enemy();
    //for some reason the enemy code doesnt work ;-;,,, gotta fix that.

    Lanes();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Score:");
    lcd.setCursor(0, 1);
    lcd.print("Highscore:");
    
    if (digitalRead (ButtonUP) == LOW){
    PlayerY = PlayerY + PlayerSpeed;
    angle = angle - 1;
    if (angle < -10){angle = -10;}
    }

    while( (digitalRead(ButtonUP)==HIGH) && angle < 0){
      angle++;
      if (angle>0){angle= 0;}
    }


    if (digitalRead (ButtonDOWN) == LOW){
    PlayerY= PlayerY - PlayerSpeed;
    angle = angle + 1;
    if (angle > 10){angle = 10;}
    }
    while( (digitalRead(ButtonDOWN)==HIGH) && angle > 0){
      angle--;
      if (angle<0){angle= 0;}
    }


    if (PlayerY > (270 - carh)) {
      PlayerY= (270 - carh);
      }
      
    if (PlayerY < 50) {
      PlayerY=(50);
      }
    
    if (PlayerX < 0){
      //insert game over stuff
      DrawRoad();
      PlayerX = ((WIDTH/2)- (carw/2));
    }

    //Pause function stuff:

    // handle up button
    if (ButtonUPState && !ButtonUPPressed) {
      ButtonUPPressed = true;
      ButtonUPStartTime = millis();
    } else if (!ButtonUPState && ButtonUPPressed) {
      ButtonUPPressed = false;
      ButtonUPStartTime = 0;
    }
    
    // handle down button
    if (ButtonDOWNState && !ButtonDOWNPressed) {
      ButtonDOWNPressed = true;
      ButtonDOWNStartTime = millis();
    } else if (!ButtonDOWNState && ButtonDOWNPressed) {
      ButtonDOWNPressed = false;
      ButtonDOWNStartTime = 0;
    }
    
    // check if both buttons are held down for HOLD_TIME milliseconds
    if (ButtonUPPressed && ButtonDOWNPressed &&
        millis() - ButtonUPStartTime >= HOLD_TIME &&
        millis() - ButtonDOWNStartTime >= HOLD_TIME) {
      // run pause function
      GameState = 0;
      PauseState = 1;
      //change the pause state if they continue game or quit
      Pause();
    }
    //End Pause code section


    //player:
    img.pushImage(0,0,carw,carh,car3);

    img.pushRotated(&under,angle);
    under.pushSprite(PlayerX,PlayerY);


    //CheckCollision();

  }

}

////////////////


void Enemy(){

  for (int i: EnemyY){
    enemy.pushImage(EnemyX,EnemyY[i], truckw, truckh, truck);
  }

  EnemyX = EnemyX-EnemySpeed;
  if (EnemyX < 0) {
    //cover the left end of the road with black to coverup the enemy image instead of resetting the whole road
    tft.fillRect(0,50,40, 220,TFT_BLACK);

    EnemyX = 480;
  }

}


void CheckCollision(){
  int PlayerBottomLeft = PlayerY + carh;



  //enemy on top:
  if (PlayerX <= EnemyX && (PlayerX +carw) <= (EnemyX + truckw) &&
      PlayerY <= (EnemyY + truckh)) {
      PlayerY = (EnemyY + truckh);}
  //enemy below
  else if (PlayerX <= EnemyX && (PlayerX +carw) <= (EnemyX + truckw) &&
      (PlayerY + carh) >= EnemyY) {
      PlayerBottomLeft = EnemyY; }
  //enemy on front from top
  else if (PlayerY >= EnemyY &&
          (PlayerY + carh)  >= (EnemyY + carh) &&
          (EnemyX <= (PlayerX + carw))) {
          PlayerX = PlayerX - 1; }
  // enemy on front from below
  else if (PlayerY >= EnemyY &&
          (PlayerY + carh) <= (EnemyY + truckh) &&
          (EnemyX <= (PlayerX + carw))) {
          PlayerX = PlayerX -1; }
}

