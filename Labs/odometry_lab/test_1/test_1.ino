#include <Sparki.h> // include the sparki library

  double x = 0;     // left/right directions
  double y = 0;     // forward/backward directions 
  double theta = 0; // initial heading = 0, CW to 360
  double wr = 5/2;   // cm     //(5.5/2)
  double ad = 8.51;   // cm (7.5)
  double pi = 3.14159265359; //value of pi
  double v;
  double phi;
  double phi_2;  

void setup() 
{
  double x = 30;
  double t1 = millis();
  sparki.moveForward(x);
  double t2 = millis();
  double t = t2-t1;
  sparki.print("30cm: ");
  sparki.println(t);
  sparki.updateLCD();
  delay(100000);
  v = x/(t/1000);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
