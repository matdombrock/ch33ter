//
// Misc
//
//
void print_logo() {
    printfc(CLR2, "       .__    ________ ________  __    \n");
    printfc(CLR3, "  ____ |  |__ \\_____  \\\\_____  \\/  |_  ___________\n");
    printfc(CLR4, "_/ ___\\|  |  \\  _(__  <  _(__  <   __\\/ __ \\_  __ \\\n");
    printfc(CLR5, "\\  \\___|   Y  \\/       \\/       \\  | \\  ___/|  | \\/\n");
    printfc(CLR6, " \\___  >___|  /______  /______  /__|  \\___  >__|   \n");
    printfc(CLR7, "     \\/     \\/       \\/       \\/          \\/       \n");
}
// Return a random number between 1 and sides
int roll_die(int sides) {
    return rand() % sides + 1;
}
// Purchase from the vendor
void vendor_purchase(struct State *state, struct Cheat cheats_list[], int *cheat_index, int *cheat_price) {
    clear_screen("Purchasing");
    printfc(CLR4, "You ask to purchase %s\n", cheats_list[cheat_index[0]].name);
    if (state_count_cheats(state) >= state->cheat_slots) {
        printfc(CLR2, "But you have no more cheat slots available!\n");
    }
    else if (state->gold >= cheat_price[0]) {
        state->gold -= cheat_price[0];
        state_attempt_gain_cheat(state, cheats_list, cheat_index[0]);
        cheat_index[0] = rand() % CHEATS_AMT;
        cheat_index[0] = rand() % MAX_SHOP_PRICE + 1;
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