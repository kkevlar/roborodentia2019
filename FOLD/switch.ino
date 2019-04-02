
#include "switch.h"


void switch_init(void)
{
    pinMode(PIN_SWITCH_FRONT, INPUT_PULLUP);
    pinMode(PIN_SWITCH_RIGHT_F, INPUT_PULLUP);
    pinMode(PIN_SWITCH_RIGHT_B, INPUT_PULLUP);
    pinMode(PIN_SWITCH_BACK, INPUT_PULLUP);
    pinMode(PIN_SWITCH_LEFT_BACK, INPUT_PULLUP);
    pinMode(PIN_SWITCH_LEFT_FRONT, INPUT_PULLUP);
}

int switch_simple_read(uint8_t switch_pin)
{
    if(switch_pin > 0)
        return digitalRead(switch_pin);
    else
        return HIGH;
}

// int mass_switch_read()
// {
//     for(int i = 2; i <= 7; i++)
//     {
//         if(digitalRead(i) == LOW)
//             return 1;
//     }
//     return 0;
// }

// int test_switch_arbitrary(long breaktime, int pincount, int* pins)
// {
//     int test[TOTAL_SWITCH_COUNT];
//     int result = 1;
//     int i;

//     for(i = 0; i < pincount; i++)
//     {
//         test[i] = 0;
//     }

//     long starttime = millis();

//     while (millis() - starttime < breaktime)
//     {
//         result = 1;
//         for(i = 0; i < pincount; i++)
//         {
//             test[i] = (digitalRead(pins[i]) == LOW || test[i]);
//             result = (test[i] && result);
//         }
//         if(result)
//         {
//             delay(80);
//             return SUCCESS;
//         }
//     }
//     return FAILURE;
// }

// int test_switch_south(long breaktime)
// {
//     pins[0] = SWITCH_PIN_SOUTH;
//     return test_switch_arbitrary(breaktime, 1, pins);
// }

// int test_switch_north(long breaktime)
// {
//     pins[0] = SWITCH_PIN_NORTH;
//     return test_switch_arbitrary(breaktime, 1, pins);
// }

// int test_switch_east(long breaktime)
// {
//     pins[0] = SWITCH_PIN_EAST_NORTH;
//     pins[1] = SWITCH_PIN_EAST_SOUTH;
//     return test_switch_arbitrary(breaktime, 2, pins);
// }

// int test_switch_west(long breaktime)
// {
//     pins[0] = SWITCH_PIN_WEST_NORTH;
//     pins[1] = SWITCH_PIN_WEST_SOUTH;
//     return test_switch_arbitrary(breaktime, 2, pins);
// }
