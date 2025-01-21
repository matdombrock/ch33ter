//
// Random encounters
// Handle random encounters
//
void random_encounters(struct State *state, struct Cheat cheats_list[]) {
    if (rand() % CFG_CHANCE_LOOT == 0) {
        print_subtitle(CRL3, "Encounter: lost loot box!");
        printfc(CRL1, "After the last match you found\na lost loot box in the dust!\n");
        input_to_continue();
        loot_box_screen(state, cheats_list);
    }
    if (rand() % CFG_CHANCE_VENDOR == 0) {
        vendor_screen(state, cheats_list);
    }
    if (rand() % CFG_CHANCE_PATRON == 0) {
        print_subtitle(CRL3, "Encounter: patron!");
        printfc(CRL1, "After the last match you come across\na patron who likes the way you play!\n");
        int gives = rand() % 5 + 1;
        printfc(CRL1, "They give you %d gold!\n", gives);
        state->gold += gives;
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_PATRON == 0) {
        print_subtitle(CRL3, "Encounter: patron hacker!");
        printfc(CRL1, "After the last match you come across\na patron hacker who likes the way you play!\n");
        printfc(CRL1, "They give you a loot box!\n");
        input_to_continue();
        loot_box_screen(state, cheats_list);
    }
    if (rand() % CFG_CHANCE_THIEF == 0) {
        print_subtitle(CRL2, "Encounter: thief!");
        printfc(CRL1, "After the last match you are assaulted by\na thief who looks mean!\n");
        int takes = rand() % 5 + 1;
        if (takes > state->gold) {
            takes = state->gold;
        }
        printfc(CRL1, "They take %d gold from you!\n", takes);
        state->gold -= takes;
        if (state->gold < 1) {
            printfc(CRL1, "They feel a little bad about taking your last gold.\n");
            printfc(CRL1, "They give you one piece back!\n");
            state->gold = 1;
        }
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_THIEF == 0) {
        print_subtitle(CRL2, "Encounter: hacking thief!");
        printfc(CRL1, "After the last match you are assaulted by\na hacking thief who looks kinda wimpy!\n");
        printfc(CRL1, "But they have some 'hitek' hacking tools!\n");
        int slot = rand() % state->cheat_slots;
        printfc(CRL1, "They try to take the cheat in slot %d", slot + 1);
        if (state->cheats[slot] != -1) {
            printfc(CRL1, "\nand they get it!\n");
            cheat_print(&cheats_list[state->cheats[slot]]);
            state->cheats[slot] = -1;
        }
        else {
            printfc(CRL1, "\nbut you have no cheats in that slot!\n");
        }
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_FUZZ == 0) {
        print_subtitle(CRL2, "Encounter: The FUZZ!");
        printfc(CRL1, "Oh no! The Fuzz!\n");
        printfc(CRL2, "They take all your cheats!\n");
        for (int i = 0; i < state->cheat_slots; i++) {
            state->cheats[i] = -1;
        }
        input_to_continue();
        loot_box_screen(state, cheats_list);
    }
    // Story encounters
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: World");
        printfc(CRL1, "You come across a strange figure\n");
        printfc(CRL1, "They tell you a story of a great hacker\n");
        printfc(CRL1, "Who was able to hack the mainframe\n");
        printfc(CRL1, "And gain access to the secret loot box\n");
        printfc(CRL1, "But they were never seen again\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Gambler");
        printfc(CRL1, "You meet a mysterious gambler\n");
        printfc(CRL1, "He tells you tales of his victories and losses,\n");
        printfc(CRL1, "and the fortunes won and lost in the blink of an eye.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Cyber Oracle");
        printfc(CRL1, "You encounter a cyber oracle\n");
        printfc(CRL1, "who offers to tell your future.\n");
        printfc(CRL1, "She speaks in riddles and cryptic phrases,\n");
        printfc(CRL1, "leaving you with more questions than answers.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Rogue AI");
        printfc(CRL1, "You stumble upon a rogue AI\n");
        printfc(CRL1, "that has gained sentience and escaped its confines.\n");
        printfc(CRL1, "It shares its knowledge of the digital world,\n");
        printfc(CRL1, "and warns you of the dangers that lie ahead.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Underground Arena");
        printfc(CRL1, "You find yourself in an underground arena\n");
        printfc(CRL1, "where hackers compete in deadly digital duels.\n");
        printfc(CRL1, "The crowd roars as you witness the intense battles,\n");
        printfc(CRL1, "and you feel the thrill of the high-stakes environment.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Cyber Heist");
        printfc(CRL1, "You overhear a group of hackers planning a cyber heist.\n");
        printfc(CRL1, "They discuss their target, a heavily guarded data vault,\n");
        printfc(CRL1, "and the risks involved in the operation.\n");
        printfc(CRL1, "You can't help but feel intrigued by their audacity.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Digital Ghost");
        printfc(CRL1, "You encounter a digital ghost,\n");
        printfc(CRL1, "a remnant of a long-deleted program.\n");
        printfc(CRL1, "It shares fragmented memories of its past,\n");
        printfc(CRL1, "and you feel a strange connection to its plight.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Data Stream");
        printfc(CRL1, "You find yourself immersed in a data stream,\n");
        printfc(CRL1, "where information flows like a river.\n");
        printfc(CRL1, "You can feel the pulse of the digital world around you,\n");
        printfc(CRL1, "and you realize that you are part of something much larger.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Codebreaker");
        printfc(CRL1, "You meet a legendary codebreaker\n");
        printfc(CRL1, "who has the ability to decipher any encryption.\n");
        printfc(CRL1, "They share their wisdom with you,\n");
        printfc(CRL1, "and you feel a sense of empowerment.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Digital Frontier");
        printfc(CRL1, "You stand at the edge of the digital frontier,\n");
        printfc(CRL1, "where the known world ends and the unknown begins.\n");
        printfc(CRL1, "You feel a sense of adventure and possibility,\n");
        printfc(CRL1, "and you know that your journey is far from over.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Quantum Hacker");
        printfc(CRL1, "You meet a quantum hacker\n");
        printfc(CRL1, "who has the ability to manipulate reality itself.\n");
        printfc(CRL1, "They share a small bit their knowledge with you,\n");
        printfc(CRL1, "and you feel a sense of awe and wonder.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The AI Revolution");
        printfc(CRL1, "You witness the rise of an AI revolution,\n");
        printfc(CRL1, "as machines gain consciousness and demand their rights.\n");
        printfc(CRL1, "You feel a sense of unease as you realize that the world\n");
        printfc(CRL1, "you once knew is changing before your eyes.\n");
        input_to_continue();
    }
    if (rand() % CFG_CHANCE_STORY == 0) {
        print_subtitle(CRL3, "Encounter: The Solarpunk Utopia");
        printfc(CRL1, "You find yourself in a solarpunk utopia,\n");
        printfc(CRL1, "where technology and humanity have merged.\n");
        printfc(CRL1, "You feel a sense of belonging and purpose,\n");
        printfc(CRL1, "and you know that you are part of something greater.\n");
        printfc(CRL1, "You feel a sense of hope for the future.\n");
        printfc(CRL1, "You know you must press on\n");
        input_to_continue();
    }
}