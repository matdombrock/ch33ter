//
// Utils
// General utilities for the program
//
enum Color { CFG_CLR1, CFG_CLR2, CFG_CLR3, CFG_CLR4, CFG_CLR5, CFG_CLR6, CFG_CLR7, CFG_CLR8 };
// Begin printing in the given color
void clr_start(enum Color color) {
    if (!CFG_ENABLE_COLORS) return;
    const char *codes[] = {CFG_CLR1_CODE, CFG_CLR2_CODE, CFG_CLR3_CODE, CFG_CLR4_CODE, CFG_CLR5_CODE, CFG_CLR6_CODE, CFG_CLR7_CODE, CFG_CLR8_CODE};
    printf("%s", codes[color]);
}
// Stop printing in color
void clr_end() {
    if (!CFG_ENABLE_COLORS) return;
    printf("\033[0m");
}
// Print in color
// Example: printfc(CFG_CLR4, "Hello, %s!\n", "world");
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
    printfc(CFG_CLR4, "▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂  ▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂  ▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂\n");
}
// Print a title
void print_screen_title(char title[]) {
    if (CFG_ENABLE_BELL) printf("\a");
    printfc(CFG_CLR6, "█ %s ", title);
    for (int i = 0; i < TERM_WIDTH - strlen(title) - 2; i++) {
        printfc(CFG_CLR6, "█");
    }
    printfc(CFG_CLR1, "\n");
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
void print_logo() {
    printfc(CFG_CLR2, "       .__    ________ ________  __    \n");
    printfc(CFG_CLR3, "  ____ |  |__ \\_____  \\\\_____  \\/  |_  ___________\n");
    printfc(CFG_CLR4, "_/ ___\\|  |  \\  _(__  <  _(__  <   __\\/ __ \\_  __ \\\n");
    printfc(CFG_CLR5, "\\  \\___|   Y  \\/       \\/       \\  | \\  ___/|  | \\/\n");
    printfc(CFG_CLR6, " \\___  >___|  /______  /______  /__|  \\___  >__|   \n");
    printfc(CFG_CLR7, "     \\/     \\/       \\/       \\/          \\/       \n");
}
void print_win() {
    printfc(CFG_CLR2, " __      __.___ _______   \n");
    printfc(CFG_CLR3, "/  \\    /  \\   |\\      \\  \n");
    printfc(CFG_CLR4, "\\   \\/\\/   /   |/   |   \\ \n");
    printfc(CFG_CLR5, " \\        /|   /    |    \\ \n");
    printfc(CFG_CLR6, "  \\__/\\  / |___\\____|__  / \n");
    printfc(CFG_CLR7, "       \\/              \\/  \n");
}
void print_lose() {
    printfc(CFG_CLR2, ".____   _______    ___________________\n");
    printfc(CFG_CLR3, "|    |  \\   _  \\  /   _____|_   _____/\n");
    printfc(CFG_CLR4, "|    |  /  /_\\  \\ \\_____  \\ |    __)_ \n");
    printfc(CFG_CLR5, "|    |__\\  \\_/   \\/        \\|        \\\n");
    printfc(CFG_CLR6, "|_______ \\_____  /_______  /_______  /\n");
    printfc(CFG_CLR7, "        \\/     \\/        \\/        \\/ \n");
}
void print_draw() {
    printfc(CFG_CLR2, "________ __________    _____  __      __ \n");
    printfc(CFG_CLR3, "\\______ \\\\______   \\  /  _  \\/  \\    /  \\\n");
    printfc(CFG_CLR4, " |    |  \\|       _/ /  /_\\  \\   \\/\\/   /\n");
    printfc(CFG_CLR5, " |    `   \\    |   \\/    |    \\        / \n");
    printfc(CFG_CLR6, "/_______  /____|_  /\\____|__  /\\__/\\  /  \n");
    printfc(CFG_CLR7, "        \\/       \\/         \\/      \\/   \n");
}
void print_bust() {
    printfc(CFG_CLR2, "__________ ____ ___  ___________________\n");
    printfc(CFG_CLR3, "\\______   \\    |   \\/   _____|__    ___/\n");
    printfc(CFG_CLR4, " |    |  _/    |   /\\_____  \\  |    |   \n");
    printfc(CFG_CLR5, " |    |   \\    |  / /        \\ |    |   \n");
    printfc(CFG_CLR6, " |______  /______/ /_______  / |____|   \n");
    printfc(CFG_CLR7, "        \\/                 \\/           \n");
}
void print_slam() {
    printfc(CFG_CLR2, "  _________.____       _____      _____   \n");
    printfc(CFG_CLR3, " /   _____/|    |     /  _  \\    /     \\  \n");
    printfc(CFG_CLR4, " \\_____  \\ |    |    /  /_\\  \\  /  \\ /  \\ \n");
    printfc(CFG_CLR5, " /        \\|    |___/    |    \\/    Y    \\\n");
    printfc(CFG_CLR6, "/_______  /|_______ \\____|__  /\\____|__  /\n");
    printfc(CFG_CLR7, "        \\/         \\/       \\/         \\/ \n");
}
// Return a random number between 1 and sides
int roll_die(int sides) {
    return rand() % sides + 1;
}
