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

int counter = 0;

LiquidCrystal lcd(lcdRSPin, lcdEPin, lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);

NewPing sonar (trig, echo);
float reading;

void setup() {
    lcd.begin(16,2);
    lcd.print("turning on");

    Serial.begin(9600);
}

void loop() {
    reading=sonar.ping_cm();
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
      lcd.setCursor(0,0);
      lcd.print("Please stand 2m away");

      tone(buzzer, 1000, 1000);
      delay (1000);
  
      noTone(buzzer);
      delay (1000);
      
    }
      

    delay(1000);

    
}
