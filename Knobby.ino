#include <Encoder.h>

//Rotary Encoder Init
Encoder EncLeft(5, 6);
Encoder EncRight(7, 8);

//LED Pins
const int LED1 = 9;
const int LED2 = 10;
const int LED3 = 11;
const int LED4 = 12;
const int LED5 = 14;
const int LED6 = 15;
const int LED7 = 16;
const int LED8 = 17;

//Push Button Pins
const int PushLeft = 0;
const int PushRight = 1;

void setup() {

  //LEDs Pin Init
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);

  //Push Button Pin Init
  pinMode(PushLeft, INPUT_PULLUP);
  pinMode(PushRight, INPUT_PULLUP);
}

//Encoder
long OldLeft  = -999;
long OldRight = -999;

//Push Buttons
boolean PushLeftState = HIGH;  //Left State
boolean PushRightState = HIGH; //Right State
boolean PushReleased = 0;   //Has button been released state

/*
  Mode Section
  1= Hdg
  2= Crs
  3= Alt
  4= VS
  5= Com1
  6= Com2
  7= Nav1
  8= Nav2

  Function to change mode and led
  x accepts 0 or 1
  0 = left
  1 = right
*/

int Mode = 1;

void ModeChange(int x) {                  //Function to change modes and turn off and on LEDs
  int OldMode = Mode;
  switch (OldMode) {                         //turn off old LED. could just turn off all leds
    case 1:
      digitalWrite(LED1, HIGH);
      break;
    case 2:
      digitalWrite(LED2, HIGH);
      break;
    case 3:
      digitalWrite(LED3, HIGH);
      break;
    case 4:
      digitalWrite(LED4, HIGH);
      break;
    case 5:
      digitalWrite(LED5, HIGH);
      break;
    case 6:
      digitalWrite(LED6, HIGH);
      break;
    case 7:
      digitalWrite(LED7, HIGH);
      break;
    case 8:
      digitalWrite(LED8, HIGH);
      break;
  }
  if (x == 0) {                           //Mode --
    if (Mode != 1) {
      Mode--;
    }
    else Mode = 8;
  }
  else if (x == 1) {                      //Mode ++
    if (Mode != 8) {
      Mode++;
    }
    else Mode = 1;
  }
  if (Mode < 1 || Mode > 8) {             //somethings wrong, mode is out of range. set mode to 1
    Mode = 1;
  }
  int NewMode = Mode;
  switch (NewMode) {                      //turn on new LED
    case 1:
      digitalWrite(LED1, LOW);
      break;
    case 2:
      digitalWrite(LED2, LOW);
      break;
    case 3:
      digitalWrite(LED3, LOW);
      break;
    case 4:
      digitalWrite(LED4, LOW);
      break;
    case 5:
      digitalWrite(LED5, LOW);
      break;
    case 6:
      digitalWrite(LED6, LOW);
      break;
    case 7:
      digitalWrite(LED7, LOW);
      break;
    case 8:
      digitalWrite(LED8, LOW);
      break;
  }
}

void loop() {
  //Encoders
  long NewLeft, NewRight;
  NewLeft = EncLeft.read();
  NewRight = EncRight.read();

  //Push Buttons
  PushLeftState = digitalRead(PushLeft);
  PushRightState = digitalRead(PushRight);

  //Push Buttons
  if (PushLeftState == LOW || PushRightState == LOW) {        //Is a button being pushed
    if (PushReleased == 0) {                                  //is this a new press
      PushReleased = 1;                                       //button press is new, track until released
      if (PushLeftState == LOW) {
        ModeChange(0);                                        //Send left to ModeChange
      }
      else if (PushRightState == LOW) {
        ModeChange(1);                                        //Send right to ModeChange
      }
    }
    else {
      PushReleased = 0;                                        //No button currently being pushed, set PushReleased
    }
  }

  //Encoders
  if (NewLeft != OldLeft || NewRight != OldRight) {
    switch (Mode) {
      case 1:                     //Hdg
        if (NewLeft < OldLeft) {
          Joystick.button(1, 1);
          //might need delay here
          Joystick.button(1, 0);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(2, 1);
          Joystick.button(2, 0);
        }
        break;
      case 2:                     //Crs
        if (NewLeft < OldLeft) {
          Joystick.button(3, 1);
          Joystick.button(3, 0);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(4, 1);
          Joystick.button(4, 0);
        }
        break;
      case 3:                     //Alt
        if (NewLeft < OldLeft) {
          Joystick.button(5, 1);
          Joystick.button(5, 0);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(6, 1);
          Joystick.button(6, 0);
        }
        break;
      case 4:                     //VS
        if (NewLeft < OldLeft) {
          Joystick.button(7, 1);
          Joystick.button(7, 0);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(8, 1);
          Joystick.button(8, 0);
        }
        break;
      case 5:                     //Com1
        if (NewLeft < OldLeft) {
          Joystick.button(9, 1);
          Joystick.button(9, 0);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(10, 1);
          Joystick.button(10, 0);
        }
        else if (NewRight < OldRight) {
          Joystick.button(11, 1);
          Joystick.button(11, 0);
        }
        else if (NewRight > OldRight) {
          Joystick.button(12, 1);
          Joystick.button(12, 0);
        }
        break;
      case 6:                     //Com2
        if (NewLeft < OldLeft) {
          Joystick.button(13, 1);
          Joystick.button(13, 0);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(14, 1);
          Joystick.button(14, 0);
        }
        else if (NewRight < OldRight) {
          Joystick.button(15, 1);
          Joystick.button(15, 0);
        }
        else if (NewRight > OldRight) {
          Joystick.button(16, 1);
          Joystick.button(16, 0);
        }
        break;
      case 7:                     //Nav1
        if (NewLeft < OldLeft) {
          Joystick.button(17, 1);
          Joystick.button(17, 0);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(18, 1);
          Joystick.button(18, 0);
        }
        else if (NewRight < OldRight) {
          Joystick.button(19, 1);
          Joystick.button(19, 0);
        }
        else if (NewRight > OldRight) {
          Joystick.button(20, 1);
          Joystick.button(20, 0);
        }
        break;
      case 8:                     //Nav2
        if (NewLeft < OldLeft) {
          Joystick.button(21, 1);
          Joystick.button(21, 0);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(22, 1);
          Joystick.button(22, 0);
        }
        else if (NewRight < OldRight) {
          Joystick.button(23, 1);
          Joystick.button(23, 0);
        }
        else if (NewRight > OldRight) {
          Joystick.button(24, 1);
          Joystick.button(24, 0);
        }
        break;
    }
  }
  //Encoders
  OldLeft = NewLeft;
  OldRight = NewRight;
}
