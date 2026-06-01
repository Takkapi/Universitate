#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "state.txt"

/// Laboratorul nr. 4 la Structuri de Date si Algoritm
/// Realizat de Smolenschi Petru, TI-252FR

/// Sarcina lucrarii:
/*
Pentru fisiere textuale cu elemente de tip satructura (conform variantelor) 
sa se afiseze la ecran urmatorul meniu de optiuni:
    1. Crearea unui fisier textual nou, introducerea campurilor structurilor de la
        tastatura si inscrierea lor in acest fisier.
    2. Afisarea elementelor fisierului binar la ecran
    3. Adaugarea unei structuri noi la sfarsit de fisier.
    4. Modificarea unei structuri a fisierului.
    5. Cautarea dupa un camp al structurii in fisier.
    6. Sortarea structurilor fisierului dupa un careva camp de tip string & integer(float).
    7. Eliminarea unei structuri din fisier.
    0. Iesire din program.

Sa se elaboreze functiile pentru implementarea optiunilor meniului.

! Varianta 8
Structura Stat cu campurile: denumirea, capitala, suprafata, populatia, produsul intern brut.
*/

typedef struct {
    char name[100];
    char capital[100];
    double area;
    long long population;
    double pib;
} State;

void writeState(FILE *f, State s);
int readState(FILE *f, State *s);
State* loadFile(int *count);
void saveMatrix(State *tab, int count);

void createFile();
void showFile();
void appendEnd();
void modifyStruct();
void searchName();
void sortFile();
void purgeStruct();

