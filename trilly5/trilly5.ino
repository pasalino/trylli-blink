// PWM outputs connected to LED driver circuits
const int giallo1 = 3;//Red LED drive
const int giallo2 = 5;//Green LED drive
const int bianco = 6;//Blue LED drive
const int power = 4; //Always on for soundsensor

const int sensore_suono = 2; //Sensore sonoro attivo basso

// initial value for the variable resistors
long val_giallo1 = 0;
long val_giallo2 = 0;
long val_bianco = 0;

int side_giallo1 = +1;
int side_giallo2 = +1;
int side_bianco = +1;

int wait_time = 50;

int casual = 0;
int count = 0;

bool debug = false;

void setup() {
  //Serial
  Serial.begin(9600);
  if (debug) Serial.println("Inizio\n");
  //Pin led
  pinMode(giallo1, OUTPUT);
  pinMode(giallo2, OUTPUT);
  pinMode(bianco, OUTPUT);
  pinMode(power, OUTPUT);

  digitalWrite(power, HIGH);

  //Sensore sonoro
  attachInterrupt(digitalPinToInterrupt(sensore_suono), clap, FALLING);

  //Valori iniziali led
  val_bianco = 0;
  val_giallo1 = 0;
  val_giallo2 = 128000;
}

void loop() {
  
  //Fade gialli
  fade(giallo1, &val_giallo1, &side_giallo1, 2000);

  fade(giallo2, &val_giallo2, &side_giallo2, 4000);

  //Effetti blink
  switch (casual) {
    case 1:
      //Rapid blink
      Serial.println("BLink 80");
      rapid_blink(bianco, &val_bianco, 140);
      break;
    case 2:
      //Rapid blink
      Serial.println("BLink 40");
      rapid_blink(bianco, &val_bianco, 40);
      break;
    case 3:
      //Fade lento
      Serial.println("Fade lento");
      fade_blink(bianco, &val_bianco, &side_bianco, 5000);
      break;
    case 4:
      //Fade veloce
      Serial.println("Fade lento lento");
      fade_blink(bianco, &val_bianco, &side_bianco, 2000);
      break;
    case 5:
      //Sempre attivo
      Serial.println("Top white");
      top_high();
      break;
    case 6:
      //Tutto spento
      Serial.println("Bottom low");
      bottom_low();
      break;
    case 7:
      //Blink piccolo
      Serial.println("Blink 10");
      rapid_blink(bianco, &val_bianco, 40);
      break;
    case 8:
      //Rapid blink
      Serial.println("Blink 40");
      rapid_blink(bianco, &val_bianco, 160);
      break;
    case 9:
      //Fade lentissimo
      Serial.println("Fade lentissimo");
      fade_blink(bianco, &val_bianco, &side_bianco, 1000);
      break;
    case -1:
      //Clapclap
      rapid_blink_clap();
      break;
    default:
      if (casual < 0) {
        break;
      }
      //Generatore colore
      casual = random(600);
      if (debug) Serial.print("Casual: ");
      if (debug) Serial.println(casual);
      break;
  }

  delay(wait_time);
}

void top_high() {
  static unsigned long val = 0;
  
  if (count < 50) {
    count++;
    if(val<255) val +=60;
    if (debug) Serial.println(count);
  } else {
    val = 20;
    count = 0;
    casual = 0;
  }
  val_giallo1 = 255000;
  val_giallo2 = 255000;
  side_giallo1 = -1;
  side_giallo2 = -1;
  
  analogWrite(bianco, val);
}

void bottom_low() {
  if (count < 50) {
    count++;
    if(val_bianco>0) val_bianco -=60;
    if (debug) Serial.println(count);
  } else {
    val_bianco = 255;
    count = 0;
    casual = 0;
  }
  val_giallo1 = 0;
  val_giallo2 = 0;
  side_giallo1 = +1;
  side_giallo2 = +1;
  analogWrite(bianco, val_bianco);
}

void fade(int led, long* value, int* side, long step_value) {
  *value += *side * step_value;

  if (*value >= 255000) {
    *side = -1;
    *value = 255000;
  } else if (*value <= 20) {
    *side = +1;
    *value = 20;
  }
  analogWrite(led, *value / 1000);
}

void fade_blink(int led, long* value, int* side, long step_value) {
  if (debug) Serial.print("Fade");
  *value += *side * step_value;

  if (*value >= 255000) {
    *side = -1;
    *value = 255000;
  } else if (*value <= 0) {
    *side = +1;
    *value = 20;
    casual = 0;
  }
  analogWrite(led, *value / 1000);
}

void rapid_blink(int led, long* value, int blink_n) {
  //Controllo di ciclo
  if (count < blink_n) {
    count++;
    if (debug) Serial.print("Count: ");
    if (debug) Serial.println(count);
  } else {
    Serial.println("End blink");
    analogWrite(led, 20);
    count = 0;
    casual = 0;
    return;
  }

  if(count % 2 != 0) return;


  if (*value != 255 && *value != 0) {
    *value = 20;
  }
  if (*value == 255) {
    *value = 20;
  } else {
    *value = 255;
  }
  analogWrite(led, *value);
}

void rapid_blink_clap() {
  //Controllo di ciclo
  if (count < 20) {
    count++;
    if (debug) Serial.print("Count: ");
    if (debug) Serial.println(count);
  } else {
    Serial.println("End blink");
    analogWrite(bianco, 20);
    count = 0;
    casual = 0;
    return;
  }

  if (val_bianco != 255 && val_bianco != 0) {
    val_bianco = 20;
  }
  if (val_bianco == 255) {
    val_bianco = 20;
  } else {
    val_bianco = 255;
  }
  analogWrite(bianco, val_bianco);
}

void reset_white() {
  analogWrite(bianco, 0);
  val_bianco = 0;
}

void clap() {
  static unsigned long last_interrupt_time = 0;
  static unsigned long last_clap = 0;
  static int count_clap = 0;
  unsigned long interrupt_time = millis();


  if (interrupt_time - last_clap > 1000) {
      Serial.println("Azzera");
      count_clap = 0;
  }
  
  if (interrupt_time - last_interrupt_time > 100) {
    count_clap++;
    Serial.print("Clap: ");
    Serial.println(count_clap);

    Serial.print("Last clap: ");
    Serial.println(last_clap);
    Serial.print("Difference clap: ");
    Serial.println(interrupt_time - last_clap);

    if (count_clap == 1) {
      Serial.println("un clap");
      last_clap = millis();
    }

    if (count_clap >= 2) {
      Serial.println("due clap");
      Serial.print("Span:");
      Serial.println(interrupt_time - last_clap);
      if (interrupt_time - last_clap < 500) {
        Serial.println("Start clap clap");
        count = 0;
        casual = -1;
        reset_white();
      }
      last_clap = 0;
      count_clap = 0;
    }
  }

  last_interrupt_time = interrupt_time;
}


