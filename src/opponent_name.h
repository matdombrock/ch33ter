//
// Opponent Names
// A list of possible opponent names and a function to get a random one.
//
// Get a random opponent name
const char opponent_names[][64] = {
    "archalis",
    "alaniel",
    "bertule",
    "betruel" 
    "chalistis",
    "caldel", 
    "dalth", 
    "daldor",
    "erdwin",
    "eoldor", 
    "flen", 
    "faldor",
    "galdor",
    "gailiel", 
    "haldor", 
    "hendel",
    "isandul",
    "ioldor",
    "jaldor",
    "Jilden", 
    "kaldor",
    "kilandor", 
    "lailer",
    "luldor",
    "miike", 
    "maldrik",
    "nilandor",
    "nunder", 
    "oldwald",
    "oaldor", 
    "paldor",
    "pilel", 
    "quildor",
    "qualdor", 
    "raldor",
    "rildor", 
    "saldor",
    "siminel",
    "taldor",
    "teatul",
    "uoldor", 
    "uundil",
    "vildor",
    "valdirk", 
    "waldor",
    "wamil",
    "xildor", 
    "xutul",
    "yooldor",
    "yaldil", 
    "zandor",
    "zilfden",
};
void opponent_name_rand(char *name) {
    strcpy(name, opponent_names[rand() % (sizeof(opponent_names) / sizeof(opponent_names[0]))]);
}