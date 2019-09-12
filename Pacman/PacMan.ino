//LET THIS BE IN THIS ORDER!!
#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
//END OF ZONE

int joystickButton = A13;
int joystickXAxis = A14;
int joystickYAxis = A15;

int valueButton = 0;
int valueX = 0;
int valueY = 0;

float moveX = 237.7;
float moveY = 206;

bool walkableUP = true;
bool walkableDOWN = true;
bool walkableLEFT = true;
bool walkableRIGHT = true;
bool lockAxisX = false;
bool lockAxisY = false;

int worldLeft = 125;
int worldTop = 5;
int worldRight = 360;
int worldBottom = 267;

int mapLayout[868];
int mapCollision[28][31];

int pacmanPosX = 13;
int pacmanPosY = 23;
float pacmanMoveSpeed = 8.72;
//int movesInTile = 5;

//GHOST A
int ghostAPosX = 13;
int ghostAPosY = 11;
float ghostAMoveX = 237.7;
float ghostAMoveY = 101.6;
int ghostACurrentDir = 1;
bool ghostACaught = false;

//GHOST B
int ghostBPosX = 13;
int ghostBPosY = 11;
float ghostBMoveX = 237.7;
float ghostBMoveY = 101.6;
int ghostBCurrentDir = 3;
bool ghostBCaught = false;

//GHOST C
int ghostCPosX = 13;
int ghostCPosY = 11;
float ghostCMoveX = 237.7;
float ghostCMoveY = 101.6;
int ghostCCurrentDir = 3;
bool ghostCCaught = false;

//GHOST D
int ghostDPosX = 13;
int ghostDPosY = 11;
float ghostDMoveX = 237.7;
float ghostDMoveY = 101.6;
int ghostDCurrentDir = 1;
bool ghostDCaught = false;

bool powerUpActive = false;
int powerTimerStart = 100;
int powerTimerLeft = 100;

float coinStartPosX = 132.5 - 8;
float coinStartPosY = 5;
float coinPosX = 0;
float coinPosY = 0;

int pointsLeft = 0;
int pacmanLifes = 3;
float lifeStatPosX = 30;
float lifeStatPosY = 250;
bool victory = false;

//TODO LIST CREATED 21/10, 14:05

//TODO: SMOOTHEN MOVEMENT
//TODO: IMPLEMENT SPRITES OF GHOSTS
//TODO: IMPLEMENT SOME SOUND AT ALL
//TODO: TURN IN THE PROJECT AND MOVE ON WITH YOUR LIFE
//TODO: GET SOME SLEEP

void setup()
{
  // put your setup code here, to run once:

  /* BUTTON = A13
     X-AXIS = A14
     Y-AXIS = A15
  */

  //MAP COLLISION, map is 28x31
  String level =
 //         1111111111222222222
 //1234567890123456789012345678
  "############################"//1
  "#............##............#"//2
  "#.####.#####.##.#####.####.#"//3
  "#*####.#####.##.#####.####*#"//4
  "#.####.#####.##.#####.####.#"//5
  "#..........................#"//6
  "#.####.##.########.##.####.#"//7
  "#.####.##.########.##.####.#"//8
  "#......##....##....##......#"//9
  "######.##### ## #####.######"//10
  "######.##### ## #####.######"//11
  "######.##          ##.######"//12
  "######.## ######## ##.######"//13
  "######.## ######## ##.######"//14
  "      .   ########   .      "//15
  "######.## ######## ##.######"//16
  "######.## ######## ##.######"//17
  "######.##          ##.######"//18
  "######.## ######## ##.######"//19
  "######.## ######## ##.######"//20
  "#............##............#"//21
  "#.####.#####.##.#####.####.#"//22
  "#.####.#####.##.#####.####.#"//23
  "#*..##.......  .......##..*#"//24
  "###.##.##.########.##.##.###"//25
  "###.##.##.########.##.##.###"//26
  "#......##....##....##......#"//27
  "#.##########.##.##########.#"//28
  "#.##########.##.##########.#"//29
  "#..........................#"//30
  "############################";//31

  Serial.begin(9600);

  char tileData = 0;
  int arrayX = 0;
  int arrayY = 0;
  for(int i = 0 ; i < level.length() ; i++)
  {
    tileData = level.charAt(i);
    
    if (tileData == ' ')
    {
      mapCollision[arrayX][arrayY] = 1;
    }

    else if(tileData == '#')
    {
      mapCollision[arrayX][arrayY] = 0;
    }

    else if(tileData == '.')
    {
      mapCollision[arrayX][arrayY] = 3;
    }

    else if(tileData == '*')
    {
      mapCollision[arrayX][arrayY] = 7;
    }

    if(arrayX >= 28)
    {
      arrayX = 0;
      arrayY += 1;
    }
    
    arrayX += 1;
  }

  randomSeed(analogRead(A10));

  GD.begin();
  GD.cmd_loadimage(0, 0);
  GD.load("levelOne.jpg");
}

