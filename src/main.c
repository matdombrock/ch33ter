#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h> // va_list, va_start, va_end
#include <ctype.h>  // toupper

#include "constant.h"
#include "_config.h"

#include "util.h"
#include "input.h"
#include "opponent_names.h"
#include "cheat.h"
#include "state.h"
#include "loot_box.h"
#include "match.h"
#include "misc.h"
#include "random_encounters.h"
#include "misc_screens.h"
#include "commands.h"

//
// Main
//
int main() {
    // Setup RNG
    int seed = time(NULL);
    srand(seed);
    // Setup basic game state
    struct State state = state_constructor();
    // Welcome
    welcome_screen();
    // Setup cheats
    struct Cheat cheats_list[1024];
    cheats_list_init(cheats_list);
    // Gain some cheats
    loot_box_screen(&state, cheats_list);
    loot_box_screen(&state, cheats_list);
    loot_box_screen(&state, cheats_list);
    // Intro
    intro_screen();
    // Start first match
    clear_screen("ch33ter");
    struct Match match;
    match_start(&state, &match);
    int run = 1;
    while(run) {
        print_div();
        char input = get_input();
        switch (input) {
            case CMD_USE_CHEAT_1:
                cmd_use_cheat(&state, &match, 0, cheats_list);
                break;
            case CMD_USE_CHEAT_2:
                cmd_use_cheat(&state, &match, 1, cheats_list);
                break;
            case CMD_USE_CHEAT_3:
                cmd_use_cheat(&state, &match, 2, cheats_list);
                break;
            case CMD_USE_CHEAT_4: 
                cmd_use_cheat(&state, &match, 3, cheats_list);
                break;
            case CMD_USE_CHEAT_5:
                cmd_use_cheat(&state, &match, 4, cheats_list);
                break;
            case CMD_USE_CHEAT_6:
                cmd_use_cheat(&state, &match, 5, cheats_list);
                break;
            case CMD_USE_CHEAT_7:
                cmd_use_cheat(&state, &match, 6, cheats_list);
                break;
            case CMD_USE_CHEAT_8:
                cmd_use_cheat(&state, &match, 7, cheats_list);
                break;
            case CMD_ROLL:
                cmd_roll(&match);
                break;
            case CMD_HOLD:
                cmd_hold(&match);
                break;
            case CMD_CHEAT_LIST:
                cmd_cheat_list(&state, cheats_list);
                break;
            case CMD_OPPONENT:
                cmd_opponent(&state, &match);
                break;
            case CMD_STATUS:
                cmd_status(&state);
                break;
            case CMD_HELP:
                cmd_help();
                break;
            case CMD_QUIT:
                run = 0;
                break;
            default:
                printfc(CLR2, "Invalid input\n");
                printfc(CLR3, "Press %c for help\n", CMD_HELP);
        }
        // Show match info
        match_print(&match);
        state_print_gold(&state);
        // Check for match end
        match_check(&match, &state, cheats_list);
        if (state.gold < 0) {
            game_over_screen(); 
            run = 0;
            break; // end game
        }
        if (match.ended) {
            random_encounters(&state, cheats_list);
            match_start(&state, &match);
        }
    }
    printfc(CLR1, "goodbye\n");
    return 0;
}