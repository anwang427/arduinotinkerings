#include <LiquidCrystal.h>
#define echoPin 2
#define trigPin 3 
#define buzzer 11
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// defines variables
long duration; // variable for sound wave travel duration
int distance; // variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);

  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  if (distance < 150) { //only sound when in danger of colliding
    tone(buzzer, 800);
    delay(distance * 8);
    noTone(buzzer);
    delay(distance * 8);
  }
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  //LCD display
  lcd.setCursor(0,1);
  lcd.print(distance);
}
