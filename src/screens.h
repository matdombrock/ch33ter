//
// Screens
// Various screens used in the game
//
void welcome_screen(struct State *state) {
    clear_screen("INFO");
    print_logo();
    printfc(CLR1, "v%s\n", VERSION);
    printfc(CLR3, "Mathieu Dombrock - GPL3\n\n");
    printfc(CLR1, "Note: Ch33ter is an offline game.\n");
    printfc(CLR6, "- It is not connected to the internet.\n");
    printfc(CLR6, "- It does not collect any data.\n");
    printfc(CLR6, "- It does not send any data.\n");
    printfc(CLR1, "The 'login' data is used to generate an\nRNG seed.");
    input_to_continue();
    clear_screen("SIGN IN");
    print_logo();
    input_get_string("new username: ", state->username);
    clear_screen("SIGN IN");
    print_logo();
    input_get_string("new password: ", state->password);
    int password_sum = 0;
    for (int i = 0; i < strlen(state->username); i++) {
        password_sum += state->username[i];
    }
    for (int i = 0; i < strlen(state->password); i++) {
        password_sum += state->password[i];
    }
    // Set the random seed
    srand(password_sum);
    clear_screen("WELCOME");
    print_logo();
    printfc(CLR1, "Hello %s (#%d)!\n", state->username, password_sum);
    printfc(CLR1, "You will be challenged in a game something\nlike what you might call '21'.\n");
    printfc(CLR1, "Here, the goal is to reach %d without going over.\nAnd we play with custom dice!\n", GOAL_NUM);
    printfc(CLR1, "Your opponents will be many.");
    printfc(CLR1, "Some will be strong some will be weak.\n");
    printfc(CLR4, "They will bring their own dice. You must account for that.\n");
    printfc(CLR5, "The best way to account for that might be cheating...\n");
    printfc(CLR1, "Good luck!\n");
    input_to_continue();
}
void intro_screen() {
    clear_screen("Intro");
    printfc(CLR4, "You have been given some cheats to start with\n");
    printfc(CLR3, "-  use these cheats to help you win matches\n");
    printfc(CLR3, "-  gain more cheats by winning matches\n");
    printfc(CLR3, "-  inspect your cheats by pressing");
    printfc(CLR6, " %c\n", CMD_CHEAT_LIST);
    printfc(CLR3, "-  inspect your opponent by pressing");
    printfc(CLR6, " %c\n", CMD_OPPONENT);
    printfc(CLR3, "-  roll by pressing");
    printfc(CLR6, " %c\n", CMD_ROLL);
    printfc(CLR3, "-  hold by pressing");
    printfc(CLR6, " %c\n", CMD_HOLD);
    printfc(CLR3, "-  use cheats by pressing");
    printfc(CLR6, " %c, %c", CMD_USE_CHEAT_1, CMD_USE_CHEAT_2);
    printfc(CLR3, " and so on\n");
    printfc(CLR4, "The goal is to get as high of a score as you can\nwithout going over");
    printfc(CLR4, " %d\n", GOAL_NUM);
    printfc(CLR7, "\n███ Press %c to see the help screen during a match! ██████████████\n", CMD_HELP);
    input_to_continue();
}
void game_over_screen() {
    clear_screen("Game Over");
    printfc(CLR1, "\n       $$$$$$$$$$$$$$$\n");
    printfc(CLR2, "     $$$$$$$$$$$$$$$$$$$$\n");
    printfc(CLR3, "   $$$$$$$$$$$$$$$$$$$$$$$$    NO\n");
    printfc(CLR4, "  $$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printfc(CLR5, " $$$$$$$$$$$$/      \\$$$/   $    MORE\n");
    printfc(CLR6, "$$$$$$$$$$$$$\\      $$  $___$\n");
    printfc(CLR7, "$$$$$$$$$$ $$$$$$$$$$  | \\$$$$$    GOLD!\n");
    printfc(CLR8, "$$$$$$$$$$ $$$$$$$$$\\__$_/$$$$$\n");
    printfc(CLR1, " $$$$$$$$$$$$/,/,/./'/_|.\\'\\,\\\n");
    printfc(CLR2, "   $$$$$$$$$$||||||||||||||||||\n");
    printfc(CLR3, "              \\/|/|/|/|/|/|/|/ \n\n");
    printfc(CLR2, "\nYou are brutally assaulted for your inability to pay your debts.\n");
    print_div();
}
// Open a loot box
void loot_box_screen(struct State *state, struct Cheat cheats_list[]) {
    clear_screen("Loot Box");
    printfc(CLR3, "You got a loot box!\n");
    int cheat_list_index = rand() % CHEATS_AMT;
    state_attempt_gain_cheat(state, cheats_list, cheat_list_index);
    cheat_print(&cheats_list[cheat_list_index]);
    print_div();
    printfc(CLR1, "\n");
    state_print_cheats(state, cheats_list);
    input_to_continue();
}
// Coin flip (gamble)
void coin_flip_screen(int amt, struct State *state) {
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
    input_to_continue();
}