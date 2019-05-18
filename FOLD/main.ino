#include "main.h"

#ifndef TEST_NO_GAME

void main_setup()
{
    lcd_init();

    lcd_print_top("Init.....");

    wheel_init();
    switch_init();
    drive_init();
    echo_init();
    aim_init();
    collect_init();
    // shoot_init();

    lcd_print_bot(" success! :)");
}

void simple_aim_n_shoot(aim_location_t loc)
{
    char buf[17];
    long time_start;

    // aim_location_t loc = aim_select_location();
    snprintf(buf, 16, "Gonna shoot @%d", loc);
    lcd_print_top(buf);
    aim(loc);
    go_stop();
    shoot_flywheel_both_start();
    shoot_conveyor_both_start();
    shoot_indexer_start();

    while(millis() - time_start < 10000)
    {
        shoot_indexer_spam_forward();
        delay(10);
    }
    lcd_print_bot("Pew! Pew! Pew!");

    shoot_indexer_stop();
    shoot_flywheel_both_stop();
    shoot_conveyor_both_stop();
}

void main_game_a_loop(void)
{
    // go_stop();
    // shoot_flywheel_both_stop();
    // shoot_conveyor_both_stop();
    // shoot_indexer_stop();
    // while(switch_test_up(DIRECTION_ID_FRONT))
    // {
    //     delay(10);
    // }

    // shoot_indexer_start();

    // delay(2000);

    // shoot_indexer_stop();

    // go_stop();
    // go_right();
    // delay(500);
    // go_stop();
    // delay(5000);

    while(1)
    {


        collection_victory_lap();
        collection_victory_lap();
        go_stop();
        simple_aim_n_shoot(AIM_LOCATION_ID_LEFT);
        // // lcd_print_bot("Collect 1 Done");

        // collection_victory_lap();
        collection_victory_lap();
        collection_victory_lap();
        go_stop();
        simple_aim_n_shoot(AIM_LOCATION_ID_CENTER);

        // collection_victory_lap();
        collection_victory_lap();
        collection_victory_lap();
        go_stop();
        simple_aim_n_shoot(AIM_LOCATION_ID_RIGHT);
    }
}

void main_loop()
{
    go_stop();

    #if defined(GAME_A)
        main_game_a_loop();
    #endif
}

#endif
