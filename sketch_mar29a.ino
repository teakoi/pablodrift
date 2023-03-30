#include <TFT_eSPI.h>
#include <EEPROM.h>
#include "game_bitmaps_again.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite img = TFT_eSprite(&tft);
TFT_eSprite under = TFT_eSprite(&tft);


#define TFTW 480 //screen width (x)
#define TFTH 320 //screen height (y)

#define TFThalfW 240 //half screen width (x)
#define TFThalfH 160 //half screen height (y)

const int ButtonUP = 2 ; //Right
const int ButtonDOWN = 3 ; //Left

int rect_x[24] = {480, 460, 440, 420, 400, 380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 40, 20};
int rect_y[2] = {138,182};


int PlayerX = 70;
int PlayerY = 145;
int carw = 34;
int carh = 30;
#define extra_y_space 6 
/* this is the extra TRANSPARENT space that
I've left above and below the car's bitmap//art.
This is the max speed that the car can move up and down without the car's body leaving a trail*/

int PlayerSpeed = 6;
int angle = 0;


int EnemyX = 480;
int EnemyX2 = 480;
int EnemyX3 = 480;
int EnemyX4 = 480;
int EnemyX5 = 480;
int EnemyX6 = 480;


int enemyw = 15; //(temp)
int enemyh = 15; //(temp)


int EnemySpeed = 3;

int randomEnemyYs[6]={104,118,149,163,190,200};
long randIndex = random(0,6);
int randElem = randomEnemyYs[randIndex];

int randomEnemyYs2[6]={104,118,149,163,190,200};
long randIndex2 = random(0,6);
int randElem2 = randomEnemyYs2[randIndex2];

int randomEnemyYs3[6]={104,118,149,163,190,200};
long randIndex3 = random(0,6);
int randElem3 = randomEnemyYs3[randIndex3];

int randomEnemyYs4[6]={104,118,149,163,190,200};
long randIndex4 = random(0,6);
int randElem4 = randomEnemyYs4[randIndex4];

int randomEnemyYs5[6]={104,118,149,163,190,200};
long randIndex5 = random(0,6);
int randElem5 = randomEnemyYs5[randIndex5];

int randomEnemyYs6[6]={104,118,149,163,190,200};
long randIndex6 = random(0,6);
int randElem6 = randomEnemyYs6[randIndex6];


// Check for collision between the player and the enemy
bool checkCollision() {
  // Calculate the actual height of the player (excluding transparent space)
  int playerActualH = carh - 6;

  if (PlayerX + carw >= EnemyX && PlayerX <= EnemyX + enemyw &&
      PlayerY + playerActualH >= randElem && PlayerY + 6 <= randElem + enemyh) {
    return true;
  }
  return false;
}

int score = 0;
int lastSpeedUpScore = 0;
int highestScore;
bool gameStarted = false;
bool MainMenuState=false;




