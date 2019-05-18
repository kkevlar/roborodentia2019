
#include <Arduino.h>
#include <Wire.h>

#define PIN_PWM_1 11
#define PIN_F_1 12
#define PIN_B_1 8

#define PIN_PWM_2 10
#define PIN_F_2 7
#define PIN_B_2 4

#define SLAVE_ADDRESS 8 

uint8_t index_speed;
uint8_t other_info;

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) 
{
    uint8_t i = 0;

    if(Wire.available())
    {
       index_speed = Wire.read();
    }
    else
    {
        return;
    }

    if(Wire.available())
    {
       other_info = Wire.read();
    }
    else
    {
        return;
    }
}

void setup() 
{
    // pinMode(13, OUTPUT);
    // for(int i = 0; i < 10; i++)
    // {
    //     digitalWrite(13,HIGH);
    //     delay(200);
    //     digitalWrite(13,LOW);
    //     delay(200);
    // }

    Wire.begin(8);                // join i2c bus with address #8
    Wire.onReceive(receiveEvent); // register event
    pinMode(PIN_PWM_1 , OUTPUT);
    pinMode(PIN_PWM_2 , OUTPUT);
    pinMode(PIN_PWM_3 , OUTPUT);
    pinMode(PIN_PWM_4 , OUTPUT);
    pinMode(PIN_F_1 , OUTPUT);
    pinMode(PIN_F_2 , OUTPUT);
    pinMode(PIN_B_1 , OUTPUT);
    pinMode(PIN_B_2 , OUTPUT);

}



void loop() 
{
    int n = 2;
    if(SLAVE_MODE_RELEASE == modes[n])
    {
        digitalWrite(PIN_F_1,LOW);
        digitalWrite(PIN_B_1,LOW);
        analogWrite(PIN_PWM_1,0);

    }
    else
    {
        if(SLAVE_MODE_FORWARD == modes[n])
        {
            digitalWrite(PIN_F_1,HIGH);
            digitalWrite(PIN_B_1,LOW);
        }
        else if(SLAVE_MODE_REVERSE == modes[n])
        {
            digitalWrite(PIN_F_1,LOW);
            digitalWrite(PIN_B_1,HIGH);
        }
        analogWrite(PIN_PWM_1, speeds[n]);
    }

    n=0;
    if(SLAVE_MODE_RELEASE == modes[n])
    {
        digitalWrite(PIN_F_2,LOW);
        digitalWrite(PIN_B_2,LOW);
        analogWrite(PIN_PWM_2,0);

    }
    else
    {
        if(SLAVE_MODE_FORWARD == modes[n])
        {
            digitalWrite(PIN_F_2,HIGH);
            digitalWrite(PIN_B_2,LOW);
        }
        else if(SLAVE_MODE_REVERSE == modes[n])
        {
            digitalWrite(PIN_F_2,LOW);
            digitalWrite(PIN_B_2,HIGH);
        }
        analogWrite(PIN_PWM_2, speeds[n]);
    }

    n = 1;
    if(SLAVE_MODE_RELEASE == modes[n])
    {
        digitalWrite(PIN_F_3,LOW);
        digitalWrite(PIN_B_3,LOW);
        analogWrite(PIN_PWM_3,0);

    }
    else
    {
        if(SLAVE_MODE_FORWARD == modes[n])
        {
            digitalWrite(PIN_F_3,HIGH);
            digitalWrite(PIN_B_3,LOW);
        }
        else if(SLAVE_MODE_REVERSE == modes[n])
        {
            digitalWrite(PIN_F_3,LOW);
            digitalWrite(PIN_B_3,HIGH);
        }
        analogWrite(PIN_PWM_3, speeds[n]);
    }

    n= 3;

    if(SLAVE_MODE_RELEASE == modes[n])
    {
        digitalWrite(PIN_F_4,LOW);
        digitalWrite(PIN_B_4,LOW);
        analogWrite(PIN_PWM_4,0);
    }
    else
    {
        if(SLAVE_MODE_FORWARD == modes[n])
        {
            digitalWrite(PIN_F_4,HIGH);
            digitalWrite(PIN_B_4,LOW);
        }
        else if(SLAVE_MODE_REVERSE == modes[n])
        {
            digitalWrite(PIN_F_4,LOW);
            digitalWrite(PIN_B_4,HIGH);
        }
        analogWrite(PIN_PWM_4, speeds[n]);
    }

    delay(1);


}


