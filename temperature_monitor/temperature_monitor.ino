#include <LiquidCrystal.h>


int time = 50;
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
int thermistorPin = 0;

void setup() {
    lcd.begin(16, 2);
    lcd.clear();
}

void loop() {
    float a = analogRead(thermistorPin);
    float resistor = (1023.0 * 10000) / a - 10000;
    float tempC = (3435.0 / (log(resistor / 10000) + (3435.0 / (273.15 + 25)))) - 273.15;
    
    lcd.setCursor(0, 0);
    lcd.print("   this is me   ");
    lcd.setCursor(0, 1);
    lcd.print("  Temp: ");
    lcd.print(tempC);
    lcd.print(" C  ");
    delay(500);
}
