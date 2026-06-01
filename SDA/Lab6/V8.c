#include "muzeu.h"

/// Laboratorul nr. 6 la Structuri de Date si Algoritm
/// Realizat de Smolenschi Petru, TI-252FR

/// Sarcina lucrarii:
/*
Sa se scrie 3 fisiere-text in limbajul C pentru implementarea
si utilizarea tipului abstract de date "Lista simplu inlantuita"
cu asigurarea operatiilor de prelucrare de baza ale listei:
1. Fisier antet cu extensia .h, care contine specificarea structurii
    date a elementului listei simplu inlantuite (conform variantelor)
    si prototipurile functiilor de prelucrare de baza ale listei.
2. Fisier cu extensia .c, care contine implementarile (codurile)
    functiilor declarate in fisierul antet.
3. Fisier al utilizatorului, functia main() pentru prelucrarea listei de 
    afisare la ecran a urmatorului meniu de optiuni de baza:
        1. Crearea listei in memoria dinamica
        2. Introducerea informatiei despre elementele listei de la tastatura.
        3. Afisarea informatieie despre elementele listei la ecran.
        4. Cautarea elementului in lista.
        5. Modificarea campurilor unui element din lista.
        6. Determinarea andresei ultimului element din lista.
        7. Determinarea lungimii listei (numarul de elemente).
        8. Interschimbarea a doua elemente indicate in lista.
        9. Sortarea listei (utilizati o tehnica de sortare neimplementate in
            laboratoarele precedente).
        10. Eliberarea memoriei alocate pentru lista.
        0. Iesire din program.

! Varianta 8
Structura Muzeu cu campurile: denumirea, adresa, telefonul, numarul de exponate,
pretul biletului.
*/

int main() {
    Node* museumLists = NULL;
    int option;

    do {
        printf("\n============================ MENIU ============================\n");
        printf("1. Crearea listei in memoria dinamica\n");
        printf("2. Introducerea informatiei despre un element de la tastatura\n");
        printf("3. Afisarea informatiei despre elementele listei la ecran\n");
        printf("4. Cautarea elementului in lista\n");
        printf("5. Modificarea campurilor unui element din lista\n");
        printf("6. Determinarea adresei ultimului element din lista\n");
        printf("7. Determinarea lungimii listei\n");
        printf("8. Interschimbarea a doua elemente indicate in lista\n");
        printf("9. Sortarea listei (Insertion Sort dupa numar exponate)\n");
        printf("10. Eliberarea memoriei alocate pentru lista\n");
        printf("0. Iesire din program\n");
        printf("===============================================================\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &option);

        switch(option) {
            case 1: createList(&museumLists); break;
            case 2: insertElements(&museumLists); break;
            case 3: showList(museumLists); break;
            case 4: showElement(museumLists); break;
            case 5: modifyElements(museumLists); break;
            case 6: lastElementAddress(museumLists); break;
            case 7: {
                int len = listLength(museumLists);
                printf("Lungimea curenta a listei este de: %d elemente\n", len);
                break;
            }
            case 8: interchangeElements(museumLists); break;
            case 9: sortList(&museumLists); break;
            case 10: freeMemory(&museumLists); break;
            case 0:
                printf("Iesire din program...\n");
                freeMemory(&museumLists);
                break;
            default: printf("Optiune invalida!\n");
        }
    } while(option != 0);

    return 0;
}