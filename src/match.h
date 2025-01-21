//
// Match
// Structs and functions dealing with "matches"
//
struct Opponent {
    char name[64];
    int caution;
    int die_sides;
    bool is_boss;
    bool trait_aggressive;
    bool trait_clever;
    bool trait_cheater;
    bool trait_high_stakes;
};
struct Match {
    int player_total;
    int opponent_total;
    int turn;
    bool player_held;
    bool opponent_held;
    bool ended;
    struct Opponent opponent;
};
// Print the score bar
void match_print_score_bar(int total) {
    int per = (int)((float)TERM_WIDTH / GOAL_NUM + 0.5f);
    enum Color color = total > GOAL_NUM ? CLR2 : CLR5;
    color = total == GOAL_NUM ? CLR3 : color;
    for (int i = 0; i < GOAL_NUM; i++) {
        if (i < total) {
            for (int j = 0; j < per; j++) {
                printfc(color, "█");
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
    printfc(CLR3, ">> Scanning Opponent With Scanner LVL %d/%d <<\n", state->scanner_lvl, SCAN_LVL_MAX);
    printfc(CLR6, "Opponent: %s\n", match->opponent.name);
    printfc(CLR5, "⚄⚀ Die sides: %d\n", match->opponent.die_sides);
    char unknown[] = "?";
    char yes[] = "Y";
    char no[] = "N";
    char aggressive[8];
    strcpy(aggressive, unknown);
    char clever[8];
    strcpy(clever, unknown);
    char cheater[8];
    strcpy(cheater, unknown);
    char high_stakes[8];
    strcpy(high_stakes, unknown);
    char caution[8];
    strcpy(caution, unknown);
    char caution_hold[16];
    strcpy(caution_hold, unknown);
    enum Color unknown_color = CLR1;
    enum Color yes_color = CLR2;
    enum Color no_color = CLR3;
    enum Color aggressive_color = unknown_color;
    enum Color clever_color = unknown_color;
    enum Color cheater_color = unknown_color;
    enum Color high_stakes_color = unknown_color;
    if (state->scanner_lvl >= 0) {
        high_stakes_color = (match->opponent.trait_high_stakes ?  yes_color : no_color);
        strcpy(high_stakes, (match->opponent.trait_high_stakes ?  yes : no));
    }
    if (state->scanner_lvl >= 1) {
        clever_color = (match->opponent.trait_clever ?  yes_color : no_color);
        strcpy(clever, (match->opponent.trait_clever ?  yes : no));
    }
    if (state->scanner_lvl >= 2) {
        cheater_color = (match->opponent.trait_cheater ?  yes_color : no_color);
        strcpy(cheater, (match->opponent.trait_cheater ?  yes : no));
    }
    if (state->scanner_lvl >= 3) {
        aggressive_color = (match->opponent.trait_aggressive ?  yes_color : no_color);
        strcpy(aggressive, (match->opponent.trait_aggressive ?  yes : no));
    }
    if (state->scanner_lvl >= 4) {
        sprintf(caution, "%d", match->opponent.caution);
    }
    if (state->scanner_lvl >= 5) {
        sprintf(caution_hold, "%d", GOAL_NUM - match->opponent.caution); 
    }
    printfc(high_stakes_color, "㊋ Hi-Stakes: %s | ", high_stakes);
    printfc(clever_color, "㈫ Clever: %s \n", clever);
    printfc(cheater_color,     "㊋ Cheater: %s   | ", cheater);
    printfc(aggressive_color, "㈫ Aggressive: %s \n", aggressive);
    printfc(CLR5, "㈫ Caution: %s (Usually holds at %s) \n", caution, caution_hold);
    print_div();
}
// Print the match info
void match_print(struct Match *match) {
    print_div();
    printfc(CLR5, "player total: %d\n", match->player_total);
    match_print_score_bar(match->player_total);
    printf("\n");
    printfc(CLR7, "%s total: %d\n", match->opponent.name, match->opponent_total);
    match_print_score_bar(match->opponent_total);
    printf("\n");
    print_div();
}
// Start a match with a new opponent and reset the match state
//TODO: Does too much - shouldnt print
void match_start(struct State *state, struct Match *match) {
    match->player_total = 0;
    match->opponent_total = 0;
    match->turn = 0;
    match->opponent.die_sides = (rand() % (GOAL_NUM -3)) + 3;
    match->player_held = false;
    match->opponent_held = false;
    match->opponent.is_boss = false;
    match->opponent.caution = rand() % (GOAL_NUM / 2);
    match->opponent.trait_aggressive = rand() % 4 == 0;
    match->opponent.trait_clever = rand() % 4 == 0;
    match->opponent.trait_cheater = rand() % 4 == 0;
    match->opponent.trait_high_stakes = rand() % 4 == 0;
    match->ended = false;
    opponent_name_rand(match->opponent.name);
    // Boss
    if (state->wins >= 7 && rand() % CHANCE_BOSS == 0) {
        char boss_name[128];
        sprintf(boss_name, "㊋ mega %s ㊋", match->opponent.name);
        strcpy(match->opponent.name, boss_name);
        match->opponent.is_boss = true;
        match->opponent.die_sides = GOAL_NUM / 10;
        match->opponent.caution = 1;
        match->opponent.trait_aggressive = true;
        match->opponent.trait_clever = true;
        match->opponent.trait_cheater = true;
        match->opponent.trait_high_stakes = true;
    }
    print_div();
    print_subtitle(CLR2, "Match Started");
    match_print_opponent(state, match);
    state_print_gold(state);
    int base_stakes = state->lvl;
    if (match->opponent.trait_high_stakes) base_stakes *= 2;
    if (match->opponent.is_boss) base_stakes *= 2; 
    printfc(CLR1, "Stakes: $%d-$%d \n", base_stakes, base_stakes * 2);
    print_div();
}
// End a match
// TODO: should not include initial subtitle
void match_end_screen(struct Match *match, struct State *state, struct Cheat cheats_list[], int won, char msg[]) { // won = 2 == draw
    print_subtitle(CLR2, "Match Ended");
    input_to_continue();
    // Update gold
    int gold_delta = 0;
    if (won == 1) gold_delta = state->lvl;
    if (won == 0) gold_delta = -state->lvl;
    if (match->player_total == GOAL_NUM) gold_delta *= 2;
    else if (match->player_total > GOAL_NUM) gold_delta *= 2;
    if (match->opponent.trait_high_stakes) gold_delta *= 2;
    if (match->opponent.is_boss) gold_delta *= 2;
    state->gold += gold_delta;
    // Update match record
    if (won == 0) state->losses++;
    if (won == 1) state->wins++;
    if (won == 2) state->draws++;
    // Draw to screen
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
    input_to_continue();
    clear_screen("Match Summary");
    if (gold_delta == 0) printfc(CLR1, "// Gained no gold\n");
    if (gold_delta > 0) printfc(CLR4, "++ Gained %d gold\n", gold_delta);
    if (gold_delta < 0) printfc(CLR2, "-- Lost %d gold\n", -gold_delta);
    if (match->opponent.trait_high_stakes) printfc(CLR4, "(Match was HI-STAKES)\n");
    state_print_status(state, 1);
    if (won == 1) printfc(CLR4, "You got a loot box for winning!");
    input_to_continue();
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