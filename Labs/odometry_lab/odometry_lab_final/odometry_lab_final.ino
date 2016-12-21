/*******************************************
 Sparki Line-following example
 
 Threshold is the value that helps you 
 determine what's black and white. Sparki's 
 infrared reflectance sensors indicate white 
 as close to 900, and black as around 200.
 This example uses a threshold of 700 for 
 the example, but if you have a narrow line, 
 or perhaps a lighter black, you may need to 
 adjust.
********************************************/

#include <Sparki.h> // include the sparki library
#include <math.h>

  double x = 0;     // forwards/backwards
  double y = 0;     // left/right
  double theta = 0; 
  double wr = 5.5/2;   // wheel radius in cm
  double ad = 7.5;   // axle diameter in cm
  double speed;
  double phi;  

void setup() 
{
  /* Calculate speed of robot */
  double x = 10;
  double time_1 = millis();
  sparki.moveForward(x);
  double time_2 = millis();
  double delta_t = time_2 - time_1;
  speed = x / (delta_t / 1000);
  phi = speed / wr; 
 //calculate the angular rotation (phi) by measuring a 2pi wheel rotation
 sparki.clearLCD();
}

void loop() {
  int threshold = 700;
  int move_forward = 0;
  int move_left = 0;
  int move_right = 0;
  //delay(00);
  unsigned long time_1 = millis();
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  //Move forward
  if ( lineCenter < threshold ) 
  {  
    sparki.moveForward();
    move_forward = 1;
  }
  else{
    //Move left
    if ( lineLeft < threshold ) 
    {  
      sparki.moveLeft();
      move_left = 1;
    }
    //Move right
    if ( lineRight < threshold )
    { 
      sparki.moveRight();
      move_right = 1;
    }
  }

  sparki.clearLCD(); 
 

  unsigned long time_2 = millis();

  unsigned long delta_t = time_2 - time_1;

  //Wait 100ms before continuing
  delay(100 - delta_t); 

  //If moving forward, increment x,y coordinates
  if (move_forward == 1){
    y += .1 * speed * sin(theta);
    x += .1 * speed * cos(theta);



    sparki.drawPixel(x, y);
    sparki.drawPixel(x+1, y);
    sparki.drawPixel(x, y+1);
    sparki.drawPixel(x+1, y+1);



    //sparki.updateLCD();
 
  }

  //If turning left, theta decreases
  if (move_left == 1){
    theta = theta - .1 * (wr / ad) * (phi + phi);

    //sparki.drawPixel(x, y);
    //sparki.updateLCD();

  }

  //If turning right, theta increases
  if (move_right == 1){
    theta = theta + .1 * (wr / ad) * (phi + phi);
    //sparki.drawPixel(x, y);
    //sparki.updateLCD();

  }

 

//  //Print x-coordinate
  //sparki.print("X: "); 
  //sparki.println(x);
//
//  //Print y-coordinate
//  sparki.print("Y: ");
//  sparki.println(y);
//
//  //Print theta
//  sparki.print("Theta: ");
//  sparki.println(theta);

  sparki.updateLCD();
}
