#include "echo.h"
 
void echo_init()
{
    pinMode(PIN_ULTRASONIC_TRIG, OUTPUT);
    pinMode(PIN_ULTRASONIC_ECHO_SOUTH, INPUT);
    pinMode(PIN_ULTRASONIC_ECHO_WEST, INPUT);
    pinMode(PIN_ULTRASONIC_ECHO_NORTH, INPUT);
    pinMode(PIN_ULTRASONIC_ECHO_EAST, INPUT);

    Serial.begin(9600);
}

float echo_test_mm(uint8_t pin)
{
	long duration;
	float myout;

	digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
 
    pinMode(pin, INPUT);
    duration = pulseIn(pin, HIGH);

    myout = (duration);
    myout *= (0.171821f);
    Serial.println(myout);
    return myout;
}

void echo_print_all()
{
    #ifdef TEST_ECHO
        char buf[1024];
        int offset = 0;

        offset += sprintf(buf+offset, "N: %4d ",(int) echo_test_mm(PIN_ULTRASONIC_ECHO_NORTH));
        delay(10);
        offset += sprintf(buf+offset, "E: %4d ",(int) echo_test_mm(PIN_ULTRASONIC_ECHO_EAST));
        delay(10);
        offset += sprintf(buf+offset, "S: %4d ",(int) echo_test_mm(PIN_ULTRASONIC_ECHO_SOUTH));
        delay(10);
        offset += sprintf(buf+offset, "W: %4d ",(int) echo_test_mm(PIN_ULTRASONIC_ECHO_WEST));
        delay(10);

        Serial.println(buf);
    #endif
}

