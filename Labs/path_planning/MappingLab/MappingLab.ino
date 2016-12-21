#include <Sparki.h>
int startTime, endTime, lineLeft, lineCenter, lineRight;
const int THRESHOLD = 700;

float theta = 0.0;
float x = 0.0;
float y = 0.0;

float rightWheel = 0.0;
float leftWheel = 0.0;

int currCol = 0;
int currRow = 0;

float theInverseD = 0.00116469;
float halfLR = 0.0;

int loopTime = 100;
char topGrid[4][4];
char dMap[4][4];

void doDMap(){
  char notCompleted[16];
  int nodesLeft = 10;
  int nodes[16];
  for(int i = 0; i < 16; i++){
    notCompleted[i] = 1;
    nodes[i] = 50;
  }
  nodes[0] = 0;
  
  while(nodesLeft > 0){
    int minNode = 0;
    int minCost = 255;
    for(int i = 0; i < 16; i++){
      char isLeft = notCompleted[i];
      char cost = nodes[i];
      if(isLeft > 0 && cost < minCost){
        minNode = i;
        minCost = cost;
      }
      else if(minNode < 0 && isLeft > 0){
        minNode = i;
        minCost = cost;
      }
    }
    
    int row = minNode / 4;
    int col = minNode % 4;
    int newCost = minCost + 1;
    notCompleted[minNode] = 0;
    if(col + 1 <= 3){
     int index = row * 4 + col + 1;
     char isLeft = notCompleted[index];
     char cost = nodes[index];
     if(cost > newCost && isLeft > 0 && topGrid[row][col+1] != 'B')nodes[index] = newCost;
    }
    if(col - 1 >= 0){
     int index = row * 4 + col - 1;
     char isLeft = notCompleted[index];
     char cost = nodes[index];
     if(cost > newCost && isLeft > 0 && topGrid[row][col-1] != 'B')nodes[index] = newCost;
    }
    if(row + 1 <= 3){
     int index = (row + 1) * 4 + col;
     char isLeft = notCompleted[index];
     char cost = nodes[index];
     if(cost > newCost && isLeft > 0 && topGrid[row+1][col] != 'B')nodes[index] = newCost;
    }
    if(row - 1 >= 0){
     int index = (row - 1) * 4 + col;
     char isLeft = notCompleted[index];
     char cost = nodes[index];
     if(cost > newCost && isLeft > 0 && topGrid[row-1][col] != 'B')nodes[index] = newCost;
    }
    nodesLeft--;
  }
  dMap[0][0] = 0;
  dMap[3][1] = 0;
  int row = 3;
  int col = 1;
  while(row > 0 || col > 0){
    int forward = 255, backward = 255, right = 255, left = 255;
    if(col + 1 <= 3){
     int index = row * 4 + col + 1;
     forward = nodes[index];
    }
    if(col - 1 >= 0){
     int index = row * 4 + col - 1;
     backward = nodes[index];
    }
    if(row + 1 <= 3){
     int index = (row + 1) * 4 + col;
     right = nodes[index];
    }
    if(row - 1 >= 0){
     int index = (row - 1) * 4 + col;
     left = nodes[index];
    }
    
    if(forward < backward && forward < right && forward < left){
      dMap[row][col+1] = 0;
      row = row;
      col = col+1;
    }else if(backward < forward && backward < right && backward < left){
      dMap[row][col-1] = 0;
      row = row;
      col = col-1;
    }else if(right < backward && right < forward && right < left){
      dMap[row+1][col] = 0;
      row = row+1;
      col = col;
    }else if(left < backward && left < right && left < forward){
      dMap[row - 1][col] = 0;
      row = row - 1;
      col = col;
    }
  }
}
    
int orient = 0;          

void setup()
{
  sparki.clearLCD();
  for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++){
         topGrid[i][j] = 'O';
         dMap[i][j] = 1;
      }
  }
  topGrid[0][0] = 'R';
  topGrid[0][3] = 'B';
  
  topGrid[1][0] = 'B';
  topGrid[1][1] = 'B';
  topGrid[1][3] = 'B';
  
  topGrid[3][0] = 'B';
  topGrid[3][1] = 'D';
  topGrid[3][2] = 'B';
  doDMap(); 

  sparki.gripperOpen();
  delay(3000);
  sparki.gripperStop();
}

