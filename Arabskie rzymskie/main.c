#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct RZYM {
    int arab;
    char *rzym;
};
int value(char r)
{
    if (r == 'I')
        return 1;
    if (r == 'V')
        return 5;
    if (r == 'X')
        return 10;
    if (r == 'L')
        return 50;
    if (r == 'C')
        return 100;
    if (r == 'D')
        return 500;
    if (r == 'M')
        return 1000;

    return -1;
}

int roman_arab(char str[])
{

    int res = 0;

    for (int i = 0; i < strlen(str); i++) {
        if (!isupper(str[i])) {
            printf("Error: Liczby rzymskie musza byc podane wielkimi literami!\n");
            return 0;
        }
    }


    for (int i = 0; i < strlen(str); i++)
    {

        int s1 = value(str[i]);

        if (i + 1 < strlen(str))
        {

            int s2 = value(str[i + 1]);


            if (s1 >= s2)
            {

                res = res + s1;
            }
            else
            {

                res = res + s2 - s1;
                i++;
            }
        }
        else {
            res = res + s1;
        }
    }
    return res;
}
int arab_roman(int num)
{
    struct RZYM rz[] = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
            {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
            {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
// Weryfikacja poprawności liczby arabskiej
    if (num <= 0 || num > 3999)
    {
// Liczba arabska musi być dodatnia i nie większa niż 3999
        printf("Wprowadzono niepoprawną liczbę arabską\n");
        return 1;
    }
    int i = 0;
    while (num > 0)
    {
        if (num >= rz[i].arab)
        {
            printf("%s", rz[i].rzym);
            num = num -  rz[i].arab;
        }
        else
        {
            i++;
        }
    }
    return 0;
}

int main()
{
    while (1)
    {
        char input[50];
        printf("\nWprowadz liczbe w systemie rzymskim lub arabskim: ");
        scanf("%s", input);

        // Sprawdzenie, czy liczba jest w systemie rzymskim
        int is_roman = 1;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isalpha(input[i]))
            {
                is_roman = 0;
                break;
            }
        }

        if (is_roman)
        {
            int result = roman_arab(input);
            if (result == -1)
            {
                printf("Wprowadzono niepoprawną liczbę rzymską\n");
                continue;
            }
            else
            {
                printf("W systemie arabskim: %d\n", result);
            }
        }
        else
        {
            int num = atoi(input);
            printf("W systemie rzymskim: ");
            arab_roman(num);
        }
    }

}
