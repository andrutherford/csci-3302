#include <Sparki.h> // include the sparki library

// 50.45 diameter of the wheel
// 85.86 axle length

int startTime, endTime, lineLeft, lineCenter, lineRight;
const int THRESHOLD = 700;

float halfRadius = 12.6125;
float radiusOverAxle = 0.29379;

float theta = 0.0;
float x = 1.0;
float y = 1.0;

float rightWheel = 0.0;
float leftWheel = 0.0;

float theInverseD = 0.00116469;
float halfLR = 0.0;

int loopTime = 100;

char isFwd = 0;

void setup()
{
  sparki.clearLCD();
}

void loop() {
  startTime = millis();
  
  lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  lineCenter = sparki.lineCenter(); // measure the center IR sensor
  lineRight  = sparki.lineRight();  // measure the right IR sensor

  if (x >= 600 && isFwd == 0) {
    rightWheel = 0;
    leftWheel = 0;
    isFwd = 1;
    sparki.moveRight(90);

    sparki.moveForward(1);
//    delay(20);
    y -= 10;
    sparki.moveRight(90); // turn right
    theta += 3.14;
  } else if (x <= 0 && isFwd == 1) {
    rightWheel = 0.0278551532;
    leftWheel = -0.0278551532;
    isFwd = 0;
    sparki.moveLeft(90);

    sparki.moveForward(1);
//    delay(20);
    y -= 10;
    sparki.moveLeft(90); // turn left
    theta -= 3.14;
  } else {
    rightWheel = 0.0278551532;
    leftWheel = 0.0278551532;
    sparki.moveForward(); // move forward
  }

  halfLR = (rightWheel + leftWheel) * 0.5;
  
  x += cos(theta) * halfLR * loopTime;
  y += sin(theta) * halfLR * loopTime;
//  theta += (rightWheel - leftWheel) * theInverseD * loopTime * 10;
  
  if ( lineCenter < THRESHOLD) // if line is below left line sensor
  {
    int a = (x/10) + 30;
    int b = (y/10) + 50;
    sparki.drawPixel(a, b);
  }

 // sparki.clearLCD();
  //sparki.println(x/10);
  //sparki.println(y/10);
  //sparki.println(theta);
  sparki.updateLCD();

  endTime = millis();
  
  if (loopTime - (endTime - startTime) > 0) {
    delay(loopTime - (endTime - startTime));
  }
}
