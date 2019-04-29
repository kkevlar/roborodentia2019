
#ifndef WIRING_H
#define WIRING_H

/* Switch Type: Pick one */
// #define SWITCH_COUNT_FOUR
#define SWITCH_COUNT_SIX
// #define SWITCH_COUNT_EIGHT

/* LCD? Pick one */
#define LCD_ENABLED
// #define LCD_DISABLED

#define MOTOR_SHEILD_ADDRESS_WHEEL 0x61
#define MOTOR_SHEILD_ADDRESS_SHOOT 0x60

#define BOT_PORT_FL 1
#define BOT_PORT_FR 4
#define BOT_PORT_BL 2
#define BOT_PORT_BR 3

#define OFFSET_FL -1
#define OFFSET_FR -1
#define OFFSET_BL -1
#define OFFSET_BR -1

#define PIN_ULTRASONIC_ECHO_LEFT 9
#define PIN_ULTRASONIC_ECHO_FRONT 8
#define PIN_ULTRASONIC_ECHO_RIGHT 11
#define PIN_ULTRASONIC_ECHO_BACK 10
#define PIN_ULTRASONIC_TRIG 7

#if defined(SWITCH_COUNT_FOUR) || \
defined(SWITCH_COUNT_SIX) ||\
defined(SWITCH_COUNT_EIGHT)
	#define PIN_SWITCH_FRONT_L 2
	#define PIN_SWITCH_BACK_L 3
	#define PIN_SWITCH_RIGHT_F 6
	#define PIN_SWITCH_LEFT_F 4
#else
	#error "No valid switch configuration defined"
#endif

#if defined(SWITCH_COUNT_SIX) ||\
defined(SWITCH_COUNT_EIGHT)
	#define PIN_SWITCH_LEFT_B 5
	#define PIN_SWITCH_RIGHT_B A2
#endif

#ifdef SWITCH_COUNT_EIGHT
	#define PIN_SWITCH_FRONT_R A1
	#define PIN_SWITCH_BACK_R A0
#endif

#endif
