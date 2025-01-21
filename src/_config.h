//
// Config
// Use this config file to set the compile-time game configuration options
//

// General
#define USE_RAW_INPUT 1 // Set to false to use require enter key
#define ENABLE_COLORS 1 // Set to false to disable color printing
#define ENABLE_BELL 1 // Set to false to disable bell sound (must be enabled in the terminal as well)

// Command mapping
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

// Colors
#define CLR1_CODE "\033[1;90m" // grey
#define CLR2_CODE "\033[1;91m" // red
#define CLR3_CODE "\033[1;94m" // blue
#define CLR4_CODE "\033[1;32m" // green
#define CLR5_CODE "\033[1;33m" // yellow
#define CLR6_CODE "\033[1;95m" // magenta
#define CLR7_CODE "\033[1;96m" // cyan
#define CLR8_CODE "\033[1;97m" // white

// Random chances (1 in X)
#define CHANCE_BOSS 10
#define CHANCE_LOOT 3
#define CHANCE_VENDOR 1
#define CHANCE_PATRON 5
#define CHANCE_THIEF 8
#define CHANCE_FUZZ 13
#define CHANCE_STORY 99

// Vendor prices
#define MAX_SHOP_PRICE 33
#define SHOP_SCANNER_MULT 10
#define SHOP_CHEAT_SLOTS_MULT 4

// Starting values
#define STARTING_GOLD 10
#define STARTING_SCANNER_LVL 5
#define STARTING_CHEAT_SLOTS 4