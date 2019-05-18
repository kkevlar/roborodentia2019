
#include <Arduino.h>
#include <Wire.h>

#define PIN_PWM_1 11
#define PIN_F_1 12
#define PIN_B_1 8

#define PIN_PWM_2 10
#define PIN_F_2 7
#define PIN_B_2 4

#define PIN_PWM_3 3
#define PIN_F_3 A0
#define PIN_B_3 A1

#define PIN_PWM_4 6
#define PIN_F_4 A2
#define PIN_B_4 A3

#define SLAVE_ADDRESS 8 
#define SLAVE_MODE_RELEASE 1
#define SLAVE_MODE_FORWARD 2
#define SLAVE_MODE_REVERSE 3

#define WHEEL_FL 0x00
#define WHEEL_FR 0x01
#define WHEEL_BL 0x02
#define WHEEL_BR 0x03

#define PORT1_WHEEL WHEEL_BL
#define PORT2_WHEEL WHEEL_FL
#define PORT3_WHEEL WHEEL_BR
#define PORT4_WHEEL WHEEL_FR

uint8_t modes[4];
uint8_t speeds[4];
uint8_t buf[8];


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) 
{
    uint8_t i = 0;
    

    while(Wire.available())
    {
       buf[i++] = Wire.read();
    } 

    modes[0] = buf[0];  
    speeds[0] = buf[1];   
    modes[1] = buf[2];   
    speeds[1] = buf[3];
    modes[2] = buf[4];   
    speeds[2] = buf[5];
    modes[3] = buf[6];   
    speeds[3] = buf[7];
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
    pinMode(PIN_F_3 , OUTPUT);
    pinMode(PIN_F_4 , OUTPUT);
    pinMode(PIN_B_1 , OUTPUT);
    pinMode(PIN_B_2 , OUTPUT);
    pinMode(PIN_B_3 , OUTPUT);
    pinMode(PIN_B_4 , OUTPUT);

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


