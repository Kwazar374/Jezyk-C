#include <stdio.h>
#include <stdlib.h>
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

int ReadPlayersFromCSV(const char *input_file, Player **players, bool debug);
void PrintPlayers(Player *players, int records);

///////////////////////////

int main(void)
{
    Player *players = NULL;
    int records = ReadPlayersFromCSV("players.txt", &players, true);
    if (records < 0) return 1;

    PrintPlayers(players, records);

    free(players);
    return 0;
}

///////////////////////////

int ReadPlayersFromCSV(const char *input_file, Player **players_ptr, bool debug) {
    FILE *file;
    file = fopen(input_file, "r");
    if (file == NULL)
    {
        printf("BLAD: problem z otwarciem pliku.\n");
        return -1;
    }

    const int MORE_PLAYERS = 5;
    if(!(*players_ptr = calloc(5, sizeof(Player)))) {
        printf("BLAD: problem z alokacja pamieci.\n");
        return 1;
    }
    int player_slots_left = 5;

    int read = 0;
    int records = 0;
    do {
        if (player_slots_left <= 1) {
            *players_ptr = realloc(*players_ptr, (records + MORE_PLAYERS) * sizeof(Player));
            if(!players_ptr) {
                printf("BLAD: problem z realokacja pamieci");
                return -4;
            }
        }
        read = fscanf(file,
                        "%49[^,],%49[^,],%49[^,],%d,%d\n",
                        (*players_ptr)[records].player_name,
                        (*players_ptr)[records].character_name,
                        (*players_ptr)[records].character_class,
                        &(*players_ptr)[records].character_level,
                        &(*players_ptr)[records].character_hp);

        if (read == 5) {
            records++;
            player_slots_left--;
        }
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