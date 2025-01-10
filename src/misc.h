//
// Misc
//
// Return a random number between 1 and sides
int roll_die(int sides) {
    return rand() % sides + 1;
}
// Opponent logic
void opponent_turn(struct Match *match) {
    // Greater than caution and (not aggressive or greater than player)
    if (match->opponent_total >= (GOAL_NUM - match->opponent_caution) && (!match->trait_aggressive || match->opponent_total >= match->player_total)) {
        printfc(CLR5, "%s holds\n", match->opponent_name);
        match->opponent_held = true;
        return;
    }
    int roll = roll_die(match->die_sides);
    match->opponent_total += roll;
    match->opponent_held = false;
    printfc(CLR4, "%s rolls: %d / %d\n", match->opponent_name, roll, match->die_sides);
}
#define MAX_PRICE 33
// Purchase from the vendor
void vendor_purchase(struct State *state, struct Cheat cheats_list[], int *cheat_index, int *cheat_price) {
    clear_screen("Purchasing");
    printfc(CLR4, "You ask to purchase %s\n", cheats_list[cheat_index[0]].name);
    if (state_count_cheats(state) >= state->cheats_cap) {
        printfc(CLR2, "But you have no more cheat slots available!\n");
    }
    else if (state->gold >= cheat_price[0]) {
        state->gold -= cheat_price[0];
        state_attempt_gain_cheat(state, cheats_list, cheat_index[0]);
        cheat_index[0] = rand() % CHEATS_AMT;
        cheat_index[0] = rand() % MAX_PRICE + 1;
    }
    else {
        printfc(CLR2, "But you dont have enough gold! (missing: %d)\n", cheat_price[0] - state->gold);
    }
    cheat_print(&cheats_list[cheat_index[0]]);
    print_div();
    state_print_cheats(state, cheats_list);
    state_print_gold(state);
    to_continue();
}
// Coin flip (gamble)
void coin_flip(int amt, struct State *state) {
    clear_screen("Coin Flip");
    printfc(CLR4, "You ask to flip a coin\n");
    if (state->gold >= amt) {
        int flip = rand() % 2;
        if (flip == 0) {
            printfc(CLR2, "You lost %d gold!\n", amt);
            state->gold -= amt;
        }
        else {
            printfc(CLR4, "You gained %d gold!\n", amt);
            state->gold += amt;
        }
    }
    else {
        printfc(CLR2, "But you dont have enough gold to wager! (missing: %d)\n", amt - state->gold);
    }
    state_print_gold(state);
    to_continue();
}