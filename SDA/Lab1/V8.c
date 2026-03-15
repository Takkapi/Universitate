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
// HEAPSORT -> Crescator
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

// COUNTING SORT -> Descrescator
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

// RADIX SORT -> Descrescator
void radix_sort(int arr[], int size) {
    int i, m = arr[0], exp = 1;
    int bucket[size], b[size];

    for(i = 0; i < size; i++) {
        if(arr[i] > m) m = arr[i];
    }

    while(m / exp > 0) {
        int bucket_count[10] = {0};
        for(i = 0; i < size; i++) bucket_count[9 - arr[i] / exp % 10]++;
        for(i = 1; i < 10; i++) bucket_count[i]  += bucket_count[i - 1];
        for(i = size - 1; i >= 0; i--) b[--bucket_count[9 - arr[i] / exp % 10]] = arr[i];
        for(i = 0; i < size; i++) arr[i] = b[i];

        exp *= 10;
    }

    print_arr(arr, size);
}

// COMBSORT -> Crescator
void comb_sort(int *arr, int size) {
    int gap = size;
    int i, j, temp;
    int swapped = 1;

    while(gap > 1 || swapped) {
        gap = gap * 10 / 13;

        if(gap == 9 || gap == 10) gap = 11;
        if(gap < 1) gap = 1;

        swapped = 0;
        for(i = 0, j = gap; j < size; i++, j++) {
            if(*(arr + i) > *(arr + j)) {
                temp = *(arr  + i);
                *(arr + i) = *(arr + j);
                *(arr + j) = temp;
                swapped = 1;
            }
        }
    }

    print_arr(arr, size);
}

// MERGE SORT -> Crescator
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int Left[n1], Right[n2];

    for(i = 0; i < n1; i++) Left[i] = arr[left + i];
    for(j = 0; j < n2; j++) Right[j] = arr[mid + 1 + j];

    i = 0, j = 0, k = left;
    while(i < n1 && j < n2) {
        if(Left[i] <= Right[j]) {
            arr[k] = Left[i];
            i++;
        } else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = Left[i];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k] = Right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

// BUBBLE SORT -> Descrescator
void bubble_sort(int *arr, int size) {
    int i, j, temp;

    for(i = 0; i < size - 1; i++) {
        for(j = 0; j < size - i - 1; j++) {
            if(*(arr + j) < *(arr + j + 1)) {
                temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }

    print_arr(arr, size);
}

#pragma endregion

int isPrime(int number) {
    if(number <= 1) return 0;

    for(int i =  2; i * i <= number; i++) {
        if(number % i == 0) return 0;
    }

    return 1;
}

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

void v8_1B(int *arr, int size) {
    int sumPar = 0, sumImp = 0, impNum = 0, medImp;

    for(int i = 0; i < size; i++) {
        if(arr[i] % 2 == 0) sumPar += arr[i];
        else {
            sumImp += arr[i];
            impNum++;
        }
    }

    medImp = sumImp / impNum;

    if(sumPar < medImp) 
        radix_sort(arr, size);
    else
        comb_sort(arr, size);
}

void v8_1C(int *arr, int size) {
    int primes = 0;

    for(int i = 0; i < size; i++)
        if(isPrime(arr[i])) primes++;
    
    if(primes > 1) {
        printf("%d prime numbers -> MergeSort\n", primes);
        mergeSort(arr, 0, size - 1);
        print_arr(arr, size);
    } else {
        printf("%d prime numbers -> BubbleSort\n", primes);
        bubble_sort(arr, size);
    }
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
    printf("5) V8.1 - Subprogramul B\n");
    printf("6) V8.1 - Subprogramul C\n");
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

        case 5:
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                v8_1B(arr, size);
            break;

        case 6:
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                v8_1C(arr, size);
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