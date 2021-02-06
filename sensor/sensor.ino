#include <NewPing.h> //import ultrasonic library
#include <LiquidCrystal.h> // Import LCD library


int lcdRSPin = 7; // set pins for LCD
int lcdEPin = 6;
int lcdD4Pin = 5;
int lcdD5Pin = 4;
int lcdD6Pin = 3;
int lcdD7Pin = 2;

int trig = 8; //set pins for ultrasonic
int echo = 9;

int buzzer = 10; //set buzzer pin

int led1 = 11;
int led2 = 12;

int counter = 0;

LiquidCrystal lcd(lcdRSPin, lcdEPin, lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);

NewPing sonar (trig, echo);
float reading;

void setup() {
    lcd.begin(16,2);
    lcd.print("turning on");

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);

    Serial.begin(9600);
}

void loop() {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    reading=sonar.ping_cm();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Distance : ");
    lcd.print(reading);
    Serial.println(reading);

    if (reading < 200){
      counter++;
    }
    else{
      counter = 0;
    }

    if (counter >= 5){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Please stand 2m ");
      lcd.setCursor(0,1);
      lcd.print("away");

      tone(buzzer, 1000, 1000);
      digitalWrite (led1, HIGH);
      digitalWrite (led2, HIGH);
      delay (1000);
  
      noTone(buzzer);
      digitalWrite (led1,  LOW);
      digitalWrite (led2, LOW);
      delay (1000);
      
    }
      

    delay(1000);

    
}
