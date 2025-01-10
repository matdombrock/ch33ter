//
// State
//
struct State {
    int gold;
    int cheats[MAX_CHEATS];
    int cheats_cap;
    int scanner_lvl;
    int wins;
    int losses;
    int draws;
};
// Create a new state
struct State state_constructor() {
    struct State state;
    state.gold = STARTING_GOLD;
    state.cheats_cap = 4;
    state.wins = 0;
    state.losses = 0;
    state.draws = 0;
    state.scanner_lvl = 0;
    for (int i = 0; i < MAX_CHEATS; i++) {
        state.cheats[i] = -1;
    }
    return state;
}
// Attempt to gain a cheat and print a message
// Returns true if the cheat was gained
bool state_attempt_gain_cheat(struct State* state, struct Cheat cheats_list[], int cheat_list_index) {
    bool gained = false;
    for (int i = 0; i < state->cheats_cap; i++) {
        if (state->cheats[i] == -1) {
            gained = true;
            state->cheats[i] = cheat_list_index;
            return gained;
        }
    }
    if (gained) printfc(CLR1, "Gained Cheat: %s\n", cheats_list[cheat_list_index].name);
    else printfc(CLR2, "Attempted to gain %s\nbut there are no more cheat slots available\n", cheats_list[cheat_list_index].name);
    return gained;
}
// Use a cheat - returns the index of the cheat used or -1 if not found
// Does not actually handle the cheat logic
// Removes the cheat from the state
int state_use_cheat(struct State* state, int cheat_index) {
    if (cheat_index >= state->cheats_cap) return -1;
    int at = state->cheats[cheat_index];
    if (at == -1) return -1;
    state->cheats[cheat_index] = -1;
    return at;
}
// Count the number of cheats in the state
int state_count_cheats(struct State *state) {
    int count = 0;
    for (int i = 0; i < MAX_CHEATS; i++) {
        if (state->cheats[i] != -1) count++;
    }
    return count;
}
// Print the cheats in the state
void state_print_cheats(struct State *state, struct Cheat cheats_list[]) {
    for (int i = 0; i < state->cheats_cap; i++) {
        printfc(CLR1, "%d. ", i + 1);
        if (state->cheats[i] != -1) {
            cheat_print(&cheats_list[state->cheats[i]]);
        }
        else {
            printfc(CLR1, "---\n");
        }
    }
    printfc(CLR1, "\n");
}
// Simple prints ensure color
void state_print_gold(struct State *state) {
    printfc(CLR4, "Your Gold: %d\n", state->gold);
}
void state_print_scanner_lvl(struct State *state) {
    printfc(CLR3, "Scanner LVL: %d/%d\n", state->scanner_lvl, SCAN_LVL_MAX);
}
void state_print_cheats_cap(struct State *state) {
    printfc(CLR5, "Cheat Slots: %d/%d\n", state->cheats_cap, MAX_CHEATS);
}
void state_print_open_cheat_slots(struct State *state) {
    printfc(CLR5, "Open Cheat Slots: %d\n", state->cheats_cap - state_count_cheats(state));
}
// Print the player status 
void state_print_status(struct State *state, bool trunc) {
    printfc(CLR3, "W: %d", state->wins);
    printfc(CLR2, " L: %d", state->losses);
    printfc(CLR4, " D: %d", state->draws);
    printfc(CLR8, " T: %d\n", state->wins + state->losses + state->draws);
    state_print_gold(state);
    if (trunc) return;
    state_print_cheats_cap(state);
    state_print_open_cheat_slots(state);
    state_print_scanner_lvl(state);
}