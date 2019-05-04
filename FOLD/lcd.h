
#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "wiring.h"

void lcd_init(void);
void lcd_hello_world(void);

#endif
