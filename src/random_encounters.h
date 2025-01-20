//
// Random encounters
// Handle random encounters
//
void random_encounters(struct State *state, struct Cheat cheats_list[]) {
    if (rand() % CHANCE_LOOT == 0) {
        print_subtitle(CLR3, "Encounter: lost loot box!");
        printfc(CLR1, "After the last match you found\na lost loot box in the dust!\n");
        input_to_continue();
        loot_box_screen(state, cheats_list);
    }
    if (rand() % CHANCE_VENDOR == 0) {
        print_subtitle(CLR3, "Encounter: hacker vendor!");
        printfc(CLR1, "After the last match you come across\na hacker who is willing to trade cheats for gold!\n");
        input_to_continue();
        int cheat_index[4];
        cheat_index[0] = rand() % CHEATS_AMT;
        cheat_index[1] = rand() % CHEATS_AMT;
        cheat_index[2] = rand() % CHEATS_AMT;
        cheat_index[3] = rand() % CHEATS_AMT;
        int cheat_price[4];
        cheat_price[0] = rand() % MAX_SHOP_PRICE + 1;
        cheat_price[1] = rand() % MAX_SHOP_PRICE + 1;
        cheat_price[2] = rand() % MAX_SHOP_PRICE + 1;
        cheat_price[3] = rand() % MAX_SHOP_PRICE + 1;
        bool in_shop = 1;
        while(in_shop) {
            // update prices
            int scanner_price = 10 * state->scanner_lvl;
            int cheat_slots_price = 15 * state->cheat_slots;
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
            printfc(CLR2, "\nPress %c to exit\n", CMD_QUIT);
            char input = input_get();
            printfc(CLR1, "%c\n", input);
            switch(input) {
                case CMD_QUIT:
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
                    printfc(CLR2, "\nPress %c to exit\n", CMD_QUIT);
                    char slotc = input_get();
                    if (slotc == CMD_QUIT) break;
                    clear_screen("Selling");
                    int slot = slotc - '0' - 1;// offset by ascii
                    int price = rand() % (MAX_SHOP_PRICE / 3) + 1;
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
                    printfc(CLR3, "\nPress %c at vendor screen to quit\n", CMD_QUIT);
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
    if (rand() % CHANCE_PATRON == 0) {
        print_subtitle(CLR3, "Encounter: patron!");
        printfc(CLR1, "After the last match you come across\na patron who likes the way you play!\n");
        int gives = rand() % 5 + 1;
        printfc(CLR1, "They give you %d gold!\n", gives);
        state->gold += gives;
        input_to_continue();
    }
    if (rand() % CHANCE_PATRON == 0) {
        print_subtitle(CLR3, "Encounter: patron hacker!");
        printfc(CLR1, "After the last match you come across\na patron hacker who likes the way you play!\n");
        printfc(CLR1, "They give you a loot box!\n");
        input_to_continue();
        loot_box_screen(state, cheats_list);
    }
    if (rand() % CHANCE_THIEF == 0) {
        print_subtitle(CLR2, "Encounter: thief!");
        printfc(CLR1, "After the last match you are assaulted by\na thief who looks mean!\n");
        int takes = rand() % 5 + 1;
        if (takes > state->gold) {
            takes = state->gold;
        }
        printfc(CLR1, "They take %d gold from you!\n", takes);
        state->gold -= takes;
        if (state->gold < 1) {
            printfc(CLR1, "They feel a little bad about taking your last gold.\n");
            printfc(CLR1, "They give you one piece back!\n");
            state->gold = 1;
        }
        input_to_continue();
    }
    if (rand() % CHANCE_THIEF == 0) {
        print_subtitle(CLR2, "Encounter: hacking thief!");
        printfc(CLR1, "After the last match you are assaulted by\na hacking thief who looks kinda wimpy!\n");
        printfc(CLR1, "But they have some 'hitek' hacking tools!\n");
        int slot = rand() % state->cheat_slots;
        printfc(CLR1, "They try to take the cheat in slot %d", slot + 1);
        if (state->cheats[slot] != -1) {
            printfc(CLR1, "\nand they get it!\n");
            cheat_print(&cheats_list[state->cheats[slot]]);
            state->cheats[slot] = -1;
        }
        else {
            printfc(CLR1, "\nbut you have no cheats in that slot!\n");
        }
        input_to_continue();
    }
    if (rand() % CHANCE_FUZZ == 0) {
        print_subtitle(CLR2, "Encounter: The FUZZ!");
        printfc(CLR1, "Oh no! The Fuzz!\n");
        printfc(CLR2, "They take all your cheats!\n");
        for (int i = 0; i < state->cheat_slots; i++) {
            state->cheats[i] = -1;
        }
        input_to_continue();
        loot_box_screen(state, cheats_list);
    }
    // Story encounters
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: World");
        printfc(CLR1, "You come across a strange figure\n");
        printfc(CLR1, "They tell you a story of a great hacker\n");
        printfc(CLR1, "Who was able to hack the mainframe\n");
        printfc(CLR1, "And gain access to the secret loot box\n");
        printfc(CLR1, "But they were never seen again\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Gambler");
        printfc(CLR1, "You meet a mysterious gambler\n");
        printfc(CLR1, "He tells you tales of his victories and losses,\n");
        printfc(CLR1, "and the fortunes won and lost in the blink of an eye.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Cyber Oracle");
        printfc(CLR1, "You encounter a cyber oracle\n");
        printfc(CLR1, "who offers to tell your future.\n");
        printfc(CLR1, "She speaks in riddles and cryptic phrases,\n");
        printfc(CLR1, "leaving you with more questions than answers.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Rogue AI");
        printfc(CLR1, "You stumble upon a rogue AI\n");
        printfc(CLR1, "that has gained sentience and escaped its confines.\n");
        printfc(CLR1, "It shares its knowledge of the digital world,\n");
        printfc(CLR1, "and warns you of the dangers that lie ahead.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Underground Arena");
        printfc(CLR1, "You find yourself in an underground arena\n");
        printfc(CLR1, "where hackers compete in deadly digital duels.\n");
        printfc(CLR1, "The crowd roars as you witness the intense battles,\n");
        printfc(CLR1, "and you feel the thrill of the high-stakes environment.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Cyber Heist");
        printfc(CLR1, "You overhear a group of hackers planning a cyber heist.\n");
        printfc(CLR1, "They discuss their target, a heavily guarded data vault,\n");
        printfc(CLR1, "and the risks involved in the operation.\n");
        printfc(CLR1, "You can't help but feel intrigued by their audacity.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Digital Ghost");
        printfc(CLR1, "You encounter a digital ghost,\n");
        printfc(CLR1, "a remnant of a long-deleted program.\n");
        printfc(CLR1, "It shares fragmented memories of its past,\n");
        printfc(CLR1, "and you feel a strange connection to its plight.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Data Stream");
        printfc(CLR1, "You find yourself immersed in a data stream,\n");
        printfc(CLR1, "where information flows like a river.\n");
        printfc(CLR1, "You can feel the pulse of the digital world around you,\n");
        printfc(CLR1, "and you realize that you are part of something much larger.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Codebreaker");
        printfc(CLR1, "You meet a legendary codebreaker\n");
        printfc(CLR1, "who has the ability to decipher any encryption.\n");
        printfc(CLR1, "They share their wisdom with you,\n");
        printfc(CLR1, "and you feel a sense of empowerment.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Digital Frontier");
        printfc(CLR1, "You stand at the edge of the digital frontier,\n");
        printfc(CLR1, "where the known world ends and the unknown begins.\n");
        printfc(CLR1, "You feel a sense of adventure and possibility,\n");
        printfc(CLR1, "and you know that your journey is far from over.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Quantum Hacker");
        printfc(CLR1, "You meet a quantum hacker\n");
        printfc(CLR1, "who has the ability to manipulate reality itself.\n");
        printfc(CLR1, "They share a small bit their knowledge with you,\n");
        printfc(CLR1, "and you feel a sense of awe and wonder.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The AI Revolution");
        printfc(CLR1, "You witness the rise of an AI revolution,\n");
        printfc(CLR1, "as machines gain consciousness and demand their rights.\n");
        printfc(CLR1, "You feel a sense of unease as you realize that the world\n");
        printfc(CLR1, "you once knew is changing before your eyes.\n");
        input_to_continue();
    }
    if (rand() % CHANCE_STORY == 0) {
        print_subtitle(CLR3, "Encounter: The Solarpunk Utopia");
        printfc(CLR1, "You find yourself in a solarpunk utopia,\n");
        printfc(CLR1, "where technology and humanity have merged.\n");
        printfc(CLR1, "You feel a sense of belonging and purpose,\n");
        printfc(CLR1, "and you know that you are part of something greater.\n");
        printfc(CLR1, "You feel a sense of hope for the future.\n");
        printfc(CLR1, "You know you must press on\n");
        input_to_continue();
    }
}