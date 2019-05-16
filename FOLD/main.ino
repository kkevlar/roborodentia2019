#include "main.h"

#ifndef TEST_NO_GAME

void main_setup()
{
    lcd_init();

    lcd_print_top("Init.....");

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

    // aim_location_t loc = aim_select_location();
    snprintf(buf, 16, "Gonna shoot @%d", loc);
    lcd_print_top(buf);
    aim(loc);
    go_stop();
    lcd_print_bot("Pew! Pew! Pew!");
    delay(2000);
}

void main_game_a_loop(void)
{
    // lcd_print_top("Game A             ");

    // collection_victory_lap();
    // collection_victory_lap();
    collection_victory_lap();

    simple_aim_n_shoot(AIM_LOCATION_ID_LEFT);
    // // lcd_print_bot("Collect 1 Done");

    // collection_victory_lap();
    // collection_victory_lap();
    collection_victory_lap();

    simple_aim_n_shoot(AIM_LOCATION_ID_CENTER);

    // collection_victory_lap();
    // collection_victory_lap();
    collection_victory_lap();

    simple_aim_n_shoot(AIM_LOCATION_ID_RIGHT);



    // lcd_print_bot("Collect 2 Done");


    while(1)
    {
        go_stop();
        lcd_print_top("Im slept");
        lcd_print_bot("zzzzzzzzzzz");
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
