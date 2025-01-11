//
// Input
//
// Get a single character of input
char get_input() {
    char input;
    if (USE_RAW_INPUT) {
        printfc(CLR7, "██████████████▛ Awaiting Input ▜▛ ");
        system("stty raw");
        input = getchar();
        system("stty cooked");
        clear_screen("ch33ter");   
    }
    else {
        printfc(CLR7, "██████████████▛ Awaiting Input ▜▛ ");
        scanf("%c", &input);
        // clear the buffer
        while(getchar() != '\n');
        clear_screen("ch33ter");
    }
    return input;
}
void get_input_string(char text[], char *input) {
    printfc(CLR8, "%s", text);
    scanf("%s", input);
    // clear the buffer
    while(getchar() != '\n');
}
// Press any key to continue
void to_continue() {
    // Wait for user input
    printfc(CLR6, "\n\n██████████████       Press any key to continue       ██████████████\n");
    system("stty raw");
    getchar();
    system("stty cooked");
    clear_screen("ch33ter");
}