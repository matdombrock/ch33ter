//
// State
// Structs and functions dealing with "state"
// This is the main game state which persists across matches
//
struct State {
    int gold;
    int cheats[MAX_CHEAT_SLOTS];
    int cheat_slots;
    int scanner_lvl;
    int wins;
    int losses;
    int draws;
    int lvl;
    char username[1024];
    char password[1024];
};
// Create a new state
struct State state_new() {
    struct State state;
    state.gold = STARTING_GOLD;
    state.cheat_slots = STARTING_CHEAT_SLOTS;
    state.scanner_lvl = STARTING_SCANNER_LVL;
    state.wins = 0;
    state.losses = 0;
    state.draws = 0;
    state.lvl = 1;
    for (int i = 0; i < MAX_CHEAT_SLOTS; i++) {
        state.cheats[i] = -1;
    }
    return state;
}
// Attempt to gain a cheat and print a message
// Returns true if the cheat was gained
bool state_attempt_gain_cheat(struct State* state, struct Cheat cheats_list[], int cheat_list_index) {
    bool gained = false;
    for (int i = 0; i < state->cheat_slots; i++) {
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
    if (cheat_index >= state->cheat_slots) return -1;
    int at = state->cheats[cheat_index];
    if (at == -1) return -1;
    state->cheats[cheat_index] = -1;
    return at;
}
// Count the number of cheats in the state
int state_count_cheats(struct State *state) {
    int count = 0;
    for (int i = 0; i < MAX_CHEAT_SLOTS; i++) {
        if (state->cheats[i] != -1) count++;
    }
    return count;
}
// Print the cheats in the state
void state_print_cheats(struct State *state, struct Cheat cheats_list[]) {
    for (int i = 0; i < state->cheat_slots; i++) {
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
    printfc(CLR4, "Your Gold: $%d\n", state->gold);
}
void state_print_scanner_lvl(struct State *state) {
    printfc(CLR3, "Scanner LVL: %d/%d\n", state->scanner_lvl, SCAN_LVL_MAX);
}
void state_print_cheat_slots(struct State *state) {
    printfc(CLR5, "Cheat Slots: %d/%d\n", state->cheat_slots, MAX_CHEAT_SLOTS);
}
void state_print_open_cheat_slots(struct State *state) {
    printfc(CLR5, "Open Cheat Slots: %d\n", state->cheat_slots - state_count_cheats(state));
}
void state_print_lvl(struct State *state) {
    printfc(CLR6, "Level: %d\n", state->lvl);
}
// Print the player status 
void state_print_status(struct State *state, bool trunc) {
    printfc(CLR3, "W: %d", state->wins);
    printfc(CLR2, " L: %d", state->losses);
    printfc(CLR4, " D: %d", state->draws);
    printfc(CLR8, " T: %d\n", state->wins + state->losses + state->draws);
    state_print_gold(state);
    if (trunc) return;
    state_print_lvl(state);
    state_print_cheat_slots(state);
    state_print_open_cheat_slots(state);
    state_print_scanner_lvl(state);
}