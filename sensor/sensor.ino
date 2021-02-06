#include <NewPing.h>
#include <LiquidCrystal.h> // Download Liquid Crystal


int lcdRSPin = 7;
int lcdEPin = 6;
int lcdD4Pin = 5;
int lcdD5Pin = 4;
int lcdD6Pin = 3;
int lcdD7Pin = 2;

int trig = 8;
int echo = 9;

LiquidCrystal lcd(lcdRSPin, lcdEPin, lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);

UltraDistSensor mysensor;
float reading;

void setup() {
    lcd.begin(16,2);
    lcd.print("turning on");

    Serial.begin(9600);
    mysensor.attach(trig, echo);//Trigger pin , Echo pin
}

void loop() {
    reading=mysensor.distanceInCm();
     lcd.setCursor(0,0);
     lcd.print("Distance : ");
      lcd.print(reading);

    delay(1000);
}
