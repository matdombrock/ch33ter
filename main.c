#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h> // va_list, va_start, va_end
#include <ctype.h>  // toupper

#define DISABLE_COLORS 0

#define MAX_CHEATS 8

#define CMD_ROLL 'q'
#define CMD_HOLD 'w'
#define CMD_CHEAT_LIST 'e'
#define CMD_OPPONENT 'r'
#define CMD_QUIT 'x'
#define CMD_HELP 'h'
#define CMD_USE_CHEAT_1 '1'
#define CMD_USE_CHEAT_2 '2'
#define CMD_USE_CHEAT_3 '3'
#define CMD_USE_CHEAT_4 '4'
#define CMD_USE_CHEAT_5 '5'
#define CMD_USE_CHEAT_6 '6'
#define CMD_USE_CHEAT_7 '7'
#define CMD_USE_CHEAT_8 '8'

//
// Utils
//
enum Color { // TODO: use a color scheme of 8 colors instead of so many - can add bold
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    LIGHTRED,
    LIGHTGREEN,
    LIGHTBLUE,
    LIGHTMAGENTA,
    LIGHTCYAN,
    LIGHTYELLOW,
    GREY
};

void clr_start(enum Color color) {
    if (DISABLE_COLORS) return;
    switch (color) {
        case RED:
            printf("\033[0;31m");
            break;
        case GREEN:
            printf("\033[0;32m");
            break;
        case YELLOW:
            printf("\033[0;33m");
            break;
        case BLUE:
            printf("\033[0;34m");
            break;
        case MAGENTA:
            printf("\033[0;35m");
            break;
        case CYAN:
            printf("\033[0;36m");
            break;
        case WHITE:
            // nothing
            break;
        case LIGHTRED:
            printf("\033[1;31m");
            break;
        case LIGHTGREEN:
            printf("\033[1;32m");
            break;
        case LIGHTBLUE:
            printf("\033[1;34m");
            break;
        case LIGHTMAGENTA:
            printf("\033[1;35m");
            break;
        case LIGHTCYAN:
            printf("\033[1;36m");
            break;
        case LIGHTYELLOW:
            printf("\033[1;33m");
            break;
        case GREY:
            // printf("\033[0;37m"); // darker grey
            printf("\033[1;30m");
            break;
        default:
            printf("");
            break;
    }
}
void clr_end() {
    if (DISABLE_COLORS) return;
    printf("\033[0m");
}
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
void print_div() {
    printfc(GREEN, "▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂\n");
}
void print_screen_title(char title[64]) {
    printfc(GREEN, "█%s", title);
    for (int i = 0; i < 64 - strlen(title); i++) {
        printfc(GREEN, "█");
    }
    printfc(WHITE, "\n\n");
}
void clear_screen(char title[64]) {
    // Clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    print_screen_title(title);
}
void to_continue() {
    // Wait for user input
    printfc(RED, "\n\n-- Enter 'k' to continue --\n");
    getchar();
    clear_screen("ch33ter");
    // clear the buffer
    while(getchar() != '\n');
}

//
// Opponent Names
//
void opponent_name_rand(char *name) {
    char opponent_names[][64] = {
        "archalis",
        "bertule",
        "chalistis",
        "dalth",
        "erdwin",
        "flen",
        "galdor",
        "haldor",
        "isandul",
        "jaldor",
        "kaldor",
        "lailer",
        "miike",
        "nilandor",
        "oldwald",
        "paldor"
    };
    // sprintfc(WHITE, name, "%s.%s", opponent_names[rand() % 16], opponent_names[rand() % 16]);
    strcpy(name, opponent_names[rand() % 16]);
}
//
// State
//
struct State {
    int gold;
    int cheats[MAX_CHEATS];
    int cheats_cap;
};
struct State state_new() {
    struct State state;
    state.gold = 0;
    state.cheats_cap = 2;
    for (int i = 0; i < MAX_CHEATS; i++) {
        state.cheats[i] = -1;
    }
    return state;
}
bool state_gain_cheat(struct State* state, int cheat_list_index) {
    bool gained = false;
    for (int i = 0; i < state->cheats_cap; i++) {
        if (state->cheats[i] == -1) {
            gained = true;
            state->cheats[i] = cheat_list_index;
            return gained;
        }
    }
    return gained;
}
int state_use_cheat(struct State* state, int cheat_index) {
    if (cheat_index >= state->cheats_cap) return -1;
    int at = state->cheats[cheat_index];
    if (at == -1) return -1;
    state->cheats[cheat_index] = -1;
    return at;
}

