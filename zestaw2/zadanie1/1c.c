#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int PlayersBinarySearch(Player players[], const char *player_name, int left, int right);
void PrintPlayer(Player *players, int records, int index);

///////////////////////////

int main(void)
{
    Player *players = NULL;
    int records = ReadPlayersFromCSV("players.txt", &players, false);
    if (records < 0) return 1;

    PrintPlayers(players, records);

    int search_res = PlayersBinarySearch(players, "Agata", 0, records-1);
    printf("\nGracz o szukanym imieniu znajduje sie pod indeksem: %d\n", search_res);
    PrintPlayer(players, records, search_res);

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
        printf("%d. %s %s %s %d %d\n",
                i,
                players[i].player_name,
                players[i].character_name,
                players[i].character_class,
                players[i].character_level,
                players[i].character_hp);
}

///////////////////////////

void PrintPlayer(Player *players, int records, int index) {
        if (index < 0 || index > records-1) {
            printf("\nBLAD: funkcja PrintPlayer otrzymala nieodpowiedni argument index\n");
            return;
        }
        printf("GRACZ O INDEKSIE %d: %s %s %s %d %d\n",
                index,
                players[index].player_name,
                players[index].character_name,
                players[index].character_class,
                players[index].character_level,
                players[index].character_hp);
}

///////////////////////////
int PlayersBinarySearch(Player players[], const char *player_name, int left, int right) {
    int mid = left + (right - left) / 2;

    if (left > right) return -1;

    int cmp_res = strcmp(players[mid].player_name, player_name);
    // cmp_res < 0, jesli players[mid].player_name < player_name
    if(cmp_res == 0)
        return mid;
    else if (cmp_res < 0) 
        return PlayersBinarySearch(players, player_name, mid+1, right);
    else
        return PlayersBinarySearch(players, player_name, left, mid-1);
        
}

