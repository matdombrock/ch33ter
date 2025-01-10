//
// Match
//
struct Match {
    int player_total;
    int opponent_total;
    int opponent_caution;
    int turn;
    int die_sides;
    bool player_held;
    bool opponent_held;
    bool trait_aggressive;
    bool trait_clever;
    bool trait_cheater;
    bool trait_high_stakes;
    bool ended;
    char opponent_name[64];
};
// Print the score bar
void match_print_score_bar(int total) {
    int per = (int)((float)TERM_WIDTH / GOAL_NUM + 0.5f);
    for (int i = 0; i < GOAL_NUM; i++) {
        if (i < total) {
            for (int j = 0; j < per; j++) {
                printfc(total > GOAL_NUM ? CLR2 : CLR5, "█");
            }
        } else {
            for (int j = 0; j < per; j++) {
                printfc(CLR8, "▒");
            }
        }
    }
    printfc(CLR3, "|");
}
// Print the opponent info
void match_print_opponent(struct State *state, struct Match *match) {
    printfc(CLR6, "Opponent: %s\n", match->opponent_name);
    printfc(CLR5, "⚄⚀ Die sides: %d\n", match->die_sides);
    if (state->scanner_lvl == 0) {
        printfc(CLR5, "㊋ Aggressive: ¿¿¿\n");
        printfc(CLR5, "㈫ Caution: ¿¿¿ (holds at ¿¿¿) \n");
    }
    if (state->scanner_lvl == 1) {
        printfc(CLR5, "㊋ Aggressive: %s\n", match->trait_aggressive ? "✓" : "X");
        printfc(CLR5, "㈫ Caution: %d (holds at ¿¿¿) \n", match->opponent_caution);
    }
    if (state->scanner_lvl >= 1) {
        printfc(CLR5, "㊋ Aggressive: %s\n", match->trait_aggressive ? "✓" : "X");
        printfc(CLR5, "㈫ Caution: %d (holds at %d) \n", match->opponent_caution, GOAL_NUM - match->opponent_caution);
    }
    printfc(CLR3, "Scanned with: Scanner LVL%d\n", state->scanner_lvl);
}
// Print the match info
void match_print(struct Match *match) {
    print_div();
    printfc(CLR5, "player total: %d\n", match->player_total);
    match_print_score_bar(match->player_total);
    printf("\n");
    printfc(CLR7, "%s total: %d\n", match->opponent_name, match->opponent_total);
    match_print_score_bar(match->opponent_total);
    printf("\n");
    print_div();
}
// Start a match with a new opponent and reset the match state
//TODO: Does too much - shouldnt print
void match_start(struct State *state, struct Match *match) {
    match->player_total = 0;
    match->opponent_total = 0;
    match->opponent_caution = rand() % 11;
    match->turn = 0;
    match->die_sides = (rand() % (GOAL_NUM -3)) + 3;
    match->player_held = false;
    match->opponent_held = false;
    match->trait_aggressive = rand() % 4 == 0;
    match->trait_clever = rand() % 4 == 0;
    match->trait_cheater = rand() % 4 == 0;
    match->trait_high_stakes = rand() % 4 == 0;
    match->ended = false;
    strcpy(match->opponent_name, "OpponentX");
    opponent_name_rand(match->opponent_name);
    print_div();
    print_subtitle(CLR2, "Match Started");
    match_print_opponent(state, match);
    state_print_gold(state);
    print_div();
}
// End a match
// TODO: should not include initial subtitle
void match_end_screen(struct Match *match, struct State *state, struct Cheat cheats_list[], int won, char msg[]) { // won = 2 == draw
    print_subtitle(CLR2, "Match Ended");
    to_continue();
    // Update gold
    int gained = 0;
    if (won == 1) {
        gained += 1;
        if (match->player_total == GOAL_NUM) {
            gained += 1;
        }
    }
    if (won == 0) {
        gained -= 1;
        if (match->player_total > GOAL_NUM) {
            gained -= 2;
        }
    }
    state->gold += gained;
    // Update match record
    if (won == 0) state->losses++;
    if (won == 1) state->wins++;
    if (won == 2) state->draws++;
    // Draw
    enum Color result_colors[3] = {CLR2, CLR4, CLR5};
    enum Color result_color = result_colors[won];
    clear_screen("Match Summary");
    if (won == 1) {
        print_subtitle(result_color, "WIN!");
    }
    if (won == 0) {
        print_subtitle(result_color, "LOSE!");
    }
    if (won == 2) {
        print_subtitle(result_color, "DRAW!");
    }
    printfc(result_color, "%s\n", msg);
    match_print_opponent(state, match);
    match_print(match);
    if (gained == 0) printfc(CLR1, "// Gained no gold\n");
    if (gained > 0) printfc(CLR4, "++ Gained %d gold\n", gained);
    if (gained < 0) printfc(CLR2, "-- Lost %d gold\n", -gained);
    state_print_status(state, 1);
    to_continue();
    // Get new cheat
    if ( won == 1) {
        loot_box_screen(state, cheats_list);
    }
    match->ended = true;
}
// Check if the match has ended
void match_check(struct Match *match, struct State *state, struct Cheat cheats_list[]) {
    if (match->player_total == GOAL_NUM && match->opponent_total == GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 2, "Both slammed it!");
    }
    else if (match->player_total == GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 1, "Player slammed it!");
    }
    else if (match->opponent_total == GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 0, "Opponent slammed it!");
    }
    else if (match->player_total > GOAL_NUM && match->opponent_total > GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 2, "Both bust!");
    }
    else if (match->opponent_total > GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 1, "Opponent busts!");
    }
    else if (match->player_total > GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 0, "Player busts!");
    }
    else if (match->player_held && match->opponent_held) {
        if (match->player_total == match->opponent_total) {
            match_end_screen(match, state, cheats_list, 2, "Even scores!");
        }
        else if (match->player_total > match->opponent_total) {
            match_end_screen(match, state, cheats_list, 1, "Player wins with a higher score!");
        } 
        else {
            match_end_screen(match, state, cheats_list, 0, "Opponent wins with a higher score!");
        }
    }
}