#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Afisarea array-ului
void print_arr(int *arr, int size) {
    printf("\nElementele array-ului: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n\n");
}

#pragma region Sortari
// HEAPSORT
void heapify(int *arr, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < size && *(arr + left) > *(arr + largest)) largest = left;
    if(right < size && *(arr + right) > *(arr + largest)) largest = right;

    if(largest != i) {
        int temp = *(arr + i);

        *(arr + i) = *(arr + largest);
        *(arr + largest) = temp;

        heapify(arr, size, largest);
    }
}

void heap_sort(int *arr, int size) {
    for(int i = size / 2 - 1; i >= 0; i--) heapify(arr, size, i);

    for(int i = size - 1; i >= 0; i--) {
        int temp = *(arr);
        *(arr) = *(arr + i);
        *(arr + i) = temp;
        heapify(arr, i, 0);
    }

    print_arr(arr, size);
}

// COUNTING SORT
void counting_sort(int arr[], int size) {
    int i, max = arr[0];
    
    for(int i = 1; i < size; i++) {
        if(arr[i] > max) max = arr[i];
    }

    int bucket[max + 1];
    for(i = 0; i <= max; i++) bucket[i] = 0;
    for(i = 0; i < size; i++) bucket[arr[i]]++;

    int j = 0;
    for(i = max; i >= 0; i--) {
        while(bucket[i] > 0) {
            arr[j++] = i;
            bucket[i]--;
        }
    }

    print_arr(arr, size);
}

#pragma endregion

void v8_1A(int *arr, int size) {
    int negPar = 0;

    for(int i = 0; i < size; i++) {
        if(arr[i] < 0 && i % 2 == 0) {
            negPar = 1;
            break;
        } else negPar = 0;
    }

    if(negPar) heap_sort(arr, size);
    else counting_sort(arr, size);
}

// Alocarea memoriei pentru array
int *mem_alloc(int size) {
    int *arr = (int*)malloc(size * sizeof(int));
    if(arr == NULL) {
        printf("Nu s-a putut aloca memorie pentru array!.\n EXITING PROGRAM...");
        exit(-1);
    }

    return arr;
}

void input8_1(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        printf("Dati valoare elementului %d: ", i);
        scanf("%d", &arr[i]);
    }

    print_arr(arr, size);
}

// Completarea array-ului cu valori random
void random_fill(int *arr, int size) {
    srand(time(NULL));
    for(int i = 0; i < size; i ++) {
        arr[i] = rand() % 100;
    }

    print_arr(arr, size);
}

// Eliberarea memoriei
void free_mem(int *arr) {
    free(arr);
    printf("Memoria a fost eliberata cu succes!\n");
}

// Meniu
void menu(int *arr, int size) {
    int option;

    // Printarea variantelor de problema
    printf("MENIU\n");
    printf("\n1) V8.1 - Alocarea memoriei\n");
    printf("2) V8.1 - Introducerea valorilor de la tastatura\n");
    printf("3) V8.1 - Completarea array-ului cu valori random\n");
    printf("4) V8.1 - Subprogramul A\n");
    printf("9) Eliberarea memoriei\n");
    printf("0) Finisarea programului\n");
    printf("\n Alegeti programul: ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            while(size < 0 || size % 2 != 1) {
                printf("Introduceti dimensiunea array-ului: ");
                scanf("%d", &size);
            }

            arr = mem_alloc(size);
            break;
        
        case 2:
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                input8_1(arr, size);
            break;
        
        case 3:
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                random_fill(arr, size);
            break;
        
        case 4:
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                v8_1A(arr, size);
            break;

        case 9:
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else free_mem(arr);
            break;
        case 0:
            exit(0);
        default:
            printf("Invalid subprogram!\n");
            break;
    }

    menu(arr, size);
}

int main() {
    int *arr = NULL;
    int size = 0;
    printf("Laborator 1 - SDA\n");

    menu(arr, size);

    return 0;
}