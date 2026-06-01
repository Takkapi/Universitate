#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "tablete.bin"
#define TEMP_FILE "temp.bin"

/// Laboratorul nr. 3 la Structuri de Date si Algoritm
/// Realizat de Smolenschi Petru, TI-252FR

/// Sarcina lucrarii:
/*
Pentru fisierele binare cu elemente de tip structura (conform variantelor)
sa se afiseze la ecarn urmatorul meniu de optiuni:
    1. Creare unui fisier binar nou, introducere campurilor structurilor
        de la tastatura si inscrierea lor in acest fisier.
    2. Afisarea elementelor fisierului binar la ecran.
    3. Adaugarea unei structuri noi la sfarsit de fisier.
    4. Modificarea unei structuri a fisierului.
    5. Cautarea dupa camp al structurii in fisier.
    6. Eliminarea unei strcturi de fisier.
    8. Stergerea fisierului de pe disc.
    0. Iesire din program.

Sa se elaboreze functiile pentru implementarea optiunilor meniului.

! Varianta 8
Structura Tablete cu campurile: tip(tableta, carte electronica, tableta grafica), producator,
dimensiune ecran, sistem de operare, numar de nuclee, pret.
*/

typedef struct {
    char tip[50];
    char producator[50];
    float dimensiune;
    char os[50];
    int cores;
    float pret;
} Tableta;

void creareFisier();
void afisareFisier();
void adaugareSfarsit();
void modificareStructura();
void cautareProducator();
void sortareFisier();
void eliminareStructura();
void stergereFisier();
Tableta citireTabletaTastatura();

int main() {
    int option;

    do {
        printf("\n================ MENIU FISIERE BINARE ================\n");
        printf("1. Crearea unui fisier binar nou si introducerea datelor\n");
        printf("2. Afisarea elementelor fisierului la ecran\n");
        printf("3. Adaugarea unei structuri noi la sfarsit de fisier\n");
        printf("4. Modificarea unei structuri a fisierului\n");
        printf("5. Cautarea dupa producator in fisier\n");
        printf("6. Sortarea structurilor fisierului dupa pret\n");
        printf("7. Eliminarea unei structuri din fisier\n");
        printf("8. Stergerea fisierului de pe disc\n");
        printf("0. Iesire din program\n");
        printf("======================================================\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &option);

        switch(option) {
            case 1: creareFisier(); break;
            case 2: afisareFisier(); break;
            case 3: adaugareSfarsit(); break;
            case 4: modificareStructura(); break;
            case 5: cautareProducator(); break;
            case 6: sortareFisier(); break;
            case 7: eliminareStructura(); break;
            case 8: stergereFisier(); break;
            case 0: printf("Iesire program...\n"); break;
            default: printf("Optiune invalida!\n"); break;
        }
    } while(option != 0);

    return 0;
}

Tableta citireTabletaTastatura() {
    Tableta t;
    printf("Tip (tableta / carte electronica / tableta grafica): ");
    scanf(" %d[^\n]", t.tip);
    printf("Producator: ");
    scanf(" %[^\n]", t.producator);
    printf("Dimensiune ecran (inch): ");
    scanf("%f", &t.dimensiune);
    printf("Sistem de operare: ");
    scanf(" %[^\n]", t.os);
    printf("Numar de nuclee: ");
    scanf("%d", &t.cores);
    printf("Pret: ");
    scanf("%f", &t.pret);
    
    return t;
}

void creareFisier() {
    FILE *f = fopen(FILE_NAME, "wb");
    if(!f) {
        printf("Nu se poate crea fisierul!\n");
        return;
    }

    int n;
    printf("Cate tablete doriti sa introduceti? ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("\n--- Introduceti datele pentru tableta %d ---\n", i + 1);
        Tableta t = citireTabletaTastatura();
        fwrite(&t, sizeof(Tableta), 1, f);
    }

    fclose(f);
    printf("Fisierul a fost creat si datele au fost salvate!\n");
}

void afisareFisier() {
    FILE *f = fopen(FILE_NAME, "rb");
    if(!f) {
        printf("Fisierul nu exista! Creati-l mai intai (Optiunea 1).\n");
        return;
    }

    Tableta t;
    int i = 1;
    printf("%-3s | %-18s | %-15s | %-12s | %-18s | %-10s | %-10s\n", 
            "Nr", "Tip", "Producator", "Dim. Ecran", "Sistem Operare", "Nr Nuclee", "Pret");
    
    while(fread(&t, sizeof(Tableta), 1, f) == 1) {
        printf("%-3d | %-18s | %-15s | %-10.1f\" | %-18s | %-10d | %-10.2f\n", 
            i++, t.tip, t.producator, t.dimensiune, t.os, t.cores, t.pret);
    }

    fclose(f);
}

void adaugareSfarsit() {
    FILE *f = fopen(FILE_NAME, "ab");
    if(!f) {
        printf("Fisierul nu a putut fi deschis!\n");
        return;
    }

    printf("\n--- Introduceti datele pentru noua tableta ---\n");
    Tableta t = citireTabletaTastatura();
    fwrite(&t, sizeof(Tableta), 1, f);

    fclose(f);
    printf("Tableta a fost adaugata la sfarsitul fisierului!\n");
}

void modificareStructura() {
    FILE *f = fopen(FILE_NAME, "rb+");
    if(!f) {
        printf("Fisierul nu exista!\n");
        return;
    }

    int recordNo;
    printf("Introduceti numarul de ordine al tabletei pe care doriti sa o modificati (incepand cu 1): ");
    scanf("%d", &recordNo);

    long offset = (recordNo - 1) * sizeof(Tableta);
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);

    if(offset < 0 || offset >= fileSize) {
        printf("Numarul de ordine nu exista in fisier!\n");
        fclose(f);
        return;
    }

    fseek(f, offset, SEEK_SET);
    printf("\n--- Introduceti NOILE date pentru tableta &d ---\n", recordNo);
    Tableta t = citireTabletaTastatura();

    fseek(f, offset, SEEK_SET);
    fwrite(&t, sizeof(Tableta), 1, f);

    fclose(f);
    printf("\nStructura a fost modificata!\n");
}

