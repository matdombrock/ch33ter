//
// Utils
// General utilities for the program
//
enum Color { CRL1, CRL2, CRL3, CRL4, CRL5, CRL6, CRL7, CRL8 };
// Begin printing in the given color
void clr_start(enum Color color) {
    if (!CFG_ENABLE_COLORS) return;
    const char *codes[] = {CFG_CRL1, CFG_CRL2, CFG_CRL3, CFG_CRL4, CFG_CRL5, CFG_CRL6, CFG_CRL7, CFG_CRL8};
    printf("%s", codes[color]);
}
// Stop printing in color
void clr_end() {
    if (!CFG_ENABLE_COLORS) return;
    printf("\033[0m");
}
// Print in color
// Example: printfc(CRL4, "Hello, %s!\n", "world");
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
    printfc(CRL4, "▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂  ▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂  ▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂\n");
}
// Print a title
void print_screen_title(char title[]) {
    if (CFG_ENABLE_BELL) printf("\a");
    printfc(CRL6, "█ %s ", title);
    for (int i = 0; i < TERM_WIDTH - strlen(title) - 2; i++) {
        printfc(CRL6, "█");
    }
    printfc(CRL1, "\n");
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
    printfc(CRL2, "       .__    ________ ________  __    \n");
    printfc(CRL3, "  ____ |  |__ \\_____  \\\\_____  \\/  |_  ___________\n");
    printfc(CRL4, "_/ ___\\|  |  \\  _(__  <  _(__  <   __\\/ __ \\_  __ \\\n");
    printfc(CRL5, "\\  \\___|   Y  \\/       \\/       \\  | \\  ___/|  | \\/\n");
    printfc(CRL6, " \\___  >___|  /______  /______  /__|  \\___  >__|   \n");
    printfc(CRL7, "     \\/     \\/       \\/       \\/          \\/       \n");
}
void print_win() {
    printfc(CRL2, " __      __.___ _______   \n");
    printfc(CRL3, "/  \\    /  \\   |\\      \\  \n");
    printfc(CRL4, "\\   \\/\\/   /   |/   |   \\ \n");
    printfc(CRL5, " \\        /|   /    |    \\ \n");
    printfc(CRL6, "  \\__/\\  / |___\\____|__  / \n");
    printfc(CRL7, "       \\/              \\/  \n");
}
void print_lose() {
    printfc(CRL2, ".____   _______    ___________________\n");
    printfc(CRL3, "|    |  \\   _  \\  /   _____|_   _____/\n");
    printfc(CRL4, "|    |  /  /_\\  \\ \\_____  \\ |    __)_ \n");
    printfc(CRL5, "|    |__\\  \\_/   \\/        \\|        \\\n");
    printfc(CRL6, "|_______ \\_____  /_______  /_______  /\n");
    printfc(CRL7, "        \\/     \\/        \\/        \\/ \n");
}
void print_draw() {
    printfc(CRL2, "________ __________    _____  __      __ \n");
    printfc(CRL3, "\\______ \\\\______   \\  /  _  \\/  \\    /  \\\n");
    printfc(CRL4, " |    |  \\|       _/ /  /_\\  \\   \\/\\/   /\n");
    printfc(CRL5, " |    `   \\    |   \\/    |    \\        / \n");
    printfc(CRL6, "/_______  /____|_  /\\____|__  /\\__/\\  /  \n");
    printfc(CRL7, "        \\/       \\/         \\/      \\/   \n");
}
void print_bust() {
    printfc(CRL2, "__________ ____ ___  ___________________\n");
    printfc(CRL3, "\\______   \\    |   \\/   _____|__    ___/\n");
    printfc(CRL4, " |    |  _/    |   /\\_____  \\  |    |   \n");
    printfc(CRL5, " |    |   \\    |  / /        \\ |    |   \n");
    printfc(CRL6, " |______  /______/ /_______  / |____|   \n");
    printfc(CRL7, "        \\/                 \\/           \n");
}
void print_slam() {
    printfc(CRL2, "  _________.____       _____      _____   \n");
    printfc(CRL3, " /   _____/|    |     /  _  \\    /     \\  \n");
    printfc(CRL4, " \\_____  \\ |    |    /  /_\\  \\  /  \\ /  \\ \n");
    printfc(CRL5, " /        \\|    |___/    |    \\/    Y    \\\n");
    printfc(CRL6, "/_______  /|_______ \\____|__  /\\____|__  /\n");
    printfc(CRL7, "        \\/         \\/       \\/         \\/ \n");
}
// Return a random number between 1 and sides
int roll_die(int sides) {
    return rand() % sides + 1;
}
