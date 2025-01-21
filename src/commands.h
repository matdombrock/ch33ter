//
// Commands
// These functions handle the main game commands
//
void cmd_roll(struct Match *match) {
    clear_screen("Roll");
    int roll = roll_die(match->opponent.die_sides);
    match->player_total += roll;
    match->turn++;
    printfc(CFG_CLR4, "player rolls: %d / %d\n", roll, match->opponent.die_sides);
    opponent_turn(match);
    match->player_held = false;
}
void cmd_hold(struct Match *match) {
    clear_screen("Hold");
    match->player_held = true;
    printfc(CFG_CLR5, "player holds\n");
    opponent_turn(match);
    match->player_held = true;
}
void cmd_cheat_list(struct State *state, struct Cheat cheats_list[]) {
    clear_screen("Cheat Slots");
    state_print_cheats(state, cheats_list);
}

void cmd_use_cheat(struct State *state, struct Match *match, int cheat_index, struct Cheat cheats_list[]) {
    clear_screen("Use Cheat");
    printfc(CFG_CLR1, "Using cheat \n");
    int used_index = state_use_cheat(state, cheat_index);
    if (used_index == -1) {
        printfc(CFG_CLR1, "Invalid cheat\n");
        return;
    }
    struct Cheat cheat = cheats_list[used_index];
    cheat_print(&cheat);
    bool affects_player = cheat.affects == 0 || cheat.affects == 2;
    bool affects_opponent = cheat.affects == 1 || cheat.affects == 2;
    if (cheat.add != 0) {
        printfc(CFG_CLR1, "Adding %d\n", cheat.add);
        if (affects_player) match->player_total += cheat.add;
        if (affects_opponent) match->opponent_total += cheat.add;
    }
    if (cheat.sub != 0) {
        printfc(CFG_CLR1, "Subtracting %d\n", cheat.sub);
        if (affects_player) match->player_total -= cheat.sub;
        if (affects_opponent) match->opponent_total -= cheat.sub;
    }
    if (cheat.div != 0) {
        printfc(CFG_CLR1, "Dividing by %d\n", cheat.div);
        if (affects_player) match->player_total /= cheat.div;
        if (affects_opponent) match->opponent_total /= cheat.div;
    }
    if (cheat.mult != 0) {
        printfc(CFG_CLR1, "Multiplying by %d\n", cheat.mult);
        if (affects_player) match->player_total *= cheat.mult;
        if (affects_opponent) match->opponent_total *= cheat.mult;
    }
    if (cheat.set != 0) {
        printfc(CFG_CLR1, "Setting to %d\n", cheat.set);
        if (affects_player) match->player_total = cheat.set;
        if (affects_opponent) match->opponent_total = cheat.set;
    }
    if (cheat.swap) {
        printfc(CFG_CLR1, "Swapping scores\n");
        int temp = match->player_total;
        match->player_total = match->opponent_total;
        match->opponent_total = temp;
    }
    if (cheat.invert) {
        printfc(CFG_CLR1, "Inverting scores\n");
        if (affects_player) match->player_total = GOAL_NUM - match->player_total;
        if (affects_opponent) match->opponent_total = GOAL_NUM - match->opponent_total;
    }
    if (cheat.reset) {
        printfc(CFG_CLR1, "Resetting score\n");
        if (affects_player) match->player_total = 0;
        if (affects_opponent) match->opponent_total = 0;
    }
    if (cheat.match_high) {
        printfc(CFG_CLR1, "Matching high score\n");
        if (match->player_total > match->opponent_total) {
            match->opponent_total = match->player_total;
        } else {
            match->player_total = match->opponent_total;
        }
    }
    if (cheat.match_low) {
        printfc(CFG_CLR1, "Matching low score\n");
        if (match->player_total < match->opponent_total) {
            match->opponent_total = match->player_total;
        } else {
            match->player_total = match->opponent_total;
        }
    }
}

void cmd_opponent(struct State *state, struct Match *match) {
    clear_screen("Opponent");
    match_print_opponent(state, match);
    input_to_continue();
}

void cmd_status(struct State *state) {
    clear_screen("Status");
    state_print_status(state, 0);
    input_to_continue();
}

