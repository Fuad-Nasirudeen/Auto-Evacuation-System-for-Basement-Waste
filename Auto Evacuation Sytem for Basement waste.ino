#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  //Include LCD Library

// LCD wiring
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ultrasonic pins
#define TRIG 6
#define ECHO 5

// Pump relays
#define PUMP1 3
#define PUMP2 4

// Button Pin
#define button 7

// Tank parameters
const int tankHeight = 17; // cm
const int startDrainLevel = 70; // % full
const int stopDrainLevel = 20; // % full

bool pump1On = false;
bool pump2On = false;

// Automatic Drain Time
unsigned long lastDrainTime = 0;
const unsigned long drainInterval = 3L * 60L * 1000L; // 3 mins

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(PUMP1, OUTPUT);
  pinMode(PUMP2, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  digitalWrite(PUMP1, LOW);
  digitalWrite(PUMP2, LOW);

  lcd.init();
  lcd.backlight();
  lcd.print("Extraction Sys");
  delay(2000);  // Welcome screen
  lcd.clear();
}

float getLevelPercent() {
  // Measure distance
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH);
  float distance = duration * 0.034 / 2; // cm

  // Convert to % full    
  float level = tankHeight - distance;
  return constrain((level / tankHeight) * 100, 0, 100);
}



void loop() {
  float levelPercent = getLevelPercent();
  unsigned long currentTime = millis();
  

  //Display status
  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.print(levelPercent);
  lcd.print("%  ");
  lcd.setCursor(0, 1);
  if (pump1On)
    lcd.print("Pump1: ON ");
  else if (pump2On)
    lcd.print("P1:Failed P2:ON");
  else
    lcd.print("Pumps: OFF ");

  delay(1000);


  // Time-based trigger OR Level-based trigger
  bool timeToDrain = (currentTime - lastDrainTime >= drainInterval);
  bool levelHigh = (levelPercent >= startDrainLevel);

  bool manualdrain = !
digitalRead(button);


  if (levelHigh || manualdrain)  {
    if (!pump1On) {
      digitalWrite(PUMP1, HIGH);
      pump1On = true;
      delay(10000); // give Pump 1 a chance
      if (getLevelPercent() >= startDrainLevel) {
        // Pump 1 failed in a level-trigger situation
        digitalWrite(PUMP1, LOW);
        pump1On = false;
        digitalWrite(PUMP2, HIGH);
        pump2On = true;
      }
    }
    lastDrainTime = millis(); // reset timer after starting a drain

  } else if (timeToDrain) {
  // Timer-based drain logic
  if (levelPercent > stopDrainLevel) {  
    if (!pump1On) {
      digitalWrite(PUMP1, HIGH);
      pump1On = true;
      delay(10000);
      if (getLevelPercent() >= startDrainLevel && !timeToDrain) {
        // Pump 1 failed in a level-trigger situation
        digitalWrite(PUMP1, LOW);
        pump1On = false;
        digitalWrite(PUMP2, HIGH);
        pump2On = true;
      }
    }
    lastDrainTime = millis();
  } 

} 
  else if (levelPercent <= stopDrainLevel) {
  digitalWrite(PUMP1, LOW);
  digitalWrite(PUMP2, LOW);
  pump1On = false;
  pump2On = false;
} 
  delay(1000);
}  