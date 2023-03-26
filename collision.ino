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

