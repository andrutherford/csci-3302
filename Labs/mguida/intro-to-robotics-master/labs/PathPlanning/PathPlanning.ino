#include <Sparki.h> // include the sparki library

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

float theInverseD = 0.00116469;
float halfLR = 0.0;

int loopTime = 100;
char grid[15][15];
void setup()
{
  sparki.clearLCD();
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      grid[i][j] = 0;
    }
  }
}

void loop() {
  startTime = millis();
  
  lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  lineCenter = sparki.lineCenter(); // measure the center IR sensor
  lineRight  = sparki.lineRight();  // measure the right IR sensor

  if ( lineCenter < THRESHOLD ) // if line is below left line sensor
  {
    rightWheel = 0.0278551532;
    leftWheel = 0.0278551532;
    
    sparki.moveForward(); // move forward
  }
  else{
    if ( lineLeft < THRESHOLD ) // if line is below left line sensor
    {
      rightWheel = 0.0278551532;
      leftWheel = -0.0278551532;
      
      sparki.moveLeft(); // turn left
    }
  
    if ( lineRight < THRESHOLD ) // if line is below right line sensor
    {  
      rightWheel = -0.0278551532;
      leftWheel = 0.0278551532;
      
      sparki.moveRight(); // turn right
    }
  }

  sparki.clearLCD(); // wipe the screen

  halfLR = (rightWheel + leftWheel) * 0.5;
  //sparki.println(halfLR);
  
  x += cos(theta) * halfLR * loopTime;
  y += sin(theta) * halfLR * loopTime;
  theta += (rightWheel - leftWheel) * theInverseD * loopTime * 10;
  
  /*sparki.print("X: ");
  sparki.println(x / 10);
  
  sparki.print("Y: ");
  sparki.println(-1*(y / 10));
  
  sparki.print("Theta: " );
  sparki.println(theta * 57.295);*/
  int locx = floor((x/10)/2.54);
  int locy = floor((-1*y/10)/2.54);
  //sparki.println(locx);
  grid[locx][locy] = 1;
  for(int i = 0; i < 15; i++)
  {
    for(int j = 0; j < 15; j++)
    {
      if(grid[i][j] < 1)sparki.print("0");
      else sparki.print("1");
      //sparki.print(" ");
    }
    sparki.println();
  }
  sparki.updateLCD();

  endTime = millis();
  
  //sparki.print("Time: ");
  //sparki.println(loopTime - (endTime - startTime));
  //sparki.updateLCD();
  
  if (loopTime - (endTime - startTime) > 0) {
    delay(loopTime - (endTime - startTime));
  }
}
