//
// Cheat
// Structs and functions dealing with "cheats"
//
struct Cheat {
    char name[32];
    int affects; // 0 = player, 1 = opponent, 2 = both
    int add;
    int sub;
    int div;
    int mult;
    int set;
    bool swap;
    bool invert;
    bool reset;
    bool match_high;
    bool match_low;
};
// Create a new cheat
struct Cheat cheat_new(char name[]) {
    struct Cheat cheat;
    strcpy(cheat.name, name);
    cheat.affects = 0;
    cheat.add = 0;
    cheat.sub = 0;
    cheat.div = 0;
    cheat.mult = 0;
    cheat.set = 0;
    cheat.swap = 0;
    cheat.invert = 0;
    cheat.reset = 0;
    cheat.match_high = 0;
    cheat.match_low = 0;
    return cheat;
}
// Updates props according to other set props
void cheat_sync(struct Cheat *cheat) {
    if (cheat->match_high 
        || cheat->match_low 
        || cheat->swap) 
    { cheat->affects = 2; }
}
// Print a cheat
void cheat_print(struct Cheat *cheat) {
    printfc(CLR3, "%s ", cheat->name);
    if (cheat->affects == 0) printfc(CLR5, "| plr ");
    if (cheat->affects == 1) printfc(CLR5, "| opn ");
    if (cheat->affects == 2) printfc(CLR5, "| bth ");
    if (cheat->add != 0) printfc(CLR4, "| +%d ", cheat->add);
    if (cheat->sub != 0) printfc(CLR4, "| -%d ", cheat->sub);
    if (cheat->div != 0) printfc(CLR4, "| /%d ", cheat->div);
    if (cheat->mult != 0) printfc(CLR4, "| *%d ", cheat->mult);
    if (cheat->set != 0) printfc(CLR4, "| =%d ", cheat->set);
    if (cheat->swap) printfc(CLR4, "| swp ");
    if (cheat->invert) printfc(CLR4, "| inv ");
    if (cheat->reset) printfc(CLR4, "| rst");
    if (cheat->match_high) printfc(CLR4, "| =H ");
    if (cheat->match_low) printfc(CLR4, "| =L ");
    printfc(CLR1, "\n");
    clr_end();
}
//
// Cheats list
//
// Initialize the cheats list with all possible cheats
void cheats_list_init(struct Cheat *cheats_list) {
    int off = 0;
    // Add
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "sh4rdx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].add = i + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "mov3rx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].add = i + 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "push3rx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].add = i + 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Sub
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "m3dx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].sub = i + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "d4gg3rx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].sub = i + 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "d1gg3rx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].sub = i + 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Mult
    for (int i = 0; i < GOAL_NUM_H; i++) {
        char name[32];
        sprintf(name, "w1ndf4llx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].mult = i + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        char name[32];
        sprintf(name, "b0mbx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].mult = i + 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        char name[32];
        sprintf(name, "f1r3st0rmx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].mult = i + 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Div
    for (int i = 0; i < GOAL_NUM_H; i++) {
        char name[32];
        sprintf(name, "f0rg3x%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].div = i + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        char name[32];
        sprintf(name, "f41lx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].div = i + 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        char name[32];
        sprintf(name, "4ng3lx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].div = i + 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Set
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "l04d3rx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].set = i + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "thr0w3rx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].set = i + 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "g1v3rx%d", i);
        cheats_list[off] = cheat_new(name);
        cheats_list[off].set = i + 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Swap
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("5w4px");
        cheats_list[off].swap = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Invert
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("1nvmx");
        cheats_list[off].invert = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("1nvux");
        cheats_list[off].invert = 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("1nvu5x");
        cheats_list[off].invert = 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Reset
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("r5tmx");
        cheats_list[off].reset = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("r5tux");
        cheats_list[off].reset = 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("r5tusx");
        cheats_list[off].reset = 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Match high
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("h1m3rx");
        cheats_list[off].match_high = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Match low
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("l0m3rx");
        cheats_list[off].match_low = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Winners
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("w1nx");
        cheats_list[off].set = GOAL_NUM - 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Slammers
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("s14mrx");
        cheats_list[off].set = GOAL_NUM;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Busters
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_new("w1nx");
        cheats_list[off].affects = 1;
        cheats_list[off].set = GOAL_NUM + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    if (DEBUG_CHEATS) {
        for (int i = 0; i < off; i++) {
            cheat_print(&cheats_list[i]);
        }
        printfc(CLR1, "Cheat Count: %d\n", off);
        exit(0);
    }
}