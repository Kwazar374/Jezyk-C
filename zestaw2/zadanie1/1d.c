#include <stdlib.h>
#include <stdio.h>

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


///////////////////////////

int main()
{
    Node *head = NULL;
    ReadPlayersFromCSV("players.txt", &head);

    PrintList(head);

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