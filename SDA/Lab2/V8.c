#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void clrscr() {
    // !!! NOTA !!!
    // A SE SECHIMBA COMANDA DIN ARGUMENTUL FUNCTIEI 'system();' IN DEPENDENTA DE SISTEMUL DE OPERARE
    // WINDOWS: 'system("cls");'
    // UNIX/LINUX/MAC: 'system("clear");'
    system("clear");
    //system("cls");
}

enum Type {
    Tableta,
    CarteElectronica,
    TabletaGrafica
};

enum Manufacturers {
    // Tablete
    Apple,
    Lenovo,
    Huawei,
    Samsung,
    Motorola,
    Realme,
    
    // Carti Electronice
    Amazon,
    Rakuten,
    Onyx,

    // Tablete Grafice
    Wacom,
    Huion,
    XP_Pen,
};

enum OS {
    // Tablete
    iPadOS,
    Android,
    
    // Carti Electronice
    // Android poate fi folosit pentru carti electronice
    Linux,
    InkBox,
    Kindle,
    Kobo,

    // Tableta Grafica
    None,
};

typedef struct {
    enum Type type;
    enum Manufacturers prod;
    float displaySize;
    enum OS os;
    int cores;
    int price;
} Tablete;

static inline char *stringFromType(enum Type t) {
    static const char *strings[] = { "Tableta", "Carte Electroica", "Tableta Grafica" };

    return strings[t];
}

static inline char *stringFromManufacturer(enum Manufacturers m) {
    static const char *strings[] = { "Apple", "Lenovo", "Huawei", "Samsung", "Motorola", "Realme", "Amazon", "Rakuten", "Onyx", "Wacom", "Huion", "XP-Pen" };

    return strings[m];
}

static inline char *stringFromOS(enum OS os) {
    static const char *strings[] = { "iPadOS", "Android", "Linux", "InkBox", "Kindle", "Kobo", "None" };

    return strings[os];
}

Tablete *mem_alloc(int size) {
    Tablete *arrTab = (Tablete*)malloc(size * sizeof(Tablete));
    if(arrTab == NULL) {
        printf("Nu s-a putut aloca memorie pentru array!.\n EXITING PROGRAM...");
        exit(-1);
    }

    return arrTab;
}

int *mem_alloc_arr(int size) {
    int *arr = (int*)malloc(size * sizeof(int));
    if(arr == NULL) {
        printf("Nu s-a putut aloca memorie pentru array!.\n EXITING PROGRAM...");
        exit(-1);
    }

    return arr;
}

void chooseManufacturer(Tablete tab, int choice) {
    if(choice == 1) {
        printf("1) Apple\n");
        printf("2) Lenovo\n");
        printf("3) Huawei\n");
        printf("4) Samsung\n");
        printf("5) Motorola\n");
        printf("6) Realme\n");
        printf("Selecteaza o optiune: ");
        scanf("%d", choice);

        switch(choice) {
            case 1:
                tab.prod = Apple;
                break;
            case 2:
                tab.prod = Lenovo;
                break;
            case 3: 
                tab.prod = Huawei;
                break;
            case 4:
                tab.prod = Samsung;
                break;
            case 5:
                tab.prod = Motorola;
                break;
            case 6: 
                tab.prod = Realme;
                break;
            default:
                printf("Optiune invalida!\n");
                break;
        }
    } else if(choice == 2) {
        printf("1) Amazon\n");
        printf("2) Rakuten\n");
        printf("3) Onyx\n");
        printf("Selecteaza o optiune: ");
        
        printf("Selecteaza o optiune: ");
        scanf("%d", choice);

        switch(choice) {
            case 1:
                tab.prod = Amazon;
                break;
            case 2:
                tab.prod = Rakuten;
                break;
            case 3: 
                tab.prod = Onyx;
                break;
            default:
                printf("Optiune invalida!\n");
        }
    }
}

