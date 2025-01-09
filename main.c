#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h> // va_list, va_start, va_end
#include <ctype.h>  // toupper

#define MAX_CHEATS 8
#define GOAL_NUM 33
#define TERM_WIDTH 66
#define SCAN_LVL_MAX 4

// Config
#define USE_RAW_INPUT 1
#define ENABLE_COLORS 1
#define ENABLE_BELL 1

#define CMD_ROLL 'r'
#define CMD_HOLD 'w'
#define CMD_CHEAT_LIST 'e'
#define CMD_OPPONENT 'q'
#define CMD_STATUS 's'
#define CMD_QUIT 'c'
#define CMD_HELP 'h'
#define CMD_USE_CHEAT_1 '1'
#define CMD_USE_CHEAT_2 '2'
#define CMD_USE_CHEAT_3 '3'
#define CMD_USE_CHEAT_4 '4'
#define CMD_USE_CHEAT_5 '5'
#define CMD_USE_CHEAT_6 '6'
#define CMD_USE_CHEAT_7 '7'
#define CMD_USE_CHEAT_8 '8'

#define CLR1_CODE "\033[1;90m" // grey
#define CLR2_CODE "\033[1;91m" // red
#define CLR3_CODE "\033[1;94m" // blue
#define CLR4_CODE "\033[1;32m" // green
#define CLR5_CODE "\033[1;33m" // yellow
#define CLR6_CODE "\033[1;95m" // magenta
#define CLR7_CODE "\033[1;96m" // cyan
#define CLR8_CODE "\033[1;97m" // white

#define STARTING_GOLD 100

//
// Utils
//
// TODO: Color codes could be stored in an array
enum Color { CLR1, CLR2, CLR3, CLR4, CLR5, CLR6, CLR7, CLR8 };
// Begin printing in the given color
void clr_start(enum Color color) {
    if (!ENABLE_COLORS) return;
    switch (color) {
        case CLR1:
            printf(CLR1_CODE);
            break;
        case CLR2:
            printf(CLR2_CODE);
            break;
        case CLR3:
            printf(CLR3_CODE);
            break;
        case CLR4:
            printf(CLR4_CODE);
            break;
        case CLR5:
            printf(CLR5_CODE);
            break;
        case CLR6:
            printf(CLR6_CODE);
            break;
        case CLR7:
            printf(CLR7_CODE);
            break;
        case CLR8:
            printf(CLR8_CODE);
            break;
    }
}
// Stop printing in color
void clr_end() {
    if (!ENABLE_COLORS) return;
    printf("\033[0m");
}
// Print in color
// Example: printfc(CLR4, "Hello, %s!\n", "world");
void printfc(enum Color color, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    for (int i = 0; buffer[i]; i++) {
        buffer[i] = toupper(buffer[i]);
    }
    clr_start(color);
    printf("%s", buffer);
    clr_end();
}
// Print a divider
void print_div() {
    printfc(CLR4, "▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂  ▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂  ▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂\n");
}
// Print a title
void print_screen_title(char title[]) {
    if (ENABLE_BELL) printf("\a");
    printfc(CLR6, "█ %s ", title);
    for (int i = 0; i < TERM_WIDTH - strlen(title) - 2; i++) {
        printfc(CLR6, "█");
    }
    printfc(CLR1, "\n");
    print_div();
}
// Print a subtitle
void print_subtitle(enum Color color, char subtitle[]) {
    printfc(color, "███ %s █████████████████████\n", subtitle);
}
// Clear the screen and print the title
void clear_screen(char title[]) {
    // Clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    print_screen_title(title);
}
//
// Input
//
// Get a single character of input
char get_input() {
    char input;
    if (USE_RAW_INPUT) {
        printfc(CLR7, "██████████████▛ Awaiting Input ▜▛ ");
        system("stty raw");
        input = getchar();
        system("stty cooked");
        clear_screen("ch33ter");   
    }
    else {
        printfc(CLR7, "██████████████▛ Awaiting Input ▜▛ ");
        scanf("%c", &input);
        // clear the buffer
        while(getchar() != '\n');
        clear_screen("ch33ter");
    }
    return input;
}
// Press any key to continue
void to_continue() {
    // Wait for user input
    printfc(CLR6, "\n\n██████████████       Press any key to continue       ██████████████\n");
    system("stty raw");
    getchar();
    system("stty cooked");
    clear_screen("ch33ter");
}

