//led display
#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//ultrasonic sensor
#define echoPin 2
#define trigPin 3 

//sound output; A Minor pentatonic scale
#define buzzer 11
int distance = 0;
int previous;
int distanceHigh = 0;
int lengthOfScale = 0;

int note = 0;
//int scale[] = { //A-minor scale
//  147, 165, 196, 220, 262, 294, 330, 392, 440,
//  523, 587, 659, 784, 880, 1047, 1175, 1319, 1568,
//  1760, 2093, 2349
//};
int scale[] = { //C-major scale
  131, 147, 165, 175, 196, 220, 247, 262, 294,
  330, 349, 392, 440, 494, 523, 587, 659, 698,
  784, 880, 988, 1047
};

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  

  while (millis() < 5000) {
    digitalWrite(trigPin, HIGH);
    digitalWrite(trigPin, LOW);
    distance = pulseIn(echoPin, HIGH);

    if (distance > distanceHigh) {
      distanceHigh = distance;
    }
  }

    for (byte i = 0; i < (sizeof(scale) / sizeof(scale[0])); i++) {
    lengthOfScale += 1;
  }
  
  lcd.begin(16, 2);

  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  distance = pulseIn(echoPin, HIGH);

  note = map(distance, 250, distanceHigh, scale[0], scale[lengthOfScale - 1]);

  for (byte j = 0; j < (lengthOfScale); j++) {
    
    if (note == scale[j]) {
      tone(buzzer, note);
      break;
    } else if (note > scale[j] && note < scale[j + 1]) {
      note = scale[j];
      tone(buzzer, note);
      break;
    }
  }

  delay(30);

  //LCD display
  lcd.setCursor(0,1);

  if (previous != distance) { //if distance updates, then displace the value
    lcd.print(distance);
  }
}
