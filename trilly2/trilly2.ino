#include <SoftPWM.h>


 // PWM outputs connected to LED driver circuits
const int giallo1 = 3;//Red LED drive
const int giallo2 = 5;//Green LED drive
const int bianco = 6;//Blue LED drive

// initial value for the variable resistors
int val_giallo1 = 0;
int val_giallo2 = 0;
int val_bianco = 0;

int fadeUp = 200;
int fadeDown = 500;
int de = 2000;

  
void setup() {
  SoftPWMBegin();
  SoftPWMSet(giallo1, LOW);
  SoftPWMSet(giallo2, LOW);
  SoftPWMSet(bianco, LOW);
  
  SoftPWMSetFadeTime(giallo1, 2000, fadeDown);
  SoftPWMSetFadeTime(giallo2, fadeUp, fadeDown);
  SoftPWMSetFadeTime(bianco, fadeUp, fadeDown);
}

void loop() {
  game_one();
}

void game_one() {
  SoftPWMSetPercent(giallo1, 100);
  SoftPWMSetPercent(giallo2, 100);
  SoftPWMSetPercent(bianco, 100);
  delay(de);
  SoftPWMSetPercent(giallo1, 0);
  SoftPWMSetPercent(giallo2, 0);
  SoftPWMSetPercent(bianco, 0);
  delay(de);
}

void rapidblink(){
  
}