void loop()
{
  while(victory == false && pacmanLifes > 0)
  {
    GD.Clear();
    
    worldCollision();
    
    // put your main code here, to run repeatedly:
    valueX = analogRead(joystickXAxis);
  
    delay(100);
  
    valueY = analogRead(joystickYAxis);
  
    GD.Begin(BITMAPS);

    if(powerUpActive == true)
    {
      powerTimerLeft -= 1;
      GD.ColorRGB(GD.random(255), GD.random(255), GD.random(255));
      
      if(powerTimerLeft <= 0)
      {
        powerUpActive = false;
        powerTimerLeft = powerTimerStart;
      }
    }
    
    GD.Vertex2ii(480 / 4, 0);

    mapUpdate();

    //PACMAN
    GD.Begin(POINTS);
    GD.PointSize(16 * 7);
    GD.ColorRGB(255, 255, 0);
    GD.Vertex2ii(moveX, moveY);

    //GHOST A
    GD.ColorRGB(255, 0, 0);
    GD.Vertex2ii(ghostAMoveX, ghostAMoveY);

    //GHOST B
    GD.ColorRGB(50, 50, 255);
    GD.Vertex2ii(ghostBMoveX, ghostBMoveY);

    //GHOST C
    GD.ColorRGB(255, 50, 50);
    GD.Vertex2ii(ghostCMoveX, ghostCMoveY);
    
    //GHOST D
    GD.ColorRGB(255, 150, 0);
    GD.Vertex2ii(ghostDMoveX, ghostDMoveY);

    movePacman();
    moveGhostA();
    moveGhostB();
    moveGhostC();
    moveGhostD();
    
    GD.swap();
  }

  if(pacmanLifes <= 0)
  {
    GD.ClearColorRGB(0x103000);
    GD.Clear();
    GD.cmd_text(240, 136, 31, OPT_CENTER, "GAME OVER");
    //GD.cmd_text(240, 156, 31, OPT_CENTER, "Score: ");
    GD.swap(); 
  }

  else if(victory == true)
  {
    GD.ClearColorRGB(0x103000);
    GD.Clear();
    GD.cmd_text(240, 136, 31, OPT_CENTER, "VICTORY");
    //GD.cmd_text(240, 156, 31, OPT_CENTER, "Score: ");
    GD.swap(); 
  }
}

void ResetCharacters()
{
  moveX = 237.7;
  moveY = 206;
  pacmanPosX = 13;
  pacmanPosY = 23;
  
  ghostAPosX = 13;
  ghostAPosY = 11;
  ghostAMoveX = 237.7;
  ghostAMoveY = 101.6;
  ghostACurrentDir = 1;

  ghostBPosX = 13;
  ghostBPosY = 11;
  ghostBMoveX = 237.7;
  ghostBMoveY = 101.6;
  ghostBCurrentDir = 3;

  ghostCPosX = 13;
  ghostCPosY = 11;
  ghostCMoveX = 237.7;
  ghostCMoveY = 101.6;
  ghostCCurrentDir = 3;

  ghostDPosX = 13;
  ghostDPosY = 11;
  ghostDMoveX = 237.7;
  ghostDMoveY = 101.6;
  ghostDCurrentDir = 1;
}

void mapUpdate()
{
  coinPosX = coinStartPosX;
  coinPosY = coinStartPosY;

  GD.Begin(POINTS);
  GD.PointSize(16 * 7);
  GD.ColorRGB(255, 255, 0);

  for(int a = 0 ; a < pacmanLifes ; a++)
  {
    GD.Vertex2ii(lifeStatPosX + (a * 20), lifeStatPosY);
  }
  
  GD.ColorRGB(255, 255, 255);

  //If you get caught by the Ghosts
  if((moveX + 3 > ghostAMoveX && moveY + 3 > ghostAMoveY) && (moveX - 3 < ghostAMoveX && moveY - 3 < ghostAMoveY) && powerUpActive == false)
  { 
    pacmanLifes -= 1;
    ResetCharacters();
    return;
  }

  if((moveX + 3 > ghostAMoveX && moveY + 3 > ghostAMoveY) && (moveX - 3 < ghostAMoveX && moveY - 3 < ghostAMoveY) && powerUpActive == true)
  { 
    ghostAPosX = 13;
    ghostAPosY = 11;
    ghostAMoveX = 237.7;
    ghostAMoveY = 101.6;
    ghostACurrentDir = 1;
  }

  else if((moveX + 3 > ghostBMoveX && moveY + 3 > ghostBMoveY) && (moveX - 3 < ghostBMoveX && moveY - 3 < ghostBMoveY) && powerUpActive == false)
  { 
    pacmanLifes -= 1;
    ResetCharacters();
    return;
  }

  else if((moveX + 3 > ghostBMoveX && moveY + 3 > ghostBMoveY) && (moveX - 3 < ghostBMoveX && moveY - 3 < ghostBMoveY) && powerUpActive == true)
  { 
    ghostBPosX = 13;
    ghostBPosY = 11;
    ghostBMoveX = 237.7;
    ghostBMoveY = 101.6;
    ghostBCurrentDir = 1;
  }

  else if((moveX + 3 > ghostCMoveX && moveY + 3 > ghostCMoveY) && (moveX - 3 < ghostCMoveX && moveY - 3 < ghostCMoveY) && powerUpActive == false)
  { 
    pacmanLifes -= 1;
    ResetCharacters();
    return;
  }

  else if((moveX + 3 > ghostCMoveX && moveY + 3 > ghostCMoveY) && (moveX - 3 < ghostCMoveX && moveY - 3 < ghostCMoveY) && powerUpActive == true)
  { 
    ghostCPosX = 13;
    ghostCPosY = 11;
    ghostCMoveX = 237.7;
    ghostCMoveY = 101.6;
    ghostCCurrentDir = 1;
  }

  else if((moveX + 3 > ghostDMoveX && moveY + 3 > ghostDMoveY) && (moveX - 3 < ghostDMoveX && moveY - 3 < ghostDMoveY) && powerUpActive == false)
  { 
    pacmanLifes -= 1;
    ResetCharacters();
    return;
  }

  else if((moveX + 3 > ghostDMoveX && moveY + 3 > ghostDMoveY) && (moveX - 3 < ghostDMoveX && moveY - 3 < ghostDMoveY) && powerUpActive == true)
  { 
    ghostDPosX = 13;
    ghostDPosY = 11;
    ghostDMoveX = 237.7;
    ghostDMoveY = 101.6;
    ghostDCurrentDir = 1;
  }
  
  for(int y = 0 ; y < 31; y++)
  {
    for(int x = 0 ; x < 28 ; x++)
    { 
      if((moveX + 3 > coinPosX && moveY + 3 > coinPosY) && (moveX - 3 < coinPosX && moveY - 3 < coinPosY))
      { 
        mapCollision[x][y] = 1;
      }
      
      else if (mapCollision[x][y] == 3)
      {
        GD.PointSize(16 * 1);
        GD.Vertex2ii(coinPosX, coinPosY);
        pointsLeft += 1;
      }

      else if (mapCollision[x][y] == 7)
      {
        //GD.Begin(BITMAPS);
        GD.PointSize(16 * 3);
        GD.Vertex2ii(coinPosX, coinPosY);
        pointsLeft += 1;
      }

      coinPosX += 8.7;
    }

    coinPosX = coinStartPosX;
    coinPosY = coinPosY + 8.7;
  }

  //If we collect all points, we win
  if(pointsLeft <= 0)
  {
    victory = true;
  }

  pointsLeft = 0;
}

