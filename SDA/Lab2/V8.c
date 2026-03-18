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
    iPasOS,
    Android,
    
    // Carti Electronice
    // Android poate fi folosit pentru carti electronice
    Linux,
    InkBox,
    Kindle,
    Kobo,
};

typedef struct {
    enum Type type;
    enum Manufacturers prod;
    float displaySize;
    enum OS os;
    int cores;
    int price;
} Tablete;

int main() {
    printf("We are cooked!...\n");
    
    return 1;
}