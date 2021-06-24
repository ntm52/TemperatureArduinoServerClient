#include <LiquidCrystal.h>
#include "IRremote.h"

int tempDesired = 0;
int tempReceived = 0;
int receiver = 13;
float tempF = 10.0;
float tempC = 5.0;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
IRrecv irrecv(receiver);
decode_results results;

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
  irrecv.enableIRIn();

}

void loop() {
  
  if (Serial.available() > 0) {
    tempReceived = Serial.read();

    Serial.print("Received: ");
    Serial.println(tempReceived, DEC);

    lcd.setCursor(0, 0);

    if (tempDesired == 1) {
   
      lcd.print("Temp         F  ");
    
    } else {
    
      lcd.print("Temp         C  ");
    
    }

    lcd.setCursor(6, 0);
    lcd.print(tempReceived);
  
  }
  
  if (irrecv.decode(&results)) {
    if (results.value == 0xFFA25D) {
      if (tempDesired == 0) {
        tempDesired = 1;
      } else {
        tempDesired = 0;
      }
    }
    Serial.println(tempDesired);
    lcd.setCursor(0, 0);
    lcd.print(tempDesired);
    irrecv.resume();
  }

  Serial.write(tempDesired);
  
}
