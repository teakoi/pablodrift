boolean CheckCollision(){

  boolean result = false
  if ((EnemyX >= PlayerX && EnemyX <= (PlayerX +carw)) &&
        (EnemyY >= (PlayerY-carh) && EnemyY <= (PlayerY))) {
          result = true;
        }
  return result;
}

