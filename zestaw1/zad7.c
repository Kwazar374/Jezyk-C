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

    // jesli modyfikator jest ujemny pozbywam sie spacji pomiedzy minusem a modulem
    // dzieki temu, pozniej latwiej jest mi wczytac wartosc modyfikatora
    ptr = input_string;
    while(*(ptr++) != '\0')
        if (*ptr == '-' && *(ptr + 1) == ' ') {
            *ptr = ' ';
            *(ptr + 1) = '-';
        }

    if (number_of_dice == 0) {
        printf("Blad: Nie wprowadzono informacji o zadnych kosciach\n");
        return 1;
    }

    int rolls = 0;
    int dice = 0;
    char *portion;
    char *second_portion;
    char temp_str[INTEGER_STR_MAXSIZE];
    int result = 0;
    int i = 0;
    int d = number_of_dice;
    

    while (1) {

        if (d <= 0) {
            if ((portion = strtok(NULL, " +")) != NULL) {
                strcpy(temp_str, portion);
                int modifier = atoi(temp_str+strspn(temp_str, " +"));
                printf("\tModyfikator: %d\n", modifier);
                result += modifier;
            }
            break;
        }

        // wczytywanie liczby rzutow dana koscia
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
        if (!rolls || !dice) {
            printf("\nBlad: Wprowadzony ciag jest bledny lub niezgodny z wczesniej okreslonymi zasadami\n");
            return 1;
        }

        // wykonywanie rzutow dana koscia
        for (int i = 1; i <= rolls; i++) {
            int roll = (rand() % dice) + 1;
            printf("\tRzut koscia %d-scienna nr %d: %d\n", dice, i, roll);
            result += roll;
        }
        printf("\t------------------------------------\n");

        i++;
        d--;     
    }


    printf("Wynik: %d", result);
    return 0;
}