//
// Opponent Names
//
// Get a random opponent name
void opponent_name_rand(char *name) {
    char opponent_names[][64] = {"archalis", "bertule", "chalistis", "dalth", "erdwin", "flen", "galdor", "haldor", "isandul", "jaldor", "kaldor", "lailer", "miike", "nilandor", "oldwald", "paldor", "quildor", "raldor", "saldor", "taldor", "uoldor", "vildor", "waldor", "xildor", "yooldor", "zandor"};
    strcpy(name, opponent_names[rand() % 26]);
}

//
// Cheat
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
struct Cheat cheat_constructor(char name[32]) {
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
#define GOAL_NUM_H (GOAL_NUM / 2)
#define CHEATS_AMT ((15 * GOAL_NUM) + (9 * GOAL_NUM_H))
// Initialize the cheats list with all possible cheats
void cheats_list_init(struct Cheat *cheats_list) {
    int off = 0;
    // Add
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "sh4rdx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].add = i + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "mov3rx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].add = i + 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "push3rx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].add = i + 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Sub
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "m3dx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].sub = i + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "d4gg3rx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].sub = i + 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "d1gg3rx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].sub = i + 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Mult
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "w1ndf4llx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].mult = i + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "b0mbx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].mult = i + 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "f1r3st0rmx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].mult = i + 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Div
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "f0rg3x%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].div = i + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "f41lx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].div = i + 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "4ng3lx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].div = i + 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Set
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "l04d3rx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].set = i + 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "thr0w3rx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].set = i + 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM; i++) {
        char name[32];
        sprintf(name, "g1v3rx%d", i);
        cheats_list[off] = cheat_constructor(name);
        cheats_list[off].set = i + 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Swap
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_constructor("5w4px");
        cheats_list[off].swap = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Invert
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_constructor("1nvmx");
        cheats_list[off].invert = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_constructor("1nvux");
        cheats_list[off].invert = 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_constructor("1nvu5x");
        cheats_list[off].invert = 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Reset
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_constructor("r5tmx");
        cheats_list[off].reset = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_constructor("r5tux");
        cheats_list[off].reset = 1;
        cheats_list[off].affects = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_constructor("r5tusx");
        cheats_list[off].reset = 1;
        cheats_list[off].affects = 2;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Match high
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_constructor("h1m3rx");
        cheats_list[off].match_high = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // Match low
    for (int i = 0; i < GOAL_NUM_H; i++) {
        cheats_list[off] = cheat_constructor("l0m3rx");
        cheats_list[off].match_low = 1;
        cheat_sync(&cheats_list[off]);
        off++;
    }
    // for (int i = 0; i < off; i++) {
    //     cheat_print(&cheats_list[i]);
    // }
    // exit(0);
}

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
//
// Match
//
struct Match {
    int player_total;
    int opponent_total;
    int opponent_caution;
    int turn;
    int die_sides;
    bool player_held;
    bool opponent_held;
    bool trait_aggressive;
    bool trait_clever;
    bool trait_cheater;
    bool trait_high_stakes;
    bool ended;
    char opponent_name[64];
};
// Print the score bar
void match_print_score_bar(int total) {
    int per = (int)((float)TERM_WIDTH / GOAL_NUM + 0.5f);
    for (int i = 0; i < GOAL_NUM; i++) {
        if (i < total) {
            for (int j = 0; j < per; j++) {
                printfc(total > GOAL_NUM ? CLR2 : CLR5, "█");
            }
        } else {
            for (int j = 0; j < per; j++) {
                printfc(CLR8, "▒");
            }
        }
    }
    printfc(CLR3, "|");
}
// Print the opponent info
void match_print_opponent(struct State *state, struct Match *match) {
    printfc(CLR6, "Opponent: %s\n", match->opponent_name);
    printfc(CLR5, "⚄⚀ Die sides: %d\n", match->die_sides);
    if (state->scanner_lvl == 0) {
        printfc(CLR5, "㊋ Aggressive: ¿¿¿\n");
        printfc(CLR5, "㈫ Caution: ¿¿¿ (holds at ¿¿¿) \n");
    }
    if (state->scanner_lvl == 1) {
        printfc(CLR5, "㊋ Aggressive: %s\n", match->trait_aggressive ? "✓" : "X");
        printfc(CLR5, "㈫ Caution: %d (holds at ¿¿¿) \n", match->opponent_caution);
    }
    if (state->scanner_lvl >= 1) {
        printfc(CLR5, "㊋ Aggressive: %s\n", match->trait_aggressive ? "✓" : "X");
        printfc(CLR5, "㈫ Caution: %d (holds at %d) \n", match->opponent_caution, GOAL_NUM - match->opponent_caution);
    }
    printfc(CLR3, "Scanned with: Scanner LVL%d\n", state->scanner_lvl);
}
// Print the match info
void match_print(struct Match *match) {
    print_div();
    printfc(CLR5, "player total: %d\n", match->player_total);
    match_print_score_bar(match->player_total);
    printf("\n");
    printfc(CLR7, "%s total: %d\n", match->opponent_name, match->opponent_total);
    match_print_score_bar(match->opponent_total);
    printf("\n");
    print_div();
}
// Start a match with a new opponent and reset the match state
//TODO: Does too much - shouldnt print
void match_start(struct State *state, struct Match *match) {
    match->player_total = 0;
    match->opponent_total = 0;
    match->opponent_caution = rand() % 11;
    match->turn = 0;
    match->die_sides = (rand() % (GOAL_NUM -3)) + 3;
    match->player_held = false;
    match->opponent_held = false;
    match->trait_aggressive = rand() % 4 == 0;
    match->trait_clever = rand() % 4 == 0;
    match->trait_cheater = rand() % 4 == 0;
    match->trait_high_stakes = rand() % 4 == 0;
    match->ended = false;
    strcpy(match->opponent_name, "OpponentX");
    opponent_name_rand(match->opponent_name);
    print_div();
    print_subtitle(CLR2, "Match Started");
    match_print_opponent(state, match);
    state_print_gold(state);
    print_div();
}
// End a match
// TODO: should not include initial subtitle
void match_end_screen(struct Match *match, struct State *state, struct Cheat cheats_list[], int won, char msg[]) { // won = 2 == draw
    print_subtitle(CLR2, "Match Ended");
    to_continue();
    // Update gold
    int gained = 0;
    if (won == 1) {
        gained += 1;
        if (match->player_total == GOAL_NUM) {
            gained += 1;
        }
    }
    if (won == 0) {
        gained -= 1;
        if (match->player_total > GOAL_NUM) {
            gained -= 2;
        }
    }
    state->gold += gained;
    // Update match record
    if (won == 0) state->losses++;
    if (won == 1) state->wins++;
    if (won == 2) state->draws++;
    // Draw
    enum Color result_colors[3] = {CLR2, CLR4, CLR5};
    enum Color result_color = result_colors[won];
    clear_screen("Match Summary");
    if (won == 1) {
        print_subtitle(result_color, "WIN!");
    }
    if (won == 0) {
        print_subtitle(result_color, "LOSE!");
    }
    if (won == 2) {
        print_subtitle(result_color, "DRAW!");
    }
    printfc(result_color, "%s\n", msg);
    match_print_opponent(state, match);
    match_print(match);
    if (gained == 0) printfc(CLR1, "// Gained no gold\n");
    if (gained > 0) printfc(CLR4, "++ Gained %d gold\n", gained);
    if (gained < 0) printfc(CLR2, "-- Lost %d gold\n", -gained);
    state_print_status(state, 1);
    to_continue();
    // Get new cheat
    if ( won == 1) {
        loot_box_screen(state, cheats_list);
    }
    match->ended = true;
}
// Check if the match has ended
void match_check(struct Match *match, struct State *state, struct Cheat cheats_list[]) {
    if (match->player_total == GOAL_NUM && match->opponent_total == GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 2, "Both slammed it!");
    }
    else if (match->player_total == GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 1, "Player slammed it!");
    }
    else if (match->opponent_total == GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 0, "Opponent slammed it!");
    }
    else if (match->player_total > GOAL_NUM && match->opponent_total > GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 2, "Both bust!");
    }
    else if (match->opponent_total > GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 1, "Opponent busts!");
    }
    else if (match->player_total > GOAL_NUM) {
        match_end_screen(match, state, cheats_list, 0, "Player busts!");
    }
    else if (match->player_held && match->opponent_held) {
        if (match->player_total == match->opponent_total) {
            match_end_screen(match, state, cheats_list, 2, "Even scores!");
        }
        else if (match->player_total > match->opponent_total) {
            match_end_screen(match, state, cheats_list, 1, "Player wins with a higher score!");
        } 
        else {
            match_end_screen(match, state, cheats_list, 0, "Opponent wins with a higher score!");
        }
    }
}

