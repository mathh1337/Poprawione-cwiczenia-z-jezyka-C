#include <stdio.h>

int main()
{
    int liczba, base, i;
    int tab[100];

    // Nieskonczona petla
    while (1)
    {
        printf("Podaj liczbe w systemie dziesietnym: "); // Wyświetlenie komunikatu

        // Weryfikacja wejscia uzytkownika - można wpisać tylko liczby
        if (!scanf("%d", &liczba))
        {
            printf("Prosze podac liczbe!\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Podaj system docelowy (od 2 do 16): ");

        // Weryfikacja wejscia uzytkownika - można wpisać tylko liczby
        if (!scanf("%d", &base))
        {
            printf("Proszę podać liczbę!\n");
            while (getchar() != '\n');
            continue;
        }

        i = 0;
        while (liczba > 0)
        {
            tab[i] = liczba % base; // Przypisanie do tablicy pozostałości z dzielenia
            liczba /= base; // Dzielenie przez podaną liczbę
            i++;
        }

        printf("Liczba w systemie %d-kowym: ", base);
        for (i--; i >= 0; i--) // Pętla od ostatniego elementu tablicy do pierwszego
        {
            if (tab[i] > 9) //
                printf("%c", tab[i] + 55); // Wyświetlenie znaku (ASCII)
            else
                printf("%d", tab[i]); // Wyświetlenie cyfry
        }

        printf("\n");
    }

    return 0;
}
