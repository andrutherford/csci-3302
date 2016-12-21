#include <Sparki.h>

// 50.45 diameter of the wheel
// 85.86 axle length

int startTime, endTime, lineLeft, lineCenter, lineRight;
const int THRESHOLD = 700;

float halfRadius = 12.6125;
float radiusOverAxle = 0.29379;

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

char waypointsx[16];
char waypointsy[16];
int pushIndex = 15;

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
    sparki.print(minCost);
    sparki.println(": Cost");
    sparki.updateLCD();
    
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
  waypointsx[pushIndex] = 22.5; 
  waypointsy[pushIndex] = 36.75;
  pushIndex--;
  int row = 3;
  int col = 1;
  while(row > 0 || col > 0){
    int north = 255, south = 255, east = 255, west = 255;
    if(col + 1 <= 3){
     int index = row * 4 + col + 1;
     north = nodes[index];
    }
    if(col - 1 >= 0){
     int index = row * 4 + col - 1;
     south = nodes[index];
    }
    if(row + 1 <= 3){
     int index = (row + 1) * 4 + col;
     east = nodes[index];
    }
    if(row - 1 >= 0){
     int index = (row - 1) * 4 + col;
     west = nodes[index];
    }
    
    if(north < south && north < east && north < west){
      dMap[row][col+1] = 0;
      row = row;
      col = col+1;
    }else if(south < north && south < east && south < west){
      dMap[row][col-1] = 0;
      row = row;
      col = col-1;
    }else if(east < south && east < north && east < west){
      dMap[row+1][col] = 0;
      row = row+1;
      col = col;
    }else if(west < south && west < east && west < north){
      dMap[row - 1][col] = 0;
      row = row - 1;
      col = col;
    }
    waypointsx[pushIndex] = row*10.5 + 5.25; 
    waypointsy[pushIndex] = col*15 + 7.5;
    pushIndex--;
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
  pushIndex++;
}

void loop() {
  startTime = millis();
  int turn = 0;

  sparki.clearLCD(); // wipe the screen

  halfLR = (rightWheel + leftWheel) * 0.5;
  //sparki.println(halfLR);
  
  x += cos(theta) * halfLR * loopTime;
  y += sin(theta) * halfLR * loopTime;
  theta += (rightWheel - leftWheel) * theInverseD * loopTime * 10;
  
  if((x < waypointsx[pushIndex] + 5 && x > waypointsx[pushIndex] - 5) && (y < waypointsy[pushIndex] + 5 && y > waypointsy[pushIndex] - 5)){
    pushIndex++;
    if(pushIndex == 16)while(1);
  }  
  
  float calcTheta = atan2(waypointsy[pushIndex] - y, waypointsx[pushIndex] - x);
  float desTheta =  calcTheta - theta;
  sparki.print("reqTheta ");
  sparki.println(calcTheta);
  int rightspeed;
  int leftspeed;
  int right;
  int left;
  if(desTheta < 5 && desTheta > -5){
    rightspeed = 1;
    leftspeed = 1;
    right = 100;
    left = 100;
  }else if(desTheta < 0){
    rightspeed = 1;
    leftspeed = 0.5;
    right = 100;
    left = 50;
  } else {
    leftspeed = 1;
    rightspeed = 0.5;
    right = 50;
    left = 100;
  }
    
  rightWheel = 0.0278551532 * rightspeed;
  leftWheel = 0.0278551532 * leftspeed;
  sparki.motorRotate(MOTOR_LEFT, DIR_CCW, left);
  sparki.motorRotate(MOTOR_RIGHT, DIR_CW, right);
  
  sparki.print(waypointsx[pushIndex]);
  sparki.print(" ");
  sparki.println(x);
  sparki.print(waypointsy[pushIndex]);
  sparki.print(" ");
  sparki.println(y);
  
  sparki.updateLCD();

  endTime = millis();
  
  if (loopTime - (endTime - startTime) > 0) {
    delay(loopTime - (endTime - startTime));
  }
}
