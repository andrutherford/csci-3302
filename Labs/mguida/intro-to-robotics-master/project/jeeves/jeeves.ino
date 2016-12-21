#include <Sparki.h> // include the sparki library

// 50.45 diameter of the wheel
// 85.86 axle length

int startTime, endTime, lineLeft, lineCenter, lineRight;
int state = 0;
const int THRESHOLD = 700;

float halfRadius = 12.6125;
float radiusOverAxle = 0.29379;
int pingValue;

float theta = 0.0;
float x = 0.0;
float y = 0.0;
int locx;
int locy;

float rightWheel = 0.0;
float leftWheel = 0.0;

float theInverseD = 0.00116469;
float halfLR = 0.0;
int loopTime = 100;
float product = theInverseD * loopTime * 10;

char layoutV[4][4];



//TODO: send map via phone application to sparki
//TODO: eliminate line following altogether

void setupLayouts(){
  layoutV[3][1] = 'P';
  layoutV[3][2] = 'P';
  layoutV[3][3] = 'E';
  layoutV[3][0] = 'S';
  
  layoutV[2][3] = 'E';
  layoutV[2][2] = 'P';
  layoutV[2][1] = 'P';
  layoutV[2][0] = 'S';
  
  layoutV[1][3] = 'E';
  layoutV[1][2] = 'P';
  layoutV[1][1] = 'P';
  layoutV[1][0] = 'S';
  
  layoutV[0][3] = 'E';
  layoutV[0][2] = 'P';
  layoutV[0][1] = 'P';
  layoutV[0][0] = 'S';
}

void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);
  setupLayouts();
  sparki.servo(0);
}

