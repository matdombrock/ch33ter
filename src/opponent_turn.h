//
// Opponent Turn
// The logic used to determine the opponent's actions during their turn.
//
void opponent_turn(struct Match *match) {
    if (match->opponent.trait_cheater) {
        if (rand() % 4 == 0) {
            printfc(CFG_CLR2, "%s cheats!!!\n", match->opponent.name);
            match->opponent_total = GOAL_NUM - 1;
        }
    }
    bool hold = false;
    // Hold if greater than caution
    if (match->opponent_total >= (GOAL_NUM - match->opponent.caution)) {
        hold = true;
    }
    // Aggressive overrides caution
    if (match->opponent.trait_aggressive && (match->opponent_total <= match->player_total)) { 
        hold = false;
    }
    // Clever rolls again if it cant bust
    if (match->opponent.trait_clever && ((GOAL_NUM - match->opponent_total) > match->opponent.die_sides)) {
        hold = false;
    }
    if (hold) {
        printfc(CFG_CLR5, "%s holds\n", match->opponent.name);
        match->opponent_held = true;
    }
    else { // Roll
        int roll = roll_die(match->opponent.die_sides);
        match->opponent_total += roll;
        match->opponent_held = false;
        printfc(CFG_CLR4, "%s rolls: %d / %d\n", match->opponent.name, roll, match->opponent.die_sides);   
    }
}