void movePacman()
{ 
  if (treatValue(valueX) > 52 && walkableRIGHT == true && lockAxisY == false)
  {
    lockAxisX = true;
    moveX += pacmanMoveSpeed;
    pacmanPosX++;
  }

  if (treatValue(valueX) < 52 && walkableLEFT == true && lockAxisY == false)
  {
    lockAxisX = true;
    moveX -= pacmanMoveSpeed;
    pacmanPosX--;
  }

  if (treatValue(valueY) > 52 && walkableDOWN == true && lockAxisX == false)
  {
    lockAxisY = true;
    moveY -= pacmanMoveSpeed;
    pacmanPosY--;
  }

  if (treatValue(valueY) < 52 && walkableUP == true && lockAxisX == false)
  {
    lockAxisY = true;
    moveY += pacmanMoveSpeed;
    pacmanPosY++;
  }

  else
  {
    lockAxisX = false;
    lockAxisY = false;
  }
}

void moveGhostA()
{ 
  //NORTH
  if (ghostACurrentDir == 0)
  {
    //If we collide while going upward
    if(mapCollision[ghostAPosX][ghostAPosY - 1] == 0)
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostAPosX + 1][ghostAPosY] == 0)
      {
        ghostACurrentDir = 3;
        ghostAMoveX -= pacmanMoveSpeed;
        ghostAPosX--;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostAPosX - 1][ghostAPosY] == 0)
      {
        ghostACurrentDir = 1;
        ghostAMoveX += pacmanMoveSpeed;
        ghostAPosX++;
        return;
      }

      //If we can go both left and right, randomize to decide
      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostACurrentDir = 3;
          ghostAMoveX -= pacmanMoveSpeed;
          ghostAPosX--;
          return;
        }

        else
        {
          ghostACurrentDir = 1;
          ghostAMoveX += pacmanMoveSpeed;
          ghostAPosX++;
          return;
        }
      }
    }

    else
    {
      ghostAMoveY -= pacmanMoveSpeed;
      ghostAPosY--;
    }
  }

  //EAST
  if (ghostACurrentDir == 1)
  {
    //If we collide while going right
    if(mapCollision[ghostAPosX + 1][ghostAPosY] == 0)
    {
      //Check if we have collision downward, in that case upward
      if(mapCollision[ghostAPosX][ghostAPosY + 1] == 0)
      {
        ghostACurrentDir = 0;
        ghostAMoveY -= pacmanMoveSpeed;
        ghostAPosY--;
        return;
      }

      //Check if we have collision upward, in that case go downward
      else if(mapCollision[ghostAPosX][ghostAPosY - 1] == 0)
      {
        ghostACurrentDir = 2;
        ghostAMoveY += pacmanMoveSpeed;
        ghostAPosY++;
        return;
      }

      //If we can go both up and down, randomize to decide
      else
      {
        int upOrDown = random(3);
        
        //Up
        if(upOrDown == 0)
        {
          ghostACurrentDir = 0;
          ghostAMoveY -= pacmanMoveSpeed;
          ghostAPosY--;
          return;
        }

        else if(upOrDown == 1)
        {
          ghostACurrentDir = 3;
          ghostAMoveX -= pacmanMoveSpeed;
          ghostAPosX--;
          return;
        }
        
        //Down
        else
        {
          ghostACurrentDir = 2;
          ghostAMoveY += pacmanMoveSpeed;
          ghostAPosY++;
          return;
        }
      }
    }

    else
    {
      ghostAMoveX += pacmanMoveSpeed;
      ghostAPosX++; 
    }
  }

  //SOUTH
  if (ghostACurrentDir == 2)
  {
    //If we collide while going downward
    if(mapCollision[ghostAPosX][ghostAPosY + 1] == 0)
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostAPosX + 1][ghostAPosY] == 0)
      {
        ghostACurrentDir = 3;
        ghostAMoveX -= pacmanMoveSpeed;
        ghostAPosX--;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostAPosX - 1][ghostAPosY] == 0)
      {
        ghostACurrentDir = 1;
        ghostAMoveX += pacmanMoveSpeed;
        ghostAPosX++;
        return;
      }

      //If we can go both left and right, randomize to decide
      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostACurrentDir = 3;
          ghostAMoveX -= pacmanMoveSpeed;
          ghostAPosX--;
          return;
        }

        else
        {
          ghostACurrentDir = 1;
          ghostAMoveX += pacmanMoveSpeed;
          ghostAPosX++;
          return;
        }
      }
    }

    else
    {
      ghostAMoveY += pacmanMoveSpeed;
      ghostAPosY++;
    }
  }

  //WEST
  if (ghostACurrentDir == 3)
  {
    //If we collide while going left
    if(mapCollision[ghostAPosX - 1][ghostAPosY] == 0)
    {
      //Check if we have collision downward, in that case upward
      if(mapCollision[ghostAPosX][ghostAPosY + 1] == 0 && mapCollision[ghostAPosX][ghostAPosY - 1] != 0)
      {
        ghostACurrentDir = 0;
        ghostAMoveY -= pacmanMoveSpeed;
        ghostAPosY--;
        return;
      }

      //Check if we have collision upward, in that case go downward
      else if(mapCollision[ghostAPosX][ghostAPosY - 1] == 0 && mapCollision[ghostAPosX][ghostAPosY + 1] != 0)
      {
        ghostACurrentDir = 2;
        ghostAMoveY += pacmanMoveSpeed;
        ghostAPosY++;
        return;
      }

      //If we can go both up and down, randomize to decide
      else
      {
        int upOrDown = random(3);

        //Up
        if(upOrDown == 0)
        {
          ghostACurrentDir = 0;
          ghostAMoveY -= pacmanMoveSpeed;
          ghostAPosY--;
          return;
        }

        else if(upOrDown == 1)
        {
          ghostACurrentDir = 1;
          ghostAMoveX += pacmanMoveSpeed;
          ghostAPosX++;
          return;
        }
        
        //Down
        else
        {
          ghostACurrentDir = 2;
          ghostAMoveY += pacmanMoveSpeed;
          ghostAPosY++;
          return;
        }
      }
    }

    else
    {
      ghostAMoveX -= pacmanMoveSpeed;
      ghostAPosX--;
    }
  }
}

