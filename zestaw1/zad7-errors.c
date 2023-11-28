#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    // obsluga wejscia
    char *input_string;
    scanf("%s", input_string);
    char *delimeter = " ";

    // tablica z informacjami na temat kosci oraz (opcjonalnego) modyfikatora
    int **dice_array = calloc(sizeof(int *), 1);
    int size_of_dice_array = 1;
    bool modifier_flag = false;

    // analizowanie wejsciowego stringa i przenoszenie go do tablicy z info o kosciach
    char *new_string; 
    printf("%s", new_string);
    while ((new_string = strtok(input_string, delimeter)) != NULL) {
        char *d_pointer = strchr(new_string, 'd');

        // analizowanie liczby rzutow
        char *rolls_str = malloc(sizeof(char) * (d_pointer - new_string + 1));
        strncpy(rolls_str, new_string, d_pointer - new_string);
        rolls_str[d_pointer - new_string] = '\0';
        int rolls = atoi(rolls_str);
        free(rolls_str);

        char *dice_str = malloc(sizeof(char) * (new_string + strlen(new_string) - d_pointer));
        strncpy(dice_str, d_pointer + 1, new_string + strlen(new_string) - d_pointer - 1);
        dice_str[(new_string + strlen(new_string) - d_pointer - 1)] = '\0';
        int dice = atoi(dice_str);
        free(dice_str);

        printf("rolls: %d\n", rolls);
        printf("dice: %d\n", dice);

        //dodawanie informacji o liczbie rzutów lub kości do tablicy
        if (*dice_array == NULL) {
            dice_array[0] = calloc(sizeof(int), 2);
            dice_array[0][0] = rolls;
            dice_array[0][1] = dice;
        }
        else {
            dice_array = realloc(dice_array, sizeof(int *) * (size_of_dice_array + 1));
            size_of_dice_array++;
            dice_array[size_of_dice_array-1] = calloc(sizeof(int), 2);
            dice_array[size_of_dice_array-1][0] = rolls;
            dice_array[size_of_dice_array-1][1] = dice;

        }
    }

    /* for(int i = 0, j = 0; i < size_of_dice_array; i++, j++) {
        if (j > 1) j = 0;
        printf("%d", dice_array[i][j]);
    } */

    /* for(int i = 0; i < size_of_dice_array; i++) {
        free(dice_array[i]);
    } */
    free(dice_array);
    return 0;
}