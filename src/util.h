//
// Utils
// General utilities for the program
//
enum Color { CLR1, CLR2, CLR3, CLR4, CLR5, CLR6, CLR7, CLR8 };
// Begin printing in the given color
void clr_start(enum Color color) {
    if (!ENABLE_COLORS) return;
    const char *codes[] = {CLR1_CODE, CLR2_CODE, CLR3_CODE, CLR4_CODE, CLR5_CODE, CLR6_CODE, CLR7_CODE, CLR8_CODE};
    printf("%s", codes[color]);
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
void print_logo() {
    printfc(CLR2, "       .__    ________ ________  __    \n");
    printfc(CLR3, "  ____ |  |__ \\_____  \\\\_____  \\/  |_  ___________\n");
    printfc(CLR4, "_/ ___\\|  |  \\  _(__  <  _(__  <   __\\/ __ \\_  __ \\\n");
    printfc(CLR5, "\\  \\___|   Y  \\/       \\/       \\  | \\  ___/|  | \\/\n");
    printfc(CLR6, " \\___  >___|  /______  /______  /__|  \\___  >__|   \n");
    printfc(CLR7, "     \\/     \\/       \\/       \\/          \\/       \n");
}
void print_win() {
    printfc(CLR2, " __      __.___ _______   \n");
    printfc(CLR3, "/  \\    /  \\   |\\      \\  \n");
    printfc(CLR4, "\\   \\/\\/   /   |/   |   \\ \n");
    printfc(CLR5, " \\        /|   /    |    \\ \n");
    printfc(CLR6, "  \\__/\\  / |___\\____|__  / \n");
    printfc(CLR7, "       \\/              \\/  \n");
}
void print_lose() {
    printfc(CLR2, ".____   _______    ___________________\n");
    printfc(CLR3, "|    |  \\   _  \\  /   _____|_   _____/\n");
    printfc(CLR4, "|    |  /  /_\\  \\ \\_____  \\ |    __)_ \n");
    printfc(CLR5, "|    |__\\  \\_/   \\/        \\|        \\\n");
    printfc(CLR6, "|_______ \\_____  /_______  /_______  /\n");
    printfc(CLR7, "        \\/     \\/        \\/        \\/ \n");
}
void print_draw() {
    printfc(CLR2, "________ __________    _____  __      __ \n");
    printfc(CLR3, "\\______ \\\\______   \\  /  _  \\/  \\    /  \\\n");
    printfc(CLR4, " |    |  \\|       _/ /  /_\\  \\   \\/\\/   /\n");
    printfc(CLR5, " |    `   \\    |   \\/    |    \\        / \n");
    printfc(CLR6, "/_______  /____|_  /\\____|__  /\\__/\\  /  \n");
    printfc(CLR7, "        \\/       \\/         \\/      \\/   \n");
}
void print_bust() {
    printfc(CLR2, "__________ ____ ___  ___________________\n");
    printfc(CLR3, "\\______   \\    |   \\/   _____|__    ___/\n");
    printfc(CLR4, " |    |  _/    |   /\\_____  \\  |    |   \n");
    printfc(CLR5, " |    |   \\    |  / /        \\ |    |   \n");
    printfc(CLR6, " |______  /______/ /_______  / |____|   \n");
    printfc(CLR7, "        \\/                 \\/           \n");
}
void print_slam() {
    printfc(CLR2, "  _________.____       _____      _____   \n");
    printfc(CLR3, " /   _____/|    |     /  _  \\    /     \\  \n");
    printfc(CLR4, " \\_____  \\ |    |    /  /_\\  \\  /  \\ /  \\ \n");
    printfc(CLR5, " /        \\|    |___/    |    \\/    Y    \\\n");
    printfc(CLR6, "/_______  /|_______ \\____|__  /\\____|__  /\n");
    printfc(CLR7, "        \\/         \\/       \\/         \\/ \n");
}
// Return a random number between 1 and sides
int roll_die(int sides) {
    return rand() % sides + 1;
}