void moveGhostB()
{ 
  //NORTH
  if (ghostBCurrentDir == 0)
  {
    //If we collide while going upward
    if(mapCollision[ghostBPosX][ghostBPosY - 1] == 0)
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostBPosX + 1][ghostBPosY] == 0)
      {
        ghostBCurrentDir = 3;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostBPosX - 1][ghostBPosY] == 0)
      {
        ghostBCurrentDir = 1;
        return;
      }

      //If we can go both left and right, randomize to decide
      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostBCurrentDir = 3;
          return;
        }

        else
        {
          ghostBCurrentDir = 1;
          return;
        }
      }
    }

    else
    {
      ghostBMoveY -= pacmanMoveSpeed;
      ghostBPosY--;
    }
  }

  //EAST
  if (ghostBCurrentDir == 1)
  {
    //If we collide while going right
    if(mapCollision[ghostBPosX + 1][ghostBPosY] == 0)
    {
      //Check if we have collision downward, in that case upward
      if(mapCollision[ghostBPosX][ghostBPosY + 1] == 0)
      {
        ghostBCurrentDir = 0;
        return;
      }

      //Check if we have collision upward, in that case go downward
      else if(mapCollision[ghostBPosX][ghostBPosY - 1] == 0)
      {
        ghostBCurrentDir = 2;
        return;
      }

      //If we can go both up and down, randomize to decide
      else
      {
        int upOrDown = random(2);

        //Up
        if(upOrDown == 0)
        {
          ghostBCurrentDir = 0;
          return;
        }

        //Down
        else
        {
          ghostBCurrentDir = 2;
          return;
        }
      }
    }

    else
    {
      ghostBMoveX += pacmanMoveSpeed;
      ghostBPosX++; 
    }
  }

  //SOUTH
  if (ghostBCurrentDir == 2)
  {
    //If we collide while going downward
    if(mapCollision[ghostBPosX][ghostBPosY + 1] == 0)
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostBPosX + 1][ghostBPosY] == 0)
      {
        ghostBCurrentDir = 3;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostBPosX - 1][ghostBPosY] == 0)
      {
        ghostBCurrentDir = 1;
        return;
      }

      //If we can go both left and right, randomize to decide
      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostBCurrentDir = 3;
          return;
        }

        else
        {
          ghostBCurrentDir = 1;
          return;
        }
      }
    }

    else
    {
      ghostBMoveY += pacmanMoveSpeed;
      ghostBPosY++;
    }
  }

  //WEST
  if (ghostBCurrentDir == 3)
  {
    //If we collide while going left
    if(mapCollision[ghostBPosX - 1][ghostBPosY] == 0)
    {
      //Check if we have collision downward, in that case upward
      if(mapCollision[ghostBPosX][ghostBPosY + 1] == 0 && mapCollision[ghostBPosX][ghostBPosY - 1] != 0)
      {
        ghostBCurrentDir = 0;
        return;
      }

      //Check if we have collision upward, in that case go downward
      else if(mapCollision[ghostBPosX][ghostBPosY - 1] == 0 && mapCollision[ghostBPosX][ghostBPosY + 1] != 0)
      {
        ghostBCurrentDir = 2;
        return;
      }

      //If we can go both up and down, randomize to decide
      else
      {
        int upOrDown = random(2);
        
        //Up
        if(upOrDown == 0)
        {
          ghostBCurrentDir = 0;
          return;
        }

        //Down
        else
        {
          ghostBCurrentDir = 2;
          return;
        }
      }
    }

    else
    {
      ghostBMoveX -= pacmanMoveSpeed;
      ghostBPosX--;
    }
  }
}

