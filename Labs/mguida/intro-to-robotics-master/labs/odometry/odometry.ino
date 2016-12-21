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

void setup()
{
  sparki.print("");
  sparki.updateLCD();
  sparki.clearLCD();
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

//  sparki.clearLCD(); // wipe the screen

  halfLR = (rightWheel + leftWheel) * 0.5;
//  sparki.println(halfLR);
  
  x += cos(theta) * halfLR * loopTime;
  y += sin(theta) * halfLR * loopTime;
  theta += (rightWheel - leftWheel) * theInverseD * loopTime * 10;
  
//  sparki.print("X: ");
//  sparki.println(x / 10);
  int a = (x/10) + 30;
  int b = (y/10) + 50;
  
  sparki.drawPixel(a, b); 
//  sparki.print("Y: ");
//  sparki.println(y / 10);
  
//  sparki.print("Theta: " );
//  sparki.println(theta * 57.295);
  
  sparki.updateLCD();

  endTime = millis();
  
//  sparki.print("Time: ");
//  sparki.println(loopTime - (endTime - startTime));
//  sparki.updateLCD();
  
  if (loopTime - (endTime - startTime) > 0) {
    delay(loopTime - (endTime - startTime));
  }
}
