#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h> // va_list, va_start, va_end
#include <ctype.h>  // toupper

#define MAX_CHEATS 8

// Config
#define DISABLE_COLORS 0
#define USE_RAW_INPUT 1

#define CMD_ROLL 'q'
#define CMD_HOLD 'w'
#define CMD_CHEAT_LIST 'e'
#define CMD_OPPONENT 'r'
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

#define CLR1_CLR "\033[0;37m"
#define CLR2_CLR "\033[0;91m"
#define CLR3_CLR "\033[0;94m"
#define CLR4_CLR "\033[0;92m"
#define CLR5_CLR "\033[0;93m"
#define CLR6_CLR "\033[0;95m"
#define CLR7_CLR "\033[0;96m"
#define CLR8_CLR "\033[1;31m"

//
// Utils
//
enum Color { // TODO: use a color scheme of 8 colors instead of so many - can add bold
    CLR1,
    CLR2,
    CLR3,
    CLR4,
    CLR5,
    CLR6,
    CLR7,
    CLR8
};

void clr_start(enum Color color) {
    if (DISABLE_COLORS) return;
    switch (color) {
        case CLR1:
            printf(CLR1_CLR);
            break;
        case CLR2:
            printf(CLR2_CLR);
            break;
        case CLR3:
            printf(CLR3_CLR);
            break;
        case CLR4:
            printf(CLR4_CLR);
            break;
        case CLR5:
            printf(CLR5_CLR);
            break;
        case CLR6:
            printf(CLR6_CLR);
            break;
        case CLR7:
            printf(CLR7_CLR);
            break;
        case CLR8:
            printf(CLR8_CLR);
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
    printfc(CLR4, "▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂\n");
}
void print_screen_title(char title[64]) {
    printfc(CLR4, "█%s", title);
    for (int i = 0; i < 64 - strlen(title); i++) {
        printfc(CLR4, "█");
    }
    printfc(CLR1, "\n\n");
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
    printfc(CLR2, "\n\n-- Press any key to continue --\n");
    system("stty raw");
    getchar();
    system("stty cooked");
    clear_screen("ch33ter");
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
    // sprintfc(CLR1, name, "%s.%s", opponent_names[rand() % 16], opponent_names[rand() % 16]);
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
    state.cheats_cap = 4;
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
    printfc(CLR3, "%s ", cheat->name);
    if (cheat->add != 0) printfc(CLR4, "adds %d, ", cheat->add);
    if (cheat->sub != 0) printfc(CLR4, "subtracts %d, ", cheat->sub);
    if (cheat->div != 0) printfc(CLR4, "divides by %d, ", cheat->div);
    if (cheat->mult != 0) printfc(CLR4, "multiplies by %d, ", cheat->mult);
    if (cheat->set != 0) printfc(CLR4, "sets to %d, ", cheat->set);
    if (cheat->reverse) printfc(CLR4, "reverses scores, ");
    if (cheat->invert) printfc(CLR4, "inverts scores, ");
    if (cheat->reset_both) printfc(CLR4, "resets both scores, ");
    if (cheat->reset_player) printfc(CLR4, "resets player score, ");
    if (cheat->reset_opponent) printfc(CLR4, "resets opponent score, ");
    if (cheat->match_high) printfc(CLR4, "matches high score, ");
    if (cheat->match_low) printfc(CLR4, "matches low score, ");
    printfc(CLR1, "\n");
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
// Loot box
//
void loot_box(struct State *state, struct Cheat cheats_list[]) {
    clear_screen("Loot Box");
    printfc(CLR1, "You got a loot box!\n");
    int cheat_list_index = rand() % CHEATS_AMT;
    bool rc = state_gain_cheat(state, cheat_list_index);
    if (rc) {
        printfc(CLR1, "Gained Cheat: %s\n", cheats_list[cheat_list_index].name);
        cheat_print(&cheats_list[cheat_list_index]);
    }
    else {
        printfc(CLR1, "Attempted to gain %s but there are no more cheat slots available\n", cheats_list[cheat_list_index].name);
    }
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
    bool opponent_aggressive;
    char opponent_name[64];
};
void match_print(struct Match *match) {
    print_div();
    printfc(CLR5, "player total: %d\n", match->player_total);
    for (int i = 0; i < 21; i++) {
        if (i < match->player_total) {
            printfc(match->player_total > 21 ? CLR2 : CLR4, "█");
        } else {
            printfc(CLR8, "▒");
        }
    }
    printf("\n");
    printfc(CLR7, "%s total: %d\n", match->opponent_name, match->opponent_total);
    for (int i = 0; i < 21; i++) {
        if (i < match->opponent_total) {
            printfc(match->opponent_total > 21 ? CLR2 : CLR4, "█");
        } else {
            printfc(CLR8, "▒");
        }
    }
    printf("\n");
    print_div();
}
void match_print_opponent(struct Match *match) {
    printfc(CLR6, "Opponent: %s\n", match->opponent_name);
    printfc(CLR5, "⚄⚀ Die sides: %d\n", match->die_sides);
    printfc(CLR5, "㈫ Caution: %d (holds at %d) \n", match->opponent_caution, 21 - match->opponent_caution);
    printfc(CLR5, "㊋ Aggressive: %s\n", match->opponent_aggressive ? "yes" : "no");
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
    printfc(CLR2, "--- Match started ---\n");
    match_print_opponent(match);
    print_div();
}
struct Match match_new() {
    struct Match match;
    match_start(&match);
    return match;
}
void match_end(struct Match *match, struct State *state, struct Cheat cheats_list[], int won, char msg[64]) { // won = 2 == draw
    printfc(CLR4, "Match ended\n");
    to_continue();
    if (won == 1) {
        state->gold += 1;
    }
    if (won == 0) {
        state->gold -= 1;
    }
    clear_screen("Match Summary");
    print_div();
    enum Color title_color[3] = {CLR2, CLR4, CLR5};
    printfc(title_color[won], "%s\n", msg);
    match_print_opponent(match);
    match_print(match);
    printfc(CLR1, "Gold: %d\n", state->gold);
    to_continue();
    // Get new cheat
    if ( won == 1) {
        loot_box(state, cheats_list);
    }
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
void opponent_turn(struct Match *match) {
    // Greater than caution and (not aggressive or greater than player)
    if (match->opponent_total >= (21 - match->opponent_caution) && (!match->opponent_aggressive || match->opponent_total >= match->player_total)) {
        printfc(CLR5, "%s holds\n", match->opponent_name);
        match->opponent_held = true;
        return;
    }
    int roll = roll_die(match->die_sides);
    match->opponent_total += roll;
    match->opponent_held = false;
    printfc(CLR4, "%s rolls: %d\n", match->opponent_name, roll);
}

//
// Commands
//
void cmd_roll(struct Match *match) {
    clear_screen("Roll");
    int roll = roll_die(match->die_sides);
    match->player_total += roll;
    match->turn++;
    printfc(CLR4, "player rolls: %d\n", roll);
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
    for (int i = 0; i < state->cheats_cap; i++) {
        // if (state->cheats[i] != -1) printfc(CLR1, "%d.%s \n", i, cheats_list[state->cheats[i]].name);
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
    if (cheat.add != 0) {
        printfc(CLR1, "Adding %d\n", cheat.add);
        match->player_total += cheat.add;
    }
    if (cheat.sub != 0) {
        printfc(CLR1, "Subtracting %d\n", cheat.sub);
        match->player_total -= cheat.sub;
    }
    if (cheat.div != 0) {
        printfc(CLR1, "Dividing by %d\n", cheat.div);
        match->player_total /= cheat.div;
    }
    if (cheat.mult != 0) {
        printfc(CLR1, "Multiplying by %d\n", cheat.mult);
        match->player_total *= cheat.mult;
    }
    if (cheat.set != 0) {
        printfc(CLR1, "Setting to %d\n", cheat.set);
        match->player_total = cheat.set;
    }
    if (cheat.reverse) {
        printfc(CLR1, "Reversing scores\n");
        int temp = match->player_total;
        match->player_total = match->opponent_total;
        match->opponent_total = temp;
    }
    if (cheat.invert) {
        printfc(CLR1, "Inverting scores\n");
        match->player_total = 21 - match->player_total;
        match->opponent_total = 21 - match->opponent_total;
    }
    if (cheat.reset_both) {
        printfc(CLR1, "Resetting both scores\n");
        match->player_total = 0;
        match->opponent_total = 0;
    }
    if (cheat.reset_player) {
        printfc(CLR1, "Resetting player score\n");
        match->player_total = 0;
    }
    if (cheat.reset_opponent) {
        printfc(CLR1, "Resetting opponent score\n");
        match->opponent_total = 0;
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
void cmd_help() {
    clear_screen("Help");
    printfc(CLR1, "Commands:\n");
    printfc(CLR1, "%c - roll\n", CMD_ROLL);
    printfc(CLR1, "%c - hold\n", CMD_HOLD);
    printfc(CLR1, "%c - inspect cheat slots\n", CMD_CHEAT_LIST);
    printfc(CLR1, "%c - inspect opponent\n", CMD_OPPONENT);
    printfc(CLR1, "%c - use cheat slot 1\n", CMD_USE_CHEAT_1);
    printfc(CLR1, "%c - use cheat slot 2\n", CMD_USE_CHEAT_2);
    printfc(CLR1, "%c - use cheat slot 3\n", CMD_USE_CHEAT_3);
    printfc(CLR1, "%c - use cheat slot 4\n", CMD_USE_CHEAT_4);
    printfc(CLR1, "%c - use cheat slot 5\n", CMD_USE_CHEAT_5);
    printfc(CLR1, "%c - use cheat slot 6\n", CMD_USE_CHEAT_6);
    printfc(CLR1, "%c - use cheat slot 7\n", CMD_USE_CHEAT_7);
    printfc(CLR1, "%c - use cheat slot 8\n", CMD_USE_CHEAT_8);
    printfc(CLR1, "%c - quit\n", CMD_QUIT);
    printfc(CLR1, "%c - help\n", CMD_HELP);
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
    printfc(CLR1, "Welcome to ch33ter\n");
    printfc(CLR1, "You will be challenged in a game something like what you might call '21'.\n");
    printfc(CLR1, "Your opponents will be many. Some will be strong some will be weak.\n");
    printfc(CLR1, "They will bring their own dice. You must account for that.\n");
    printfc(CLR1, "The best way to account for that might be cheating...\n");
    printfc(CLR1, "Good luck!\n");
    printfc(CLR7, "Press %c to see the help screen now!\n", CMD_HELP);
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
        print_div();
        char input;
        if (USE_RAW_INPUT) {
            printfc(CLR3, ">> ");
            system("stty raw");
            input = getchar();
            system("stty cooked");
            clear_screen("ch33ter");   
        }
        else {
            printfc(CLR3, ">> ");
            scanf("%c", &input);
            // clear the buffer
            while(getchar() != '\n');
            clear_screen("ch33ter");
        }
        bool show_match = 1;
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
                show_match = 0;
                break;
            case CMD_QUIT:
                run = 0;
                break;
            default:
                printfc(CLR1, "Invalid input\n");
        }
        if (show_match) match_print(&match);
        // Check for match end
        match_check(&match, &state, cheats_list);
    }
    printfc(CLR1, "goodbye\n");
    return 0;
}