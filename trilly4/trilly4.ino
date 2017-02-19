// PWM outputs connected to LED driver circuits
const int giallo1 = 3;//Red LED drive
const int giallo2 = 5;//Green LED drive
const int bianco = 6;//Blue LED drive

// initial value for the variable resistors
long val_giallo1 = 0;
long val_giallo2 = 0;
long val_bianco = 0;

int side_giallo1 = +1;
int side_giallo2 = +1;
int side_bianco = +1;

int wait_time = 100;

int casual = 0;
int count = 0;

void setup() {
  Serial.println("Inizio\n");
  
  Serial.begin(9600); 
  pinMode(giallo1, OUTPUT);  
  pinMode(giallo2, OUTPUT); 
  pinMode(bianco, OUTPUT); 
  val_bianco = 0;
  val_giallo1 = 0;
  val_giallo2 = 128000;
}

void loop() {
  
  fade(giallo1,&val_giallo1,&side_giallo1,10000);
  
  fade(giallo2,&val_giallo2,&side_giallo2,20000);

  switch(casual) {
    case 1:
      rapid_blink(bianco,&val_bianco,20);
      break;
    case 2:
      rapid_blink(bianco,&val_bianco,5);
      break;
    case 3:
      fade_blink(bianco,&val_bianco,&side_bianco,50000);
      break;
    case 4:
      fade_blink(bianco,&val_bianco,&side_bianco,5000);
      break;
    case 5:
      Serial.println("Top bianco");
      if (count<100) {
        count++;   
        Serial.println(count);
      } else {
        count = 0;
        casual = 0;
      }
      val_giallo1 = 255000;
      val_giallo2 = 255000;
      side_giallo1 = -1;
      side_giallo2 = -1;
      analogWrite(bianco, 255);
      break;
    case 6:
      Serial.println("Bottom bianco");
      if (count<50) {
        count++;   
        Serial.println(count);
      } else {
        count = 0;
        casual = 0;
      }
      val_giallo1 = 0;
      val_giallo2 = 0;
      side_giallo1 = +1;
      side_giallo2 = +1;
      analogWrite(bianco, 10);
      break;
    case 7:
      rapid_blink(bianco,&val_bianco,2);
      break;
    case 8:
      rapid_blink(bianco,&val_bianco,20);
      break;
    case 9:
      fade_blink(bianco,&val_bianco,&side_bianco,100000);
      break;
    default:
      casual = random(300);
      Serial.print("Casual: ");
      Serial.println(casual);
      break;
  }
  
  delay(wait_time);
}

void fade(int led,long* value, int* side, long step_value) {  
  *value += *side * step_value;
  
  if(*value >= 255000){
    *side = -1;
    *value = 255000;
  }else if(*value<= 0) {
    *side = +1;
    *value = 0;
  }
  analogWrite(led, *value/1000);
}

void fade_blink(int led,long* value, int* side, long step_value) {  
  Serial.print("Fade");
  *value += *side * step_value;
  
  if(*value >= 255000){
    *side = -1;
    *value = 255000;
  }else if(*value<= 0) {
    *side = +1;
    *value = 20;
    casual = 0;
  }
  analogWrite(led, *value/1000);
}

void rapid_blink(int led,long* value, int blink_n) {
  if (count<blink_n) {
    count++;   
    Serial.print("Count: ");
    Serial.println(count);
  } else {
    Serial.println("End blink");
    analogWrite(led, 20);
    count = 0;
    casual = 0;
    return;
  }
  
  if(*value != 128 && *value != 0) {
    *value = 20;
  }
  if(*value == 128) {
    *value = 20;
  } else { 
    *value = 128;
  }
  analogWrite(led, *value);
}

