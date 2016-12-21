#define NO_LCD 
#include  <Sparki.h>; // include the sparki library 
int angle=-60; 
void setup() { } 
void loop() { 
 sparki.servo(angle); 
 angle=angle+1; 
 if(angle>60){ 
   angle=-60; Serial.println(); 
 } 
int cm = sparki.ping(); // measures the distance with Sparki's eyes 
Serial.print(cm); 
Serial.print(" "); 
}
