// TEST CODE V2 - sourced (modified) from circuito.io
// CHANGES: added Servo

// Include Libraries
#include "Arduino.h"
#include "BTHC05.h"
#include "Buzzer.h"
#include "NewPing.h"
#include "LiquidCrystal.h"
#include "LED.h"
#include "Servo.h"
#include "PiezoSpeaker.h"

// Pin Definitions
#define BTHC05_PIN_TXD 11
#define BTHC05_PIN_RXD 10
#define BUZZER_PIN_SIG 2
#define HCSR04_PIN_TRIG 4
#define HCSR04_PIN_ECHO 3
#define LCD_PIN_RS A3
#define LCD_PIN_E 13
#define LCD_PIN_DB4 7
#define LCD_PIN_DB5 8
#define LCD_PIN_DB6 9
#define LCD_PIN_DB7 12
#define LEDR_1_PIN_VIN 5
#define LEDR_2_PIN_VIN 6
#define SERVO9G_PIN_SIG A4
#define THINSPEAKER_PIN_POS A1

// Global variables and defines
const int servo9gRestPosition = 20;                                                              //Starting position
const int servo9gTargetPosition = 150;                                                           //Position when event is detected
unsigned int thinSpeakerHoorayLength = 6;                                                        // amount of notes in melody
unsigned int thinSpeakerHoorayMelody[] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5}; // list of notes. List length must match HoorayLength!
unsigned int thinSpeakerHoorayNoteDurations[] = {8, 8, 8, 4, 8, 4};                              // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match HoorayLength!
// object initialization
BTHC05 bthc05(BTHC05_PIN_RXD, BTHC05_PIN_TXD);
Buzzer buzzer(BUZZER_PIN_SIG);
NewPing hcsr04(HCSR04_PIN_TRIG, HCSR04_PIN_ECHO);
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_E, LCD_PIN_DB4, LCD_PIN_DB5, LCD_PIN_DB6, LCD_PIN_DB7);
LED ledR_1(LEDR_1_PIN_VIN);
LED ledR_2(LEDR_2_PIN_VIN);
Servo servo9g;
PiezoSpeaker thinSpeaker(THINSPEAKER_PIN_POS);

// define vars for testing menu
const int timeout = 10000; //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial)
        ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");

    bthc05.begin(9600);
    //This example uses HC-05 Bluetooth to communicate with an Android device.
    //Download bluetooth terminal from google play store, https://play.google.com/store/apps/details?id=Qwerty.BluetoothTerminal&hl=en
    //Pair and connect to 'HC-05', the default password for connection is '1234'.
    //You should see this message from your arduino on your android device
    bthc05.println("Bluetooth On....");
    // set up the LCD's number of columns and rows
    lcd.begin(16, 2);
    servo9g.attach(SERVO9G_PIN_SIG);
    servo9g.write(servo9gRestPosition);
    delay(100);
    servo9g.detach();
    menuOption = menu();
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{

    if (menuOption == '1')
    {
        // HC - 05 Bluetooth Serial Module - Test Code
        String bthc05Str = "";
        //Receive String from bluetooth device
        if (bthc05.available())
        {
            //Read a complete line from bluetooth terminal
            bthc05Str = bthc05.readStringUntil('\n');
            // Print raw data to serial monitor
            Serial.print("BT Raw Data: ");
            Serial.println(bthc05Str);
        }
        //Send sensor data to Bluetooth device
        //Send sensor data to Bluetooth device
        //Send sensor data to Bluetooth device
        bthc05.println("PUT YOUR SENSOR DATA HERE");
    }
    else if (menuOption == '2')
    {
        // Buzzer - Test Code
        // The buzzer will turn on and off for 500ms (0.5 sec)
        buzzer.on();  // 1. turns on
        delay(500);   // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
        buzzer.off(); // 3. turns off.
        delay(500);   // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if (menuOption == '3')
    {
        // Ultrasonic Sensor - HC-SR04 - Test Code
        // Read distance measurment from UltraSonic sensor
        // Read distance measurment from UltraSonic sensor
        // Read distance measurment from UltraSonic sensor
        int hcsr04Dist = hcsr04.ping_cm();
        delay(10);
        Serial.print(F("Distance: "));
        Serial.print(hcsr04Dist);
        Serial.println(F("[cm]"));
    }
    else if (menuOption == '4')
    {
        // LCD 16x2 - Test Code
        // Print a message to the LCD.
        lcd.setCursor(0, 0);
        lcd.print("Circuito Rocks !");
        // Turn off the display:
        lcd.noDisplay();
        delay(500);
        // Turn on the display:
        lcd.display();
        delay(500);
    }
    else if (menuOption == '5')
    {
        // LED - Basic Red 5mm #1 - Test Code
        // The LED will turn on and fade till it is off
        for (int i = 255; i > 0; i -= 5)
        {
            ledR_1.dim(i); // 1. Dim Led 1
            ledR_2.dim(i); // 2. Dim Led 2
            delay(15);     // 3. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
        }
        ledR_1.off(); // 4. turns off
        ledR_2.off(); // 5. turns off
    }
    else if (menuOption == '6')
    {
        // 9G Micro Servo - Test Code
        // The servo will rotate to target position and back to resting position with an interval of 500 milliseconds (0.5 seconds)
        servo9g.attach(SERVO9G_PIN_SIG);      // 1. attach the servo to correct pin to control it.
        servo9g.write(servo9gTargetPosition); // 2. turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
        delay(500);                           // 3. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
        servo9g.write(servo9gRestPosition);   // 4. turns servo back to rest position. Modify initial position by modifying the 'ServoRestPosition' definition above.
        delay(500);                           // 5. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
        servo9g.detach();                     // 6. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    }
    else if (menuOption == '7')
    {
        // Thin Speaker - Test Code
        // The Speaker will play the Hooray tune
        thinSpeaker.playMelody(thinSpeakerHoorayLength, thinSpeakerHoorayMelody, thinSpeakerHoorayNoteDurations);
        thinSpeaker.playMelody(thinSpeakerHoorayLength, thinSpeakerHoorayMelody, thinSpeakerHoorayNoteDurations);
        thinSpeaker.playMelody(thinSpeakerHoorayLength, thinSpeakerHoorayMelody, thinSpeakerHoorayNoteDurations);
        delay(500);
        delay(500);
        delay(500);
    }

    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
}

// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) HC - 05 Bluetooth Serial Module"));
    Serial.println(F("(2) Buzzer"));
    Serial.println(F("(3) Ultrasonic Sensor - HC-SR04"));
    Serial.println(F("(4) LCD 16x2"));
    Serial.println(F("(5) LED - Basic Red 5mm #1"));
    Serial.println(F("(6) 9G Micro Servo"));
    Serial.println(F("(7) Thin Speaker"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available())
        ;

    // Read data from serial monitor if received
    while (Serial.available())
    {
        char c = Serial.read();
        if (isAlphaNumeric(c))
        {

            if (c == '1')
                Serial.println(F("Now Testing HC - 05 Bluetooth Serial Module"));
            else if (c == '2')
                Serial.println(F("Now Testing Buzzer"));
            else if (c == '3')
                Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04"));
            else if (c == '4')
                Serial.println(F("Now Testing LCD 16x2"));
            else if (c == '5')
                Serial.println(F("Now Testing LED - Basic Red 5mm #1"));
            else if (c == '6')
                Serial.println(F("Now Testing 9G Micro Servo"));
            else if (c == '7')
                Serial.println(F("Now Testing Thin Speaker"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/