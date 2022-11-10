/*
 * ESIOT a.y. 2022/2023
 *
 * ASSIGNMENT #1 - CATCH THE LED PATTERN  
 * 
 * Author: A. Ricci
 * 
 */
#include "config.h"
#include "game_core.h"
#include "user_console.h" 
#include "led_board.h"

void setup() {
  init_player_console();
  init_led_board();
  test_led_board();
  change_game_state(GAME_INTRO);
}

void loop(){ 
  update_game_state_time();
 
  switch (game_state) { 
  case GAME_INTRO:
    game_intro();
    break;
  case GAME_WAIT_TO_START:
    game_wait_to_start();
    break;
  case GAME_INIT:
    game_init();
    break;
  case GAME_LOOP_GENERATE_PATTERN:
    game_loop_generate_pattern();
    break;
  case GAME_LOOP_DISPLAY_PATTERN:
    game_loop_display_pattern();
    break;
  case GAME_LOOP_WAITING_PLAYER_PATTERN:
    game_loop_wait_player_pattern();
    break;
  case GAME_OVER:
    game_over();
    break;
  case GAME_SLEEP:
    game_sleep();
    break;
  }
}
