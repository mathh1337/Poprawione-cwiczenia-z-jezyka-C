#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Nie podano nazwy pliku do zaszyfrowania\n");
        return 1;
    }

    FILE *file1, *file2;
    char haslo[100];
    int dlugosc_hasla, j = 0;
    char znak, Tymczasowy[] = "tempfileXXXXXX";
    int fd = mkstemp(Tymczasowy);

    if (fd == -1) {
        printf("Nie można utworzyć pliku tymczasowego\n");
        return 1;
    }
    file2 = fdopen(fd, "wb");

    if (NULL == (file1 = fopen(argv[1], "rb"))) {
        printf("Nie można otworzyć pliku do odczytu: %s\n", argv[1]);
        return 1;
    }

    printf("Podaj hasło: ");
    fgets(haslo, sizeof(haslo), stdin);
    dlugosc_hasla = strlen(haslo);
    haslo[dlugosc_hasla-1] = '\0'; // usuwamy '\n' z hasła
    dlugosc_hasla--;

    while((znak = getc(file1)) != EOF) {
        znak ^= haslo[j % dlugosc_hasla];
        putc(znak, file2);
        j++;
    }

    fclose(file1);
    fclose(file2);

    unlink(argv[1]);
    rename(Tymczasowy, argv[1]);

    return 0;
}