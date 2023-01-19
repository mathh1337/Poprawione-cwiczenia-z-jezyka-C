#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N_MAX 100

// funkcja porównująca dwa ciągi znaków
int compare(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main() {
    while(1) {
        char *words[N_MAX]; // tablica słów
        char buffer[256];
        char *rozb; // wskaźnik do kontynuowania rozbijania ciągu znaków
        int n = 0;
        printf("\nWprowadz zdanie oddzielone wylacznie spacjami: ");
        fgets(buffer, 256, stdin);
        buffer[strcspn(buffer, "\r\n")] = 0;
        int wrong = 0;
        char *word = strtok_r(buffer, " ", &rozb); // rozpoczęcie rozbijania ciągu znaków
        while (word != NULL) {
            int len = strlen(word);
            int is_wrong = 0;
            for (int i = 0; i < len; i++) {
                if (!isalpha(word[i])) {
                    printf("wprowadzono nieprawidlowy znak, wprowadz tylko litery\n");
                    is_wrong = 1;
                    break;
                }
            }
            if (is_wrong) {
                wrong = 1;
                break;
            }
            words[n] = malloc(strlen(word) + 1);
            strcpy(words[n], word); // kopiowanie słowa do tablicy
            n++; // zwiększenie licznika słów
            word = strtok_r(NULL, " ", &rozb); // pobranie kolejnego słowa
        }
        if (wrong) {
            continue;
        }
        // sortowanie tablicy słów
        qsort(words, n, sizeof(char *), compare);

        printf("Posortowane zdanie: ");
        for (int i = 0; i < n; i++) { // wyświetlenie posortowanego zdania
            printf("%s ", words[i]);
        }
        for (int i = 0; i < n; i++) {
            free(words[i]);
        }
    }

    return 0;
}