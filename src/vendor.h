// Purchase from the vendor
void vendor_purchase_screen(struct State *state, struct Cheat cheats_list[], int *cheat_index, int *cheat_price) {
    clear_screen("Purchasing");
    printfc(CLR4, "You ask to purchase %s\n", cheats_list[cheat_index[0]].name);
    if (state_count_cheats(state) >= state->cheat_slots) {
        printfc(CLR2, "But you have no more cheat slots available!\n");
    }
    else if (state->gold >= cheat_price[0]) {
        state->gold -= cheat_price[0];
        state_attempt_gain_cheat(state, cheats_list, cheat_index[0]);
        cheat_index[0] = rand() % CHEATS_AMT;
        cheat_index[0] = rand() % CFG_MAX_SHOP_PRICE + 1;
    }
    else {
        printfc(CLR2, "But you dont have enough gold! (missing: %d)\n", cheat_price[0] - state->gold);
    }
    cheat_print(&cheats_list[cheat_index[0]]);
    print_div();
    state_print_cheats(state, cheats_list);
    state_print_gold(state);
    input_to_continue();
}

void vendor_screen(struct State *state, struct Cheat cheats_list[]) {
    print_subtitle(CLR3, "Encounter: hacker vendor!");
    printfc(CLR1, "After the last match you come across\na hacker who is willing to trade cheats for gold!\n");
    input_to_continue();
    int cheat_index[4];
    cheat_index[0] = rand() % CHEATS_AMT;
    cheat_index[1] = rand() % CHEATS_AMT;
    cheat_index[2] = rand() % CHEATS_AMT;
    cheat_index[3] = rand() % CHEATS_AMT;
    int cheat_price[4];
    cheat_price[0] = rand() % CFG_MAX_SHOP_PRICE + 1;
    cheat_price[1] = rand() % CFG_MAX_SHOP_PRICE + 1;
    cheat_price[2] = rand() % CFG_MAX_SHOP_PRICE + 1;
    cheat_price[3] = rand() % CFG_MAX_SHOP_PRICE + 1;
    bool in_shop = 1;
    while(in_shop) {
        // update prices
        int scanner_price = CFG_SHOP_SCANNER_MULT * ((state->scanner_lvl + 1) * (state->scanner_lvl + 1));
        int cheat_slots_price = CFG_SHOP_CHEAT_SLOTS_MULT * (state->cheat_slots * state->cheat_slots);
        if (state->scanner_lvl >= SCAN_LVL_MAX) scanner_price = 999999;
        if (state->cheat_slots >= MAX_CHEAT_SLOTS) cheat_slots_price = 999999;
        clear_screen("Hacker Vendor");
        state_print_gold(state);
        state_print_open_cheat_slots(state);
        printfc(CLR1, "-------\n");
        printfc(CLR1, "Goods: \n");
        printfc(CLR1, "1. $%d - ", cheat_price[0]);
        cheat_print(&cheats_list[cheat_index[0]]);
        printfc(CLR1, "2. $%d - ", cheat_price[1]);
        cheat_print(&cheats_list[cheat_index[1]]);
        printfc(CLR1, "3. $%d - ", cheat_price[2]);
        cheat_print(&cheats_list[cheat_index[2]]);
        printfc(CLR1, "4. $%d - ", cheat_price[3]);
        cheat_print(&cheats_list[cheat_index[3]]);
        printfc(CLR1, "5. $10 - loot box\n");
        printfc(CLR1, "6. $%d - Upgrade scanner\n", scanner_price);
        printfc(CLR1, "7. $%d - Upgrade cheat slots\n", cheat_slots_price);
        printfc(CLR1, "8. $1 - Coin flip\n");
        printfc(CLR1, "9. $10 - Coin flip\n");
        printfc(CLR1, "0. Sell Cheats\n");
        printfc(CLR2, "\nPress %c to exit\n", CFG_CMD_QUIT);
        char input = input_get();
        printfc(CLR1, "%c\n", input);
        switch(input) {
            case CFG_CMD_QUIT:
                in_shop = 0;
                break;
            case '1':
                vendor_purchase_screen(state, cheats_list, &cheat_index[0], &cheat_price[0]);
                break;
            case '2':
                vendor_purchase_screen(state, cheats_list, &cheat_index[1], &cheat_price[1]);
                break;
            case '3':
                vendor_purchase_screen(state, cheats_list, &cheat_index[2], &cheat_price[2]);
                break;
            case '4':
                vendor_purchase_screen(state, cheats_list, &cheat_index[3], &cheat_price[3]);
                break;
            case '5':
                clear_screen("Purchase");
                printfc(CLR4, "You ask to purchase a loot box\n");
                if (state->gold >= 10) {
                    state->gold -= 10;
                    loot_box_screen(state, cheats_list);
                }
                else {
                    printfc(CLR2, "But you dont have enough gold! (missing: %d)\n", 2 - state->gold);
                    print_div();
                    state_print_gold(state);
                    input_to_continue();
                }
                break;
            case '6':
                clear_screen("Scanner Upgrade");
                printfc(CLR4, "You ask to upgrade your scanner\n");
                if (state->scanner_lvl >= SCAN_LVL_MAX) {
                    printfc(CLR2, "But your scanner is already at max level!\n");
                }
                else if (state->gold >= scanner_price) {
                    state->gold -= scanner_price;
                    state->scanner_lvl++;
                    printfc(CLR8, "Scanner upgraded!\n");
                }
                else {
                    printfc(CLR2, "But you dont have enough gold! (missing: %d)\n", 10 - state->gold);
                }
                state_print_scanner_lvl(state);
                state_print_gold(state);
                input_to_continue();
                break;
            case '7':
                clear_screen("Cheat Slot Upgrade");
                printfc(CLR4, "You ask to upgrade your cheat slots\n");
                if (state->cheat_slots >= MAX_CHEAT_SLOTS) {
                    printfc(CLR2, "But your cheat slots are already at max level!\n");
                }
                else if (state->gold >= cheat_slots_price) {
                    state->gold -= cheat_slots_price;
                    state->cheat_slots++;
                    printfc(CLR8, "Cheat slots upgraded!\n");
                }
                else {
                    printfc(CLR2, "But you dont have enough gold! (missing: %d)\n", 15 - state->gold);
                }
                state_print_cheat_slots(state);
                state_print_gold(state);
                input_to_continue();
                break;
            case '8':
                coin_flip_screen(1, state);
                break;
            case '9':
                coin_flip_screen(10, state);
                break;
            case '0':
                clear_screen("Selling");
                printfc(CLR4, "You ask to sell cheats\n");
                state_print_cheats(state, cheats_list);
                printfc(CLR4, "Which cheat would you like to sell?\n");
                printfc(CLR2, "\nPress %c to exit\n", CFG_CMD_QUIT);
                char slotc = input_get();
                if (slotc == CFG_CMD_QUIT) break;
                clear_screen("Selling");
                int slot = slotc - '0' - 1;// offset by ascii
                int price = rand() % (CFG_MAX_SHOP_PRICE / 3) + 1;
                if (slot >= 0 && slot < state->cheat_slots) {
                    if (state->cheats[slot] != -1) {
                        printfc(CLR4, "You sold: ");
                        cheat_print(&cheats_list[state->cheats[slot]]);
                        printfc(CLR4, "For %d gold!\n", price);
                        state->gold += price;
                        state->cheats[slot] = -1;
                    }
                    else {
                        printfc(CLR2, "But there is no cheat in that slot!\n");
                    }
                }
                else {
                    printfc(CLR2, "Invalid input\n");
                }
                state_print_gold(state);
                input_to_continue();
                break;
            default:
                clear_screen("Invalid Input");
                printfc(CLR2, "Input not recognized\n");
                printfc(CLR3, "\nPress %c at vendor screen to quit\n", CFG_CMD_QUIT);
                input_to_continue();
                break;
        }
    }
    clear_screen("Exit Vendor");
    printfc(CLR4, "You exit the vendor\n");
    state_print_status(state, 1);
    state_print_cheats(state, cheats_list);
    input_to_continue();
}