void moveGhostC()
{ 
  if(ghostCMoveX > worldRight)
  {
    ghostCMoveX = worldLeft;
    ghostCPosX = 0;
  }

  else if(ghostCMoveX < worldLeft)
  {
    ghostCMoveX = worldRight;
    ghostCPosX = 27;
  }
  
  //NORTH
  if (ghostCCurrentDir == 0)
  {
    //If we collide while going upward
    if(mapCollision[ghostCPosX][ghostCPosY - 1] == 0)
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostCPosX + 1][ghostCPosY] == 0)
      {
        ghostCCurrentDir = 3;
        ghostCMoveX -= pacmanMoveSpeed;
        ghostCPosX--;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostCPosX - 1][ghostCPosY] == 0)
      {
        ghostCCurrentDir = 1;
        ghostCMoveX += pacmanMoveSpeed;
        ghostCPosX++;
        return;
      }

      //If we can go both left and right, randomize to decide
      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostCCurrentDir = 3;
          ghostCMoveX -= pacmanMoveSpeed;
          ghostCPosX--;
          return;
        }

        else
        {
          ghostCCurrentDir = 1;
          ghostCMoveX += pacmanMoveSpeed;
          ghostCPosX++;
          return;
        }
      }
    }

    //If we can continue in our direction but have the option of going in another direction
    else if(mapCollision[ghostCPosX][ghostCPosY - 1] != 0 && (mapCollision[ghostCPosX - 1][ghostCPosY] != 0 || mapCollision[ghostCPosX + 1][ghostCPosY] != 0))
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostCPosX + 1][ghostCPosY] == 0)
      {
        ghostCCurrentDir = 3;
        ghostCMoveX -= pacmanMoveSpeed;
        ghostCPosX--;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostCPosX - 1][ghostCPosY] == 0)
      {
        ghostCCurrentDir = 1;
        ghostCMoveX += pacmanMoveSpeed;
        ghostCPosX++;
        return;
      }

      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostCCurrentDir = 3;
          ghostCMoveX -= pacmanMoveSpeed;
          ghostCPosX--;
          return;
        }

        else
        {
          ghostCCurrentDir = 1;
          ghostCMoveX += pacmanMoveSpeed;
          ghostCPosX++;
          return;
        }
      }
    }

    else
    {
      ghostCMoveY -= pacmanMoveSpeed;
      ghostCPosY--;
    }
  }

  //EAST
  if (ghostCCurrentDir == 1)
  {
    //If we collide while going right
    if(mapCollision[ghostCPosX + 1][ghostCPosY] == 0)
    {
      if(mapCollision[ghostCPosX + 1][ghostCPosY] == 0 && (ghostCPosY == 14 && ghostCPosX > 24))
      {
        ghostCMoveX += pacmanMoveSpeed;
        ghostCPosX++;
        return;
      }
      
      //Check if we have collision downward, in that case upward
      else if(mapCollision[ghostCPosX][ghostCPosY + 1] == 0)
      {
        ghostCCurrentDir = 0;
        ghostCMoveY -= pacmanMoveSpeed;
        ghostCPosY--;
        return;
      }

      //Check if we have collision upward, in that case go downward
      else if(mapCollision[ghostCPosX][ghostCPosY - 1] == 0)
      {
        ghostCCurrentDir = 2;
        ghostCMoveY += pacmanMoveSpeed;
        ghostCPosY++;
        return;
      }

      //If we can go both up and down, randomize to decide
      else
      {
        int upOrDown = random(2);

        //Up
        if(upOrDown == 0)
        {
          ghostCCurrentDir = 0;
          ghostCMoveY -= pacmanMoveSpeed;
          ghostCPosY--;
          return;
        }
        
        //Down
        else
        {
          ghostCCurrentDir = 2;
          ghostCMoveY += pacmanMoveSpeed;
          ghostCPosY++;
          return;
        }
      }
    }

    //If we can continue in our direction but have the option of going in another direction
    else if(mapCollision[ghostCPosX + 1][ghostCPosY] != 0 && (mapCollision[ghostCPosX][ghostCPosY - 1] != 0 || mapCollision[ghostCPosX][ghostCPosY + 1] != 0))
    {
      //Check if we have collision upward, go downward
      if(mapCollision[ghostCPosX][ghostCPosY - 1] == 0)
      {
        ghostCCurrentDir = 2;
        ghostCMoveY += pacmanMoveSpeed;
        ghostCPosY++;
        return;
      }

      //Check if we have collision downward, go upward
      else if(mapCollision[ghostCPosX][ghostCPosY + 1] == 0)
      {
        ghostCCurrentDir = 0;
        ghostCMoveY -= pacmanMoveSpeed;
        ghostCPosY--;
        return;
      }

      else
      {
        int upOrDown = random(2);
        
        if(upOrDown == 0)
        {
          ghostCCurrentDir = 0;
          ghostCMoveY -= pacmanMoveSpeed;
          ghostCPosY--;
          return;
        }

        else
        {
          ghostCCurrentDir = 2;
          ghostCMoveY += pacmanMoveSpeed;
          ghostCPosY++;
          return;
        } 
      }
    }

    else
    {
      ghostCMoveX += pacmanMoveSpeed;
      ghostCPosX++; 
    }
  }

  //SOUTH
  if (ghostCCurrentDir == 2)
  {
    //If we collide while going downward
    if(mapCollision[ghostCPosX][ghostCPosY + 1] == 0)
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostCPosX + 1][ghostCPosY] == 0)
      {
        ghostCCurrentDir = 3;
        ghostCMoveX -= pacmanMoveSpeed;
        ghostCPosX--;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostCPosX - 1][ghostCPosY] == 0)
      {
        ghostCCurrentDir = 1;
        ghostCMoveX += pacmanMoveSpeed;
        ghostCPosX++;
        return;
      }

      //If we can go both left and right, randomize to decide
      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostCCurrentDir = 3;
          ghostCMoveX -= pacmanMoveSpeed;
          ghostCPosX--;
          return;
        }

        else
        {
          ghostCCurrentDir = 1;
          ghostCMoveX += pacmanMoveSpeed;
          ghostCPosX++;
          return;
        }
      }
    }

    //If we can continue in our direction but have the option of going in another direction
    else if(mapCollision[ghostCPosX][ghostCPosY + 1] != 0 && (mapCollision[ghostCPosX - 1][ghostCPosY] != 0 || mapCollision[ghostCPosX + 1][ghostCPosY] != 0))
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostCPosX + 1][ghostCPosY] == 0)
      {
        ghostCCurrentDir = 3;
        ghostCMoveX -= pacmanMoveSpeed;
        ghostCPosX--;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostCPosX - 1][ghostCPosY] == 0)
      {
        ghostCCurrentDir = 1;
        ghostCMoveX += pacmanMoveSpeed;
        ghostCPosX++;
        return;
      }

      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostCCurrentDir = 3;
          ghostCMoveX -= pacmanMoveSpeed;
          ghostCPosX--;
          return;
        }

        else
        {
          ghostCCurrentDir = 1;
          ghostCMoveX += pacmanMoveSpeed;
          ghostCPosX++;
          return;
        }
      }
    }

    else
    {
      ghostCMoveY += pacmanMoveSpeed;
      ghostCPosY++;
    }
  }

  //WEST
  if (ghostCCurrentDir == 3)
  {
    //If we collide while going left
    if(mapCollision[ghostCPosX - 1][ghostCPosY] == 0)
    {
      if(mapCollision[ghostCPosX - 1][ghostCPosY] == 0 && (ghostCPosY == 14 && ghostCPosX < 5))
      {
        ghostCMoveX -= pacmanMoveSpeed;
        ghostCPosX--;
        return;
      }
      
      //Check if we have collision downward, in that case upward
      else if(mapCollision[ghostCPosX][ghostCPosY + 1] == 0 && mapCollision[ghostCPosX][ghostCPosY - 1] != 0)
      {
        ghostCCurrentDir = 0;
        ghostCMoveY -= pacmanMoveSpeed;
        ghostCPosY--;
        return;
      }

      //Check if we have collision upward, in that case go downward
      else if(mapCollision[ghostCPosX][ghostCPosY - 1] == 0 && mapCollision[ghostCPosX][ghostCPosY + 1] != 0)
      {
        ghostCCurrentDir = 2;
        ghostCMoveY += pacmanMoveSpeed;
        ghostCPosY++;
        return;
      }

      //If we can go both up and down, randomize to decide
      else
      {
        int upOrDown = random(3);

        //Up
        if(upOrDown == 0)
        {
          ghostCCurrentDir = 0;
          ghostCMoveY -= pacmanMoveSpeed;
          ghostCPosY--;
          return;
        }

        else if(upOrDown == 1)
        {
          ghostCCurrentDir = 1;
          ghostCMoveX += pacmanMoveSpeed;
          ghostCPosX++;
          return;
        }
        
        //Down
        else
        {
          ghostCCurrentDir = 2;
          ghostCMoveY += pacmanMoveSpeed;
          ghostCPosY++;
          return;
        }
      }
    }

    //If we can continue in our direction but have the option of going in another direction
    else if(mapCollision[ghostCPosX - 1][ghostCPosY] != 0 && (mapCollision[ghostCPosX][ghostCPosY - 1] != 0 || mapCollision[ghostCPosX][ghostCPosY + 1] != 0))
    {
      //Check if we have collision upward, go downward
      if(mapCollision[ghostCPosX][ghostCPosY - 1] == 0)
      {
        ghostCCurrentDir = 2;
        ghostCMoveY += pacmanMoveSpeed;
        ghostCPosY++;
        return;
      }

      //Check if we have collision downward, go upward
      else if(mapCollision[ghostCPosX][ghostCPosY + 1] == 0)
      {
        ghostCCurrentDir = 0;
        ghostCMoveY -= pacmanMoveSpeed;
        ghostCPosY--;
        return;
      }

      else
      {
        int upOrDown = random(2);
        
        if(upOrDown == 0)
        {
          ghostCCurrentDir = 0;
          ghostCMoveY -= pacmanMoveSpeed;
          ghostCPosY--;
          return;
        }

        else
        {
          ghostCCurrentDir = 2;
          ghostCMoveY += pacmanMoveSpeed;
          ghostCPosY++;
          return;
        }
      }
    }
      
    else
    {
      ghostCMoveX -= pacmanMoveSpeed;
      ghostCPosX--;
    }
  }
}

