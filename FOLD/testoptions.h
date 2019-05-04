
#ifndef TESTOPTIONS_H
#define TESTOPTIONS_H

// #define TEST_DRIVE_STOP
// #define TEST_SWITCH
// #define TEST_DRIVE_DIAG
// #define TEST_DRIVE_CARD
// #define TEST_ECHO
#define TEST_LCD

#if defined(TEST_DRIVE_STOP) || \
	defined(TEST_SWITCH) ||\
	defined(TEST_DRIVE_DIAG) ||\
	defined(TEST_DRIVE_CARD) ||\
	defined(TEST_ECHO) || \
	defined(TEST_LCD)

#define TEST_NO_GAME

#endif

// #define GAME_A


#endif

