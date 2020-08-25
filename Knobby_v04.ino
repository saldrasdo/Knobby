#include <RotaryEncoder.h>

//Rotary Encoder Init
RotaryEncoder EncLeft(5, 6);
RotaryEncoder EncRight(7, 8);

//Define Number of LEDs and give them pins
const int LEDNum = 8;
const int LED[8] = {9, 10, 11, 12, 14, 15, 16, 17};

//Define pins for push buttons
const int PushLeft = 0;
const int PushRight = 1;

//Define mode variables
int Mode = 0;
const int ModeMin = 0;
const int ModeMax = 7;

//Encoder
long OldLeft  = -1;
long OldRight = -1;

//Joystick push delays. delay after sending joystick commands to usb in millis
int PreDelay = 40;
int PostDelay = 20;

//Push Buttons
boolean PushLeftState = HIGH;     //Left State
boolean PushRightState = HIGH;    //Right State
boolean PushReleased = 0;         //Has button been released state

void setup() {
  Serial.begin(57600);

  //Cheeky LED pins init
  for (int i = ModeMin; i > LEDNum; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH);
    delay(250);
    digitalWrite(LED[i], LOW);
    delay(25);
  }

  //Turn on LED1 to match Mode
  digitalWrite(LED[Mode], HIGH);

  //Push Button Pin Init
  pinMode(PushLeft, INPUT_PULLUP);
  pinMode(PushRight, INPUT_PULLUP);

  //Encoder
  EncLeft.setPosition(1);
  EncRight.setPosition(1);
}

void ModeChange(int Dir) {
  /*Mode Section
    0= Hdg small/large
    1= Crs 1/2
    2= Alt 1000/100
    3= Spd/VS
    4= Com1/Com1 decimal
    5= Com2/Com2 decimal
    6= Nav1/Nav1 decimal
    7= Nav2/Nav2 decimal

    Function to change mode and led
    x accepts 0 or 1
    0 = left
    1 = right
  */

  for (int i = 0; i < LEDNum; i++) {             //Turn off all leds
    digitalWrite(LED[i], LOW);
  }
  if (Mode < ModeMin || Mode > ModeMax) {        //somethings wrong, mode is out of range. set mode to 1
    Mode = ModeMin;
  }
  else if (Dir == 0) {                           //Mode --
    if (Mode != ModeMin) {
      Mode--;
    }
    else Mode = ModeMax;
  }
  else if (Dir == 1) {                            //Mode ++
    if (Mode != ModeMax) {
      Mode++;
    }
    else Mode = ModeMin;
  }
  digitalWrite(LED[Mode], HIGH);
}

