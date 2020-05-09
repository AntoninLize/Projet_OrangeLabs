#include "DualVNH5019MotorShield.h"

//---------------------------------------------Variables moteurs----------------------------------------------//
DualVNH5019MotorShield md;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
String avancer = "8\n";
String reculer = "2\n";
String arret = "5\n";

void stopIfFault()
{
  if (md.getM1Fault())
  {
    Serial.println("M1 fault");
    while(1);
  }
  if (md.getM2Fault())
  {
    Serial.println("M2 fault");
    while(1);
  }
}

//--------------------------------------------------Variables codeurs--------------------------------------------------//

int val;
int encoder1PinA = 3;
int encoder1PinB = 4;
int nbre_ticks = 0;
int previous_nbre_ticks = LOW;
int n = LOW;

//---------------------------------------------------------------------FONCTIONS CODEUR-------------------------------------------------------------------//

void compte_tour() {
  n = digitalRead(encoder1PinA);
  if ((previous_nbre_ticks == LOW) && (n == HIGH)) {
    if (digitalRead(encoder1PinB) == LOW) {
      nbre_ticks--;
    } 
    else {
      nbre_ticks++;
    }
    Serial.print (nbre_ticks);
    Serial.print ("/");
  }
  previous_nbre_ticks = n; 
}

//---------------------------------------------------------------------FONCTIONS NAVIGATION-------------------------------------------------------------------//

void forward() {
  md.setM1Speed(50);
}

void backward() {
  md.setM1Speed(-50);
}

void stop() {
  md.setM1Speed(0);
}
//-----------------------------------------------------------SETUP------------------------------------------------------------//
void setup() {
  inputString.reserve(200);
  pinMode (encoder1PinA, INPUT);
  pinMode (encoder1PinB, INPUT);
  Serial.begin (9600);
  Serial.println("Dual VNH5019 Motor Shield");
  md.init();
}
//-----------------------------------------------------------LOOP------------------------------------------------------------//
void loop() {
   if (stringComplete) {
      if (inputString == avancer) {
        Serial.println(inputString);
        forward();
      }
      else if (inputString == reculer) {
        Serial.println(inputString);
        backward();
      }
      else if (inputString == arret) {
        Serial.println(inputString);
        stop();
      }
      // clear the string:
      inputString = "";
      stringComplete = false;
    }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
