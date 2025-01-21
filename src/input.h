//
// Input
// Basic cross-platform input handling
//

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif

// Set console output to UTF-8 on windows
void set_console_output(){
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

// Get a single character of input
char input_get() {
    char input;
#if CFG_USE_RAW_INPUT 
    printfc(CRL7, "██████████████▛ Awaiting Input ▜▛ ");
#ifdef _WIN32
    input = _getch();
#else
    system("stty raw");
    input = getchar();
    system("stty cooked");
#endif
    clear_screen("ch33ter");   
#else
    printfc(CRL7, "██████████████▛ Awaiting Input ▜▛ ");
    scanf("%c", &input);
    // clear the buffer
    while(getchar() != '\n');
    clear_screen("ch33ter");
#endif
    return input;
}

void input_get_string(char text[], char *input) {
    printfc(CRL8, "%s", text);
    scanf("%s", input);
    // clear the buffer
    while(getchar() != '\n');
}

// Press any key to continue
void input_to_continue() {
    // Wait for user input
    printfc(CRL6, "\n\n██████████████       Press any key to continue       ██████████████\n");
#ifdef _WIN32
    _getch();
#else
    system("stty raw");
    getchar();
    system("stty cooked");
#endif
    clear_screen("ch33ter");
}