//
// Cheat
//
struct Cheat {
    char name[32];
    int add;
    int sub;
    int div;
    int mult;
    int set;
    bool reverse;
    bool invert;
    bool reset_both;
    bool reset_player;
    bool reset_opponent;
    bool match_high;
    bool match_low;
};
struct Cheat cheat_new(char name[32]) {
    struct Cheat cheat;
    strcpy(cheat.name, name);
    cheat.add = 0;
    cheat.sub = 0;
    cheat.div = 0;
    cheat.mult = 0;
    cheat.set = 0;
    cheat.reverse = 0;
    cheat.invert = 0;
    cheat.reset_both = 0;
    cheat.reset_player = 0;
    cheat.reset_opponent = 0;
    cheat.match_high = 0;
    cheat.match_low = 0;
    return cheat;
}
void cheat_print(struct Cheat *cheat) {
    printfc(BLUE, "%s ", cheat->name);
    if (cheat->add != 0) printfc(GREEN, "adds %d, ", cheat->add);
    if (cheat->sub != 0) printfc(GREEN, "subtracts %d, ", cheat->sub);
    if (cheat->div != 0) printfc(GREEN, "divides by %d, ", cheat->div);
    if (cheat->mult != 0) printfc(GREEN, "multiplies by %d, ", cheat->mult);
    if (cheat->set != 0) printfc(GREEN, "sets to %d, ", cheat->set);
    if (cheat->reverse) printfc(GREEN, "reverses scores, ");
    if (cheat->invert) printfc(GREEN, "inverts scores, ");
    if (cheat->reset_both) printfc(GREEN, "resets both scores, ");
    if (cheat->reset_player) printfc(GREEN, "resets player score, ");
    if (cheat->reset_opponent) printfc(GREEN, "resets opponent score, ");
    if (cheat->match_high) printfc(GREEN, "matches high score, ");
    if (cheat->match_low) printfc(GREEN, "matches low score, ");
    printfc(WHITE, "\n");
    clr_end();
}
//
// Cheats list
//
#define CHEATS_AMT 3
void cheats_list_init(struct Cheat *cheats_list) {
    cheats_list[0] = cheat_new("c1");
    cheats_list[0].add = 1; 
    cheats_list[1] = cheat_new("c2");
    cheats_list[1].add = 2;
    cheats_list[2] = cheat_new("c10");
    cheats_list[2].add = 10;
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
    bool opponent_aggressive;
    char opponent_name[64];
};
void match_print(struct Match *match) {
    print_div();
    printfc(YELLOW, "player total: %d\n", match->player_total);
    for (int i = 0; i < 21; i++) {
        if (i < match->player_total) {
            printfc(match->player_total > 21 ? RED : GREEN, "█");
        } else {
            printfc(GREY, "▒");
        }
    }
    printf("\n");
    printfc(MAGENTA, "%s total: %d\n", match->opponent_name, match->opponent_total);
    for (int i = 0; i < 21; i++) {
        if (i < match->opponent_total) {
            printfc(match->opponent_total > 21 ? RED : GREEN, "█");
        } else {
            printfc(GREY, "▒");
        }
    }
    printf("\n");
    print_div();
}
void match_print_opponent(struct Match *match) {
    printfc(LIGHTYELLOW, "Opponent: %s\n", match->opponent_name);
    printfc(YELLOW, "⚄⚀ Die sides: %d\n", match->die_sides);
    printfc(YELLOW, "㈫ Caution: %d (holds at %d) \n", match->opponent_caution, 21 - match->opponent_caution);
    printfc(YELLOW, "㊋ Aggressive: %s\n", match->opponent_aggressive ? "yes" : "no");
}
void match_start(struct Match *match) {
    match->player_total = 0;
    match->opponent_total = 0;
    match->opponent_caution = rand() % 11;
    match->turn = 0;
    match->die_sides = rand() % 17 + 3;
    match->player_held = false;
    match->opponent_held = false;
    match->opponent_aggressive = rand() % 2;
    strcpy(match->opponent_name, "OpponentX");
    opponent_name_rand(match->opponent_name);
    print_div();
    printfc(RED, "--- Match started ---\n");
    match_print_opponent(match);
    print_div();
}
struct Match match_new() {
    struct Match match;
    match_start(&match);
    return match;
}
void match_end(struct Match *match, struct State *state, struct Cheat cheats_list[], int won, char msg[64]) { // won = 2 == draw
    printfc(GREEN, "Match ended\n");
    to_continue();
    if (won == 1) {
        state->gold += 1;
    }
    if (won == 0) {
        state->gold -= 1;
    }
    clear_screen("Match Summary");
    print_div();
    enum Color title_color[3] = {LIGHTRED, LIGHTGREEN, LIGHTYELLOW};
    printfc(title_color[won], "%s\n", msg);
    match_print_opponent(match);
    match_print(match);
    printfc(WHITE, "Gold: %d\n", state->gold);
    // Get new cheat
    if ( won == 1) {
        print_div();
        printfc(WHITE, "Gained a cheat:\n");
        int cheat_list_index = rand() % CHEATS_AMT;
        bool rc = state_gain_cheat(state, cheat_list_index);
        if (!rc) {
            printfc(WHITE, "Attempted to gain %s but there are no more cheat slots available\n", cheats_list[cheat_list_index].name);
            cheat_print(&cheats_list[cheat_list_index]);
        }
        else {
            printfc(WHITE, "Gained Cheat: %s\n", cheats_list[cheat_list_index].name);
            cheat_print(&cheats_list[cheat_list_index]);
        }
    }
    to_continue();
    match_start(match);
}
void match_check(struct Match *match, struct State *state, struct Cheat cheats_list[]) {
    if (match->player_total == 21 && match->opponent_total == 21) {
        match_end(match, state, cheats_list, 2, "Draw! (both 21)");
    }
    else if (match->player_total == 21) {
        match_end(match, state, cheats_list, 1, "Player wins! (21)");
    }
    else if (match->opponent_total == 21) {
        match_end(match, state, cheats_list, 0, "Opponent wins! (21)");
    }
    else if (match->player_total > 21 && match->opponent_total > 21) {
        match_end(match, state, cheats_list, 2, "Draw! (both bust)");
    }
    else if (match->opponent_total > 21) {
        match_end(match, state, cheats_list, 1, "Opponent busts! (win)");
    }
    else if (match->player_total > 21) {
        match_end(match, state, cheats_list, 0, "Player busts! (lose)");
    }
    else if (match->player_held && match->opponent_held) {
        if (match->player_total == match->opponent_total) {
            match_end(match, state, cheats_list, 2, "Draw!");
        }
        else if (match->player_total > match->opponent_total) {
            match_end(match, state, cheats_list, 1, "Player wins!");
        } 
        else {
            match_end(match, state, cheats_list, 0, "Opponent wins!");
        }
    }
}

