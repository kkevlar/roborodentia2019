
#include "switch.h"


void switch_init(void)
{
    #if defined(SWITCH_COUNT_FOUR) || \
    defined(SWITCH_COUNT_SIX) ||\
    defined(SWITCH_COUNT_EIGHT)
        pinMode(PIN_SWITCH_FRONT_L, INPUT_PULLUP);
        pinMode(PIN_SWITCH_BACK_L, INPUT_PULLUP);
        pinMode(PIN_SWITCH_RIGHT_F, INPUT_PULLUP);
        pinMode(PIN_SWITCH_LEFT_F, INPUT_PULLUP);
    #else
    #error "No valid switch configuration defined"
    #endif

    #if defined(SWITCH_COUNT_SIX) ||\
    defined(SWITCH_COUNT_EIGHT)
        pinMode(PIN_SWITCH_LEFT_B, INPUT_PULLUP);
        pinMode(PIN_SWITCH_RIGHT_B, INPUT_PULLUP);
    #endif

    #ifdef SWITCH_COUNT_EIGHT
        pinMode(PIN_SWITCH_FRONT_R, INPUT_PULLUP);
        pinMode(PIN_SWITCH_BACK_R, INPUT_PULLUP);
    #endif
}

pin_t switch_test_all()
{
    pin_t result;

    result = -1;

    #if defined(SWITCH_COUNT_FOUR) || \
    defined(SWITCH_COUNT_SIX) ||\
    defined(SWITCH_COUNT_EIGHT)
        if(digitalRead(PIN_SWITCH_FRONT_L) == LOW)
            result = PIN_SWITCH_FRONT_L;
        if(digitalRead(PIN_SWITCH_BACK_L) == LOW)
            result = PIN_SWITCH_BACK_L;
        if(digitalRead(PIN_SWITCH_RIGHT_F) == LOW)
            result = PIN_SWITCH_RIGHT_F;
        if(digitalRead(PIN_SWITCH_LEFT_F) == LOW)
            result = PIN_SWITCH_LEFT_F;
    #else
    #error "No valid switch configuration defined"
    #endif

    #if defined(SWITCH_COUNT_SIX) ||\
    defined(SWITCH_COUNT_EIGHT)
        if(digitalRead(PIN_SWITCH_LEFT_B) == LOW)
            result = PIN_SWITCH_LEFT_B;
        if(digitalRead(PIN_SWITCH_RIGHT_B) == LOW)
            result = PIN_SWITCH_RIGHT_B;
    #endif

    #ifdef SWITCH_COUNT_EIGHT
        if(digitalRead(PIN_SWITCH_FRONT_R) == LOW)
            result = PIN_SWITCH_FRONT_R;
        if(digitalRead(PIN_SWITCH_BACK_R) == LOW)
            result = PIN_SWITCH_BACK_R;
    #endif

    return result;
}

bool switch_test_up(pin_t pin)
{
    return digitalRead(pin) != LOW;
}

bool switch_test_down(pin_t pin)
{
    return digitalRead(pin) == LOW;
}



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
