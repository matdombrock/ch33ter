//
// Misc Screens
//
void welcome_screen(struct State *state) {
    clear_screen("SIGN IN");
    print_logo();
    get_input_string("new username: ", state->username);
    clear_screen("SIGN IN");
    print_logo();
    get_input_string("new password: ", state->password);
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
    printfc(CLR1, "Your opponents will be many. Some will be\nstrong some will be weak.\n");
    printfc(CLR4, "They will bring their own dice. You must account for that.\n");
    printfc(CLR5, "The best way to account for that might be cheating...\n");
    printfc(CLR1, "Good luck!\n");
    to_continue();
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
    to_continue();
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