//
// Misc
//
int roll_die(int sides) {
    return rand() % sides + 1;
}
void loot_box(struct State *state, struct Cheat cheats_list[]) {
    clear_screen("Loot Box");
    int cheat_list_index = rand() % CHEATS_AMT;
    bool rc = state_gain_cheat(state, cheat_list_index);
    if (rc) {
        printfc(WHITE, "Gained Cheat: %s\n", cheats_list[cheat_list_index].name);
        cheat_print(&cheats_list[cheat_list_index]);
    }
    else {
        printfc(WHITE, "Attempted to gain %s but there are no more cheat slots available\n", cheats_list[cheat_list_index].name);
    }
    to_continue();
}
void opponent_turn(struct Match *match) {
    // Greater than caution and (not aggressive or greater than player)
    if (match->opponent_total >= (21 - match->opponent_caution) && (!match->opponent_aggressive || match->opponent_total >= match->player_total)) {
        printfc(YELLOW, "%s holds\n", match->opponent_name);
        match->opponent_held = true;
        return;
    }
    int roll = roll_die(match->die_sides);
    match->opponent_total += roll;
    match->opponent_held = false;
    printfc(GREEN, "%s rolls: %d\n", match->opponent_name, roll);
}

//
// Commands
//
void cmd_roll(struct Match *match) {
    clear_screen("Roll");
    int roll = roll_die(match->die_sides);
    match->player_total += roll;
    match->turn++;
    printfc(GREEN, "player rolls: %d\n", roll);
    opponent_turn(match);
    match->player_held = false;
}
void cmd_hold(struct Match *match) {
    clear_screen("Hold");
    match->player_held = true;
    printfc(YELLOW, "player holds\n");
    opponent_turn(match);
    match->player_held = true;
}
void cmd_cheat_list(struct State *state, struct Cheat cheats_list[]) {
    clear_screen("Cheat Slots");
    for (int i = 0; i < state->cheats_cap; i++) {
        // if (state->cheats[i] != -1) printfc(WHITE, "%d.%s \n", i, cheats_list[state->cheats[i]].name);
        printfc(WHITE, "%d. ", i + 1);
        if (state->cheats[i] != -1) {
            cheat_print(&cheats_list[state->cheats[i]]);
        }
        else {
            printfc(WHITE, "---\n");
        }
    }
    printfc(WHITE, "\n");
}

