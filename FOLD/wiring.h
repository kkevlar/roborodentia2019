
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
#define MOTOR_SHEILD_PORT_FR 3
#define MOTOR_SHEILD_PORT_BL 2
#define MOTOR_SHEILD_PORT_BR 4

#define MOTOR_SHEILD_PORT_INDEXER 4
#define MOTOR_SHEILD_PORT_CONVEYOR_L 3
#define MOTOR_SHEILD_PORT_CONVEYOR_R 1

#define MOTOR_MULTIPLIER_FL 1
#define MOTOR_MULTIPLIER_FR 1
#define MOTOR_MULTIPLIER_BL 1
#define MOTOR_MULTIPLIER_BR 0.97f

#define MOTOR_MULTIPLIER_CONVEYOR_L -1
#define MOTOR_MULTIPLIER_CONVEYOR_R -1
#define MOTOR_MULTIPLIER_INDEXER 1

#define WHEEL_GLOBAL_SPEED_CAP 255

typedef uint8_t direction_t;
typedef uint8_t pin_t;
typedef uint8_t aim_location_t;

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
	#define PIN_SWITCH_FRONT_L 4
	#define PIN_SWITCH_BACK_L 3
	#define PIN_SWITCH_RIGHT_F 2
	#define PIN_SWITCH_LEFT_F 6
#else
	#error "No valid switch configuration defined"
#endif

#if defined(SWITCH_COUNT_SIX) ||\
defined(SWITCH_COUNT_EIGHT)
	#define PIN_SWITCH_LEFT_B A2
	#define PIN_SWITCH_RIGHT_B 5
#endif

#ifdef SWITCH_COUNT_EIGHT
	#define PIN_SWITCH_FRONT_R A1
	#define PIN_SWITCH_BACK_R A0
#endif


#define AIM_LOCATION_COUNT 3
#define AIM_LOCATION_SELECTION_RANDOM_MIN 1
#define AIM_LOCATION_SELECTION_RANDOM_MAX 3

#define AIM_LOCATION_ID_LEFT 1
#define AIM_LOCATION_ID_CENTER 2
#define AIM_LOCATION_ID_RIGHT 3

#define DIRECTION_ID_FRONT 3
#define DIRECTION_ID_BACK 4
#define DIRECTION_ID_LEFT 5
#define DIRECTION_ID_RIGHT 6

#define DEGREES_FRONT 90
#define DEGREES_BACK 270
#define DEGREES_LEFT 180
#define DEGREES_RIGHT 0

#define DEFAULT_P_CONSTANT 1.25f
#define DEFAULT_SPEED_BOOST_ZONE 80.0f
#define DEFAULT_INTRA_ECHO_DELAY_MS 20
#define DEFAULT_SPEED_ROOMBA 125
#define DEFAULT_SPEED_INTO_WALL_FOR_HUG 110

#define FIELD_COLLECT_RIGHT_PRE_TARGET_FROM_BACK 300
#define FIELD_COLLECT_RIGHT_POST_TARGET_FROM_BACK 15
#define FIELD_COLLECT_BACK_PRE_TARGET_FROM_RIGHT 500
#define FIELD_COLLECT_BACK_POST_TARGET_FROM_LEFT 150
#define FIELD_COLLECT_LEFT_PRE_TARGET_FROM_BACK 100
#define FIELD_COLLECT_LEFT_POST_TARGET_FROM_BACK 425
#define FIELD_COLLECT_YEET_ANTI_ROOMBA_WALL_BACK 250

#define FIELD_AIM_PRE_LEFT_FROM_LEFT 755
#define FIELD_AIM_PRE_CENTER_FROM_LEFT 1010
#define FIELD_AIM_PRE_RIGHT_FROM_RIGHT 200

#define FIELD_AIM_FINAL_LEFT_FROM_RIGHT 505
#define FIELD_AIM_FINAL_CENTER_FROM_RIGHT 180
#define FIELD_AIM_FINAL_RIGHT_FROM_RIGHT 165

// #define ECHO_PULSEIN_LIMIT 500000

#define SHOOT_STOPPED_FLYWHEEL_LEFT 1000
#define SHOOT_STOPPED_FLYWHEEL_RIGHT 1000
#define SHOOT_SPEED_FLYWHEEL_LEFT 1190
#define SHOOT_SPEED_FLYWHEEL_RIGHT 1190
#define SHOOT_SPEED_CONVEYOR_LEFT 255
#define SHOOT_SPEED_CONVEYOR_RIGHT 255
#define SHOOT_SPEED_INDEXER_FORWARD 255
#define SHOOT_SPEED_INDEXER_BACKWARD -255

#define COLLECT_GENERAL_BOOST_ZONE (DEFAULT_SPEED_BOOST_ZONE)

#define COLLECT_PRE_WALL_P_CONSTANT 1.0f
#define COLLECT_PRE_TARGET_P_CONSTANT (DEFAULT_P_CONSTANT)
#define COLLECT_PRE_DESIRED_WALL_DIST_MM 20
#define COLLECT_PRE_MM_ACCURACY 40
#define COLLECT_PRE_IN_BETWEEN_ECHO_TESTS_DELAY_MS (DEFAULT_INTRA_ECHO_DELAY_MS)
#define COLLECT_PRE_EARLY_BREAK_WALL_DIST 300

#define COLLECT_ROOMBA_SPEED (DEFAULT_SPEED_ROOMBA)
#define COLLECT_ROOMBA_PERSIST_MS 300

#define COLLECT_DO_INTO_WALL_SPEED_FOR_HUG (90)
#define COLLECT_DO_P_CONSTANT 2.0f
#define COLLECT_DO_MAX_TARGET_SPEED 255
#define COLLECT_DO_MAX_NET_SPEED 120.0f
#define COLLECT_DO_MM_ACCURACY 60
#define COLLECT_DO_IN_BETWEEN_ECHO_TESTS_DELAY_MS (DEFAULT_INTRA_ECHO_DELAY_MS)

#define COLLECT_YEET_AWAY_P_CONSTANT 4.0f
#define COLLECT_YEET_AWAY_MAX_SPEED 255
#define COLLECT_YEET_AWAY_DEAD_ZONE 0
#define COLLECT_YEET_AWAY_ACCURACY 50
#define COLLECT_YEET_AWAY_DELAY_MS 15

#define AIM_GENERAL_BOOST_ZONE (DEFAULT_SPEED_BOOST_ZONE)

#define AIM_PRE_WALL_P_CONSTANT 1.0f
#define AIM_PRE_TARGET_P_CONSTANT (DEFAULT_P_CONSTANT)
#define AIM_PRE_DESIRED_WALL_DIST_MM_L_AND_C 500
#define AIM_PRE_DESIRED_WALL_DIST_MM_R 250
#define AIM_PRE_MM_ACCURACY 50
#define AIM_PRE_IN_BETWEEN_ECHO_TESTS_DELAY_MS (DEFAULT_INTRA_ECHO_DELAY_MS)

#define AIM_FINAL_WALL_HUG_SPEED 20
#define AIM_FINAL_TARGET_P_CONSTANT 2.0f
#define AIM_FINAL_MM_ACCURACY 10
#define AIM_FINAL_SPEED_MAX 140
#define AIM_FINAL_SPEED_DEAD_ZONE 5.0f
#define AIM_FINAL_SPEED_BOOST_ZONE (DEFAULT_SPEED_BOOST_ZONE)
#define AIM_FINAL_IN_BETWEEN_ECHO_TESTS_DELAY_MS (DEFAULT_INTRA_ECHO_DELAY_MS)

#endif
