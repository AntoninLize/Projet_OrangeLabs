#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include "DualVNH5019MotorShield.h"
//---------------------------------------------Variables moteurs----------------------------------------------//
DualVNH5019MotorShield md;

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
int encoder0PinA = 3;
int encoder0PinB = 4;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

//--------------------------------------------------Variables ROS--------------------------------------------------//

ros::NodeHandle  nh;
char *message;
int commande_moteur;
String valeur_enc;
int k=1;

void messageCb(std_msgs::String& msg){
    message = msg.data;
}

ros::Subscriber<std_msgs::String> sub("cmd_motor", &messageCb);


std_msgs::String str_msg;
ros::Publisher pub("value_encoder", &str_msg);

//---------------------------------------------------------------------FONCTIONS CODEUR-------------------------------------------------------------------//

void compte_ticks() {
    
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos++;
    } else {
      encoder0Pos--;
    }
    
    //Serial.print (encoder0Pos);
    //Serial.print ("/");
  }

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

void setup()
{
  Serial.begin(57600);
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  md.init();
 
  nh.initNode();
  nh.advertise(pub);
  nh.subscribe(sub);

  TCCR2B = 0b00000011;
}

//-----------------------------------------------------------LOOP------------------------------------------------------------//

//  TCNT2 = 0 ;
/*
 * Code à mesurer à placer ici
 */
//  int Nombre_de_cycles_horloge = TCNT2 ;
//  Serial.print("Nbre de tour d'horloge =");
//  Serial.println(Nombre_de_cycles_horloge); 

void loop()
{

  commande_moteur = String(message).toInt(); 
  md.setM1Speed(commande_moteur); // 7 cycles horloges 500kHz = 14**10^-6s
 
  
  n = digitalRead(encoder0PinA);
  compte_ticks();
  encoder0PinALast = n; // 3 cycles horloges 500kHz = 6**10^-6s
  
  if (k==100){
    
    valeur_enc = String(encoder0Pos);
    str_msg.data = &valeur_enc[0]; // 21 cycles horloges 500kHz = 42**10^-6s
    pub.publish( &str_msg ); // 103 cycles horloges 16MHz = 6,43*10^-6s
    nh.spinOnce(); // 10 cycles horloges 500kHz = 6,43*10^-6s

    k=1;
  }
  else{
    k++;
  }
}
