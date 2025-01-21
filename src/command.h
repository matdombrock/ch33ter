//
// Commands
// These functions handle the main game commands
//
void cmd_roll(struct Match *match) {
    clear_screen("Roll");
    int roll = roll_die(match->opponent.die_sides);
    match->player_total += roll;
    match->turn++;
    printfc(CRL4, "player rolls: %d / %d\n", roll, match->opponent.die_sides);
    opponent_turn(match);
    match->player_held = false;
}
void cmd_hold(struct Match *match) {
    clear_screen("Hold");
    match->player_held = true;
    printfc(CRL5, "player holds\n");
    opponent_turn(match);
    match->player_held = true;
}
void cmd_cheat_list(struct State *state, struct Cheat cheats_list[]) {
    clear_screen("Cheat Slots");
    state_print_cheats(state, cheats_list);
}

void cmd_use_cheat(struct State *state, struct Match *match, int cheat_index, struct Cheat cheats_list[]) {
    clear_screen("Use Cheat");
    printfc(CRL1, "Using cheat \n");
    int used_index = state_use_cheat(state, cheat_index);
    if (used_index == -1) {
        printfc(CRL1, "Invalid cheat\n");
        return;
    }
    struct Cheat cheat = cheats_list[used_index];
    cheat_print(&cheat);
    bool affects_player = cheat.affects == 0 || cheat.affects == 2;
    bool affects_opponent = cheat.affects == 1 || cheat.affects == 2;
    if (cheat.add != 0) {
        printfc(CRL1, "Adding %d\n", cheat.add);
        if (affects_player) match->player_total += cheat.add;
        if (affects_opponent) match->opponent_total += cheat.add;
    }
    if (cheat.sub != 0) {
        printfc(CRL1, "Subtracting %d\n", cheat.sub);
        if (affects_player) match->player_total -= cheat.sub;
        if (affects_opponent) match->opponent_total -= cheat.sub;
    }
    if (cheat.div != 0) {
        printfc(CRL1, "Dividing by %d\n", cheat.div);
        if (affects_player) match->player_total /= cheat.div;
        if (affects_opponent) match->opponent_total /= cheat.div;
    }
    if (cheat.mult != 0) {
        printfc(CRL1, "Multiplying by %d\n", cheat.mult);
        if (affects_player) match->player_total *= cheat.mult;
        if (affects_opponent) match->opponent_total *= cheat.mult;
    }
    if (cheat.set != 0) {
        printfc(CRL1, "Setting to %d\n", cheat.set);
        if (affects_player) match->player_total = cheat.set;
        if (affects_opponent) match->opponent_total = cheat.set;
    }
    if (cheat.swap) {
        printfc(CRL1, "Swapping scores\n");
        int temp = match->player_total;
        match->player_total = match->opponent_total;
        match->opponent_total = temp;
    }
    if (cheat.invert) {
        printfc(CRL1, "Inverting scores\n");
        if (affects_player) match->player_total = GOAL_NUM - match->player_total;
        if (affects_opponent) match->opponent_total = GOAL_NUM - match->opponent_total;
    }
    if (cheat.reset) {
        printfc(CRL1, "Resetting score\n");
        if (affects_player) match->player_total = 0;
        if (affects_opponent) match->opponent_total = 0;
    }
    if (cheat.match_high) {
        printfc(CRL1, "Matching high score\n");
        if (match->player_total > match->opponent_total) {
            match->opponent_total = match->player_total;
        } else {
            match->player_total = match->opponent_total;
        }
    }
    if (cheat.match_low) {
        printfc(CRL1, "Matching low score\n");
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
    print_subtitle(CRL3, "Page 1/4 - Commands:");
    printfc(CRL1, "%c - roll\n", CFG_CMD_ROLL);
    printfc(CRL1, "%c - hold\n", CFG_CMD_HOLD);
    printfc(CRL1, "%c - inspect cheat slots\n", CFG_CMD_CHEAT_LIST);
    printfc(CRL1, "%c - inspect opponent\n", CFG_CMD_OPPONENT);
    printfc(CRL1, "%c - inspect self\n", CFG_CMD_STATUS);
    printfc(CRL1, "%c - use cheat slot 1 | ", CFG_CMD_USE_CHEAT_1);
    printfc(CRL1, "%c - use cheat slot 2\n", CFG_CMD_USE_CHEAT_2);
    printfc(CRL1, "%c - use cheat slot 3 | ", CFG_CMD_USE_CHEAT_3);
    printfc(CRL1, "%c - use cheat slot 4\n", CFG_CMD_USE_CHEAT_4);
    printfc(CRL1, "%c - use cheat slot 5 | ", CFG_CMD_USE_CHEAT_5);
    printfc(CRL1, "%c - use cheat slot 6\n", CFG_CMD_USE_CHEAT_6);
    printfc(CRL1, "%c - use cheat slot 7 | ", CFG_CMD_USE_CHEAT_7);
    printfc(CRL1, "%c - use cheat slot 8\n", CFG_CMD_USE_CHEAT_8);
    printfc(CRL1, "%c - quit\n", CFG_CMD_QUIT);
    printfc(CRL1, "%c - help\n", CFG_CMD_HELP);
    input_to_continue();
    clear_screen("Help p2");
    print_subtitle(CRL3, "Page 2/4 - Rules:");
    printfc(CRL1, "- The goal is to approach %d without exceeding it\n", GOAL_NUM);
    printfc(CRL1, "- Each turn you may roll or hold\n");
    printfc(CRL1, "- Rolling adds to your total\n");
    printfc(CRL1, "- Holding passes your turn.\n");
    printfc(CRL1, "- You may choose to roll again after holding \n");
    printfc(CRL1, "- If you go over %d you bust\n", GOAL_NUM);
    printfc(CRL1, "- If both players hold the game is over\n");
    printfc(CRL1, "- The player with the highest score wins\n");
    printfc(CRL1, "- If both players have the same score it's a draw\n");
    printfc(CRL1, "- If both players bust it's a draw\n");
    input_to_continue();
    clear_screen("Help p3");
    print_subtitle(CRL3, "Page 3/4 - Cheating:"); 
    printfc(CRL1, "Cheat format:\n");
    printfc(CRL3, "[cheat_name] ");
    printfc(CRL5, "| [affects] ");
    printfc(CRL4, "| [properties] \n");
    printfc(CRL1, "-------\n");
    printfc(CRL3, "[cheat_name] - the name of the cheat\n");
    printfc(CRL5, "[affects] - who the cheat affects\n");
    printfc(CRL5, "plr=player opn=opponent bth=both\n");
    printfc(CRL4, "[properties] - what the cheat does\n");
    printfc(CRL5, "+N adds | -N subtracts | /N divides | *N multiplies | =N sets\n");
    printfc(CRL5, "swp swaps | inv inverts | rst resets\n");
    printfc(CRL1, "-------\n");
    printfc(CRL3, "[example ");
    printfc(CRL5, "| both ");
    printfc(CRL4, "| +1 | swp \n");
    printfc(CRL1, "This cheat would add 1 to both scores and then swap them\n");
    input_to_continue();
    clear_screen("Help p4");
    print_subtitle(CRL3, "Page 4/4 - Tips:"); 
    printfc(CRL1, "- Cheats can be used to manipulate scores\n");
    printfc(CRL1, "- Cheating does _NOT_ count as taking a turn\n");
    printfc(CRL1, "- Use cheats as much as possible\n");
    printfc(CRL1, "- Cheats are not scarce\n");
    printfc(CRL1, "- Cheats can be used to help or hinder\n");
    printfc(CRL1, "- Cheats can be used to manipulate the opponent\n");
    printfc(CRL1, "- Win +1 gold | Slam it +2 gold\n");
    printfc(CRL1, "- Lose -1 gold | Bust -2 gold \n");
    printfc(CRL1, "- 'inv' subtracts the current score from %d\n", GOAL_NUM);
    printfc(CRL1, "- 'swp' swaps the scores (always affects both)\n");
    printfc(CRL1, "- 'rst' sets the score to 0\n");
    input_to_continue();
}