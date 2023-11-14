#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void PrintPiValueForN(int n) {
    double x;
    double y;
    int k = 0;

    for (int i = 0; i < n; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (pow(x, 2) + pow(y, 2) < 1)
            k++;
    }
    printf("Wyliczona wartość liczby pi dla n = %d: %g", n, ((double)k*4)/(double)n);
}

void PrintPrecisePiValueTest(int tries) {
    double x;
    double y;
    int k = 0;
    int n = 0;
    double nsum = 0;
    int naverage;

    for (int i = 0; i < tries; i++) {
        do {
            x = (double)rand() / RAND_MAX;
            y = (double)rand() / RAND_MAX;
            if (pow(x, 2) + pow(y, 2) < 1)
                k++;
            n++;
        } while (((double)k*4)/(double)n < 3.13 || ((double)k*4)/(double)n >= 3.15);
        nsum += n;
        n = 0;
        k = 0;
    }
    naverage = (int)((double)nsum/(double)tries);

    printf("Wartosc pi obliczono %d razy i porzadna wartosc liczby pi, tzn. mieszczaca sie\n"
    "w przedziale (3.13, 3.15) wymagala wykonania srednio %d losowan punktow\n"
    "w metodzie Monte Carlo.", tries, naverage);
}



int main()
{
    srand(time(NULL));

    //int n;

    //printf("Podaj n:\n");
    //scanf("%d", &n);

    //PrintPiValueForN(n);

    PrintPrecisePiValueTest(100000);


    return 0;
}