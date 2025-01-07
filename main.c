#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h> // va_list, va_start, va_end
#include <ctype.h>  // toupper

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
enum Color {
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
            printf("\033[0;37m");
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
            printf("\033[1;30m");
            break;
        default:
            printf("");
            break;
    }
}
void clr_end() {
    printf("\033[0m");
}
void printf_caps(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    for (int i = 0; buffer[i]; i++) {
        buffer[i] = toupper(buffer[i]);
    }

    printf("%s", buffer);
}
void print_div() {
    clr_start(CYAN);
    printf_caps("--------\n");
    clr_end();
}
void clear_screen() {
    // C;ear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void to_continue() {
    // Wait for user input
    clr_start(RED);
    printf_caps("\n\n-- Enter 'k' to continue --\n");
    clr_end();
    getchar();
    clear_screen();
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
    // sprintf_caps(name, "%s.%s", opponent_names[rand() % 16], opponent_names[rand() % 16]);
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
    clr_start(BLUE);
    printf_caps("%s ", cheat->name);
    clr_start(GREEN);
    if (cheat->add != 0) printf_caps("adds %d, ", cheat->add);
    if (cheat->sub != 0) printf_caps("subtracts %d, ", cheat->sub);
    if (cheat->div != 0) printf_caps("divides by %d, ", cheat->div);
    if (cheat->mult != 0) printf_caps("multiplies by %d, ", cheat->mult);
    if (cheat->set != 0) printf_caps("sets to %d, ", cheat->set);
    if (cheat->reverse) printf_caps("reverses scores, ");
    if (cheat->invert) printf_caps("inverts scores, ");
    if (cheat->reset_both) printf_caps("resets both scores, ");
    if (cheat->reset_player) printf_caps("resets player score, ");
    if (cheat->reset_opponent) printf_caps("resets opponent score, ");
    if (cheat->match_high) printf_caps("matches high score, ");
    if (cheat->match_low) printf_caps("matches low score, ");
    printf_caps("\n");
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
    clr_start(YELLOW);
    printf_caps("player total: %d\n", match->player_total);
    clr_start(MAGENTA);
    printf_caps("%s total: %d\n", match->opponent_name, match->opponent_total);
    clr_end();
    print_div();
}
void match_print_opponent(struct Match *match) {
    printf_caps("Opponent: %s\n", match->opponent_name);
    printf_caps("Caution: %d (holds at %d) \n", match->opponent_caution, 21 - match->opponent_caution);
    printf_caps("Aggressive: %d\n", match->opponent_aggressive);
}
void match_start(struct Match *match) {
    match->player_total = 0;
    match->opponent_total = 0;
    match->opponent_caution = rand() % 11;
    match->turn = 0;
    match->die_sides = 10;
    match->player_held = false;
    match->opponent_held = false;
    match->opponent_aggressive = rand() % 2;
    strcpy(match->opponent_name, "OpponentX");
    opponent_name_rand(match->opponent_name);
    print_div();
    printf_caps("Match started...\n");
    match_print_opponent(match);
}
struct Match match_new() {
    struct Match match;
    match_start(&match);
    return match;
}
void match_end(struct Match *match, struct State *state, struct Cheat cheats_list[], int won, char msg[64]) { // won = 2 == draw
    clr_start(GREEN);
    printf_caps("Match ended\n");
    clr_end();
    to_continue();
    if (won == 1) {
        state->gold += 1;
    }
    if (won == 0) {
        state->gold -= 1;
    }
    clear_screen();
    print_div();
    int title_color[3] = {LIGHTRED, LIGHTGREEN, LIGHTYELLOW};
    clr_start(title_color[won]);
    printf_caps("Match Summary - %s\n", msg);
    clr_end();
    match_print_opponent(match);
    match_print(match);
    printf_caps("Gold: %d\n", state->gold);
    // Get new cheat
    if ( won == 1) {
        print_div();
        printf_caps("Gained a cheat:\n");
        int cheat_list_index = rand() % CHEATS_AMT;
        bool rc = state_gain_cheat(state, cheat_list_index);
        if (!rc) {
            printf_caps("Attempted to gain %s but there are no more cheat slots available\n", cheats_list[cheat_list_index].name);
            cheat_print(&cheats_list[cheat_list_index]);
        }
        else {
            printf_caps("Gained Cheat: %s\n", cheats_list[cheat_list_index].name);
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
void opponent_turn(struct Match *match) {
    // Greater than caution and (not aggressive or greater than player)
    if (match->opponent_total >= (21 - match->opponent_caution) && (!match->opponent_aggressive || match->opponent_total >= match->player_total)) {
        clr_start(YELLOW);
        printf_caps("%s holds\n", match->opponent_name);
        clr_end();
        match->opponent_held = true;
        return;
    }
    int roll = roll_die(match->die_sides);
    match->opponent_total += roll;
    match->opponent_held = false;
    clr_start(GREEN);
    printf_caps("%s rolls: %d\n", match->opponent_name, roll);
    clr_end();
}

//
// Commands
//
void cmd_roll(struct Match *match) {
    int roll = roll_die(match->die_sides);
    match->player_total += roll;
    match->turn++;
    clr_start(GREEN);
    printf_caps("player rolls: %d\n", roll);
    clr_end();
    opponent_turn(match);
    match->player_held = false;
}
void cmd_hold(struct Match *match) {
    match->player_held = true;
    clr_start(GREEN);
    printf_caps("player holds\n");
    clr_end();
    opponent_turn(match);
    match->player_held = true;
}
void cmd_cheat_list(struct State *state, struct Cheat cheats_list[]) {
    for (int i = 0; i < state->cheats_cap; i++) {
        // if (state->cheats[i] != -1) printf_caps("%d.%s \n", i, cheats_list[state->cheats[i]].name);
        printf_caps("%d. ", i + 1);
        if (state->cheats[i] != -1) {
            cheat_print(&cheats_list[state->cheats[i]]);
        }
        else {
            printf_caps("---\n");
        }
    }
    printf_caps("\n");
}

void cmd_use_cheat(struct State *state, struct Match *match, int cheat_index, struct Cheat cheats_list[]) {
    printf_caps("Using cheat \n");
    int used_index = state_use_cheat(state, cheat_index);
    if (used_index == -1) {
        printf_caps("Invalid cheat\n");
        return;
    }
    struct Cheat cheat = cheats_list[used_index];
    cheat_print(&cheat);
    if (cheat.add != 0) {
        printf_caps("Adding %d\n", cheat.add);
        match->player_total += cheat.add;
    }
    if (cheat.sub != 0) {
        printf_caps("Subtracting %d\n", cheat.sub);
        match->player_total -= cheat.sub;
    }
    if (cheat.div != 0) {
        printf_caps("Dividing by %d\n", cheat.div);
        match->player_total /= cheat.div;
    }
    if (cheat.mult != 0) {
        printf_caps("Multiplying by %d\n", cheat.mult);
        match->player_total *= cheat.mult;
    }
    if (cheat.set != 0) {
        printf_caps("Setting to %d\n", cheat.set);
        match->player_total = cheat.set;
    }
    if (cheat.reverse) {
        printf_caps("Reversing scores\n");
        int temp = match->player_total;
        match->player_total = match->opponent_total;
        match->opponent_total = temp;
    }
    if (cheat.invert) {
        printf_caps("Inverting scores\n");
        match->player_total = 21 - match->player_total;
        match->opponent_total = 21 - match->opponent_total;
    }
    if (cheat.reset_both) {
        printf_caps("Resetting both scores\n");
        match->player_total = 0;
        match->opponent_total = 0;
    }
    if (cheat.reset_player) {
        printf_caps("Resetting player score\n");
        match->player_total = 0;
    }
    if (cheat.reset_opponent) {
        printf_caps("Resetting opponent score\n");
        match->opponent_total = 0;
    }
    if (cheat.match_high) {
        printf_caps("Matching high score\n");
        if (match->player_total > match->opponent_total) {
            match->opponent_total = match->player_total;
        } else {
            match->player_total = match->opponent_total;
        }
    }
    if (cheat.match_low) {
        printf_caps("Matching low score\n");
        if (match->player_total < match->opponent_total) {
            match->opponent_total = match->player_total;
        } else {
            match->player_total = match->opponent_total;
        }
    }
}
void cmd_help() {
    printf_caps("Commands:\n");
    printf_caps("%c - roll\n", CMD_ROLL);
    printf_caps("%c - hold\n", CMD_HOLD);
    printf_caps("%c - inspect cheat slots\n", CMD_CHEAT_LIST);
    printf_caps("%c - inspect opponent\n", CMD_OPPONENT);
    printf_caps("%c - use cheat slot 1\n", CMD_USE_CHEAT_1);
    printf_caps("%c - use cheat slot 2\n", CMD_USE_CHEAT_2);
    printf_caps("%c - use cheat slot 3\n", CMD_USE_CHEAT_3);
    printf_caps("%c - use cheat slot 4\n", CMD_USE_CHEAT_4);
    printf_caps("%c - use cheat slot 5\n", CMD_USE_CHEAT_5);
    printf_caps("%c - use cheat slot 6\n", CMD_USE_CHEAT_6);
    printf_caps("%c - use cheat slot 7\n", CMD_USE_CHEAT_7);
    printf_caps("%c - use cheat slot 8\n", CMD_USE_CHEAT_8);
    printf_caps("%c - quit\n", CMD_QUIT);
    printf_caps("%c - help\n", CMD_HELP);
}

//
// Main
//
int main() {
    int seed = time(NULL);
    srand(seed);
    struct State state = state_new();
    struct Match match = match_new();
    struct Cheat cheats_list[32];
    cheats_list_init(cheats_list);
    state_gain_cheat(&state, 0);
    state_gain_cheat(&state, 1);
    int run = 1;
    while(run) {
        char input;
        printf_caps(">> ");
        scanf("%c", &input);
        // printf_caps("cheat %s", cheats[0].name);
        // clear the buffer
        while(getchar() != '\n');
        clear_screen();
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
                printf_caps("Invalid input\n");
        }
        match_print(&match);
        // Check for match end
        match_check(&match, &state, cheats_list);
    }
    printf_caps("goodbye\n");
    return 0;
}