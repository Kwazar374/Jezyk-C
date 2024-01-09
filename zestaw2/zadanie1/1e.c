#include <stdlib.h>
#include <stdio.h>
#include <string.h>

///////////////////////////

typedef struct {
    char player_name[50];
    char character_name[50];
    char character_class[50];
    int character_level;
    int character_hp;
} Player;

///////////////////////////

struct Node{
    Player player;
    struct Node *next;
};
typedef struct Node Node;

///////////////////////////

void PrintList(Node *head);
void PrintPlayer(Player player);
Node *CreateNewNode(Player player);
int ReadPlayersFromCSV(const char *input_file, Node **head);
Node *LinearSearch(Node *head, const char *player_name);
int BetterLinearSearch(Node *head, const char *player_name, Node **first_res);
void FreeList(Node *head);


///////////////////////////

int main()
{   
    // wczytywanie listy jednokierunkowej z pliku CSV
    Node *head = NULL;
    ReadPlayersFromCSV("players.txt", &head);

    // wyswietlanie wczytanej listy
    PrintList(head);

    // wyszukiwanie gracza lub graczy o wprowadzonym imieniu
    char player_name_to_find[50];
    printf("\nWprowadz imie gracza, o ktorym chcesz uzyskac informacje: ");
    scanf("%s", player_name_to_find);

    printf("\n--------Linear Search-------------\n");
    Node *res1 = LinearSearch(head, player_name_to_find);
    if(res1) PrintPlayer(res1->player);
    else printf("Nie znaleziono gracza o podanym imieniu!\n");

    printf("\n-------Better Linear Search-------\n");
    Node *res = NULL;
    int res_num = BetterLinearSearch(head, player_name_to_find, &res);
    if (res_num > 0) {
        Node *temp_res = res;
        for (int i = 0; i < res_num; i++) {
            PrintPlayer(temp_res->player);
            temp_res = temp_res->next;
        }
    }
    else {
        printf("Nie znaleziono gracza o podanym imieniu!\n");
    }

    // zwalnianie pamieci zaalokowanej na liste graczy
    FreeList(head);

    return 0;
}

///////////////////////////

int ReadPlayersFromCSV(const char *input_file, Node **head) {
    FILE *file;
    file = fopen(input_file, "r");
    if (file == NULL)
    {
        printf("\nBLAD: problem z otwarciem pliku.\n");
        return 1;
    }

    Player temp_player;
    Node *last_node = NULL;

    int read = 0;
    int records = 0;
    do {
        read = fscanf(file,
                        "%49[^,],%49[^,],%49[^,],%d,%d\n",
                        temp_player.player_name,
                        temp_player.character_name,
                        temp_player.character_class,
                        &temp_player.character_level,
                        &temp_player.character_hp);

        if (read == 5) {
            records++;

            if (*head == NULL) {
                *head = CreateNewNode(temp_player);
                last_node = *head;
            }
            else {
                last_node->next = CreateNewNode(temp_player);
                last_node = last_node->next;
            }
        }
        else if (!feof(file)) {
            printf("\nBLAD: format pliku niepoprawny.\n");
            return 1;
        }
        if (ferror(file))
        {
            printf("\nBLAD: problem w trakcie czytania pliku\n");
            return 1;
        }

    } while (!feof(file));

    return 0;
}

///////////////////////////

Node *CreateNewNode(Player player) {
    Node *result = calloc(1, sizeof(Node));
    if (result == NULL) {
        printf("\nBLAD: problem z alokacja pamieci w fukcji CreateNewNode\n");
        return NULL;
    }
    result->player = player;
    result->next = NULL;
    return result;
}

///////////////////////////

void PrintList(Node *head) {
    Node *temporary = head;

    while (temporary != NULL) {
        PrintPlayer(temporary->player);
        temporary = temporary->next;
    }
    printf("\n");
}

///////////////////////////

void PrintPlayer(Player player) {
        printf("%s %s %s %d %d\n",
                player.player_name,
                player.character_name,
                player.character_class,
                player.character_level,
                player.character_hp);
}

///////////////////////////

// fukcja zwraca pierwszy pasujacy element
Node *LinearSearch(Node *head, const char *player_name) {
    Node *temporary = head;
    while (temporary != NULL) {
        if (strcmp(temporary->player.player_name, player_name) == 0) {
            return temporary;
        }
        temporary = temporary->next;
    }
    return NULL;
}

///////////////////////////

// funkcja we wskaznku first_res zapisuje adres pierwszego pasujacego elementu,
// funkcja zwraca liczbe pasujacych elementow
int BetterLinearSearch(Node *head, const char *player_name, Node **first_res) {
    Node *temporary = head;
    *first_res = NULL;
    int res = 0;
    while (temporary != NULL) {
        if (strcmp(temporary->player.player_name, player_name) == 0) {
            if(*first_res == NULL) *first_res = temporary; 
            res++;
        }
        temporary = temporary->next;
    }
    return res;
}

///////////////////////////
void FreeList(Node *head) {
    Node *temporary = head;
    Node *next;

    while (temporary != NULL) {
        next = temporary->next;
        free(temporary);
        temporary = next;
    }
}