void input(Tablete *tabArr, int size) {
    int choice, temp;
    printf("Inroducerea valorilor:\n");

    for(int i = 0; i < size; i++) {
        printf("Selectati un tip de mai jos pentru tabelul [%d]\n", i);

        printf("0) Tableta\n");
        printf("1) Carte Electronica\n");
        printf("2) Tableta Grafica\n");
        printf("Selecteaza o optiune: ");
        scanf("%d", &choice);
        
        temp = choice;
        
        tabArr[0].type = choice;
        // switch(choice) {
        //     case 1:
        //         tabArr[i].type = Tableta;
        //         break;
        //     case 2:
        //         tabArr[i].type = CarteElectronica;
        //         break;
        //     case 3: 
        //         tabArr[i].type = TabletaGrafica;
        //         break;
        // }

        printf("\n");
        if(choice == 0) {
            printf("0) Apple\n");
            printf("1) Lenovo\n");
            printf("2) Huawei\n");
            printf("3) Samsung\n");
            printf("4) Motorola\n");
            printf("5) Realme\n");
            printf("Selecteaza o optiune: ");
            scanf("%d", &choice);

            tabArr[i].prod = choice;
        } else if(choice == 1) {
            printf("0) Amazon\n");
            printf("1) Rakuten\n");
            printf("2) Onyx\n");
            printf("Selecteaza o optiune: ");
            scanf("%d", &choice);

            tabArr[i].prod = choice + 6;
        } else if(choice == 2) {
            printf("0) Wacom\n");
            printf("1) Huion\n");
            printf("2) XP-Pen\n");
            printf("Selecteaza o optiune: ");
            scanf("%d", &choice);

            tabArr[i].prod = choice + 9;
        }
        // printf("Selecteaza o optiune: ");
        // scanf("%d", &choice);

        // tabArr[0].prod = choice;

        printf("\nDimensiune ecran: ");
        scanf("%f", &tabArr[i].displaySize);

        printf("\n");
        choice = temp;
        if(choice == 0) {
            printf("0) iPasOS\n");
            printf("1) Android\n");
            scanf("%d", &choice);

            tabArr[i].os = choice;
        } else if(choice == 1) {
            printf("0) Android\n");
            printf("1) Linux\n");
            printf("2) InkBox\n");
            scanf("%d", &choice);

            tabArr[i].os = choice + 1;
        }

        tabArr[i].os = iPadOS;
        tabArr[i].cores = 8;
        tabArr[i].price = 899;
        // chooseType(tabArr, choice);
    }
}

void showTabArray(Tablete *tabArr, int size) {
    for(int i = 0; i < size; i++) {
        printf(
            "[%d] %s\t%s\t%.1f\t%s\t%d\t%d\n",
            i,
            stringFromType(tabArr[i].type),
            stringFromManufacturer(tabArr[i].prod),
            tabArr[i].displaySize,
            stringFromOS(tabArr[i].os),
            tabArr[i].cores,
            tabArr[i].price);
    }
}

void menu(Tablete *tabArr, int *arr, int size) {
    int option;

    printf("\nMENIU\n");

    printf("\n1) Alocarea memoriei\n");
    printf("2) Introducerea valorilor de la tastatura\n");
    printf("3) Afisarea elementelor din array\n");
    printf("4) Sortarea crescatoare dupa preturi (Quick Sort)\n");
    printf("5) Sortarea descrescatoare dupa dimensiunea ecranului (Quick Sort)\n");
    printf("0) Iesire\n");
    printf("\nAlegeti optiunea: ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            clrscr();
            printf("Introduceti dimensiunea array-ului: ");
            scanf("%d", &size);
            
            tabArr = mem_alloc(size);
            arr = mem_alloc_arr(size);
            break;
        case 2:
            clrscr();
            input(tabArr, size);

            break;
        case 3:
            clrscr();
            showTabArray(tabArr, size);

            break;

        case 0:
            printf("Iesire program...\n");
            free(tabArr);
            free(arr);
            exit(0);
            
        default:
            printf("Optiune invalida");
            break;
    }

    menu(tabArr, arr, size);
}

int main() {
    Tablete *tabArr = NULL;
    int size, *arr = NULL;

    printf("Laborator 1 - SDA\n");

    menu(tabArr, arr, size);

    printf("\u2713\n");

    return 0;
}