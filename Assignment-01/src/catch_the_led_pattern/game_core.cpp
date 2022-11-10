#include "game_core.h"
#include "Arduino.h"
#include "config.h"
#include "led_board.h"
#include "user_console.h"
#include <avr/sleep.h>

#define MAX_IDLE_TIME 10000
#define TIME_IN_GAME_OVER 2000
#define T1_TIME 1000
#define T2_TIME 2000
#define T3_TIME 5000

/* current pattern to be generated */
unsigned char current_pattern;

/* current max time to generate the pattern (random) */
long max_time_to_generate_pattern;

/* current max time that can be used to input the pattern */
long max_time_to_form_pattern;

/* current max time to display the pattern */
long max_time_to_display_pattern;

/* difficulty level */
int difficulty_level;

/* difficulty scaling factor */
double difficulty_scaling_factor = 1;

/* the score */
long score = 0;

/* current game state */
int game_state;

/* time in which the game entered in the game state */
long entered_state_time;

/* how long it the game is in current state */
long current_time_in_state;


/* =========== procedures about game state ======== */

void change_game_state(int new_state){
  game_state = new_state;
  entered_state_time = millis();
}

void update_game_state_time(){
  current_time_in_state = millis() - entered_state_time;
}

void check_difficulty_level(){
  int new_difficulty_level = read_difficulty_level();
  if (new_difficulty_level != difficulty_level){
    difficulty_level = new_difficulty_level;
    print_on_console(String("New difficulty Level: ") + difficulty_level);  
  } 
}

void game_intro(){
  reset_led_board();   
  print_on_console("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
  reset_pulsing();
  change_game_state(GAME_WAIT_TO_START);
}

void game_wait_to_start(){
  if (current_time_in_state < MAX_IDLE_TIME){
    go_on_pulsing();
    check_difficulty_level();
    if (player_input_started()){
      change_game_state(GAME_INIT);
    }
  } else {
    change_game_state(GAME_SLEEP);
  }
}

void game_sleep(){
  log("Going to sleep..");
  reset_pulsing();
  delay(500);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();  
  sleep_disable();   
  change_game_state(GAME_INTRO);
}

void generatePattern(){
  max_time_to_generate_pattern = 3000 + random(T1_TIME);
  change_game_state(GAME_LOOP_GENERATE_PATTERN);
}

void game_init(){
  reset_pulsing();

  difficulty_level = read_difficulty_level();
  difficulty_scaling_factor = 1.0 + difficulty_level*0.1;
  log(String("Scaling F: ") + difficulty_scaling_factor);
  
  score = 0;
  
  print_on_console("Go!");  
  max_time_to_display_pattern = T2_TIME; 
  max_time_to_form_pattern = T3_TIME;
  generatePattern();
}


void game_loop_generate_pattern(){
  if (current_time_in_state >= max_time_to_generate_pattern){
      /* generate pattern */
      current_pattern = (unsigned char) random(16); /* 4 bits */
      log(String("turning on pattern ") + current_pattern);
      turn_on_pattern(current_pattern);
      change_game_state(GAME_LOOP_DISPLAY_PATTERN);
  }
}

void game_loop_display_pattern(){
  if (current_time_in_state >= max_time_to_display_pattern){
      turn_off_pattern();
      log(String("Now it's input time... waiting for: ") + max_time_to_form_pattern);
      reset_player_input();
      change_game_state(GAME_LOOP_WAITING_PLAYER_PATTERN);
  }
}

void change_to_game_over(){
  print_on_console(String("Game Over - Final Score: ") + score);  
  change_game_state(GAME_OVER);
}


void game_loop_wait_player_pattern(){
  unsigned char current_input_pat = get_current_pattern();
  if (current_time_in_state >= max_time_to_form_pattern){
      log("check patterns ");
      log(String("the input one is: ") + current_input_pat);
      log(String("the good one was: ") + current_pattern);
      if (current_input_pat != current_pattern){
        change_to_game_over();
      } else {
        score++;
        max_time_to_display_pattern /= difficulty_scaling_factor; 
        max_time_to_form_pattern /= difficulty_scaling_factor;
        print_on_console(String("New Point! Score ") + score);
        turn_off_pattern();
        generatePattern();
      }
  } else {
    turn_on_pattern(current_input_pat);
  }
}

void game_over(){
  if (current_time_in_state > TIME_IN_GAME_OVER){
     change_game_state(GAME_INTRO);
  }
}
