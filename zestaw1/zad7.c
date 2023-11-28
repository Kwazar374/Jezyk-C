#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INTEGER_STR_MAXSIZE 11
#define INPUT_STR_MAXSIZE 100000

int main()
{
    srand(time(NULL));
    char input_string[INPUT_STR_MAXSIZE];
    printf("Wprowadz ciag znakow w dice notation. Jesli ktoras z kosci"
            " zostala rzucona 0 razy pomin ja.\nJesli modyfikator jest rowny 0, pomin go.:\n");
    fgets(input_string, INPUT_STR_MAXSIZE, stdin);

    // zliczam litere d w ciagu znakow na wejsciu
    char *ptr = input_string;
    int number_of_dice = 0;
    while(*(ptr++) != '\0')
        if (*ptr == 'd') number_of_dice++;

    int rolls = 0;
    int dice = 0;
    char *portion;
    char *second_portion;
    char temp_str[INTEGER_STR_MAXSIZE];
    int result = 0;
    int i = 0;
    int d = number_of_dice;
    

    while (1) {
        // wczytywanie liczby rzutow dana koscia
        if (d <= 0) {
            if ((portion = strtok(NULL, " +")) != NULL) {
                strcpy(temp_str, portion);
                printf("modifier: %s\n", temp_str);
                result += atoi(temp_str+strspn(temp_str, " +"));
            }
            break;
        }
        if ((portion = strtok(((i==0) ? input_string : NULL), "d")) == NULL) {
            break;
        }
        strcpy(temp_str, portion);
        rolls = atoi(temp_str+strspn(temp_str, " +"));

        // wczytywanie liczby scian danej kosci

        second_portion = strtok(NULL, " ");
        strcpy(temp_str, second_portion);
        dice = atoi(temp_str+strspn(temp_str, " +"));

        // sprawdzanie czy liczba rzutow i liczba scian kosci sa wieksze od zera
        // 0 jest zwracane przez funkcje atoi, jesli ciag znakow zawieral niecyfry
        // w przyszlosci mozna dodac bardziej zaawansowana obsluge bledow
        // np. kosci o jednej scianie nie istnieja
        if (!rolls || !dice) {
            printf("\nBlad: Wprowadzony ciag jest bledy lub niezgodny z wczesniej okreslonymi zasadami\n");
            return 1;
        }

        // wykonywanie rzutow dana koscia
        for (int i = 1; i <= rolls; i++) {
            int rzut = (rand() % dice) + 1;
            printf("%d\n", rzut);
            result += rzut;
        }

        i++;
        d--;     
    }


    printf("wynik %d", result);
    return 0;
}