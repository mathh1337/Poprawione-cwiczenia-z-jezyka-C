#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N_MAX 100

// funkcja porównująca dwa ciągi znaków
int compare(const void *a, const void *b) {
    return *(float *)a - *(float *)b; // porównaj wartość float pod wskaźnikiem a i b
}


int main(int argc, char *argv[]) {

    int ascending = 1; // domyślnie sortuj rosnąco

    while (1) {
        char wybor;
        printf("\nWybierz rodzaj sortowania [r-rosnaco/m-malejaco]: ");
        wybor = getchar();
        if (wybor == 'm') {
            ascending = 0; // sortuj malejąco
        }

        float numbers[N_MAX]; // tablica liczb
        char buffer[256]; // bufor do przechowywania wprowadzonych liczb
        char tmp[8];
        char *rozb; // wskaźnik do kontynuowania rozbijania ciągu znaków
        int n = 0;
        printf("\nWprowadz ciag liczb rzeczywistych: ");
        fgets(tmp, 8, stdin);
        fgets(buffer, 256, stdin); // pobierz ciąg znaków od użytkownika
        buffer[strcspn(buffer, "\r\n")] = 0; // usuń znak końca linii
        int wrong = 0;
        char *word = strtok_r(buffer, " ", &rozb); // rozpoczęcie rozbijania ciągu znaków
        while (word != NULL) { // dopóki istnieje jeszcze jakieś słowo
            int len = strlen(word); // długość słowa
            int is_wrong = 0;
            for (int i = 0; i < len; i++) { // sprawdź czy słowo składa się tylko z cyfr
                if (!isdigit(word[i]) && word[i] != '.' && word[i] != '-') {
                    printf("wprowadzono nieprawidlowy znak, wprowadz tylko liczby rzeczywiste\n");
                    is_wrong = 1;
                    break;
                }
            }
            if (is_wrong) {
                wrong = 1;
                break;
            }
            int duplicate = 0;
            for (int i = 0; i < n; i++) { // sprawdź czy już nie wprowadzono tej liczby
                if (atof(word) == numbers[i]) {
                    printf("Nie mozna wprowadzic dwoch takich samych liczb!\n");
                    duplicate = 1;
                    break;
                }
            }
            if (duplicate) {
                wrong = 1;
                break;
            }
            numbers[n] = atof(word); // dodaj liczbę do tablicy
            n++;
            word = strtok_r(NULL, " ", &rozb);
        }
        if (wrong) {
            continue;
        }
        // sortowanie tablicy liczb
        if (ascending) { // jeśli sortujesz rosnąco
            qsort(numbers, n, sizeof(float), compare); // użyj funkcji qsort i porównuj wg funkcji compare
        } else {
            qsort(numbers, n, sizeof(float), compare); // użyj funkcji qsort i porównuj wg funkcji compare
            for (int i = 0; i < n / 2; i++) {
                float temp = numbers[i];
                numbers[i] = numbers[n - i - 1];
                numbers[n - i - 1] = temp;
            }
        }


        printf("Posortowane liczby: ");
        for (int i = 0; i < n; i++) { // wyświetlenie posortowanego zdania
            printf("%.2f ", numbers[i]);
        }
    }

    return 0;
}