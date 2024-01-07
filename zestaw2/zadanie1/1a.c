#include <stdio.h>
#include <stdbool.h>

///////////////////////////

typedef struct {
    char player_name[50];
    char character_name[50];
    char character_class[50];
    int character_level;
    int character_hp;
} Player;

///////////////////////////

int ReadPlayersFromCSV(const char *input_file, Player players[50], bool debug);
void PrintPlayers(Player *players, int records);

///////////////////////////

int main(void)
{
    Player players[50];
    int records = ReadPlayersFromCSV("players.txt", players, true);
    if (records < 0) return 1;

    PrintPlayers(players, records);

    return 0;
}

///////////////////////////

int ReadPlayersFromCSV(const char *input_file, Player players[50], bool debug) {
    FILE *file;
    file = fopen(input_file, "r");
    if (file == NULL)
    {
        printf("BLAD: problem z otwarciem pliku.\n");
        return -1;
    }

    int read = 0;
    int records = 0;
    do {
        read = fscanf(file,
                        "%49[^,],%49[^,],%49[^,],%d,%d\n",
                        players[records].player_name,
                        players[records].character_name,
                        players[records].character_class,
                        &players[records].character_level,
                        &players[records].character_hp);

        if (read == 5) records++;
        else if (!feof(file)) {
            printf("BLAD: format pliku niepoprawny.\n");
            return -2;
        }
        if (ferror(file))
        {
            printf("BLAD: problem w trakcie czytania pliku\n");
            return -3;
        }
    } while (!feof(file));

    fclose(file);

    if (debug) printf("\n%d wczytanych rekordow\n\n", records);

    return records;
}

///////////////////////////

void PrintPlayers(Player *players, int records) {
    for (int i = 0; i < records; i++)
        printf("%s %s %s %d %d\n",
                players[i].player_name,
                players[i].character_name,
                players[i].character_class,
                players[i].character_level,
                players[i].character_hp);
}