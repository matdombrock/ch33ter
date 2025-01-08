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

// Config
#define DISABLE_COLORS 0
#define USE_RAW_INPUT 1

#define CMD_ROLL 'r'
#define CMD_HOLD 'w'
#define CMD_CHEAT_LIST 'e'
#define CMD_OPPONENT 'q'
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

#define CLR1_CLR "\033[1;90m" // light grey
#define CLR2_CLR "\033[1;91m" // bright red
#define CLR3_CLR "\033[1;94m" // bright blue
#define CLR4_CLR "\033[1;32m" // lime green
#define CLR5_CLR "\033[1;33m" // vibrant yellow
#define CLR6_CLR "\033[1;95m" // bright magenta
#define CLR7_CLR "\033[1;96m" // bright cyan
#define CLR8_CLR "\033[1;97m" // bright white

//
// Utils
//
enum Color { 
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
    printfc(CLR4, "▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂  ▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂  ▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂\n");
}
void print_screen_title(char title[]) {
    printfc(CLR6, "█ %s ", title);
    for (int i = 0; i < TERM_WIDTH - strlen(title) - 2; i++) {
        printfc(CLR6, "█");
    }
    printfc(CLR1, "\n");
    print_div();
}
void print_subtitle(enum Color color, char subtitle[]) {
    printfc(color, "███ %s █████████████████████\n", subtitle);
}
void clear_screen(char title[]) {
    // Clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("\a");
    print_screen_title(title);
}
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
        "paldor",
        "quildor",
        "raldor",
        "saldor",
        "taldor",
        "uoldor",
        "vildor",
        "waldor",
        "xildor",
        "yooldor",
        "zandor"
    };
    // sprintfc(CLR1, name, "%s.%s", opponent_names[rand() % 16], opponent_names[rand() % 16]);
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
    bool reverse;
    bool invert;
    bool reset;
    bool match_high;
    bool match_low;
};
struct Cheat cheat_new(char name[32]) {
    struct Cheat cheat;
    strcpy(cheat.name, name);
    cheat.affects = 0;
    cheat.add = 0;
    cheat.sub = 0;
    cheat.div = 0;
    cheat.mult = 0;
    cheat.set = 0;
    cheat.reverse = 0;
    cheat.invert = 0;
    cheat.reset = 0;
    cheat.match_high = 0;
    cheat.match_low = 0;
    return cheat;
}
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
    if (cheat->reverse) printfc(CLR4, "| rev ");
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
#define CHEATS_AMT_CHAOS 4
#define CHEATS_AMT_DAGGERS 4
#define CHEATS_AMT_SHARDS 4
#define CHEATS_AMT_BOMBS 4
#define CHEATS_AMT_KINGS 4
#define CHEATS_AMT 33 + CHEATS_AMT_CHAOS + CHEATS_AMT_DAGGERS + CHEATS_AMT_SHARDS + CHEATS_AMT_BOMBS + CHEATS_AMT_KINGS
void cheats_list_init(struct Cheat *cheats_list) {
    cheats_list[0] = cheat_new("ace");
    cheats_list[0].add = 1;
    cheats_list[1] = cheat_new("jack");
    cheats_list[1].add = 2;
    cheats_list[2] = cheat_new("queen");
    cheats_list[2].add = 4;
    cheats_list[3] = cheat_new("king");
    cheats_list[3].add = 8;
    cheats_list[4] = cheat_new("joker");
    cheats_list[4].affects = 2;
    cheats_list[4].reset = 1;
    cheats_list[5] = cheat_new("wild");
    cheats_list[5].affects = 2;
    cheats_list[5].invert = 1;
    cheats_list[6] = cheat_new("rebel");
    cheats_list[6].reverse = 1;
    cheats_list[7] = cheat_new("worker");
    cheats_list[7].match_high = 1;
    cheats_list[8] = cheat_new("kingpin");
    cheats_list[8].match_low = 1;
    cheats_list[9] = cheat_new("calamity");
    cheats_list[9].div = 2;
    cheats_list[9].affects = 2;
    cheats_list[10] = cheat_new("catastrophe");
    cheats_list[10].div = 4;
    cheats_list[10].affects = 2;
    cheats_list[11] = cheat_new("lucky");
    cheats_list[11].set = 7;
    cheats_list[12] = cheat_new("unlucky");
    cheats_list[12].set = GOAL_NUM + 1;
    cheats_list[13] = cheat_new("bfg");
    cheats_list[13].set = GOAL_NUM;
    cheats_list[14] = cheat_new("sniper");
    cheats_list[14].set = GOAL_NUM - 1;
    cheats_list[15] = cheat_new("scattergun");
    cheats_list[15].set = GOAL_NUM - 7;
    cheats_list[16] = cheat_new("warlock");
    cheats_list[16].mult = 2;
    cheats_list[16].affects = 2;
    cheats_list[17] = cheat_new("wizard");
    cheats_list[17].mult = 4;
    cheats_list[18] = cheat_new("sorcerer");
    cheats_list[18].mult = 8;
    cheats_list[19] = cheat_new("saint");
    cheats_list[19].set = GOAL_NUM - 1;
    cheats_list[19].affects = 2;
    cheats_list[20] = cheat_new("sinner");
    cheats_list[20].set = 1;
    cheats_list[20].reverse = 1;
    cheats_list[21] = cheat_new("savior");
    cheats_list[21].affects = 2;
    cheats_list[21].set = GOAL_NUM - 1;
    cheats_list[22] = cheat_new("slammer");
    cheats_list[22].affects = 1;
    cheats_list[22].set = 1;
    cheats_list[23] = cheat_new("a-bomb");
    cheats_list[23].affects = 2;
    cheats_list[23].reset = 1;
    cheats_list[24] = cheat_new("bomber");
    cheats_list[24].affects = 2;
    cheats_list[24].set = 7;
    cheats_list[25] = cheat_new("c4");
    cheats_list[25].affects = 2;
    cheats_list[25].set = 14;
    cheats_list[26] = cheat_new("dynamite");
    cheats_list[26].affects = 2;
    cheats_list[26].set = 21;
    cheats_list[27] = cheat_new("glass-dagger");
    cheats_list[27].affects = 1;
    cheats_list[27].sub = 1;
    cheats_list[28] = cheat_new("buffer-knife");
    cheats_list[28].affects = 1;
    cheats_list[28].sub = 7;
    cheats_list[29] = cheat_new("short-sword");
    cheats_list[29].affects = 1;
    cheats_list[29].sub = 14;
    cheats_list[30] = cheat_new("my-axe");
    cheats_list[30].affects = 1;
    cheats_list[30].sub = 21;
    cheats_list[31] = cheat_new("ban-hammer");
    cheats_list[31].affects = 1;
    cheats_list[31].sub = 28;
    cheats_list[32] = cheat_new("falcon");
    cheats_list[32].affects = 1;
    cheats_list[32].invert = 1;
    int offset = 33;
    for (int i = 0; i < CHEATS_AMT_CHAOS; i++) {
        char cheat_name[32];
        snprintf(cheat_name, sizeof(cheat_name), "chaosX%d", i);
        cheats_list[offset + i] = cheat_new(cheat_name);
        cheats_list[offset + i].affects = rand() % 3;
        cheats_list[offset + i].add = rand() % GOAL_NUM;
        cheats_list[offset + i].div = rand() % GOAL_NUM;
        cheats_list[offset + i].set = rand() % GOAL_NUM;
        cheats_list[offset + i].reverse = rand() % 2;
        cheats_list[offset + i].invert = rand() % 2;
        cheats_list[offset + i].reset = rand() % 2;
        cheats_list[offset + i].match_low = rand() % 2;
    }
    offset += CHEATS_AMT_CHAOS;
    for (int i = 0; i < CHEATS_AMT_DAGGERS; i++) {
        char cheat_name[32];
        snprintf(cheat_name, sizeof(cheat_name), "daggerX%d", i);
        cheats_list[offset + i] = cheat_new(cheat_name);
        cheats_list[offset + i].affects = rand() % 3;
        cheats_list[offset + i].sub = rand() % GOAL_NUM;
    }
    offset += CHEATS_AMT_DAGGERS;
    for (int i = 0; i < CHEATS_AMT_SHARDS; i++) {
        char cheat_name[32];
        snprintf(cheat_name, sizeof(cheat_name), "shardX%d", i);
        cheats_list[offset + i] = cheat_new(cheat_name);
        cheats_list[offset + i].affects = rand() % 3;
        cheats_list[offset + i].add = rand() % GOAL_NUM;
    }
    offset += CHEATS_AMT_SHARDS;
    for (int i = 0; i < CHEATS_AMT_BOMBS; i++) {
        char cheat_name[32];
        snprintf(cheat_name, sizeof(cheat_name), "bombX%d", i);
        cheats_list[offset + i] = cheat_new(cheat_name);
        cheats_list[offset + i].affects = rand() % 3;
        cheats_list[offset + i].mult = rand() % (GOAL_NUM / 4);
    }
    offset += CHEATS_AMT_BOMBS;
    for (int i = 0; i < CHEATS_AMT_KINGS; i++) {
        char cheat_name[32];
        snprintf(cheat_name, sizeof(cheat_name), "kingX%d", i);
        cheats_list[offset + i] = cheat_new(cheat_name);
        cheats_list[offset + i].affects = rand() % 3;
        cheats_list[offset + i].div = rand() % (GOAL_NUM / 4);
    }
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
    state.gold = 1;
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
void state_print_cheats(struct State *state, struct Cheat cheats_list[]) {
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

//
// Loot box
//
void loot_box(struct State *state, struct Cheat cheats_list[]) {
    clear_screen("Loot Box");
    printfc(CLR3, "You got a loot box!\n");
    int cheat_list_index = rand() % CHEATS_AMT;
    bool rc = state_gain_cheat(state, cheat_list_index);
    if (rc) printfc(CLR1, "Gained Cheat: %s\n", cheats_list[cheat_list_index].name);
    else printfc(CLR2, "Attempted to gain %s\nbut there are no more cheat slots available\n", cheats_list[cheat_list_index].name);
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
    bool opponent_aggressive;
    bool ended;
    char opponent_name[64];
};
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
void match_print_opponent(struct Match *match) {
    printfc(CLR6, "Opponent: %s\n", match->opponent_name);
    printfc(CLR5, "⚄⚀ Die sides: %d\n", match->die_sides);
    printfc(CLR5, "㈫ Caution: %d (holds at %d) \n", match->opponent_caution, GOAL_NUM - match->opponent_caution);
    printfc(CLR5, "㊋ Aggressive: %s\n", match->opponent_aggressive ? "yes" : "no");
}
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
void match_start(struct Match *match) {
    match->player_total = 0;
    match->opponent_total = 0;
    match->opponent_caution = rand() % 11;
    match->turn = 0;
    match->die_sides = (rand() % (GOAL_NUM -3)) + 3;
    match->player_held = false;
    match->opponent_held = false;
    match->opponent_aggressive = rand() % 2;
    match->ended = false;
    strcpy(match->opponent_name, "OpponentX");
    opponent_name_rand(match->opponent_name);
    print_div();
    print_subtitle(CLR2, "Match Started");
    match_print_opponent(match);
    print_div();
}
struct Match match_new() {
    struct Match match;
    match_start(&match);
    return match;
}
void match_end(struct Match *match, struct State *state, struct Cheat cheats_list[], int won, char msg[]) { // won = 2 == draw
    print_subtitle(CLR2, "Match Ended");
    to_continue();
    enum Color result_colors[3] = {CLR2, CLR4, CLR5};
    enum Color result_color = result_colors[won];
    if (won == 1) {
        state->gold += 1;
    }
    if (won == 0) {
        state->gold -= 1;
    }
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
    match_print_opponent(match);
    match_print(match);
    printfc(CLR1, "Gold: %d\n", state->gold);
    to_continue();
    // Get new cheat
    if ( won == 1) {
        loot_box(state, cheats_list);
    }
    match->ended = true;
}
void match_check(struct Match *match, struct State *state, struct Cheat cheats_list[]) {
    if (match->player_total == GOAL_NUM && match->opponent_total == GOAL_NUM) {
        match_end(match, state, cheats_list, 2, "Both slammed it!");
    }
    else if (match->player_total == GOAL_NUM) {
        match_end(match, state, cheats_list, 1, "Player slammed it!");
    }
    else if (match->opponent_total == GOAL_NUM) {
        match_end(match, state, cheats_list, 0, "Opponent slammed it!");
    }
    else if (match->player_total > GOAL_NUM && match->opponent_total > GOAL_NUM) {
        match_end(match, state, cheats_list, 2, "Both bust!");
    }
    else if (match->opponent_total > GOAL_NUM) {
        match_end(match, state, cheats_list, 1, "Opponent busts!");
    }
    else if (match->player_total > GOAL_NUM) {
        match_end(match, state, cheats_list, 0, "Player busts!");
    }
    else if (match->player_held && match->opponent_held) {
        if (match->player_total == match->opponent_total) {
            match_end(match, state, cheats_list, 2, "Even scores!");
        }
        else if (match->player_total > match->opponent_total) {
            match_end(match, state, cheats_list, 1, "Player wins with a higher score!");
        } 
        else {
            match_end(match, state, cheats_list, 0, "Opponent wins with a higher score!");
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
    if (match->opponent_total >= (GOAL_NUM - match->opponent_caution) && (!match->opponent_aggressive || match->opponent_total >= match->player_total)) {
        printfc(CLR5, "%s holds\n", match->opponent_name);
        match->opponent_held = true;
        return;
    }
    int roll = roll_die(match->die_sides);
    match->opponent_total += roll;
    match->opponent_held = false;
    printfc(CLR4, "%s rolls: %d / %d\n", match->opponent_name, roll, match->die_sides);
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
    if (cheat.reverse) {
        printfc(CLR1, "Reversing scores\n");
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
    // Welcome
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
    // Setup cheats
    struct Cheat cheats_list[64];
    cheats_list_init(cheats_list);
    // Gain some cheats
    loot_box(&state, cheats_list);
    loot_box(&state, cheats_list);
    loot_box(&state, cheats_list);
    // Intro
    clear_screen("Intro");
    printfc(CLR4, "You have been given some cheats to start with\n");
    printfc(CLR3, "-  use these cheats to help you win matches\n");
    printfc(CLR3, "-  also gain more cheats by winning matches\n");
    printfc(CLR3, "-  inspect your cheats at any time by pressing");
    printfc(CLR6, " %c\n", CMD_CHEAT_LIST);
    printfc(CLR3, "-  inspect your opponent at any time by pressing");
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
    // Start first match
    clear_screen("ch33ter");
    struct Match match = match_new();
    int run = 1;
    while(run) {
        print_div();
        char input;
        if (USE_RAW_INPUT) {
            printfc(CLR6, "██████████████▛ Awaiting Input ▜▛ ");
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
        if (show_match) {
            match_print(&match);
            printfc(CLR1, "Gold: %d\n", state.gold);
        }
        // Check for match end
        match_check(&match, &state, cheats_list);
        if (state.gold < 0) {
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
            printfc(CLR2, "\nYou are brutally murdered for your inability to pay your debts.\n");
            print_div();
            run = 0;
            break; // end game
        }
        if (match.ended) {
            if (rand() % 3 == 0) {
                print_subtitle(CLR3, "found extra loot box!");
                printfc(CLR1, "After the last match you found\nan extra loot box in the dust!\n");
                to_continue();
                loot_box(&state, cheats_list);
            }
            if (rand() % 5 == 0) {
                print_subtitle(CLR3, "found a hacker!");
                printfc(CLR1, "After the last match you come across\na hacker who is willing to trade cheats for gold!\n");
                to_continue();
            }
            if (rand() % 5 == 0) {
                print_subtitle(CLR3, "found a patron!");
                printfc(CLR1, "After the last match you come across\na patron who likes the way you play!\n");
                int gives = rand() % 5 + 1;
                printfc(CLR1, "They give you %d gold!\n", gives);
                state.gold += gives;
                to_continue();
            }
            if (rand() % 5 == 0) {
                print_subtitle(CLR3, "found a patron hacker!");
                printfc(CLR1, "After the last match you come across\na patron hacker who likes the way you play!\n");
                printfc(CLR1, "They give you a loot box!\n");
                to_continue();
                loot_box(&state, cheats_list);
            }
            if (rand() % 5 == 0) {
                print_subtitle(CLR2, "found a thief!");
                printfc(CLR1, "After the last match you are assaulted by\na thief who looks mean!\n");
                int takes = rand() % 5 + 1;
                printfc(CLR1, "They take %d gold from you!\n", takes);
                state.gold -= takes;
                if (state.gold < 0) {
                    printfc(CLR1, "They feel a little bad about taking your last gold.\n");
                    printfc(CLR1, "They give you one piece back!\n");
                    state.gold = 1;
                }
                to_continue();
            }
            if (rand() % 5 == 0) {
                print_subtitle(CLR2, "found a hacking thief!");
                printfc(CLR1, "After the last match you are assaulted by\na hacking thief who looks kinda wimpy!\n");
                printfc(CLR1, "But they have some 'hitek' hacking tools!\n");
                int slot = rand() % state.cheats_cap;
                printfc(CLR1, "They try to take the cheat in slot %d", slot + 1);
                if (state.cheats[slot] != -1) {
                    printfc(CLR1, "\nand they get it!\n");
                    cheat_print(&cheats_list[state.cheats[slot]]);
                    state.cheats[slot] = -1;
                }
                else {
                    printfc(CLR1, "\nbut you have no cheats in that slot!\n");
                }
                to_continue();
            }  
            match_start(&match);
        }
    }
    printfc(CLR1, "goodbye\n");
    return 0;
}