void loop() {
  //Push Buttons, Mode Buttons
  PushLeftState = digitalRead(PushLeft);                      //Get button states
  PushRightState = digitalRead(PushRight);
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
  }
  else {
    PushReleased = 0;                                        //No button currently being pushed, set PushReleased
  }

  //Encoders
  EncLeft.tick();
  EncRight.tick();
  long NewLeft = EncLeft.getPosition();
  long NewRight = EncRight.getPosition();
  if (NewLeft != OldLeft || NewRight != OldRight) {
    switch (Mode) {
      case 1:
        //Hdg
        if (NewLeft < OldLeft) {
          Joystick.button(1, 1);
          delay(PreDelay);
          Joystick.button(1, 0);
          delay(PostDelay);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(2, 1);
          delay(PreDelay);
          Joystick.button(2, 0);
          delay(PostDelay);
        }
        //Hdg fast?
        else if (NewRight < OldRight) {
          Joystick.button(3, 1);
          delay(PreDelay);
          Joystick.button(3, 0);
          delay(PostDelay);
        }
        else if (NewRight > OldRight) {
          Joystick.button(4, 1);
          delay(PreDelay);
          Joystick.button(4, 0);
          delay(PostDelay);
        }
        break;
      case 2:
        //Crs 1
        if (NewLeft < OldLeft) {
          Joystick.button(5, 1);
          delay(PreDelay);
          Joystick.button(5, 0);
          delay(PostDelay);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(6, 1);
          delay(PreDelay);
          Joystick.button(6, 0);
          delay(PostDelay);
        }
        //Crs 2
        else if (NewRight < OldRight) {
          Joystick.button(7, 1);
          delay(PreDelay);
          Joystick.button(7, 0);
          delay(PostDelay);
        }
        else if (NewRight > OldRight) {
          Joystick.button(8, 1);
          delay(PreDelay);
          Joystick.button(8, 0);
          delay(PostDelay);
        }
        break;
      case 3:
        //Alt +-1000
        if (NewLeft < OldLeft) {
          Joystick.button(9, 1);
          delay(PreDelay);
          Joystick.button(9, 0);
          delay(PostDelay);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(10, 1);
          delay(PreDelay);
          Joystick.button(10, 0);
          delay(PostDelay);
        }
        //Alt +-100
        else if (NewRight < OldRight) {
          Joystick.button(11, 1);
          delay(PreDelay);
          Joystick.button(11, 0);
          delay(PostDelay);
        }
        else if (NewRight > OldRight) {
          Joystick.button(12, 1);
          delay(PreDelay);
          Joystick.button(12, 0);
          delay(PostDelay);
        }
        break;
      case 4:
        //Spd
        if (NewLeft < OldLeft) {
          Joystick.button(13, 1);
          delay(PreDelay);
          Joystick.button(13, 0);
          delay(PostDelay);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(14, 1);
          delay(PreDelay);
          Joystick.button(14, 0);
          delay(PostDelay);
        }
        //VS
        else if (NewRight < OldRight) {
          Joystick.button(15, 1);
          delay(PreDelay);
          Joystick.button(15, 0);
          delay(PostDelay);
        }
        else if (NewRight > OldRight) {
          Joystick.button(16, 1);
          delay(PreDelay);
          Joystick.button(16, 0);
          delay(PostDelay);
        }
        break;
      case 5:
        //Com1
        if (NewLeft < OldLeft) {
          Joystick.button(17, 1);
          delay(PreDelay);
          Joystick.button(17, 0);
          delay(PostDelay);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(18, 1);
          delay(PreDelay);
          Joystick.button(18, 0);
          delay(PostDelay);
        }
        //Com1 decimal
        else if (NewRight < OldRight) {
          Joystick.button(19, 1);
          delay(PreDelay);
          Joystick.button(19, 0);
          delay(PostDelay);
        }
        else if (NewRight > OldRight) {
          Joystick.button(20, 1);
          delay(PreDelay);
          Joystick.button(20, 0);
          delay(PostDelay);
        }
        break;
      case 6:
        //Com2
        if (NewLeft < OldLeft) {
          Joystick.button(21, 1);
          delay(PreDelay);
          Joystick.button(21, 0);
          delay(PostDelay);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(22, 1);
          delay(PreDelay);
          Joystick.button(22, 0);
          delay(PostDelay);
        }
        //Com2 decimal
        else if (NewRight < OldRight) {
          Joystick.button(23, 1);
          delay(PreDelay);
          Joystick.button(23, 0);
          delay(PostDelay);
        }
        else if (NewRight > OldRight) {
          Joystick.button(24, 1);
          delay(PreDelay);
          Joystick.button(24, 0);
          delay(PostDelay);
        }
        break;
      case 7:
        //Nav1
        if (NewLeft < OldLeft) {
          Joystick.button(25, 1);
          delay(PreDelay);
          Joystick.button(25, 0);
          delay(PostDelay);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(26, 1);
          delay(PreDelay);
          Joystick.button(26, 0);
          delay(PostDelay);
        }
        //Nav1 Decimal
        else if (NewRight < OldRight) {
          Joystick.button(27, 1);
          delay(PreDelay);
          Joystick.button(27, 0);
          delay(PostDelay);
        }
        else if (NewRight > OldRight) {
          Joystick.button(28, 1);
          delay(PreDelay);
          Joystick.button(28, 0);
          delay(PostDelay);
        }
        break;
      case 8:
        //Nav2
        if (NewLeft < OldLeft) {
          Joystick.button(29, 1);
          delay(PreDelay);
          Joystick.button(29, 0);
          delay(PostDelay);
        }
        else if (NewLeft > OldLeft) {
          Joystick.button(30, 1);
          delay(PreDelay);
          Joystick.button(30, 0);
          delay(PostDelay);
        }
        //Nav2 Decimal
        else if (NewRight < OldRight) {
          Joystick.button(31, 1);
          delay(PreDelay);
          Joystick.button(31, 0);
          delay(PostDelay);
        }
        else if (NewRight > OldRight) {
          Joystick.button(32, 1);
          delay(PreDelay);
          Joystick.button(32, 0);
          delay(PostDelay);
        }
        break;
    }
  }
  //Encoders
  OldLeft = NewLeft;
  OldRight = NewRight;
}