void moveGhostD()
{ 
  if(ghostDMoveX > worldRight)
  {
    ghostDMoveX = worldLeft;
    ghostDPosX = 0;
  }

  else if(ghostDMoveX < worldLeft)
  {
    ghostDMoveX = worldRight;
    ghostDPosX = 27;
  }
  
  //NORTH
  if (ghostDCurrentDir == 0)
  {
    //If we collide while going upward
    if(mapCollision[ghostDPosX][ghostDPosY - 1] == 0)
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostDPosX + 1][ghostDPosY] == 0)
      {
        ghostDCurrentDir = 3;
        ghostDMoveX -= pacmanMoveSpeed;
        ghostDPosX--;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostDPosX - 1][ghostDPosY] == 0)
      {
        ghostDCurrentDir = 1;
        ghostDMoveX += pacmanMoveSpeed;
        ghostDPosX++;
        return;
      }

      //If we can go both left and right, randomize to decide
      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostDCurrentDir = 3;
          ghostDMoveX -= pacmanMoveSpeed;
          ghostDPosX--;
          return;
        }

        else
        {
          ghostDCurrentDir = 1;
          ghostDMoveX += pacmanMoveSpeed;
          ghostDPosX++;
          return;
        }
      }
    }

    //If we can continue in our direction but have the option of going in another direction
    else if(mapCollision[ghostDPosX][ghostDPosY - 1] != 0 && (mapCollision[ghostDPosX - 1][ghostDPosY] != 0 || mapCollision[ghostDPosX + 1][ghostDPosY] != 0))
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostDPosX + 1][ghostDPosY] == 0)
      {
        ghostDCurrentDir = 3;
        ghostDMoveX -= pacmanMoveSpeed;
        ghostDPosX--;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostDPosX - 1][ghostDPosY] == 0)
      {
        ghostDCurrentDir = 1;
        ghostDMoveX += pacmanMoveSpeed;
        ghostDPosX++;
        return;
      }

      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostDCurrentDir = 3;
          ghostDMoveX -= pacmanMoveSpeed;
          ghostDPosX--;
          return;
        }

        else
        {
          ghostDCurrentDir = 1;
          ghostDMoveX += pacmanMoveSpeed;
          ghostDPosX++;
          return;
        }
      }
    }

    else
    {
      ghostDMoveY -= pacmanMoveSpeed;
      ghostDPosY--;
    }
  }

  //EAST
  if (ghostDCurrentDir == 1)
  {
    //If we collide while going right
    if(mapCollision[ghostDPosX + 1][ghostDPosY] == 0)
    {
      if(mapCollision[ghostDPosX + 1][ghostDPosY] == 0 && (ghostDPosY == 14 && ghostDPosX > 24))
      {
        ghostDMoveX += pacmanMoveSpeed;
        ghostDPosX++;
        return;
      }
      
      //Check if we have collision downward, in that case upward
      else if(mapCollision[ghostDPosX][ghostDPosY + 1] == 0)
      {
        ghostDCurrentDir = 0;
        ghostDMoveY -= pacmanMoveSpeed;
        ghostDPosY--;
        return;
      }

      //Check if we have collision upward, in that case go downward
      else if(mapCollision[ghostDPosX][ghostDPosY - 1] == 0)
      {
        ghostDCurrentDir = 2;
        ghostDMoveY += pacmanMoveSpeed;
        ghostDPosY++;
        return;
      }

      //If we can go both up and down, randomize to decide
      else
      {
        int upOrDown = random(3);

        //Up
        if(upOrDown == 0)
        {
          ghostDCurrentDir = 0;
          ghostDMoveY -= pacmanMoveSpeed;
          ghostDPosY--;
          return;
        }

        else if(upOrDown == 1)
        {
          ghostDCurrentDir = 3;
          ghostDMoveX -= pacmanMoveSpeed;
          ghostDPosX--;
          return;
        }
        
        //Down
        else
        {
          ghostDCurrentDir = 2;
          ghostDMoveY += pacmanMoveSpeed;
          ghostDPosY++;
          return;
        }
      }
    }

    //If we can continue in our direction but have the option of going in another direction
    else if(mapCollision[ghostDPosX + 1][ghostDPosY] != 0 && (mapCollision[ghostDPosX][ghostDPosY - 1] != 0 || mapCollision[ghostDPosX][ghostDPosY + 1] != 0))
    {
      //Check if we have collision upward, go downward
      if(mapCollision[ghostDPosX][ghostDPosY - 1] == 0)
      {
        int continueOrTurn = random(2);

        if(continueOrTurn == 0)
        {
          ghostDCurrentDir = 2;
          ghostDMoveY += pacmanMoveSpeed;
          ghostDPosY++;
          return;
        }

        else
        {
          ghostDMoveX -= pacmanMoveSpeed;
          ghostDPosX--; 
        }
      }

      //Check if we have collision downward, go upward
      else if(mapCollision[ghostDPosX][ghostDPosY + 1] == 0)
      {
        int continueOrTurn = random(2);

        if(continueOrTurn == 0)
        {
          ghostDCurrentDir = 0;
          ghostDMoveY -= pacmanMoveSpeed;
          ghostDPosY--;
          return;
        }

        else
        {
          ghostDMoveX += pacmanMoveSpeed;
          ghostDPosX++; 
        }
      }

      else
      {
        int upOrDown = random(3);

        //Up
        if(upOrDown == 0)
        {
          ghostDCurrentDir = 0;
          ghostDMoveY -= pacmanMoveSpeed;
          ghostDPosY--;
          return;
        }

        else if(upOrDown == 1)
        {
          ghostDCurrentDir = 3;
          ghostDMoveX -= pacmanMoveSpeed;
          ghostDPosX--;
          return;
        }
        
        //Down
        else
        {
          ghostDCurrentDir = 2;
          ghostDMoveY += pacmanMoveSpeed;
          ghostDPosY++;
          return;
        }
      }
    }

    else
    {
      ghostDMoveX += pacmanMoveSpeed;
      ghostDPosX++; 
    }
  }

  //SOUTH
  if (ghostDCurrentDir == 2)
  {
    //If we collide while going downward
    if(mapCollision[ghostDPosX][ghostDPosY + 1] == 0)
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostDPosX + 1][ghostDPosY] == 0)
      {
        ghostDCurrentDir = 3;
        ghostDMoveX -= pacmanMoveSpeed;
        ghostDPosX--;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostDPosX - 1][ghostDPosY] == 0)
      {
        ghostDCurrentDir = 1;
        ghostDMoveX += pacmanMoveSpeed;
        ghostDPosX++;
        return;
      }

      //If we can go both left and right, randomize to decide
      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostDCurrentDir = 3;
          ghostDMoveX -= pacmanMoveSpeed;
          ghostDPosX--;
          return;
        }

        else
        {
          ghostDCurrentDir = 1;
          ghostDMoveX += pacmanMoveSpeed;
          ghostDPosX++;
          return;
        }
      }
    }

    //If we can continue in our direction but have the option of going in another direction
    else if(mapCollision[ghostDPosX][ghostDPosY + 1] != 0 && (mapCollision[ghostDPosX - 1][ghostDPosY] != 0 || mapCollision[ghostDPosX + 1][ghostDPosY] != 0))
    {
      //Check if we have collision to the right, in that case go left
      if(mapCollision[ghostDPosX + 1][ghostDPosY] == 0)
      {
        ghostDCurrentDir = 3;
        ghostDMoveX -= pacmanMoveSpeed;
        ghostDPosX--;
        return;
      }

      //Check if we have collision to the left, in that case go right
      else if(mapCollision[ghostDPosX - 1][ghostDPosY] == 0)
      {
        ghostDCurrentDir = 1;
        ghostDMoveX += pacmanMoveSpeed;
        ghostDPosX++;
        return;
      }

      else
      {
        int leftOrRight = random(2);
        
        if(leftOrRight == 0)
        {
          ghostDCurrentDir = 3;
          ghostDMoveX -= pacmanMoveSpeed;
          ghostDPosX--;
          return;
        }

        else
        {
          ghostDCurrentDir = 1;
          ghostDMoveX += pacmanMoveSpeed;
          ghostDPosX++;
          return;
        }
      }
    }

    else
    {
      ghostDMoveY += pacmanMoveSpeed;
      ghostDPosY++;
    }
  }

  //WEST
  if (ghostDCurrentDir == 3)
  {
    //If we collide while going left
    if(mapCollision[ghostDPosX - 1][ghostDPosY] == 0)
    {
      if(mapCollision[ghostDPosX - 1][ghostDPosY] == 0 && (ghostDPosY == 14 && ghostDPosX < 5))
      {
        ghostDMoveX -= pacmanMoveSpeed;
        ghostDPosX--;
        return;
      }
      
      //Check if we have collision downward, in that case upward
      else if(mapCollision[ghostDPosX][ghostDPosY + 1] == 0 && mapCollision[ghostDPosX][ghostDPosY - 1] != 0)
      {
        ghostDCurrentDir = 0;
        ghostDMoveY -= pacmanMoveSpeed;
        ghostDPosY--;
        return;
      }

      //Check if we have collision upward, in that case go downward
      else if(mapCollision[ghostDPosX][ghostDPosY - 1] == 0 && mapCollision[ghostDPosX][ghostDPosY + 1] != 0)
      {
        ghostDCurrentDir = 2;
        ghostDMoveY += pacmanMoveSpeed;
        ghostDPosY++;
        return;
      }

      //If we can go both up and down, randomize to decide
      else
      {
        int upOrDown = random(3);

        //Up
        if(upOrDown == 0)
        {
          ghostDCurrentDir = 0;
          ghostDMoveY -= pacmanMoveSpeed;
          ghostDPosY--;
          return;
        }

        else if(upOrDown == 1)
        {
          ghostDCurrentDir = 1;
          ghostDMoveX += pacmanMoveSpeed;
          ghostDPosX++;
          return;
        }
        
        //Down
        else
        {
          ghostDCurrentDir = 2;
          ghostDMoveY += pacmanMoveSpeed;
          ghostDPosY++;
          return;
        }
      }
    }

    //If we can continue in our direction but have the option of going in another direction
    else if(mapCollision[ghostDPosX - 1][ghostDPosY] != 0 && (mapCollision[ghostDPosX][ghostDPosY - 1] != 0 || mapCollision[ghostDPosX][ghostDPosY + 1] != 0))
    {
      //Check if we have collision upward, go downward
      if(mapCollision[ghostDPosX][ghostDPosY - 1] == 0)
      {
        int continueOrTurn = random(2);

        if(continueOrTurn == 0)
        {
          ghostDCurrentDir = 2;
          ghostDMoveY += pacmanMoveSpeed;
          ghostDPosY++;
          return; 
        }

        else
        {
          ghostDMoveX -= pacmanMoveSpeed;
          ghostDPosX--;
        }
      }

      //Check if we have collision downward, go upward
      else if(mapCollision[ghostDPosX][ghostDPosY + 1] == 0)
      {
        int continueOrTurn = random(2);

        if(continueOrTurn == 0)
        {
          ghostDCurrentDir = 0;
          ghostDMoveY -= pacmanMoveSpeed;
          ghostDPosY--;
          return;
        }

        else
        {
          ghostDMoveX -= pacmanMoveSpeed;
          ghostDPosX--;
        }
      }

      else
      {
        int upOrDown = random(3);
        
        if(upOrDown == 0)
        {
          ghostDCurrentDir = 0;
          ghostDMoveY -= pacmanMoveSpeed;
          ghostDPosY--;
          return;
        }

        else if(upOrDown == 1)
        {
          ghostDCurrentDir = 1;
          ghostDMoveX += pacmanMoveSpeed;
          ghostDPosX++;
          return;
        }

        else
        {
          ghostDCurrentDir = 2;
          ghostDMoveY += pacmanMoveSpeed;
          ghostDPosY++;
          return;
        }
      }
    }
      
    else
    {
      ghostDMoveX -= pacmanMoveSpeed;
      ghostDPosX--;
    }
  }
}

