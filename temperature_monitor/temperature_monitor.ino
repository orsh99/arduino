#include <LiquidCrystal.h>


LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
int thermistor1Pin = 0;
int thermistor2Pin = 1;

void setup() {
    lcd.begin(16, 2);
    lcd.clear();
}

void loop() {
    float a = analogRead(thermistor1Pin);
    float resistor1 = (1023.0 * 10000) / a - 10000;
    float temp1C = (3435.0 / (log(resistor1 / 10000) + (3435.0 / (273.15 + 25)))) - 273.15;

    float b = analogRead(thermistor2Pin);
    float resistor2 = (1023.0 * 10000) / b - 10000;
    float temp2C = (3435.0 / (log(resistor2 / 10000) + (3435.0 / (273.15 + 25)))) - 273.15;
    
    lcd.setCursor(0, 0);
    lcd.print(" Temp1: ");
    lcd.print(temp1C);
    lcd.print(" C  ");
    lcd.setCursor(0, 1);
    lcd.print(" Temp2: ");
    lcd.print(temp2C);
    lcd.print(" C  ");
    delay(500);
}
