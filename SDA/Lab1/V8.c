#include <stdio.h>

/// Laboratorul nr. 1 la Structuri de Date si Algoritm
/// Realizat de Smolenschi Petru, TI-252FR

/// Sarcina lucrarii:
/* 
Elaborarea unui program C care va crea un meniu recursiv. Acesta trebuie sa cuprinda urmatoarele 
functii in C (cu apelare ulterioara ale acestora in functia main()):
    1. Introducerea valorilor tabloului de la tastatura;
    2. Completarea tabloului cu valori random;
    3. Afisarea elementelor tabloului la ecran;
    4. Sortarea elementelor tabloului conform variantelor:
        1) Bubble Sort;
        2) Selection Sort;
        3) Insertion Sort;
        4) Merge Sort;
        5) Quick Sort;
        6) Shell Sort;
        7) Counting Sort;
        8) Heap Sort
        9) Radix Sort;
        10) Comb Sort;
    5. Eliberarea memoriei si iesirea din program

P.S. Dupa fiecare manipulare a datelor sa fie prevazuta afisarea rezultatelor ca si concluzie.
Algoritmul functiilor va fi programat, reiesind din continutul problemei in doua versiuni:
    A. cu utilizarea metodei de transmitere a parametrilor functiilor prin valoare;
    B. cu utilizarea metodei de transmitere a parametrilor functiilor prin adresa / pointeri
        (parametrul formal va fi un pointer catre valoare obiectului corespaunzator)

! Varianta 8
1. Se da un array unidimensional cu elementele de tip integer si un numar impar n (conditia
    data trebuie sa se verifice in program!), valoarea caruia este citita de la tastatura. Sa
    se afiseze array-ul original si array-ul modificat dupa fiecare manipulare a datelor din array,
    afisarea rezultatelor ca si concluzie (De ex.: Nu exista numere prime; Nu exista asa element cu
    indexul dat si alte date stipulate in conditia problemei) etc.

        A. Daca primul element, numar negativ, intalnit in array, se afla pe pozitie para, atunci sa
            sorteze elementele array-ului crescator, aplicand tehnica de sortare HeapSort, altfel sa
            se sorteze elementele array-ului descrescator, aplicand tehnica de sortare CountingSort.
        B. Daca suma elementelor pare a array-ului este mai mica decat media aritmetica a elementelor
            impare din array, atunci sa se sorteze elementele array-ului descrescator, aplicand tehnica
            de sortare RadixSort, altfel sa se sorteze elementele array-ului crescator, aplicand tehnica
            de sortare CombSort.
        C. Daca exista cel putin doua elemente numere prime, atunci sa se sorteaze elementele array-ului
            crescator, aplicand tehnica de sortare MergeSort, altfel sa se sorteze elementele array-ului
            descrescator, aplicand tehnica de sotare BubbleSort.

2. Se da un array bidimensional cu elemente de tip integer si un numar natural n(n >= 0), valoarea caruia
    este citita de la tastatura. Sa se afiseze array-ul original si array-ul modificat dupa fiecare manipulare
    a datelokr din array, afisarea rezultatelor ca si in concluzie (De ex.L Nu exista numere prime; Nu exista
    elemente cu indexul dat si alte date stipulate in conditia problemei) etc.

        A. Daca produsul elementelor de pe prima coloana este mai mare decat valoarea lui k, declarata ca o
            constanta globala, atunci sa se sorteze crescator elementele de pe diagonala principala a array-ului,
            aplicand tehnica de sortare QuickSort, altfel sa se sorteze descrescator elementele de pe diagonala
            secundara a array-ului, aplicand tehnica de sortare ShellSort.
        B. Daca elementul minim din array se afla cel putin o data pe linie impara, atunci sa se sorteze crescator
            elementele liniei in care se afla elementul minim, aplicand tehnica de sortare SelectionSort, altfel sa
            se sorteze descrescator elementele de pe coloana in care se afla elementul minim, aplicand tehnica de
            sortare InsertionSort.
*/

int main() {
    printf("Laborator 1 SDA\nMeniu:\n");

    return 0;
}