# Roborodentia 2019

Autonomous drive code for **Fold**, the second place robot for Cal Poly's annual autonomous robotics competition.

[Roborodentia](http://roborodentia.calpoly.edu/).

[Game Rules](https://docs.google.com/document/d/1yxtSJe29Ct2Tb8KmzMLPe1f2cj2fBtazdUNPZ5FT0Tg/edit)

Authors: Kevin Kellar and Derick Louie

## Usage

This drive source code was written for an Arduino Uno, and it depends on the standard Arduino libraries. 

It also depends on the following other Arduino libraries:
* Wire
* [Adafruit_MotorShield](https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library)
* [LiquidCrystal_I2C](https://github.com/kkevlar/LiquidCrystal_I2C)
* Servo

If these libraries are installed, this project should be easily compilable / uploadable by using Arduino IDE to open FOLD.ino.

The Makefile should allow for easy (mileage may vary) compilation / uploading of the drive code using [Arduino Makefile](https://github.com/sudar/Arduino-Makefile).


