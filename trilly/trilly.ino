// PWM outputs connected to LED driver circuits
const int giallo1 = 3;//Red LED drive
const int giallo2 = 5;//Green LED drive
const int bianco = 6;//Blue LED drive

// initial value for the variable resistors
int val_giallo1 = 0;
int val_giallo2 = 0;
int val_bianco = 0;

void setup() {
   // set the drive pins as output:
   pinMode(giallo1, OUTPUT);
   pinMode(giallo2, OUTPUT);
   pinMode(bianco, OUTPUT);
}

void loop() {
   // read the variable resistors, convert it to 0 - 255
   val_giallo1 = 255;
   val_giallo2 = 255;
   val_bianco = 255;
   
   // use the data to control the drive:
   analogWrite(giallo1, val_giallo1);
   analogWrite(giallo2, val_giallo2);
   analogWrite(bianco, val_bianco);
}
