
#ifndef WIRING_H
#define WIRING_H

#include <stdbool.h>
#include <inttypes.h>

/* Switch Type: Pick one */
// #define SWITCH_COUNT_FOUR
#define SWITCH_COUNT_SIX
// #define SWITCH_COUNT_EIGHT

/* LCD? Pick one */
#define LCD_ENABLED
// #define LCD_DISABLED

#if defined(TEST_LCD) && !defined(LCD_ENABLED)
	#error "Testlcd enabled but lcd disabled"
#endif

#define MOTOR_SHEILD_ADDRESS_WHEEL 0x61
#define MOTOR_SHEILD_ADDRESS_SHOOT 0x60

#define MOTOR_SHEILD_PORT_FL 1
#define MOTOR_SHEILD_PORT_FR 4
#define MOTOR_SHEILD_PORT_BL 2
#define MOTOR_SHEILD_PORT_BR 3

#define MOTOR_SHEILD_PORT_INDEXER 1
#define MOTOR_SHEILD_PORT_CONVEYOR_L 2
#define MOTOR_SHEILD_PORT_CONVEYOR_R 3

#define MOTOR_MULTIPLIER_FL -1
#define MOTOR_MULTIPLIER_FR -1
#define MOTOR_MULTIPLIER_BL -1
#define MOTOR_MULTIPLIER_BR -1

#define PIN_ULTRASONIC_ECHO_LEFT 12
#define PIN_ULTRASONIC_ECHO_FRONT 8
#define PIN_ULTRASONIC_ECHO_RIGHT 11
#define PIN_ULTRASONIC_ECHO_BACK 13
#define PIN_ULTRASONIC_TRIG 7

#define PIN_PWM_LEFT 9
#define PIN_PWM_RIGHT 10
#define PIN_ANALOG_RANDOM A3

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

#define SHOOT_STOPPED_FLYWHEEL_LEFT 90
#define SHOOT_STOPPED_FLYWHEEL_RIGHT 90
#define SHOOT_SPEED_FLYWHEEL_LEFT 160
#define SHOOT_SPEED_FLYWHEEL_RIGHT 160
#define SHOOT_SPEED_CONVEYOR_LEFT 255
#define SHOOT_SPEED_CONVEYOR_RIGHT 255
#define SHOOT_SPEED_INDEXER_FORWARD 255
#define SHOOT_SPEED_INDEXER_BACKWARD -100

#define COLLECT_PRE_WALL_P_CONSTANT 2.0f
#define COLLECT_PRE_TARGET_P_CONSTANT 2.0f
#define COLLECT_PRE_DESIRED_WALL_DIST_MM 60
#define COLLECT_PRE_MM_ACCURACY 10
#define COLLECT_PRE_IN_BETWEEN_ECHO_TESTS_DELAY_MS 20
#define COLLECT_PRE_EARLY_BREAK_WALL_DIST 150
#define COLLECT_ROOMBA_SPEED 100
#define COLLECT_DO_INTO_WALL_SPEED_FOR_HUG 70
#define COLLECT_DO_P_CONSTANT 4.0f
#define COLLECT_DO_MAX_TARGET_SPEED 255
#define COLLECT_DO_MAX_NET_SPEED 255.0f
#define COLLECT_YEET_AWAY_P_CONSTANT 1.0f
#define COLLECT_YEET_AWAY_MAX_SPEED 255
#define COLLECT_YEET_AWAY_DEAD_ZONE 0
#define COLLECT_YEET_AWAY_BOOST_ZONE 80
#define COLLECT_YEET_AWAY_ACCURACY 25
#define COLLECT_YEET_AWAY_DELAY_MS 15

#define FIELD_COLLECT_RIGHT_PRE_TARGET_FROM_BACK 300
#define FIELD_COLLECT_RIGHT_POST_TARGET_FROM_BACK 200
#define FIELD_COLLECT_BACK_PRE_TARGET_FROM_RIGHT 500
#define FIELD_COLLECT_BACK_POST_TARGET_FROM_RIGHT 600
#define FIELD_COLLECT_LEFT_PRE_TARGET_FROM_BACK 200
#define FIELD_COLLECT_LEFT_POST_TARGET_FROM_BACK 300
#define FIELD_COLLECT_YEET_ANTI_ROOMBA_WALL_BACK 150

#define FIELD_AIM_PRE_CENTER_FROM_RIGHT 450

#define AIM_PRE_WALL_P_CONSTANT 2.0f
#define AIM_PRE_TARGET_P_CONSTANT 2.0f
#define AIM_PRE_DESIRED_WALL_DIST_MM 100
#define AIM_PRE_MM_ACCURACY 5
#define AIM_PRE_IN_BETWEEN_ECHO_TESTS_DELAY_MS 20
#define AIM_PRE_EARLY_BREAK_WALL_DIST 150

#define AIM_LOCATION_COUNT 6
#define AIM_LOCATION_SELECTION_RANDOM_MIN 1
#define AIM_LOCATION_SELECTION_RANDOM_MAX 5

#define AIM_LOCATION_ID_FAR_LEFT 1
#define AIM_LOCATION_ID_CENTER_LEFT 2
#define AIM_LOCATION_ID_CENTER 3
#define AIM_LOCATION_ID_CENTER_RIGHT 4
#define AIM_LOCATION_ID_FAR_RIGHT 5

#define DIRECTION_ID_FRONT 3
#define DIRECTION_ID_BACK 4
#define DIRECTION_ID_LEFT 5
#define DIRECTION_ID_RIGHT 6

#define DEGREES_FRONT 90
#define DEGREES_BACK 270
#define DEGREES_LEFT 180
#define DEGREES_RIGHT 0

typedef uint8_t direction_t;
typedef uint8_t pin_t;
typedef uint8_t aim_location_t;

#endif