void loop() {
  startTime = millis();
  if(state == 0 || state == 90 || state == 9){
    if(Serial1.available()){
      int inByte = Serial1.read();
      char received = (char)inByte;
      if(received == '1'){
        if(state == 0){
          state = 1;
          //begin parking
        }
      }else {
        if(state == 9){
          state = 10;
        }else if(state == 90){
          state = 100;
        }
      }
    }
  }
    
  
  lineLeft   = sparki.lineLeft();
  lineCenter = sparki.lineCenter(); 
  lineRight  = sparki.lineRight();
  //pingValue = sparki.ping();
  pingValue = 100;
  /*Serial.print(locx);
  Serial.print(" ");
  Serial.println(locy);*/
  if(pingValue >= 0 && pingValue < 15 && !(state == 4 || state == 5 || state == 8 || state == 6 || state == 7)){
    //if there is an object in front of us, stop
    sparki.moveStop();
  } else{
    if(state == 1){
      //move to the initial dropoff line, and center coordinates once there
      if(lineCenter < THRESHOLD && lineRight < THRESHOLD && lineLeft < THRESHOLD){
        state = 2;
        rightWheel = 0;
        leftWheel = 0;
        locx = ((x)/150);
        locy = ((y)/105);
        char info = layoutV[locx][locy];
        if(info == 'S'){
          locx = 3;
          locy = 0;
          x = locx * 150;
          y = locy * 105;
          y += 75;
        }else if(info == 'E'){
          locx = 0;
          locy = 3;
          x = locx * 150;
          y = locy * 105;
          y += 40;
        }
    
        sparki.moveStop();
      } else {
        //if we're not at the dropoff line, follow the guide line
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
      }
    }else if(state == 2){
      //rotate to the first row of parking spots
      //TODO: change from always turning left to picking up the rotation direction from the map of the lot
      sparki.moveLeft(90);
      theta += 1.5708;
      rightWheel = 0;
      leftWheel = 0;
      state = 3;
    } else if(state == 3){
      //move until we pick up a line indicating a parking spot
      //TODO: Distinguish between end of lane lines and parking spot lines
      //TODO: Don't reset odometry, just update to known position based on map
      if(lineCenter < THRESHOLD && lineRight < THRESHOLD && lineLeft < THRESHOLD){
        sparki.moveStop();
        rightWheel = 0;
        leftWheel = 0;
        locx = (x/150);
        locy = (y/105);
        char info = layoutV[locx][locy];
        if(info == 'P'){
          state = 4;
        }
        else if(info == 'E' || info == 'S'){
          sparki.moveForward(4);
          sparki.moveLeft(90);
          theta += 1.5708;
          state = 1;
        }
      }else{
        sparki.moveForward();
        rightWheel = 0.0278551532;
        leftWheel = 0.0278551532;
      }
    } else if(state == 4){
      //check the left parking spot for availability
      sparki.servo(SERVO_LEFT);
      delay(300);
      int ping = sparki.ping();
      if(ping == -1 || ping > 20){
        //we've found a parking spot, begin backing in
        //TODO: add odometry for rotation
         sparki.moveRight(90);
         //theta -= 1.5708;
         rightWheel = 0;
         leftWheel = 0;
         state = 7;
      }else{
        //parking spot is taken
        state = 5;
        rightWheel = 0;
        leftWheel = 0;
      }
    }else if(state == 5){
      //check the right parking spot for availability
      sparki.servo(SERVO_RIGHT);
      delay(300);
      int ping = sparki.ping();
      if(ping == -1 || ping > 20){
         sparki.moveLeft(90);
         //theta += 1.5708;
         rightWheel = 0;
         leftWheel = 0;
         state = 70;
      }else{
        //parking spot is taken
        state = 6;
        rightWheel = 0;
        leftWheel = 0;
      }
    } else if (state == 6){
      //recenter servo and move forward slightly to move off parking spot line, then continue searching for spots
      state = 3;
      sparki.servo(SERVO_CENTER);
      sparki.moveForward();
      rightWheel = 0.0278551532;
      leftWheel = 0.0278551532;
    }else if(state == 7){
      state = 8;
      rightWheel = 0;
      leftWheel = 0;
      sparki.servo(SERVO_CENTER);
    }else if(state == 8){
      //park sparki
      //TODO: use localization to determine when to stop rather than statically moving backward
      sparki.moveBackward(12);
      rightWheel = 0;
      leftWheel = 0;
      sparki.moveStop();
      state = 9;
    }else if(state == 70){
      state = 80;
      rightWheel = 0;
      leftWheel = 0;
      sparki.servo(SERVO_CENTER);
    }else if(state == 80){
      //park sparki
      //TODO: use localization to determine when to stop rather than statically moving backward
      sparki.moveBackward(12);
      rightWheel = 0;
      leftWheel = 0;
      sparki.moveStop();
      state = 90;
    }else if(state == 10){
      //move left
      sparki.moveForward(12);
      sparki.moveLeft(90);
      rightWheel = 0;
      leftWheel = 0;
      state = 11;
    }else if(state == 100){
      sparki.moveForward(12);
      sparki.moveRight(90);
      rightWheel = 0;
      leftWheel = 0;
      state = 11;
    }else if(state == 11){
      if(lineCenter < THRESHOLD && lineRight < THRESHOLD && lineLeft < THRESHOLD){
        sparki.moveStop();
        rightWheel = 0;
        leftWheel = 0;
        locx = (x/150);
        locy = (y/105);
        char info = layoutV[locx][locy];
       if(info == 'E' || info == 'S'){
          sparki.moveForward(4);
          sparki.moveLeft(90);
          theta += 1.5708;
          state = 12;
       }else{
        sparki.moveForward();
        rightWheel = 0.0278551532;
        leftWheel = 0.0278551532;
       }
      }else{
        sparki.moveForward();
        rightWheel = 0.0278551532;
        leftWheel = 0.0278551532;
      }
    }else if(state == 12){
      if(lineCenter < THRESHOLD && lineRight < THRESHOLD && lineLeft < THRESHOLD){
        sparki.moveStop();
        rightWheel = 0;
        leftWheel = 0;
        locx = (x/150);
        locy = (y/105);
        char info = layoutV[locx][locy];
       if(info == 'E'){
          locx = 0;
          locy = 3;
          x = locx * 150;
          y = locy * 105;
          y += 40;
          sparki.moveLeft(90);
          theta += 1.5708;
          state = 11;
       }else if(info == 'S'){
         /*while(1){
           sparki.servo(SERVO_RIGHT);
           delay(300);
           sparki.servo(SERVO_LEFT);
           delay(300);
         }*/
         sparki.moveStop();
         rightWheel = 0;
         leftWheel = 0;
       }
      }
      else {
        //if we're not at the dropoff line, follow the guide line
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
      }
    }
  }
  if(rightWheel > 0 && leftWheel > 0){
    halfLR = (rightWheel + leftWheel) * 0.5;
    
    x += cos(theta) * halfLR * loopTime;
    y += sin(theta) * halfLR * loopTime;
    theta += (rightWheel - leftWheel) * product;
  
    endTime = millis();
  
    if (loopTime - (endTime - startTime) > 0) {
      delay(loopTime - (endTime - startTime));
    }
  }
}
