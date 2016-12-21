
#include <sparki.h> //include Sparki library
int x = 0;
 int y = 0;

void setup(){


  sparki.clearLCD();
  sparki.print("Starting in 3 sec...");
  sparki.updateLCD();
  delay(1500);
  sparki.clearLCD();
  sparki.print("Starting in 2 sec...");
  sparki.updateLCD();
  delay(1000);
  sparki.clearLCD();
  sparki.print("Starting in 1 sec...");
  sparki.updateLCD();
  delay(1000);
  sparki.clearLCD();
}
 
void loop(){
  sparki.println(x/100);
  y = x / 100;
  sparki.drawPixel(y + 20,20);
  x++;
  sparki.updateLCD();
  sparki.moveForward();
  //sparki.clearLCD();
}