void cmd_help() {
    clear_screen("Help p1");
    print_subtitle(CFG_CLR3, "Page 1/4 - Commands:");
    printfc(CFG_CLR1, "%c - roll\n", CFG_CMD_ROLL);
    printfc(CFG_CLR1, "%c - hold\n", CFG_CMD_HOLD);
    printfc(CFG_CLR1, "%c - inspect cheat slots\n", CFG_CMD_CHEAT_LIST);
    printfc(CFG_CLR1, "%c - inspect opponent\n", CFG_CMD_OPPONENT);
    printfc(CFG_CLR1, "%c - inspect self\n", CFG_CMD_STATUS);
    printfc(CFG_CLR1, "%c - use cheat slot 1 | ", CFG_CMD_USE_CHEAT_1);
    printfc(CFG_CLR1, "%c - use cheat slot 2\n", CFG_CMD_USE_CHEAT_2);
    printfc(CFG_CLR1, "%c - use cheat slot 3 | ", CFG_CMD_USE_CHEAT_3);
    printfc(CFG_CLR1, "%c - use cheat slot 4\n", CFG_CMD_USE_CHEAT_4);
    printfc(CFG_CLR1, "%c - use cheat slot 5 | ", CFG_CMD_USE_CHEAT_5);
    printfc(CFG_CLR1, "%c - use cheat slot 6\n", CFG_CMD_USE_CHEAT_6);
    printfc(CFG_CLR1, "%c - use cheat slot 7 | ", CFG_CMD_USE_CHEAT_7);
    printfc(CFG_CLR1, "%c - use cheat slot 8\n", CFG_CMD_USE_CHEAT_8);
    printfc(CFG_CLR1, "%c - quit\n", CFG_CMD_QUIT);
    printfc(CFG_CLR1, "%c - help\n", CFG_CMD_HELP);
    input_to_continue();
    clear_screen("Help p2");
    print_subtitle(CFG_CLR3, "Page 2/4 - Rules:");
    printfc(CFG_CLR1, "- The goal is to approach %d without exceeding it\n", GOAL_NUM);
    printfc(CFG_CLR1, "- Each turn you may roll or hold\n");
    printfc(CFG_CLR1, "- Rolling adds to your total\n");
    printfc(CFG_CLR1, "- Holding passes your turn.\n");
    printfc(CFG_CLR1, "- You may choose to roll again after holding \n");
    printfc(CFG_CLR1, "- If you go over %d you bust\n", GOAL_NUM);
    printfc(CFG_CLR1, "- If both players hold the game is over\n");
    printfc(CFG_CLR1, "- The player with the highest score wins\n");
    printfc(CFG_CLR1, "- If both players have the same score it's a draw\n");
    printfc(CFG_CLR1, "- If both players bust it's a draw\n");
    input_to_continue();
    clear_screen("Help p3");
    print_subtitle(CFG_CLR3, "Page 3/4 - Cheating:"); 
    printfc(CFG_CLR1, "Cheat format:\n");
    printfc(CFG_CLR3, "[cheat_name] ");
    printfc(CFG_CLR5, "| [affects] ");
    printfc(CFG_CLR4, "| [properties] \n");
    printfc(CFG_CLR1, "-------\n");
    printfc(CFG_CLR3, "[cheat_name] - the name of the cheat\n");
    printfc(CFG_CLR5, "[affects] - who the cheat affects\n");
    printfc(CFG_CLR5, "plr=player opn=opponent bth=both\n");
    printfc(CFG_CLR4, "[properties] - what the cheat does\n");
    printfc(CFG_CLR5, "+N adds | -N subtracts | /N divides | *N multiplies | =N sets\n");
    printfc(CFG_CLR5, "swp swaps | inv inverts | rst resets\n");
    printfc(CFG_CLR1, "-------\n");
    printfc(CFG_CLR3, "[example ");
    printfc(CFG_CLR5, "| both ");
    printfc(CFG_CLR4, "| +1 | swp \n");
    printfc(CFG_CLR1, "This cheat would add 1 to both scores and then swap them\n");
    input_to_continue();
    clear_screen("Help p4");
    print_subtitle(CFG_CLR3, "Page 4/4 - Tips:"); 
    printfc(CFG_CLR1, "- Cheats can be used to manipulate scores\n");
    printfc(CFG_CLR1, "- Cheating does _NOT_ count as taking a turn\n");
    printfc(CFG_CLR1, "- Use cheats as much as possible\n");
    printfc(CFG_CLR1, "- Cheats are not scarce\n");
    printfc(CFG_CLR1, "- Cheats can be used to help or hinder\n");
    printfc(CFG_CLR1, "- Cheats can be used to manipulate the opponent\n");
    printfc(CFG_CLR1, "- Win +1 gold | Slam it +2 gold\n");
    printfc(CFG_CLR1, "- Lose -1 gold | Bust -2 gold \n");
    printfc(CFG_CLR1, "- 'inv' subtracts the current score from %d\n", GOAL_NUM);
    printfc(CFG_CLR1, "- 'swp' swaps the scores (always affects both)\n");
    printfc(CFG_CLR1, "- 'rst' sets the score to 0\n");
    input_to_continue();
}