void loop() {
  startTime = millis();
  int turn = 1;
  rightWheel = 0.0278551532;
  leftWheel = 0.0278551532;
  
  sparki.clearLCD(); // wipe the screen

  halfLR = (rightWheel + leftWheel) * 0.5;
 
  x += cos(theta) * halfLR * loopTime;
  y += sin(theta) * halfLR * loopTime;
  
  if(((int)(x/10)) % 10 == 0)currCol = ((x/10)/15);
  currRow = ((y/10)/10.5);
  sparki.print(currRow);
  sparki.print(" ");
  sparki.print(currCol);
  sparki.print(" ");
  sparki.print(theta);
  sparki.println();
  sparki.println();
  dMap[currRow][currCol] = 1;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(dMap[i][j] > 0)sparki.print("1");
      else sparki.print("0");
      sparki.print(" ");
    }
    sparki.println();
  }
  sparki.updateLCD();
  if(currRow == 3 && currCol == 1){
    sparki.moveStop();
    sparki.gripperOpen();
    delay(500);
    sparki.gripperStop();
    sparki.println();
    sparki.updateLCD();
    delay(1000);
    sparki.gripperClose();
    delay(3000);
    sparki.gripperStop();
    sparki.println("Filling coffee...");
    sparki.updateLCD();

    sparki.RGB(100,0,0);
    delay(1000);

    sparki.RGB(0,0,0);
    delay(1000);

    sparki.RGB(100,0,0);
    delay(1000);

    sparki.RGB(0,0,0);
    delay(1000);

    sparki.RGB(100,0,0);
    delay(1000);

    sparki.RGB(0,0,0);
    delay(1500);

    sparki.RGB(0,100,0);
    delay(1000);
    
    
    sparki.clearLCD();
    sparki.println("Returning to bedroom...");
    sparki.updateLCD();
    sparki.moveBackward();
    delay(2500);

    sparki.moveLeft(90);
    //delay(2500);

    sparki.moveForward();
    delay(3850);

    sparki.moveLeft(90);
    //delay(2500);

    sparki.moveForward();
    delay(8770);

    sparki.moveLeft(90);
    //delay(2500);

    sparki.moveForward();
    delay(11450);

    sparki.moveStop();

    sparki.clearLCD();

    delay(2000);

    sparki.gripperOpen();
    delay(1000);
    sparki.gripperStop();

    sparki.println("Wake up in 5 sec...");
    sparki.updateLCD();
    delay(1000);
    sparki.clearLCD();
    sparki.println("Wake up in 4 sec...");
    sparki.updateLCD();
    delay(1000);
    sparki.clearLCD();
    sparki.println("Wake up in 3 sec...");
    sparki.updateLCD();
    delay(1000);
    sparki.clearLCD();
    sparki.println("Wake up in 2 sec...");
    sparki.updateLCD();
    delay(1000);
    sparki.clearLCD();
    sparki.println("Wake up in 1 sec...");
    sparki.updateLCD();
    delay(1000);
    sparki.clearLCD();

    sparki.println("WAKE UP!");
    sparki.updateLCD();
    sparki.beep();
    sparki.RGB(100,0,0);
    delay(500);
    sparki.RGB(0,0,0);
    delay(500);
    sparki.beep();
    sparki.RGB(100,0,0);
    delay(500);
    sparki.RGB(0,0,0);
    delay(500);
    sparki.beep();
    sparki.RGB(100,0,0);
    delay(500);
    sparki.RGB(0,0,0);
    delay(500);
    sparki.RGB(100,0,0);
    delay(500);
    sparki.RGB(0,0,0);
    delay(500);
    sparki.RGB(100,0,0);
    delay(500);
    sparki.RGB(0,0,0);
    delay(500);
    sparki.RGB(100,0,0);
    delay(500);
    sparki.RGB(0,0,0);
    delay(500);
   


    
    while(1);

  }
  sparki.updateLCD();
  
  int forward = 1, left = 1, right = 1, backward = 1;
  if(currCol+1 <= 3){
    forward = dMap[currRow][currCol+1];
  }
  if(currCol-1 >= 0){
    backward = dMap[currRow][currCol-1];
  }
  if(currRow-1 >= 0){
    left = dMap[currRow-1][currCol];
  }
  if(currRow + 1 <= 3){
    right = dMap[currRow+1][currCol];
  }
  
  if ( forward == 0 ) // if line is below left line sensor
  {
    if(orient == 0){
      sparki.moveForward(); // move forward
    } else if(orient == 1){
      sparki.moveLeft(90); // turn left
      theta -= (3.1415926/2);
      orient = 0;
    } else if (orient == 3){
      sparki.moveRight(90); // turn right
      theta += (3.1415926/2);
      orient = 0;
    }
      
  }
  else if ( left == 0) // if line is below left line sensor
    {
      if(orient == 3){
        sparki.moveForward(); // move forward
      } else if(orient == 0){
        sparki.moveLeft(90); // turn left
        theta -= (3.1415926/2);
        orient = 3;
      } else if (orient == 2){
        sparki.moveRight(90); // turn right
        theta += (3.1415926/2);
        orient = 3;
      }
    }
  
  else if ( right == 0 ) // if line is below right line sensor
  {  
    if(orient == 1){
      sparki.moveForward(); // move forward
    } else if(orient == 2){
      sparki.moveLeft(90); // turn left
      theta -= (3.1415926/2);
      orient = 1;
    } else if (orient == 0){
      sparki.moveRight(90); // turn right
      theta += (3.1415926/2);
      orient = 1;
    }
  }
  else if(backward == 0)
  {
    if(orient == 2){
      sparki.moveForward(); // move forward
    } else if(orient == 3){
      sparki.moveLeft(90); // turn left
      theta -= (3.1415926/2);
      orient = 2;
    } else if (orient == 1){
      sparki.moveRight(90); // turn right
      theta += (3.1415926/2);
      orient = 2;
    }
  }
  else{
    sparki.moveStop();
    while(1);
  }

  endTime = millis();
  
  if (loopTime - (endTime - startTime) > 0) {
    delay(loopTime - (endTime - startTime));
  }
}