void setup() {
  pinMode(ButtonUP, INPUT_PULLUP);
  pinMode(ButtonDOWN, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(1);

  // initialize random seed
  randomSeed(analogRead(0));


  //highestScore = EEPROM.read(0);

  
  Menu();


}


void loop() {

  while(gameStarted = true){

    static uint32_t oldtime=millis(); //uint32_t means unsigned long

    Lanes();


    tft.fillRect(EnemyX, randElem, enemyw, enemyh, TFT_BLACK);
    EnemyX = EnemyX - EnemySpeed;
    tft.fillRect(EnemyX-1, randElem, 1, enemyh, TFT_BLACK);
    tft.fillRect(EnemyX-1, randElem, enemyw, enemyh, TFT_BLUE);
    
    if ((millis()-oldtime)>= (10*1000)){
      tft.fillRect(EnemyX2, randElem2, enemyw, enemyh, TFT_BLACK);
      EnemyX2 = EnemyX2 - EnemySpeed;
      tft.fillRect(EnemyX2-1, randElem2, 1, enemyh, TFT_BLACK);
      tft.fillRect(EnemyX2, randElem2,enemyw,enemyh,TFT_CYAN);
    }


    if ((millis()-oldtime)>= (20*1000)){
      tft.fillRect(EnemyX3, randElem3, enemyw, enemyh, TFT_BLACK);
      EnemyX3 = EnemyX3 - EnemySpeed;
      tft.fillRect(EnemyX3-1, randElem3, 1, enemyh, TFT_BLACK);
      tft.fillRect(EnemyX3, randElem3,enemyw,enemyh,TFT_GREEN);
    }

    /*
    if (score > 15){
      tft.fillRect(EnemyX4, randElem4, enemyw, enemyh, TFT_BLACK);
      EnemyX4 = EnemyX4 - EnemySpeed;
      tft.fillRect(EnemyX4-1, randElem4, 1, enemyh, TFT_BLACK);
      tft.fillRect(EnemyX4, randElem4,enemyw,enemyh,TFT_YELLOW);
    }

    

    if (score > 20){
      tft.fillRect(EnemyX5, randElem5, enemyw, enemyh, TFT_BLACK);
      EnemyX5 = EnemyX5 - EnemySpeed;
      tft.fillRect(EnemyX5-1, randElem5, 1, enemyh, TFT_BLACK);
      tft.fillRect(EnemyX5, randElem5,enemyw,enemyh,TFT_RED);
    }
    

    if (lastEnemyTime >= (55*1000)){
      tft.fillRect(EnemyX6, randElem6, enemyw, enemyh, TFT_BLACK);

      EnemyX6 = EnemyX6 - EnemySpeed;

      tft.fillRect(EnemyX6-1, randElem6, 1, enemyh, TFT_BLACK);
      tft.fillRect(EnemyX6, randElem6,enemyw,enemyh,TFT_GREENYELLOW);
    }*/
    




    //Checks for collision
    if (checkCollision()){
      gameOver();
    }
    


    //Draws the Player's car
    drawPlayer();

    //After enemy has passed thru screen////
    if (EnemyX <= -enemyw){ //negative (enemywidth number)
    EnemyX = 480;
    //randomSeed(analogRead(0));
    randIndex = random(0,6);
    randElem = randomEnemyYs[randIndex];

    score++; //Increase score by one

    }

    if (EnemyX2 <=-enemyw){
      EnemyX2 = 480;

      //randomSeed(analogRead(0));
      randIndex2 = random(0,6);
      randElem2 = randomEnemyYs2[randIndex2];
      score++;
    }

    if (EnemyX3 <=-enemyw){
      EnemyX3 = 480;
      //randomSeed(analogRead(0));

      randIndex3 = random(0,6);
      randElem3 = randomEnemyYs3[randIndex3];
      score++;
    }

    if (EnemyX4 <=-enemyw){
      EnemyX4 = 480;
      //randomSeed(analogRead(0));

      randIndex4 = random(0,6);
      randElem4 = randomEnemyYs4[randIndex4];
      score++;
    }

    if (EnemyX5 <=-enemyw){
      EnemyX5 = 480;
      //randomSeed(analogRead(0));

      randIndex5 = random(0,6);
      randElem5 = randomEnemyYs5[randIndex5];
      score++;
    }

    if (EnemyX6 <=-enemyw){
      EnemyX6 = 480;
      //randomSeed(analogRead(0));

      randIndex6 = random(0,6);
      randElem6 = randomEnemyYs6[randIndex6];
      score++;
    }

    /////////

    //Controlling the Player's Car
    if (digitalRead (ButtonDOWN) == LOW){
    PlayerY = PlayerY + PlayerSpeed;
    angle = angle - 1;
    if (angle < -10){angle = -10;}
    }

    while( (digitalRead(ButtonDOWN)==HIGH) && angle < 0){
      angle++;
      if (angle>0){angle= 0;}
    }


    if (digitalRead (ButtonUP) == LOW){
    PlayerY= PlayerY - PlayerSpeed;
    angle = angle + 1;
    if (angle > 10){angle = 10;}
    }

    while( (digitalRead(ButtonUP)==HIGH) && angle > 0){
      angle--;
      if (angle<0){angle= 0;}
    }


    if (PlayerY > (226 - carh)) {
      PlayerY= (226 - carh);
      }
      
    if (PlayerY < 94) {
      PlayerY=(94);
      }

    
    //After each (number) points, increase the EnemySpeed
    if ((score - lastSpeedUpScore) ==5){
      lastSpeedUpScore = score;
      EnemySpeed++;
      if (EnemySpeed>9){ 
        EnemySpeed = 9;
        }
    }
  }

}

void initiateGame(){
  tft.fillScreen(TFT_BLACK);

  img.createSprite(carw, carh);
  under.createSprite(carw, carh);
  
  //Grass and red border:
  tft.fillRect(0,0,TFTW,94,TFT_DARKGREEN);
  tft.fillRect(0,226,TFTW,94,TFT_DARKGREEN);
  tft.fillRect(0,90,TFTW,4,TFT_RED);
  tft.fillRect(0,226,TFTW,4,TFT_RED);

  drawPlayer(); //Draws player's car

}


void drawPlayer(){
  img.pushImage(0,0,carw,carh,car);

  img.pushRotated(&under,angle);
  under.pushSprite(PlayerX,PlayerY);

}

void gameOver(){
  delay(1000);
  gameStarted = false;
  tft.fillScreen(TFT_PINK);
  tft.setCursor(48,20);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(6);
  tft.println("GAME OVER");

  tft.setCursor(48,100);
  tft.println(score);
  delay(6*1000);

  //resets the variables to start position values

  PlayerX = 70;
  PlayerY = 145;

  EnemyX = 480;
  EnemyX2 = 480;
  EnemyX3 = 480;
  EnemyX4 = 480;
  EnemyX5 = 480;
  EnemyX6 = 480;

  //randomSeed(analogRead(0));
  

  randIndex = random(0,6);
  randElem = randomEnemyYs[randIndex];

  randIndex2 = random(0,6);
  randElem2 = randomEnemyYs[randIndex2];

  randIndex3 = random(0,6);
  randElem3 = randomEnemyYs[randIndex3];

  randIndex4 = random(0,6);
  randElem4 = randomEnemyYs[randIndex4];

  randIndex5 = random(0,6);
  randElem5 = randomEnemyYs[randIndex5];

  randIndex6 = random(0,6);
  randElem6 = randomEnemyYs[randIndex6];


  score = 0;
  lastSpeedUpScore = 0;
  EnemySpeed = 3;


  //Return to main menu
  Menu();
}

void Lanes(){
  //lane animation
   // Clear the previous positions of the rectangles
  for (int i = 0; i < 24; i++) {
    tft.fillRect(rect_x[i], rect_y[0], 5, 2, TFT_BLACK);
    tft.fillRect(rect_x[i], rect_y[1], 5, 2, TFT_BLACK);
  }

  // Update the positions of the rectangles
  for (int i = 0; i < 24; i++) {
    rect_x[i] -= 5;
    if (rect_x[i] < 0) {
      rect_x[i] = TFTW;
    }
  }

  // Draw the rectangles at their new positions
  for (int i = 0; i < 24; i++) {
    tft.fillRect(rect_x[i], rect_y[0], 5, 2, TFT_WHITE);
    tft.fillRect(rect_x[i], rect_y[1], 5, 2, TFT_WHITE);
  }
}

void Racing(){
  
}