//Collision of the world with Pac-Man
void worldCollision()
{
  walkableUP = true;
  walkableDOWN = true;
  walkableLEFT = true;
  walkableRIGHT = true;
  
  if(moveX > worldRight)
  {
    moveX = worldLeft;
    pacmanPosX = 0;
  }

  else if(moveX < worldLeft)
  {
    moveX = worldRight;
    pacmanPosX = 27;
  }

  //DOUBLE COLLISION**
  //LEFT & RIGHT OF CURRENT POS
  else if(mapCollision[pacmanPosX - 1][pacmanPosY] == 0 && mapCollision[pacmanPosX + 1][pacmanPosY] == 0)
  {
    walkableLEFT = false;
    walkableRIGHT = false;
  }

  //ABOVE & UNDER CURRENT POS
  else if(mapCollision[pacmanPosX][pacmanPosY + 1] == 0 && mapCollision[pacmanPosX][pacmanPosY - 1] == 0)
  {
    walkableUP = false;
    walkableDOWN = false;
  }

  //ABOVE & RIGHT OF CURRENT POS
  else if(mapCollision[pacmanPosX][pacmanPosY + 1] == 0 && mapCollision[pacmanPosX + 1][pacmanPosY] == 0)
  {
    walkableUP = false;
    walkableRIGHT = false;
  }

  //RIGHT OF & UNDER CURRENT POS
  else if(mapCollision[pacmanPosX + 1][pacmanPosY] == 0 && mapCollision[pacmanPosX][pacmanPosY - 1] == 0)
  {
    walkableRIGHT = false;
    walkableDOWN = false;
  }

  //UNDER & LEFT OF CURRENT POS
  else if(mapCollision[pacmanPosX][pacmanPosY - 1] == 0 && mapCollision[pacmanPosX - 1][pacmanPosY] == 0)
  {
    walkableDOWN = false;
    walkableLEFT = false;
  }

  //LEFT OF & ABOVE CURRENT POS
  else if(mapCollision[pacmanPosX - 1][pacmanPosY] == 0 && mapCollision[pacmanPosX][pacmanPosY + 1] == 0)
  {
    walkableLEFT = false;
    walkableUP = false;
  }

  //SIMPLE COLLISIONS**
  //LEFT OF CURRENT POS
  else if(mapCollision[pacmanPosX - 1][pacmanPosY] == 0)
  {
    walkableLEFT = false;
  }

  //RIGHT OF CURRENT POS
  else if(mapCollision[pacmanPosX + 1][pacmanPosY] == 0)
  {
    walkableRIGHT = false;
  }

  //ABOVE CURRENT POS
  else if(mapCollision[pacmanPosX][pacmanPosY + 1] == 0)
  {
    walkableUP = false;
  }

  //UNDER CURRENT POS
  else if(mapCollision[pacmanPosX][pacmanPosY - 1] == 0)
  {
    walkableDOWN = false;
  }

  if(mapCollision[pacmanPosX][pacmanPosY] == 7)
  {
    powerUpActive = true;
    powerTimerLeft = powerTimerStart;
  }
}

//Treated input for simple comparison
int treatValue(int data)
{
  return (data * 9 / 1024) + 48;
}
