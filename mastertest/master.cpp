
#include <Arduino.h>
#include <Wire.h>

#include <Wire.h>

void setup() 
{
  pinMode(7, INPUT_PULLUP);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  Wire.begin(); // join i2c bus (address optional for master)


}

byte x = 0;

void loop() {
  delay(50);
  Wire.beginTransmission(8); // transmit to device #8
  if(digitalRead(7) == HIGH)
  Wire.write(69);
else
  Wire.write(0);
  Wire.endTransmission();
}


