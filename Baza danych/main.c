#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct libr // struktura przechowujaca dane o czytelniku
{
    char name[20];
    int id;
    char books[5][20];
    int book_count;
    int book_limit;
};

struct libr in[100]; // Tablica przechowujaca dane o czytelnikach
int libit = 0; // licznik czytelnikow


// Deklaracja funkcji
void loadfromfile();
void savetofile();
void registerlib();
void showall();
void search();
void deletelib();
void returnbook();
void addBook(); // dodana funkcja

int main(){
    int choice;

    loadfromfile(); // odczytanie danych z pliku

    while(1){
        printf("Witam w bibliotece!\n");
        printf("Co chcesz zrobic?\n");
        printf("1. Zarejestruj czytelnika\n");
        printf("2. Wyswietl wszystkich czytelnikow\n");
        printf("3. Wyszukaj czytelnika\n");
        printf("4. Usun czytelnika\n");
        printf("5. Dodaj ksiazke\n");
        printf("6. Wyjdz\n");
        printf("Twoj wybor: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                registerlib();
                break;
            case 2:
                showall();
                break;
            case 3:
                search();
                break;
            case 4:
                deletelib();
                break;
            case 5:
                addBook();
                break;
            case 6:
                savetofile(); // zapisanie danych do pliku
                exit(1);
                break;
            default:
                printf("Nie ma takiej opcji\n");
                break;
        }
    }

    return 0;
}

void loadfromfile()
{
    FILE* infile;

    if ((infile = fopen("biblioteka", "r")) == NULL) // sprawdzenie czy plik istnieje
        infile = fopen("biblioteka", "w"); //tworzenie pliku jesli nie istnieje

    while (fread(&in[libit], sizeof(struct libr), 1, infile)) // odczytanie danych z pliku

        libit++;
    fclose(infile);
}

void savetofile()
{
    FILE* outfile;
    if ((outfile = fopen("biblioteka", "w")) == NULL) // Sprawdzenie czy plik może być otwarty do zapisu
    {
        printf("Podczas proby otwarcia wystapil blad\n");
        exit(1);
    }
    for (int i = 0; i < libit; i++)
        fwrite(&in[i], sizeof(struct libr), 1, outfile); // zapisanie danych z tablicy "in" do pliku

    fclose(outfile);
}

void registerlib(){ // Funkcja registerlib() rejestruje czytelnika
    printf("Podaj imie: ");
    scanf("%s", in[libit].name);
    printf("Podaj ID: ");
    scanf("%d", &in[libit].id);
    printf("Podaj limit przydzielonych ksiazek(Zalecany limit to 10): ");
    scanf("%d", &in[libit].book_limit);
    in[libit].book_count = 0; // ustawienie liczby przydzielonych ksiazek na 0
    libit++;
    printf("Czytelnik zarejestrowany pomyslnie!\n");
}

void showall(){ // Funkcja showall() wyswietla wszystkich zarejestrowanych czytelnikow
    printf("Lista czytelnikow:\n");
    for(int i = 0; i < libit; i++){
        printf("Imie: %s\n", in[i].name);
        printf("ID: %d\n", in[i].id);
        printf("Przydzielone ksiazki: ");
        for (int j = 0; j < in[i].book_count; j++)
            printf("%s ", in[i].books[j]);
        printf("\n");
        printf("Limit przydzielonych ksiazek: %d\n", in[i].book_limit);
        printf("\n");
    }
}

void search(){ // Funkcja search() pozwala na wyszukanie czytelnika po ID
    int id;
    printf("Podaj ID czytelnika, którego chcesz wyszukać: ");
    scanf("%d", &id);
    int index = -1;
    for (int i = 0; i < libit; i++)
    {
        if (in[i].id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Nie znaleziono czytelnika o podanym ID\n");
        return;
    }

    printf("Imie: %s\n", in[index].name);
    printf("ID: %d\n", in[index].id);
    printf("Przydzielone ksiazki: ");
    for (int j = 0; j < in[index].book_count; j++)
        printf("%s ", in[index].books[j]);
    printf("\n");
    printf("Limit przydzielonych ksiazek: %d\n", in[index].book_limit);
}

void deletelib(){ // Funkcja deletelib() pozwala na usuniecie czytelnika po ID
    int id;
    int index= -1;
    printf("Podaj ID czytelnika, którego chcesz usunąć: ");
    scanf("%d", &id);
    for (int i = 0; i < libit; i++)
    {
        if (in[i].id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Nie znaleziono czytelnika o podanym ID\n");
        return;
    }

    for (int i = index; i < libit - 1; i++)
    {
        in[i] = in[i + 1];
    }

    libit--;
    printf("Czytelnik usuniety pomyslnie!\n");
}

void addBook() { // Funkcja addBook() pozwala na dodanie ksiazki dla czytelnika
    int id;
    int index = -1;
    printf("Podaj ID czytelnika, któremu chcesz przydzielić książkę: ");
    scanf("%d", &id);

    for (int i = 0; i < libit; i++)
    {
        if (in[i].id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Nie znaleziono czytelnika o podanym ID\n");
        return;
    }

    if (in[index].book_count >= in[index].book_limit) {
        printf("Czytelnik osiagnal swoj limit przydzielonych ksiazek\n");
        return;
    }

    printf("Podaj tytul ksiazki: ");
    scanf("%s", in[index].books[in[index].book_count]);
    in[index].book_count++;
    printf("Ksiazka przydzielona pomyslnie!\n");
}

