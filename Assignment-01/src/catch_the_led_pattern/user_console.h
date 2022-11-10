/*********
 * 
 * USER CONSOLE
 * 
 * This module implements the user console,
 * containing the buttons for interacting
 * with the user as well as the console
 * to output the messages.
 * 
 */
#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__
#include "Arduino.h" 

#define NUM_INPUT_POS 4
#define LAST_POS 3

#define NO_SELECTION -1
#define DIFFICULTY_LEVELS 8

void init_player_console();

void print_on_console(const String& msg);

/* read the difficulty level */
int read_difficulty_level();

/* check if the player started the game */
bool player_input_started();

/* reset the input, at each interation */
void reset_player_input();

/* get current pattern inserted by player */
unsigned char get_current_pattern();

/* for testing */
void test_player_input();

/* for debugging */
void log(const String& msg);
 


#endif
