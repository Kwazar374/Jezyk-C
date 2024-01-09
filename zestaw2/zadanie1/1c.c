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
void BetterPlayersBinarySearch(Player players[], const char *player_name, int records, int **results);
void PrintPlayer(Player *players, int records, int index);
int PrintPlayersInRange(Player *players, int records, int lowest, int highest);

///////////////////////////

int main(void)
{
    // wczytywanie tablicy graczy z pliku CSV
    Player *players = NULL;
    int records = ReadPlayersFromCSV("players.txt", &players, false);
    if (records < 0) return 1;

    // wypisywanie tablicy graczy
    PrintPlayers(players, records);

    // wyszukiwanie gracza lub graczy o wprowadzonym imieniu
    char player_name_to_find[50];
    printf("\nWprowadz imie gracza, o ktorym chcesz uzyskac informacje: ");
    scanf("%s", player_name_to_find);

    printf("\n---------Wyniki PlayersBinarySearch------------\n");

    int search_res1 = PlayersBinarySearch(players, player_name_to_find, 0, records-1);
    if (search_res1 != -1) {
        printf("Gracz o szukanym imieniu znajduje sie pod indeksem: %d\n", search_res1);
        PrintPlayer(players, records, search_res1);
    }
    else {
        printf("Nie znaleziono gracza o podanym imieniu!\n");
    }

    printf("\n--------Wyniki BetterPlayersBinarySearch-------\n");

    int *search_results = NULL;
    BetterPlayersBinarySearch(players, player_name_to_find, records, &search_results);
    if (search_results[0] != -1)
        PrintPlayersInRange(players, records, search_results[0], search_results[1]);
    else
        printf("Nie znaleziono gracza o podanym imieniu!\n");

    printf("\n");

    // zwalnianie pamieci zaalokowanej na tablice graczy
    free(players);
    return 0;
}

///////////////////////////

int ReadPlayersFromCSV(const char *input_file, Player **players_ptr, bool debug) {
    FILE *file;
    file = fopen(input_file, "r");
    if (file == NULL)
    {
        printf("\nBLAD: problem z otwarciem pliku.\n");
        return -1;
    }

    const int MORE_PLAYERS = 5;
    if(!(*players_ptr = calloc(5, sizeof(Player)))) {
        printf("\nBLAD: problem z alokacja pamieci.\n");
        return 1;
    }
    int player_slots_left = 5;

    int read = 0;
    int records = 0;
    do {
        if (player_slots_left <= 1) {
            *players_ptr = realloc(*players_ptr, (records + MORE_PLAYERS) * sizeof(Player));
            if(!players_ptr) {
                printf("\nBLAD: problem z realokacja pamieci");
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
            printf("\nBLAD: format pliku niepoprawny.\n");
            return -2;
        }
        if (ferror(file))
        {
            printf("\nBLAD: problem w trakcie czytania pliku\n");
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
        printf("%d. %s %s %s %d %d\n",
                index,
                players[index].player_name,
                players[index].character_name,
                players[index].character_class,
                players[index].character_level,
                players[index].character_hp);
}

///////////////////////////

int PrintPlayersInRange(Player *players, int records, int lowest, int highest) {
    if (highest < lowest) {
        printf("\nBLAD: funkcja PrintPlayersInRange otrzymala niepoprawny zakres\n");
        return -1;
    }
    if (highest > records-1 || highest < 0) {
        printf("\nBLAD: funkcja PrintPlayersInRange otrzymala niepoprawny zakres\n");
        return -2;
    }
    if (lowest < 0 || lowest > records-1) {
        printf("\nBLAD: funkcja PrintPlayersInRange otrzymala niepoprawny zakres\n");
        return -1;
    }

    if (lowest == highest) {
        PrintPlayer(players, records, lowest);
        return 1;
    }
    else {
        for (int i = lowest; i < highest+1; i++)
            printf("%d. %s %s %s %d %d\n",
                    i,
                    players[i].player_name,
                    players[i].character_name,
                    players[i].character_class,
                    players[i].character_level,
                    players[i].character_hp);
        return highest-lowest + 1;
    }
}

///////////////////////////

// funkcje PlayersBinarySearch mozna ewentualnie jeszcze obudowac dodatkowa funkcja
// ktora zamiast argumentow left i right przyjmuje argument records i na jego podstawie
// ustawia left=0 oraz right=records-1, zeby uzywanie funkcji bylo wygodniejsze dla uzytkownika.
// funkcja zwraca indeks jednego z graczy o szukanym imieniu lub -1 jesli nie znaleziono
// gracza o danym imieniu.
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

///////////////////////////

// indeks pierwszego z graczy o danym imieniu znajduje sie w (*results[0]),
// a ostatniego w (*results[1]), zakladamy ze players jest posortowana alfabatycznie
// imionami graczy
void BetterPlayersBinarySearch(Player players[], const char *player_name, int records, int **results) {
    if (!(*results = calloc(2, sizeof(int)))) {
        printf("\nBLAD: problem z alokacja pamieci w funkcji PlayersSearch\n");
    }
    int results_len = 1;
    (*results)[0] = -1;
    (*results)[1] = -1;
    int binary_search_res = PlayersBinarySearch(players, player_name, 0, records-1);

    if (binary_search_res != -1) {

        int k = binary_search_res;
        while (k >= 0 && strcmp(players[k-1].player_name, player_name) == 0) k--;
        (*results)[0] = k;

        k = binary_search_res;
        while (k < records && strcmp(players[k+1].player_name, player_name) == 0) k++;
        (*results)[1] = k;
    }
}

