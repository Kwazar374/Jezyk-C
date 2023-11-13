#include <stdio.h>

int DateCheck(char *date);
int LifePathNumber(char *date);

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Wprowadz date swojego urodzenia w formacie DD-MM-RRRR:\n");
    char date[] = "DD-MM-RRRR";
    scanf("%s", &date);
    char *c = date;

    if (DateCheck(date)) {
        return 1;
    }

    printf("Liczba numerologiczna podanej daty to: %d", LifePathNumber(date));

    return 0;      
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

int DateCheck(char *date) {
    char *c = date;

    while (*c != '\0') {
        if(*c != '-' && (*c < '0' || *c > '9')) {
            printf("Blad: w dacie znajduja sie znaki inne niż cyfry i '-'!");
            return 1;
        }
        c++;
    }

    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100
                + (date[8] - '0') * 10 + (date[9] - '0') * 10;
    
    if (year == 0) {
        printf("Blad: podany rok nie istnieje!");
        return 1;
    }

    if (month == 0 || month > 12) {
        printf("Blad: podany miesiac nie istnieje");
        return 1;
    }


    if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 
        || month == 7 || month == 8 || month == 10 || month == 12)) {
        return 0;
    }
    else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 
            || month == 9 || month == 11)) {
        return 0;
    }
    else if ((day >= 1 && day <= 28) && (month == 2)) {
        return 0;
    }
    else if (day == 29 && month == 2 && (year % 400 == 0 
            || (year % 4 == 0 && year % 100 != 0))) {
        return 0;
    }
    else {
        printf("Blad: podany dzien nie istnieje!");
        return 1;
    }
}

///////////////////////////////////////////////////////////////////////////////////

int LifePathNumber(char *date) {
    char *c = date;
    int sum = 0;
    int master_sum = 0;

    // uwzglednienie liczb mistrzowskich
    if (date[0] == date[1]) {
        master_sum += (date[0]-'0') * 10 + (date[1]-'0');
        date[0] = '0';
        date[1] = '0';
    }

    if (date[3] == date[4]) {
        master_sum += (date[3]-'0') * 10 + (date[4]-'0');
        date[3] = '0';
        date[4] = '0';
    }

    int year_sum = (date[6]-'0') + (date[7]-'0') + (date[8]-'0') + (date[9]-'0');
    while (year_sum > 9 && year_sum != 11 && year_sum != 22 && year_sum != 33) {
        year_sum = (year_sum/10) + (year_sum%10);
    }
    date[6] = '0';
    date[7] = '0';
    date[8] = '0';
    date[9] = '0';

    while (*c != '\0') {
        if(*c != '-') {
            sum += (*c - '0');
        }
        c++;
    }
    sum = sum + year_sum + master_sum;

    while (sum > 9 && sum != 11 && sum != 22 && sum != 33) {
        sum = (sum/10) + (sum%10);
    }
    return sum;
}