//
// Misc
//
// Return a random number between 1 and sides
int roll_die(int sides) {
    return rand() % sides + 1;
}
// Opponent logic
void opponent_turn(struct Match *match) {
    // Greater than caution and (not aggressive or greater than player)
    if (match->opponent_total >= (GOAL_NUM - match->opponent_caution) && (!match->trait_aggressive || match->opponent_total >= match->player_total)) {
        printfc(CLR5, "%s holds\n", match->opponent_name);
        match->opponent_held = true;
        return;
    }
    int roll = roll_die(match->die_sides);
    match->opponent_total += roll;
    match->opponent_held = false;
    printfc(CLR4, "%s rolls: %d / %d\n", match->opponent_name, roll, match->die_sides);
}
#define MAX_PRICE 33
// Purchase from the vendor
void vendor_purchase(struct State *state, struct Cheat cheats_list[], int *cheat_index, int *cheat_price) {
    clear_screen("Purchasing");
    printfc(CLR4, "You ask to purchase %s\n", cheats_list[cheat_index[0]].name);
    if (state_count_cheats(state) >= state->cheats_cap) {
        printfc(CLR2, "But you have no more cheat slots available!\n");
    }
    else if (state->gold >= cheat_price[0]) {
        state->gold -= cheat_price[0];
        state_attempt_gain_cheat(state, cheats_list, cheat_index[0]);
        cheat_index[0] = rand() % CHEATS_AMT;
        cheat_index[0] = rand() % MAX_PRICE + 1;
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
// Handle random encounters
void random_encounters(struct State *state, struct Cheat cheats_list[]) {
    if (rand() % 3 == 0) {
        print_subtitle(CLR3, "Encounter: lost loot box!");
        printfc(CLR1, "After the last match you found\na lost loot box in the dust!\n");
        to_continue();
        loot_box_screen(state, cheats_list);
    }
    if (rand() % 1 == 0) {
        print_subtitle(CLR3, "Encounter: hacker vendor!");
        printfc(CLR1, "After the last match you come across\na hacker who is willing to trade cheats for gold!\n");
        to_continue();
        int cheat_index[4];
        cheat_index[0] = rand() % CHEATS_AMT;
        cheat_index[1] = rand() % CHEATS_AMT;
        cheat_index[2] = rand() % CHEATS_AMT;
        cheat_index[3] = rand() % CHEATS_AMT;
        int cheat_price[4];
        cheat_price[0] = rand() % MAX_PRICE + 1;
        cheat_price[1] = rand() % MAX_PRICE + 1;
        cheat_price[2] = rand() % MAX_PRICE + 1;
        cheat_price[3] = rand() % MAX_PRICE + 1;
        bool in_shop = 1;
        while(in_shop) {
            clear_screen("Hacker Vendor");
            state_print_gold(state);
            state_print_open_cheat_slots(state);
            printfc(CLR1, "-------\n");
            printfc(CLR1, "Goods: \n");
            printfc(CLR1, "1. $%d - ", cheat_price[0]);
            cheat_print(&cheats_list[cheat_index[0]]);
            printfc(CLR1, "2. $%d - ", cheat_price[1]);
            cheat_print(&cheats_list[cheat_index[1]]);
            printfc(CLR1, "3. $%d - ", cheat_price[2]);
            cheat_print(&cheats_list[cheat_index[2]]);
            printfc(CLR1, "4. $%d - ", cheat_price[3]);
            cheat_print(&cheats_list[cheat_index[3]]);
            printfc(CLR1, "5. $10 - loot box\n");
            printfc(CLR1, "6. $10 - Upgrade scanner\n");
            printfc(CLR1, "7. $15 - Upgrade cheat slots\n");
            printfc(CLR1, "8. $1 - Coin flip\n");
            printfc(CLR1, "9. $10 - Coin flip\n");
            printfc(CLR1, "0. Sell Cheats\n");
            printfc(CLR2, "\nPress %c to exit\n", CMD_QUIT);
            char input = get_input();
            printfc(CLR1, "%c\n", input);
            switch(input) {
                case CMD_QUIT:
                    in_shop = 0;
                    break;
                case '1':
                    vendor_purchase(state, cheats_list, &cheat_index[0], &cheat_price[0]);
                    break;
                case '2':
                    vendor_purchase(state, cheats_list, &cheat_index[1], &cheat_price[1]);
                    break;
                case '3':
                    vendor_purchase(state, cheats_list, &cheat_index[2], &cheat_price[2]);
                    break;
                case '4':
                    vendor_purchase(state, cheats_list, &cheat_index[3], &cheat_price[3]);
                    break;
                case '5':
                    clear_screen("Purchase");
                    printfc(CLR4, "You ask to purchase a loot box\n");
                    if (state->gold >= 10) {
                        state->gold -= 10;
                        loot_box_screen(state, cheats_list);
                    }
                    else {
                        printfc(CLR2, "But you dont have enough gold! (missing: %d)\n", 2 - state->gold);
                        print_div();
                        state_print_gold(state);
                        to_continue();
                    }
                    break;
                case '6':
                    clear_screen("Scanner Upgrade");
                    printfc(CLR4, "You ask to upgrade your scanner\n");
                    if (state->scanner_lvl >= SCAN_LVL_MAX) {
                        printfc(CLR2, "But your scanner is already at max level!\n");
                    }
                    else if (state->gold >= 10) {
                        state->gold -= 10;
                        state->scanner_lvl++;
                        printfc(CLR8, "Scanner upgraded!\n");
                    }
                    else {
                        printfc(CLR2, "But you dont have enough gold! (missing: %d)\n", 10 - state->gold);
                    }
                    state_print_scanner_lvl(state);
                    state_print_gold(state);
                    to_continue();
                    break;
                case '7':
                    clear_screen("Cheat Slot Upgrade");
                    printfc(CLR4, "You ask to upgrade your cheat slots\n");
                    if (state->cheats_cap >= MAX_CHEATS) {
                        printfc(CLR2, "But your cheat slots are already at max level!\n");
                    }
                    else if (state->gold >= 15) {
                        state->gold -= 15;
                        state->cheats_cap++;
                        printfc(CLR8, "Cheat slots upgraded!\n");
                    }
                    else {
                        printfc(CLR2, "But you dont have enough gold! (missing: %d)\n", 15 - state->gold);
                    }
                    state_print_cheats_cap(state);
                    state_print_gold(state);
                    to_continue();
                    break;
                case '8':
                    coin_flip(1, state);
                    break;
                case '9':
                    coin_flip(10, state);
                    break;
                case '0':
                    clear_screen("Selling");
                    printfc(CLR4, "You ask to sell cheats\n");
                    state_print_cheats(state, cheats_list);
                    printfc(CLR4, "Which cheat would you like to sell?\n");
                    printfc(CLR2, "\nPress %c to exit\n", CMD_QUIT);
                    char slotc = get_input();
                    if (slotc == CMD_QUIT) break;
                    clear_screen("Selling");
                    int slot = slotc - '0' - 1;// offset by ascii
                    int price = rand() % (MAX_PRICE / 3) + 1;
                    if (slot >= 0 && slot < state->cheats_cap) {
                        if (state->cheats[slot] != -1) {
                            printfc(CLR4, "You sold: ");
                            cheat_print(&cheats_list[state->cheats[slot]]);
                            printfc(CLR4, "For %d gold!\n", price);
                            state->gold += price;
                            state->cheats[slot] = -1;
                        }
                        else {
                            printfc(CLR2, "But there is no cheat in that slot!\n");
                        }
                    }
                    else {
                        printfc(CLR2, "Invalid input\n");
                    }
                    state_print_gold(state);
                    to_continue();
                    break;
                default:
                    clear_screen("Invalid Input");
                    printfc(CLR2, "Input not recognized\n");
                    printfc(CLR3, "\nPress %c at vendor screen to quit\n", CMD_QUIT);
                    to_continue();
                    break;
            }
        }
        clear_screen("Exit Vendor");
        printfc(CLR4, "You exit the vendor\n");
        state_print_status(state, 1);
        state_print_cheats(state, cheats_list);
        to_continue();
    }
    if (rand() % 5 == 0) {
        print_subtitle(CLR3, "Encounter: patron!");
        printfc(CLR1, "After the last match you come across\na patron who likes the way you play!\n");
        int gives = rand() % 5 + 1;
        printfc(CLR1, "They give you %d gold!\n", gives);
        state->gold += gives;
        to_continue();
    }
    if (rand() % 5 == 0) {
        print_subtitle(CLR3, "Encounter: patron hacker!");
        printfc(CLR1, "After the last match you come across\na patron hacker who likes the way you play!\n");
        printfc(CLR1, "They give you a loot box!\n");
        to_continue();
        loot_box_screen(state, cheats_list);
    }
    if (rand() % 5 == 0) {
        print_subtitle(CLR2, "Encounter: thief!");
        printfc(CLR1, "After the last match you are assaulted by\na thief who looks mean!\n");
        int takes = rand() % 5 + 1;
        if (takes > state->gold) {
            takes = state->gold;
        }
        printfc(CLR1, "They take %d gold from you!\n", takes);
        state->gold -= takes;
        if (state->gold < 0) {
            printfc(CLR1, "They feel a little bad about taking your last gold.\n");
            printfc(CLR1, "They give you one piece back!\n");
            state->gold = 1;
        }
        to_continue();
    }
    if (rand() % 5 == 0) {
        print_subtitle(CLR2, "Encounter: hacking thief!");
        printfc(CLR1, "After the last match you are assaulted by\na hacking thief who looks kinda wimpy!\n");
        printfc(CLR1, "But they have some 'hitek' hacking tools!\n");
        int slot = rand() % state->cheats_cap;
        printfc(CLR1, "They try to take the cheat in slot %d", slot + 1);
        if (state->cheats[slot] != -1) {
            printfc(CLR1, "\nand they get it!\n");
            cheat_print(&cheats_list[state->cheats[slot]]);
            state->cheats[slot] = -1;
        }
        else {
            printfc(CLR1, "\nbut you have no cheats in that slot!\n");
        }
        to_continue();
    }
}
//
// Misc Screens
//
void welcome_screen() {
    clear_screen("WELCOME");
    printfc(CLR2, "       .__    ________ ________  __    \n");
    printfc(CLR3, "  ____ |  |__ \\_____  \\\\_____  \\/  |_  ___________\n");
    printfc(CLR4, "_/ ___\\|  |  \\  _(__  <  _(__  <   __\\/ __ \\_  __ \\\n");
    printfc(CLR5, "\\  \\___|   Y  \\/       \\/       \\  | \\  ___/|  | \\/\n");
    printfc(CLR6, " \\___  >___|  /______  /______  /__|  \\___  >__|   \n");
    printfc(CLR7, "     \\/     \\/       \\/       \\/          \\/       \n");

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
//
// Commands
//
void cmd_roll(struct Match *match) {
    clear_screen("Roll");
    int roll = roll_die(match->die_sides);
    match->player_total += roll;
    match->turn++;
    printfc(CLR4, "player rolls: %d / %d\n", roll, match->die_sides);
    opponent_turn(match);
    match->player_held = false;
}
void cmd_hold(struct Match *match) {
    clear_screen("Hold");
    match->player_held = true;
    printfc(CLR5, "player holds\n");
    opponent_turn(match);
    match->player_held = true;
}
void cmd_cheat_list(struct State *state, struct Cheat cheats_list[]) {
    clear_screen("Cheat Slots");
    state_print_cheats(state, cheats_list);
}

void cmd_use_cheat(struct State *state, struct Match *match, int cheat_index, struct Cheat cheats_list[]) {
    clear_screen("Use Cheat");
    printfc(CLR1, "Using cheat \n");
    int used_index = state_use_cheat(state, cheat_index);
    if (used_index == -1) {
        printfc(CLR1, "Invalid cheat\n");
        return;
    }
    struct Cheat cheat = cheats_list[used_index];
    cheat_print(&cheat);
    bool affects_player = cheat.affects == 0 || cheat.affects == 2;
    bool affects_opponent = cheat.affects == 1 || cheat.affects == 2;
    if (cheat.add != 0) {
        printfc(CLR1, "Adding %d\n", cheat.add);
        if (affects_player) match->player_total += cheat.add;
        if (affects_opponent) match->opponent_total += cheat.add;
    }
    if (cheat.sub != 0) {
        printfc(CLR1, "Subtracting %d\n", cheat.sub);
        if (affects_player) match->player_total -= cheat.sub;
        if (affects_opponent) match->opponent_total -= cheat.sub;
    }
    if (cheat.div != 0) {
        printfc(CLR1, "Dividing by %d\n", cheat.div);
        if (affects_player) match->player_total /= cheat.div;
        if (affects_opponent) match->opponent_total /= cheat.div;
    }
    if (cheat.mult != 0) {
        printfc(CLR1, "Multiplying by %d\n", cheat.mult);
        if (affects_player) match->player_total *= cheat.mult;
        if (affects_opponent) match->opponent_total *= cheat.mult;
    }
    if (cheat.set != 0) {
        printfc(CLR1, "Setting to %d\n", cheat.set);
        if (affects_player) match->player_total = cheat.set;
        if (affects_opponent) match->opponent_total = cheat.set;
    }
    if (cheat.swap) {
        printfc(CLR1, "Swapping scores\n");
        int temp = match->player_total;
        match->player_total = match->opponent_total;
        match->opponent_total = temp;
    }
    if (cheat.invert) {
        printfc(CLR1, "Inverting scores\n");
        if (affects_player) match->player_total = GOAL_NUM - match->player_total;
        if (affects_opponent) match->opponent_total = GOAL_NUM - match->opponent_total;
    }
    if (cheat.reset) {
        printfc(CLR1, "Resetting score\n");
        if (affects_player) match->player_total = 0;
        if (affects_opponent) match->opponent_total = 0;
    }
    if (cheat.match_high) {
        printfc(CLR1, "Matching high score\n");
        if (match->player_total > match->opponent_total) {
            match->opponent_total = match->player_total;
        } else {
            match->player_total = match->opponent_total;
        }
    }
    if (cheat.match_low) {
        printfc(CLR1, "Matching low score\n");
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
    to_continue();
}

void cmd_status(struct State *state) {
    clear_screen("Status");
    state_print_status(state, 0);
    to_continue();
}

void cmd_help() {
    clear_screen("Help p1");
    print_subtitle(CLR3, "Page 1/4 - Commands:");
    printfc(CLR1, "%c - roll\n", CMD_ROLL);
    printfc(CLR1, "%c - hold\n", CMD_HOLD);
    printfc(CLR1, "%c - inspect cheat slots\n", CMD_CHEAT_LIST);
    printfc(CLR1, "%c - inspect opponent\n", CMD_OPPONENT);
    printfc(CLR1, "%c - inspect self\n", CMD_STATUS);
    printfc(CLR1, "%c - use cheat slot 1 | ", CMD_USE_CHEAT_1);
    printfc(CLR1, "%c - use cheat slot 2\n", CMD_USE_CHEAT_2);
    printfc(CLR1, "%c - use cheat slot 3 | ", CMD_USE_CHEAT_3);
    printfc(CLR1, "%c - use cheat slot 4\n", CMD_USE_CHEAT_4);
    printfc(CLR1, "%c - use cheat slot 5 | ", CMD_USE_CHEAT_5);
    printfc(CLR1, "%c - use cheat slot 6\n", CMD_USE_CHEAT_6);
    printfc(CLR1, "%c - use cheat slot 7 | ", CMD_USE_CHEAT_7);
    printfc(CLR1, "%c - use cheat slot 8\n", CMD_USE_CHEAT_8);
    printfc(CLR1, "%c - quit\n", CMD_QUIT);
    printfc(CLR1, "%c - help\n", CMD_HELP);
    to_continue();
    clear_screen("Help p2");
    print_subtitle(CLR3, "Page 2/4 - Rules:");
    printfc(CLR1, "- The goal is to approach %d without exceeding it\n", GOAL_NUM);
    printfc(CLR1, "- Each turn you may roll or hold\n");
    printfc(CLR1, "- Rolling adds to your total\n");
    printfc(CLR1, "- Holding passes your turn.\n");
    printfc(CLR1, "- You may choose to roll again after holding");
    printfc(CLR1, "- If you go over %d you bust\n", GOAL_NUM);
    printfc(CLR1, "- If both players hold the game is over\n");
    printfc(CLR1, "- The player with the highest score wins\n");
    printfc(CLR1, "- If both players have the same score it's a draw\n");
    printfc(CLR1, "- If both players bust it's a draw\n");
    to_continue();
    clear_screen("Help p3");
    print_subtitle(CLR3, "Page 3/4 - Cheating:"); 
    printfc(CLR1, "Cheat format:\n");
    printfc(CLR3, "[cheat_name] ");
    printfc(CLR5, "| [affects] ");
    printfc(CLR4, "| [properties] \n");
    printfc(CLR1, "-------\n");
    printfc(CLR3, "[cheat_name] - the name of the cheat\n");
    printfc(CLR5, "[affects] - who the cheat affects\n");
    printfc(CLR5, "plr=player opn=opponent bth=both\n");
    printfc(CLR4, "[properties] - what the cheat does\n");
    printfc(CLR5, "+N adds | -N subtracts | /N divides | *N multiplies | =N sets\n");
    printfc(CLR5, "swp swaps | inv inverts | rst resets\n");
    printfc(CLR1, "-------\n");
    printfc(CLR3, "[example ");
    printfc(CLR5, "| both ");
    printfc(CLR4, "| +1 | swp \n");
    printfc(CLR1, "This cheat would add 1 to both scores and then swap them\n");
    to_continue();
    clear_screen("Help p4");
    print_subtitle(CLR3, "Page 4/4 - Tips:"); 
    printfc(CLR1, "- Cheats can be used to manipulate scores\n");
    printfc(CLR1, "- Cheating does _NOT_ count as taking a turn\n");
    printfc(CLR1, "- Use cheats as much as possible\n");
    printfc(CLR1, "- Cheats are not scarce\n");
    printfc(CLR1, "- Cheats can be used to help or hinder\n");
    printfc(CLR1, "- Cheats can be used to manipulate the opponent\n");
    printfc(CLR1, "- Win +1 gold | Slam it +2 gold\n");
    printfc(CLR1, "- Lose -1 gold | Bust -2 gold \n");
    printfc(CLR1, "- 'inv' subtracts the current score from %d\n", GOAL_NUM);
    printfc(CLR1, "- 'swp' swaps the scores (always affects both)\n");
    printfc(CLR1, "- 'rst' sets the score to 0\n");
    to_continue();
}

//
// Main
//
int main() {
    // Setup RNG
    int seed = time(NULL);
    srand(seed);
    // Setup basic game state
    struct State state = state_constructor();
    // Welcome
    welcome_screen();
    // Setup cheats
    struct Cheat cheats_list[1024];
    cheats_list_init(cheats_list);
    // Gain some cheats
    loot_box_screen(&state, cheats_list);
    loot_box_screen(&state, cheats_list);
    loot_box_screen(&state, cheats_list);
    // Intro
    intro_screen();
    // Start first match
    clear_screen("ch33ter");
    struct Match match;
    match_start(&state, &match);
    int run = 1;
    while(run) {
        print_div();
        char input = get_input();
        switch (input) {
            case CMD_USE_CHEAT_1:
                cmd_use_cheat(&state, &match, 0, cheats_list);
                break;
            case CMD_USE_CHEAT_2:
                cmd_use_cheat(&state, &match, 1, cheats_list);
                break;
            case CMD_USE_CHEAT_3:
                cmd_use_cheat(&state, &match, 2, cheats_list);
                break;
            case CMD_USE_CHEAT_4: 
                cmd_use_cheat(&state, &match, 3, cheats_list);
                break;
            case CMD_USE_CHEAT_5:
                cmd_use_cheat(&state, &match, 4, cheats_list);
                break;
            case CMD_USE_CHEAT_6:
                cmd_use_cheat(&state, &match, 5, cheats_list);
                break;
            case CMD_USE_CHEAT_7:
                cmd_use_cheat(&state, &match, 6, cheats_list);
                break;
            case CMD_USE_CHEAT_8:
                cmd_use_cheat(&state, &match, 7, cheats_list);
                break;
            case CMD_ROLL:
                cmd_roll(&match);
                break;
            case CMD_HOLD:
                cmd_hold(&match);
                break;
            case CMD_CHEAT_LIST:
                cmd_cheat_list(&state, cheats_list);
                break;
            case CMD_OPPONENT:
                cmd_opponent(&state, &match);
                break;
            case CMD_STATUS:
                cmd_status(&state);
                break;
            case CMD_HELP:
                cmd_help();
                break;
            case CMD_QUIT:
                run = 0;
                break;
            default:
                printfc(CLR2, "Invalid input\n");
                printfc(CLR3, "Press %c for help\n", CMD_HELP);
        }
        // Show match info
        match_print(&match);
        state_print_gold(&state);
        // Check for match end
        match_check(&match, &state, cheats_list);
        if (state.gold < 0) {
            game_over_screen(); 
            run = 0;
            break; // end game
        }
        if (match.ended) {
            random_encounters(&state, cheats_list);
            match_start(&state, &match);
        }
    }
    printfc(CLR1, "goodbye\n");
    return 0;
}