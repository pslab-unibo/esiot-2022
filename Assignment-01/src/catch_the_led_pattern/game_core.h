#ifndef __GAME_CORE__
#define __GAME_CORE__

#include "Arduino.h"

#define GAME_INTRO 1
#define GAME_WAIT_TO_START 2
#define GAME_INIT 3
#define GAME_LOOP_GENERATE_PATTERN 4
#define GAME_LOOP_DISPLAY_PATTERN 5
#define GAME_LOOP_WAITING_PLAYER_PATTERN 6
#define GAME_OVER 7
#define GAME_SLEEP 8

extern int game_state;

void update_game_state_time();
void change_game_state(int new_state);

/* behaviour in the specific game states */
void game_intro();
void game_wait_to_start();
void game_init();
void game_loop_generate_pattern();
void game_loop_display_pattern();
void game_loop_wait_player_pattern();
void game_over();
void game_sleep();

/* game test */
void game_test();

#endif