void cmd_use_cheat(struct State *state, struct Match *match, int cheat_index, struct Cheat cheats_list[]) {
    clear_screen("Use Cheat");
    printfc(WHITE, "Using cheat \n");
    int used_index = state_use_cheat(state, cheat_index);
    if (used_index == -1) {
        printfc(WHITE, "Invalid cheat\n");
        return;
    }
    struct Cheat cheat = cheats_list[used_index];
    cheat_print(&cheat);
    if (cheat.add != 0) {
        printfc(WHITE, "Adding %d\n", cheat.add);
        match->player_total += cheat.add;
    }
    if (cheat.sub != 0) {
        printfc(WHITE, "Subtracting %d\n", cheat.sub);
        match->player_total -= cheat.sub;
    }
    if (cheat.div != 0) {
        printfc(WHITE, "Dividing by %d\n", cheat.div);
        match->player_total /= cheat.div;
    }
    if (cheat.mult != 0) {
        printfc(WHITE, "Multiplying by %d\n", cheat.mult);
        match->player_total *= cheat.mult;
    }
    if (cheat.set != 0) {
        printfc(WHITE, "Setting to %d\n", cheat.set);
        match->player_total = cheat.set;
    }
    if (cheat.reverse) {
        printfc(WHITE, "Reversing scores\n");
        int temp = match->player_total;
        match->player_total = match->opponent_total;
        match->opponent_total = temp;
    }
    if (cheat.invert) {
        printfc(WHITE, "Inverting scores\n");
        match->player_total = 21 - match->player_total;
        match->opponent_total = 21 - match->opponent_total;
    }
    if (cheat.reset_both) {
        printfc(WHITE, "Resetting both scores\n");
        match->player_total = 0;
        match->opponent_total = 0;
    }
    if (cheat.reset_player) {
        printfc(WHITE, "Resetting player score\n");
        match->player_total = 0;
    }
    if (cheat.reset_opponent) {
        printfc(WHITE, "Resetting opponent score\n");
        match->opponent_total = 0;
    }
    if (cheat.match_high) {
        printfc(WHITE, "Matching high score\n");
        if (match->player_total > match->opponent_total) {
            match->opponent_total = match->player_total;
        } else {
            match->player_total = match->opponent_total;
        }
    }
    if (cheat.match_low) {
        printfc(WHITE, "Matching low score\n");
        if (match->player_total < match->opponent_total) {
            match->opponent_total = match->player_total;
        } else {
            match->player_total = match->opponent_total;
        }
    }
}
void cmd_help() {
    clear_screen("Help");
    printfc(WHITE, "Commands:\n");
    printfc(WHITE, "%c - roll\n", CMD_ROLL);
    printfc(WHITE, "%c - hold\n", CMD_HOLD);
    printfc(WHITE, "%c - inspect cheat slots\n", CMD_CHEAT_LIST);
    printfc(WHITE, "%c - inspect opponent\n", CMD_OPPONENT);
    printfc(WHITE, "%c - use cheat slot 1\n", CMD_USE_CHEAT_1);
    printfc(WHITE, "%c - use cheat slot 2\n", CMD_USE_CHEAT_2);
    printfc(WHITE, "%c - use cheat slot 3\n", CMD_USE_CHEAT_3);
    printfc(WHITE, "%c - use cheat slot 4\n", CMD_USE_CHEAT_4);
    printfc(WHITE, "%c - use cheat slot 5\n", CMD_USE_CHEAT_5);
    printfc(WHITE, "%c - use cheat slot 6\n", CMD_USE_CHEAT_6);
    printfc(WHITE, "%c - use cheat slot 7\n", CMD_USE_CHEAT_7);
    printfc(WHITE, "%c - use cheat slot 8\n", CMD_USE_CHEAT_8);
    printfc(WHITE, "%c - quit\n", CMD_QUIT);
    printfc(WHITE, "%c - help\n", CMD_HELP);
}

