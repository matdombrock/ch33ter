//
// Config
// Use this config file to set the compile-time game configuration options
//

// General
#define CFG_USE_RAW_INPUT 1 // Set to false to use require enter key
#define CFG_ENABLE_COLORS 1 // Set to false to disable color printing
#define CFG_ENABLE_BELL 1 // Set to false to disable bell sound (must be enabled in the terminal as well)

// Command mapping
#define CFG_CMD_ROLL 'r'
#define CFG_CMD_HOLD 'w'
#define CFG_CMD_CHEAT_LIST 'e'
#define CFG_CMD_OPPONENT 'q'
#define CFG_CMD_STATUS 's'
#define CFG_CMD_QUIT 'c'
#define CFG_CMD_HELP 'h'
#define CFG_CMD_USE_CHEAT_1 '1'
#define CFG_CMD_USE_CHEAT_2 '2'
#define CFG_CMD_USE_CHEAT_3 '3'
#define CFG_CMD_USE_CHEAT_4 '4'
#define CFG_CMD_USE_CHEAT_5 '5'
#define CFG_CMD_USE_CHEAT_6 '6'
#define CFG_CMD_USE_CHEAT_7 '7'
#define CFG_CMD_USE_CHEAT_8 '8'

// Colors
#define CFG_CLR1 "\033[1;90m" // grey
#define CFG_CLR2 "\033[1;91m" // red
#define CFG_CLR3 "\033[1;94m" // blue
#define CFG_CLR4 "\033[1;32m" // green
#define CFG_CLR5 "\033[1;33m" // yellow
#define CFG_CLR6 "\033[1;95m" // magenta
#define CFG_CLR7 "\033[1;96m" // cyan
#define CFG_CLR8 "\033[1;97m" // white

// Random chances (1 in X)
#define CFG_CHANCE_BOSS 10
#define CFG_CHANCE_LOOT 3
#define CFG_CHANCE_VENDOR 5
#define CFG_CHANCE_PATRON 5
#define CFG_CHANCE_THIEF 8
#define CFG_CHANCE_FUZZ 13
#define CFG_CHANCE_STORY 99

// Vendor prices
#define CFG_MAX_SHOP_PRICE 33
#define CFG_SHOP_SCANNER_MULT 10
#define CFG_SHOP_CHEAT_SLOTS_MULT 4

// Starting values
#define CFG_STARTING_GOLD 10
#define CFG_STARTING_SCANNER_LVL 0
#define CFG_STARTING_CHEAT_SLOTS 4