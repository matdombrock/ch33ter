#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

int roll_die(int sides) {
    return rand() % sides + 1;
}

struct Match {
    int player_total;
    int opponent_total;
    bool player_held;
    bool opponent_held;
    int turn;
    int die_sides;
};
struct Match match_new() {
    struct Match match;
    match.player_total = 0;
    match.opponent_total = 0;
    match.turn = 0;
    match.die_sides = 10;
    return match;
}
void match_check(struct Match *match) {
    if (match->player_total == 21) {
        printf("Player wins!\n");
        exit(0);
    }
    if (match->opponent_total == 21) {
        printf("Opponent wins!\n");
        exit(0);
    }
    if (match->player_total > 21) {
        printf("Player busts!\n");
        exit(0);
    }
    if (match->opponent_total > 21) {
        printf("Opponent busts!\n");
        exit(0);
    }
    if (match->player_held && match->opponent_held) {
        if (match->player_total > match->opponent_total) {
            printf("Player wins!\n");
        } else {
            printf("Opponent wins!\n");
        }
        exit(0);
    }
}

#define MAX_CHEATS 8

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
}
void cheats_init(struct Cheat *cheats) {
    cheats[0] = cheat_new("xxx");
    cheats[1] = cheat_new("xxx");
}

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
bool state_gain_cheat(struct State* state, int cheat_dict_index) {
    bool gained = false;
    for (int i = 0; i < state->cheats_cap; i++) {
        if (state->cheats[i] == -1) {
            gained = true;
            state->cheats[i] = cheat_dict_index;
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

void opponent_turn(struct Match *match) {
    if (match->opponent_total >= 17 && match->opponent_total >= match->player_total) {
        printf("Opponent Holds\n");
        match->opponent_held = true;
        return;
    }
    int roll = roll_die(match->die_sides);
    match->opponent_total += roll;
    match->opponent_held = false;
    printf("Opponent Rolls: %d\n", roll);
}

void cmd_roll(struct Match *match) {
    int roll = roll_die(match->die_sides);
    match->player_total += roll;
    match->turn++;
    printf("Player Rolls: %d\n", roll);
    opponent_turn(match);
    match->player_held = false;
}

void cmd_hold(struct Match *match) {
    match->player_held = true;
    printf("Player Holds\n");
    opponent_turn(match);
    match->player_held = true;
}

void cmd_cheat_list(struct State *state, struct Cheat cheats[]) {
    for (int i = 0; i < state->cheats_cap; i++) {
        if (state->cheats[i] != -1) printf("%d.%s \n", i, cheats[state->cheats[i]].name);
    }
    printf("\n");
}

void clear_screen() {
    // C;ear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    int seed = time(NULL);
    srand(seed);
    struct State state = state_new();
    struct Match match = match_new();
    struct Cheat cheats[32];
    cheats_init(cheats);
    // state_gain_cheat(&state, 1);
    int run = 1;
    while(run) {
        char input;
        printf(">> ");
        scanf("%c", &input);
        printf("cheat %s", cheats[0].name);
        // clear the buffer
        while(getchar() != '\n');
        clear_screen();
        switch (input) {
            case 'r':
                cmd_roll(&match);
                break;
            case 'h':
                cmd_hold(&match);
                break;
            case 'c':
                cmd_cheat_list(&state, cheats);
                break;
            case 'q':
                run = 0;
                break;
            default:
                printf("Invalid input\n");
        }
        printf("Player: %d\nOpponent: %d\n", match.player_total, match.opponent_total);
        // Check for match end
        match_check(&match);
    }
    printf("goodbye\n");
    return 0;
}