int main() {
    int option;

    do {
        printf("\n================ MENIU FISIERE TEXTUALE ================\n");
        printf("1. Crearea unui fisier textual nou si introducerea datelor\n");
        printf("2. Afisarea elementelor fisierului la ecran\n");
        printf("3. Adaugarea unei structuri noi la sfarsit de fisier\n");
        printf("4. Modificarea unei structuri a fisierului\n");
        printf("5. Cautarea dupa denumire in fisier\n");
        printf("6. Sortarea structurilor dupa un camp (String / Numeric)\n");
        printf("7. Eliminarea unei structuri din fisier\n");
        printf("0. Iesire din program\n");
        printf("========================================================\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &option);

        switch(option) {
            case 1: createFile();                       break;
            case 2: showFile();                         break;
            case 3: appendEnd();                        break;
            case 4: modifyStruct();                     break;
            case 5: searchName();                       break;
            case 6: sortFile();                         break;
            case 7: purgeStruct();                      break;
            case 0: printf("Iesire din program...\n");  break;
            default: printf("Optiune invalida!\n");
        }
    } while(option != 0); 

    return 0;
}

void writeState(FILE *f, State s) {
    fprintf(f, "%s\n", s.name);
    fprintf(f, "%s\n", s.capital);
    fprintf(f, "%.2f\n", s.area);
    fprintf(f, "%lld\n", s.population);
    fprintf(f, "%.2f\n", s.pib);
}

int readState(FILE *f, State *s) {
    if(fscanf(f, " %[^\n]", s->name) != 1) return 0;
    if(fscanf(f, " %[^\n]", s->capital) != 1) return 0;
    if(fscanf(f, "%lf", &s->area) != 1) return 0;
    if(fscanf(f, "%lld", &s->population) != 1) return 0;
    if(fscanf(f, "%lf", &s->pib) != 1) return 0;

    return 1;
}

State* loadFile(int *count) {
    FILE *f = fopen(FILE_NAME, "r");
    if(!f) {
        *count = 0;
        return NULL;
    }
    int cap = 10;
    *count = 0;
    State *tab = (State *)malloc(cap * sizeof(State));
    State s;

    while(readState(f, &s)) {
        if(*count >= cap) {
            cap *= 2;
            tab = (State *)realloc(tab, cap * sizeof(State));
        }
        tab[*count] = s;
        (*count)++;
    }
    fclose(f);
    return tab;
}

void saveMatrix(State *tab, int count) {
    FILE *f = fopen(FILE_NAME, "w");
    if(!f) {
        printf("Nu s-a putut deschide fisierul pentru salvare!\n");
        return;
    }
    for(int i = 0; i < count; i++) writeState(f, tab[i]);

    fclose(f);
}

void createFile() {
    FILE *f = fopen(FILE_NAME, "w");
    if(!f) {
        printf("Nu se poate crea fisierul!\n");
        return;
    }

    int n;
    printf("Cate state doriti sa introduceti? ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        State s;
        printf("\n--- Date pentru statul %d ---\n", i + 1);
        printf("Denumirea statului: ");
        scanf(" %[^\n]", s.name);
        printf("Capitala: ");
        scanf(" %[^\n]", s.capital);
        printf("Suprafata (km2): ");
        scanf("%lf", &s.area);
        printf("Populatia: ");
        scanf("%lld", &s.population);
        printf("Produsul Itern Brut (mld EUR): ");
        scanf("%lf", &s.pib);

        writeState(f, s);
    }

    fclose(f);
    printf("Fisierul textual a fost creat si salvat!\n");
}

void showFile() {
    FILE *f = fopen(FILE_NAME, "r");
    if(!f) {
        printf("Fisierul nu exista! Creati-l mai intai.\n");
        return;
    }

    State s;
    int i = 1;
    printf("%-4s | %-20s | %-20s | %-12s | %-12s | %-12s\n", 
            "Nr.", "Denumire Stat", "Capitala", "Suprafata", "Populatie", "PIB (mld EUR)");
    
    while(readState(f, &s)) {
        printf("%-4d | %-20s | %-20s | %-10.1f   | %-12lld | %-12.2f\n", 
                i++, s.name, s.capital, s.area, s.population, s.pib);
    }

    fclose(f);
}

void appendEnd() {
    FILE *f = fopen(FILE_NAME, "a");
    if(!f) {
        printf("Fisierul nu poate fi deschis!\n");
        return;
    }

    State s;
    printf("\n--- Introduceti datele pentru statul nou ---\n");
    printf("Denumirea statuslui: ");
    scanf(" %[^\n]", s.name);
    printf("Capitala: ");
    scanf(" %s[^\n]", s.capital);
    printf("Suprafata (km2): ");
    scanf("%lf", &s.area);
    printf("Populatia: ");
    scanf("%lld", &s.population);
    printf("Produsul Intern Brut (mld EUR): ");
    scanf("%lf", &s.pib);

    writeState(f, s);
    fclose(f);
    printf("Statul a fost adaugat cu succes la sfarsitul fisierului!\n");
}

void modifyStruct() {
    int count;
    State *tab = loadFile(&count);
    if(!tab || count == 0) {
        printf("Fisierului este gol sau nu exista!\n");
        if(tab) free(tab);
        return;
    }

    int nr;
    printf("Introduceti numarul de ordine al statului pe care doriti sa il modificati (1-%d): ", count);
    scanf("%d", &nr);

    if(nr < 1 || nr > count) {
        printf("Numarul de ordine este invalid!\n");
        free(tab);
        return;
    }

    printf("\n--- Introduceti NOILE date pentru statul %d ---\n", nr);
    rintf("Denumirea statuslui: ");
    scanf(" %[^\n]", (tab + (nr - 1))->name);
    printf("Capitala: ");
    scanf(" %s[^\n]", (tab + (nr - 1))->capital);
    printf("Suprafata (km2): ");
    scanf("%lf", (tab + (nr - 1))->area);
    printf("Populatia: ");
    scanf("%lld", (tab + (nr - 1))->population);
    printf("Produsul Intern Brut (mld EUR): ");
    scanf("%lf", (tab + (nr - 1))->pib);

    saveMatrix(tab, count);
    free(tab);
    printf("Inregistrarea a fost modificata!\n");
}

void searchName() {
    FILE *f = fopen(FILE_NAME, "r");
    if(!f) {
        printf("Fisierul nu exista!\n");
        return;
    }

    char nameSearched[100];
    printf("Introduceti denumirea statului cautat: ");
    scanf(" %[^\n]", nameSearched);

    State s;
    int found = 0;
    printf("\n--- Rezultatele cautarii ---\n");
    while(readState(f, &s)) {
        if(strcasecmp(s.name, nameSearched) == 0) {
            printf("Stat: %s | Capitala: %s | Suprafata: %.1f km2 | Populatie: %lld loc. | PIB: %.2f mld. EUR\n",
                s.name, s.capital, s.area, s.population, s.pib);
            found = 1;
        }
    }

    if(!found) printf("Nu s-a gasiti nici un stat cu denumirea '%s'.\n", nameSearched);
    fclose(f);
}

void sortFile() {
    int count;
    State *tab = loadFile(&count);
    if(!tab || count == 0) {
        printf("Fisierul este gol sau nu exista!\n");
        if(tab) free(tab);
        return;
    }

    int opt;
    printf("\n--- Selectati criteriul de sortare ---\n");
    printf("1. Dupa denumire (Camp de tip String)\n");
    printf("2. Dupa populatie (Camp de tip Integer/Numeric)\n");
    printf("Optiunea: ");
    scanf("%d", &opt);

    for(int i = 0; i < count - 1; i ++) {
        for(int j = 0; j < count - i - 1; j++) {
            int toChange = 0;
            if(opt == 1)
                if(strcmp((tab + i)->name, (tab + (j + 1))->name) > 0) toChange = 1;
            else if(opt == 2)
                if((tab + j)->population > (tab + (j + 1))-> population) toChange = 1;
            
            if(toChange) {
                State *temp = (tab + j);
                *(tab + j) = *(tab + (j + 1));
                *(tab + (j + 1)) = *temp;
            }
        }
    }

    saveMatrix(tab, count);
    free("Fisierul textual a fost sortat conform criteriului ales!\n");
}

void purgeStruct() {
    int count;
    State *tab = loadFile(&count);
    if(!tab || count == 0) {
        printf("Fisierul este gol sau nu exista!\n");
        if(tab) free(tab);
        return;
    }

    int nr;
    printf("Introduceti numarul de ordine al statului pe care vreti sa il eliminati (1-%d): ", count);
    scanf("%d", &nr);

    if(nr < 1 || nr > count) {
        printf("Numar de ordine invalid!\n");
        free(tab);
        return;
    }

    for(int i = nr - 1; i < count - 1; i++) *(tab + i) = *(tab + (i + 1));
    count--;

    saveMatrix(tab, count);
    free(tab);
    printf("\nStructura selectata a fost eliminata din fisier!\n");
}