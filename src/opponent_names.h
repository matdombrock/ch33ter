//
// Opponent Names
//
// Get a random opponent name
void opponent_name_rand(char *name) {
    char opponent_names[][64] = {"archalis", "bertule", "chalistis", "dalth", "erdwin", "flen", "galdor", "haldor", "isandul", "jaldor", "kaldor", "lailer", "miike", "nilandor", "oldwald", "paldor", "quildor", "raldor", "saldor", "taldor", "uoldor", "vildor", "waldor", "xildor", "yooldor", "zandor"};
    strcpy(name, opponent_names[rand() % 26]);
}