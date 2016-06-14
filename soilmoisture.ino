#include <LiquidCrystal.h>

LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );

void setup() {
  Serial.begin(9600);
}

void loop()
{
    int sensorValue = analogRead(A1);
    String sensorValueString = String(sensorValue);
    lcd.begin(0,0);
    lcd.print(sensorValue);
    Serial.println(sensorValue);
    
    delay(1000);
}
