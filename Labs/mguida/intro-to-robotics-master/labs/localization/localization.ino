#include  <Sparki.h>; // include the sparki library 

void setup() {
  sparki.servo(0);
  sparki.clearLCD();
} 
int count = 0;
int pingValues[10];
int varTotal = 0;

void loop(){

    int cm = sparki.ping();
    pingValues[count] = cm;
    count++;
    if(count == 10){
    int varTotal = 0;
    for(int i=0; i < 10; i++){
      int temp = pingValues[i] * pingValues[i];
      varTotal += temp;
    }
    int variance = varTotal/10;
    sparki.print(variance);
    while(1);
    }
int variance = varTotal / 10;
sparki.println(variance);
while(1);
}

