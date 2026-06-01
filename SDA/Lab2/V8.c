#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Laboratorul nr. 2 la Structuri de Date si Algoritm
/// Realizat de Smolenschi Petru, TI-252FR

/// Sarcina lucrarii:
/*
Pentru tabloul unidimensional dat cu elemente de tip structura (conform variantelor) 
sa se afiseze la ecran urmatorul meniu recursiv de optiuni:
    1. Introducerea elementelor tabloului de la tastatura.
    2. Afisarea elementelor tabloului la ecran.
    3. Sortarea tabloului crescator/descrescator (2 tehnici de sortare la alegere).
    0. Iesire din program.

Sa se elaboreze funtiile pentru implementarea optiunilor meniului.

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

void introducereElemente(Tableta **tab, int *n);
void afisareElemente(Tableta *tab, int n);
void swap(Tableta *a, Tableta *b);
void bubbleSort(Tableta *tab, int n, int crescator);
void selectionSort(Tableta *tab, int n, int crescator);
void menu(Tableta *tab, int n);
void afisareMeniu(Tableta **tab, int *n);

int main() {
    Tableta *tab = NULL;
    int n = 0;

    afisareMeniu(&tab, &n);

    if(tab != NULL)
        free(tab);
    
    return 0;
}

void introducereElemente(Tableta **tab, int *n) {
    if(*tab != NULL) {
        free(*tab);
        *tab = NULL;
    }

    while(*n <= 0) {
        printf("\nIntroduceti numarul de tablete: ");
        scanf("%d", n);
    }

    *tab = (Tableta *)malloc((*n) * sizeof(Tableta));
    if(*tab == NULL) {
        printf("Eroare: Memoria nu a putut fi alocata!\n");
        exit(1);
    }

    for(int i = 0; i < *n; i++) {
        Tableta *p = *tab + i;
        
        printf("\n--- Date pentru Tableta %d ---\n", i + 1);

        printf("Tip (tableta / carte electronica / tableta grafica): ");
        scanf(" %[^\n]", p->tip);

        printf("Producator: ");
        scanf(" %[^\n]", p->producator);

        printf("Dimensiune ecran (inch): ");
        scanf("%f", &(p->dimensiune));

        printf("Sistem de operare: ");
        scanf(" %[^\n]", p->os);

        printf("Numar de nuclee: ");
        scanf("%d", &(p->cores));

        printf("Pret: ");
        scanf("%f", &(p->pret));
    }

    printf("\nDatele au fost introduse cu success\n");
}

void afisareElemente(Tableta *tab, int n) {
    if(tab == NULL || n == 0) {
        printf("\nTabloul este gol! Introduceti date mai intai.\n");
        return;
    }

    printf("%-3s | %-18s | %-15s | %-12s | %-18s | %-10s | %-10s\n",
            "Nr", "Tip", "Producator", "Dim. ecran", "Sistem Operare", "Nr Nuclee", "Pret");

    for(int i = 0; i < n; i++) {
        Tableta *p = tab + i;
        printf("%-3d | %-18s | %-15s | %-10.1f\" | %-18s | %-10d | %-10.2f\n",
                i + 1, p->tip, p->producator, p->dimensiune, p->os, p->cores, p->pret);
    }
}

void swap(Tableta *a, Tableta *b) {
    Tableta temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(Tableta *tab, int n, int crescator) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            int conditie = crescator ? ((tab + j)->pret > (tab + j + 1)->pret)
                                    : ((tab + j)->pret < (tab + j + 1)->pret);
            
            if(conditie) swap(tab + j, tab + j + 1);
        }
    }
}

void selectionSort(Tableta *tab, int n, int crescator) {
    for(int i = 0; i < n - 1; i++) {
        int idx_selectat = i;
        for(int j = i + 1; j < n; j++) {
            int conditie = crescator ? ((tab + j)->pret < (tab + idx_selectat)->pret)
                                    : ((tab + j)->pret < (tab + idx_selectat)->pret);
            
            if(conditie) idx_selectat = j;
        }
        if(idx_selectat != i) swap(tab + i, tab + idx_selectat);
    }
}

void menu(Tableta *tab, int n) {
    if(tab == NULL || n == 0) {
        printf("\nTabloul este gol! Nu exista elemente de sortat.\n");
        return;
    }

    int tehnica, ordine;
    printf("\n--- Optiuni Sortare (dupa pret) ---\n");
    printf("Alegeti tehnica de sortare:\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("Optinea tehnica: ");
    scanf("%d", &tehnica);

    printf("Alegeti ordinea de sortare:\n");
    printf("1. Crescator\n");
    printf("2. Descrescator\n");
    printf("Optiunea ordine: ");
    scanf("%d", &ordine);

    int esteCrescator = (ordine == 1);
    if(tehnica == 1) {
        bubbleSort(tab, n, esteCrescator);
        printf("Tabloul a fost sortat prin metoda Bubble Sort!\n");
    } else if(tehnica == 2) {
        selectionSort(tab, n, esteCrescator);
        printf("\nTabloul a fost sortat prin metoda Selection Sort!\n");
    } else printf("Tehnica selectata este invalida\n");
}

void afisareMeniuRecursiv(Tableta **tab, int *n) {
    int optiune;

    printf("\n============ MENIU PRINCIPAL ============\n");
    printf("1. Introducerea elementelor tabloului de la tastatura.\n");
    printf("2. Afisarea elementelor tabloului la ecran.\n");
    printf("3. Sortarea tabloului crescator/descrescator.\n");
    printf("0. Iesire din program.\n");
    printf("=========================================\n");
    printf("Alegeti o optiune: ");
    scanf("%d", &optiune);

    switch (optiune) {
        case 1:
            introducereElemente(tab, n);
            afisareMeniuRecursiv(tab, n);
            break;
        case 2:
            afisareElemente(*tab, *n);
            afisareMeniuRecursiv(tab, n);
            break;
        case 3:
            meniuSortare(*tab, *n);
            afisareMeniuRecursiv(tab, n);
            break;
        case 0:
            printf("\nIesire din program... Memoria a fost eliberata.\n");
            break;
        default:
            printf("\n[Eroare] Optiune invalida! Incercati din nou.\n");
            afisareMeniuRecursiv(*tab, n); 
            break;
    }
}