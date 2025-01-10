//
// Loot box
//
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
    to_continue();
}