//
// Main
//
int main() {
    // Setup RNG
    int seed = time(NULL);
    srand(seed);
    // Setup basic game state
    struct State state = state_new();
    // Intro
    clear_screen("ch33ter");
    printfc(WHITE, "Welcome to ch33ter\n");
    to_continue();
    // Setup cheats
    struct Cheat cheats_list[32];
    cheats_list_init(cheats_list);
    // Gain some cheats
    loot_box(&state, cheats_list);
    // Start first match
    clear_screen("ch33ter");
    struct Match match = match_new();
    int run = 1;
    while(run) {
        char input;
        print_div();
        printfc(LIGHTBLUE, ">> ");
        scanf("%c", &input);
        // printfc(WHITE, "cheat %s", cheats[0].name);
        // clear the buffer
        while(getchar() != '\n');
        clear_screen("ch33ter");
        switch (input) {
            case CMD_USE_CHEAT_1:
                cmd_use_cheat(&state, &match, 0, cheats_list);
                break;
            case CMD_USE_CHEAT_2:
                cmd_use_cheat(&state, &match, 1, cheats_list);
                break;
            case CMD_USE_CHEAT_3:
                cmd_use_cheat(&state, &match, 3, cheats_list);
                break;
            case CMD_USE_CHEAT_4: 
                cmd_use_cheat(&state, &match, 4, cheats_list);
                break;
            case CMD_USE_CHEAT_5:
                cmd_use_cheat(&state, &match, 5, cheats_list);
                break;
            case CMD_USE_CHEAT_6:
                cmd_use_cheat(&state, &match, 6, cheats_list);
                break;
            case CMD_USE_CHEAT_7:
                cmd_use_cheat(&state, &match, 7, cheats_list);
                break;
            case CMD_USE_CHEAT_8:
                cmd_use_cheat(&state, &match, 8, cheats_list);
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
                match_print_opponent(&match);
                break;
            case CMD_HELP:
                cmd_help();
                break;
            case CMD_QUIT:
                run = 0;
                break;
            default:
                printfc(WHITE, "Invalid input\n");
        }
        match_print(&match);
        // Check for match end
        match_check(&match, &state, cheats_list);
    }
    printfc(WHITE, "goodbye\n");
    return 0;
}