#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// https://en.wikipedia.org/wiki/Prime-counting_function
long SizeOfSieve(int num_of_primes) {
    if (num_of_primes == 2)
        return 4L;
    long double x = 2;
    while(num_of_primes > (x/log(x))) {
        x *= 2;
    }
    long result = (long)(x*1.5);
    return result;
}

void Sieve(long *primes, int num_of_primes) {
    long size_of_sieve = SizeOfSieve(num_of_primes);
    
    bool *nums = malloc ((sizeof(long)) * size_of_sieve);

    for (int i = 0; i < size_of_sieve; i++)
        nums[i] = true;

    int primes_found = 0;

    for (int i = 0, j = 0; i < size_of_sieve; i++) {
        if (primes_found >= num_of_primes)
            return;
        if (i <= 1)
            nums[i] = false;
        else
            if (nums[i] == true) {
                primes[j++] = i;
                primes_found++;
                for (int k = i; k < size_of_sieve; k += i)
                    nums[k] = false;
            }
    }

    free(nums);
    return;
}

int main()
{   
    printf("Ile najmniejszych liczb pierwszych do wyświetlenia?:\n");
    int num_of_primes;
    scanf("%d", &num_of_primes);

    if(num_of_primes < 1)
        printf("Blad: wprowadzana liczba powinna byc wieksza od 0!");

    long *primes = malloc ((sizeof(long)) * num_of_primes);

    Sieve(primes, num_of_primes);

    printf("\n*****************WYNIK**********************\n");
    for (int i = 0; i < num_of_primes; i++)
        printf("%ld\n", primes[i]);
    printf("********************************************");

    free(primes);
    return 0;
}