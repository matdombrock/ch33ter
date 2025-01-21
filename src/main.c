#include <stdio.h>
#include <stdlib.h>
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
#include "screens.h"
#include "vendor.h"
#include "match.h"
#include "opponent_turn.h"
#include "random_encounters.h"
#include "commands.h"

//
// Main Loop
//
int main() {
    // Set console output to UTF-8
    set_console_output();
    // Setup basic game state
    struct State state = state_new();
    // Welcome
    // The welcome screen will set the RNG seed based on the username and password
    welcome_screen(&state);
    // Setup cheats
    struct Cheat cheats_list[1024]; // CHEATS_AMT
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
        char input = input_get();
        switch (input) {
            case CFG_CMD_USE_CHEAT_1:
                cmd_use_cheat(&state, &match, 0, cheats_list);
                break;
            case CFG_CMD_USE_CHEAT_2:
                cmd_use_cheat(&state, &match, 1, cheats_list);
                break;
            case CFG_CMD_USE_CHEAT_3:
                cmd_use_cheat(&state, &match, 2, cheats_list);
                break;
            case CFG_CMD_USE_CHEAT_4: 
                cmd_use_cheat(&state, &match, 3, cheats_list);
                break;
            case CFG_CMD_USE_CHEAT_5:
                cmd_use_cheat(&state, &match, 4, cheats_list);
                break;
            case CFG_CMD_USE_CHEAT_6:
                cmd_use_cheat(&state, &match, 5, cheats_list);
                break;
            case CFG_CMD_USE_CHEAT_7:
                cmd_use_cheat(&state, &match, 6, cheats_list);
                break;
            case CFG_CMD_USE_CHEAT_8:
                cmd_use_cheat(&state, &match, 7, cheats_list);
                break;
            case CFG_CMD_ROLL:
                cmd_roll(&match);
                break;
            case CFG_CMD_HOLD:
                cmd_hold(&match);
                break;
            case CFG_CMD_CHEAT_LIST:
                cmd_cheat_list(&state, cheats_list);
                break;
            case CFG_CMD_OPPONENT:
                cmd_opponent(&state, &match);
                break;
            case CFG_CMD_STATUS:
                cmd_status(&state);
                break;
            case CFG_CMD_HELP:
                cmd_help();
                break;
            case CFG_CMD_QUIT:
                printfc(CFG_CLR8, "You really want to quit?\n");
                printfc(CFG_CLR3, "Press %c to confirm\n", CFG_CMD_QUIT);
                char input = input_get();
                if (input == CFG_CMD_QUIT) { 
                    printfc(CFG_CLR8, "player quit!\n");
                    run = 0;
                    break;
                }
            default:
                printfc(CFG_CLR2, "Invalid input\n");
                printfc(CFG_CLR3, "Press %c for help\n", CFG_CMD_HELP);
        }
        if (run == 0) break;
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
            state.lvl = state.wins + state.losses + state.draws;
            match_start(&state, &match);
        }
    }
    printfc(CFG_CLR1, "goodbye\n");
    return 0;
}