void cautareProducator() {
    FILE *f = fopen(FILE_NAME, "rb");
    if(!f) {
        printf("Fisierul nu exista!\n");
        return;
    }

    char prod[50];
    printf("Introduceti numele producatorului cautat: ");
    scanf(" %[^\n]", prod);

    Tableta t;
    int found = 0;

    printf("\n--- Rezultatele cautarii ---\n");
    while(fread(&t, sizeof(Tableta), 1, f) == 1) {
        if(strcmp(t.producator, prod) == 0) {
            printf("Tip: %s | Producator: %s | Ecran: %.1f\" | OS: %s | Nuclee: %d | Pret: %.2f\n",
                t.tip, t.producator, t.dimensiune, t.os, t.cores, t.pret);
            found = 1;
        }
    }

    if(!found) printf("Nu a fost gasita nicio tableta produsa de '%s'.\n", prod);

    fclose(f);
}

void sortareFisier() {
    FILE *f = fopen(FILE_NAME, "rb");
    if(!f) {
        printf("Fisierul nu exista!\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    int n = fileSize / sizeof(Tableta);
    rewind(f);

    if(n <= 1) {
        printf("Fisierul are %d elemente, nu este necesara sortarea.\n", n);
        fclose(f);
        return;
    }

    Tableta *tab = (Tableta *)malloc(n * sizeof(Tableta));
    fread(tab, sizeof(Tableta), n, f);
    fclose(f);

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if((tab + j)->pret > (tab + (j + 1))->pret) {
                Tableta *temp = tab + j;
                *(tab + j) = *(tab + (j + 1));
                *(tab + (j + 1)) = *temp;
            }
        }
    }

    f = fopen(FILE_NAME, "wb");
    fwrite(tab, sizeof(Tableta), n, f);
    fclose(f);
    free(tab);

    printf("Fisierul a fost sortat crescator dupa pret!\n");
}

void eliminareaStructura() {
    FILE *f = fopen(FILE_NAME, "rb");
    if(!f) {
        printf("Fisierul nu exista!\n");
        return;
    }

    FILE *ftemp = fopen(TEMP_FILE, "wb");
    if(!ftemp) {
        printf("Nu se poate crea fisierul temporar!\n");
        fclose(f);
        return;
    }

    int recordNo;
    printf("Introduceti numarul de ordine al tabletei pe care doriti sa o stergeti: ");
    scanf("%d", &recordNo);

    Tableta t;
    int i = 1, found = 0;
    
    while(fread(&t, sizeof(Tableta), 1, f) == 1) {
        if(i != recordNo) fwrite(&t, sizeof(Tableta), 1, ftemp);
        else found = 1;
        
        i++;
    }

    fclose(f);
    fclose(ftemp);

    if(found) {
        remove(FILE_NAME);
        rename(TEMP_FILE, FILE_NAME);
        printf("Structura a fost eliminata din fisier!\n");
    } else {
        remove(TEMP_FILE);
        printf("Numarul de inregistrare nu exista in fisier!\n");
    }
}

void stergetFisier() {
    if(remove(FILE_NAME) == 0) 
        printf("\n Fisierul '%s' a fost sters complet de pe disc!\n", FILE_NAME);
    else 
        printf("\n Fisierul nu a putut fi sters (posibil nu exista).\n");
}