#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int k = 69;

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
    a datelor din array, afisarea rezultatelor ca si in concluzie (De ex.: Nu exista numere prime; Nu exista
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

#pragma region Utils

void clrscr() {
    // !!! NOTA !!!
    // A SE SECHIMBA COMANDA DIN ARGUMENTUL FUNCTIEI 'system();' IN DEPENDENTA DE SISTEMUL DE OPERARE
    // WINDOWS: 'system("cls");'
    // UNIX/LINUX/MAC: 'system("clear");'
    system("clear");
    //system("cls");
}

// Afisarea array-ului
void print_arr(int *arr, int *clone, int size) {
    
    printf("\nArray-ul original: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", *(clone + i));
    }

    printf("\nElementele array-ului dupa manipulare: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }

    printf("\n\n");
}

void print_mat(int **mat, int **clone, int size) {
    printf("\nMatricea originala:\n");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%d\t", *(*(clone + i) + j));
        }
        printf("\n");
    }

    printf("\nElementele matricei dupa manipulare: \n");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%d\t", *(*(mat + i) + j));
        }
        printf("\n");
    }

    printf("\n");
}

// Swap
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int isPrime(int number) {

    if(number <= 1) return 0;

    for(int i =  2; i * i <= number; i++) {
        if(number % i == 0) return 0;
    }

    return 1;
}

void *clone_arr(int *arr, int *clone, int size) {
    for(int i = 0; i < size; i++) 
        *(clone + i) = *(arr + i);
}

void *clone_mat(int **mat, int **clone, int size) {
    for(int i = 0; i < size; i++) 
        for(int j = 0; j < size; j++) 
            *(*(clone + i) + j) = *(*(mat + i) + j);
}

// Eliberarea memoriei
void free_mem(int *arr, int **mat) {
    if(arr != NULL)
        free(arr);
    
    if(mat != NULL)
        free(mat);
    
    printf("Memoria a fost eliberata cu succes!\n");
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

// Alocarea memoriei pentru matrice
int *mem_alloc_mat(int size) {
    int *mat = (int*)malloc(size * size * sizeof(int));
    if(mat == NULL) {
        printf("Nu s-a putut aloca memorie pentru matrice!.\n EXITING PROGRAM...");
        exit(-1);
    }

    return mat;
}

void input8_1(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        printf("Dati valoare elementului %d: ", i);
        scanf("%d", (arr + i));
    }

    printf("Valorile introduse in array: ");
    for(int i = 0; i < size; i++)
        printf("%d ", *(arr + i));
    
    printf("\n");
}

void input8_2(int **mat, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("Dati valoare elementului de pe pozitia [%d, %d]: ", i, j);
            scanf("%d", (*(mat + i)) + j);
        }
    }

    printf("Valorile introduse in matrice:\n");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%d\t", *(*(mat + i) + j));
        }
        printf("\n");
    }
}

// Completarea array-ului cu valori random
void random_fill(int *arr, int size) {
    srand(time(NULL));
    for(int i = 0; i < size; i ++) 
        *(arr + i) = rand() % 100;

    printf("Valorile random introduse in array: ");
    for(int i = 0; i < size; i++)
        printf("%d ", *(arr + i));
    
    printf("\n");
}

void random_fill_mat(int **mat, int size) {
    srand(time(NULL));
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            *(*(mat + i) + j) = rand() % 100;
        }
    }

    printf("Valorile random introduse in matrice:\n");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%d\t", *(*(mat + i) + j));
        }
        printf("\n");
    }
}

#pragma endregion

#pragma region Sortari
// HEAPSORT -> Crescator
void heapify(int *arr, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < size && *(arr + left) > *(arr + largest)) largest = left;
    if(right < size && *(arr + right) > *(arr + largest)) largest = right;

    if(largest != i) {
        swap(arr + i, arr + largest);

        heapify(arr, size, largest);
    }
}

void heap_sort(int *arr, int size) {
    for(int i = size / 2 - 1; i >= 0; i--) heapify(arr, size, i);

    for(int i = size - 1; i >= 0; i--) {
        swap(arr, arr + i);
        heapify(arr, i, 0);
    }
}

// COUNTING SORT -> Descrescator
void counting_sort(int *arr, int size) {
    int i, max = *arr;
    
    for(int i = 1; i < size; i++) {
        if(*(arr + i) > max) max = *(arr + i);
    }

    int bucket[max + 1];
    for(i = 0; i <= max; i++) bucket[i] = 0;
    for(i = 0; i < size; i++) bucket[*(arr + i)]++;

    int j = 0;
    for(i = max; i >= 0; i--) {
        while(bucket[i] > 0) {
            *(arr + j++) = i;
            bucket[i]--;
        }
    }
}

// RADIX SORT -> Descrescator
void radix_sort(int *arr, int size) {
    int i, m = *arr, exp = 1;
    int bucket[size], b[size];

    for(i = 0; i < size; i++) {
        if(*(arr + i) > m) m = *(arr + i);
    }

    while(m / exp > 0) {
        int bucket_count[10] = {0};
        for(i = 0; i < size; i++) bucket_count[9 - *(arr + i) / exp % 10]++;
        for(i = 1; i < 10; i++) bucket_count[i]  += bucket_count[i - 1];
        for(i = size - 1; i >= 0; i--) b[--bucket_count[9 - *(arr + i) / exp % 10]] = *(arr + i);
        for(i = 0; i < size; i++) *(arr + i) = b[i];

        exp *= 10;
    }
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
                swap(arr + i, arr + j);
                swapped = 1;
            }
        }
    }
}

// MERGE SORT -> Crescator
void merge(int *arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int Left[n1], Right[n2];

    for(i = 0; i < n1; i++) Left[i] = *(arr + (left + i)); 
    for(j = 0; j < n2; j++) Right[j] = *(arr + (mid + 1 + j));

    i = 0, j = 0, k = left;
    while(i < n1 && j < n2) {
        if(Left[i] <= Right[j]) {
            *(arr + k) = Left[i];
            i++;
        } else {
            *(arr + k) = Right[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        *(arr + k) = Left[i];
        i++;
        k++;
    }

    while(j < n2) {
        *(arr + k) = Right[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int left, int right) {
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
            if(*(arr + j) < *(arr + j + 1))
                swap(arr + j, arr + j + 1);
        }
    }
}

// QUICK SORT -> Crescator
int partition(int *arr, int low, int high) {
    int pivot_index = low + (rand() % (high - low));
    if(pivot_index != high) swap((arr + pivot_index), (arr + high));

    int pivot_value = *(arr + high);
    int i = low;

    for(int j = low; j < high; j++) {
        if(*(arr + j) <= pivot_value) {
            swap((arr + i), (arr + j));
            i++;
        }
    }

    swap((arr + i), (arr + high));
    return i;
}

void quicksort_recursion(int *arr, int low, int high) {
    if(low < high) {
        int pivot_index = partition(arr, low, high);
        quicksort_recursion(arr, low, pivot_index - 1);
        quicksort_recursion(arr, pivot_index + 1, high);
    }
}

void quicksort(int *arr, int size) {
    srand(time(NULL));
    quicksort_recursion(arr, 0, size - 1);
}

// SHELL SORT -> Descrescator
int shell(int *arr, int size) {
    for(int i = size / 2; i > 0; i /= 2) {
        for(int j = i; j < size; j += 1) {
            int temp = *(arr + j);
            int k;
            for(k = j; k >= i && *(arr + (k - i)) < temp; k -= i) 
                *(arr + k) = *(arr + (k - i));
            
            *(arr + k) = temp;
        }
    }

    return 0;
}

// SELECTION SORT -> Crescator
int selection_sort(int *arr, int size) {
    for(int i = 0; i < size - 1; i++) {
        int min = i;
        for(int j = i + 1; j < size; j++) {
            if(*(arr + j) < *(arr + min)) min = j;
        }

        if(min != i)
            swap(arr + i, arr + min);
    }
}

// INSERTION SORT -> Descrescator
void insertion_sort(int *arr, int size) {
    int i, key, j;
    for(i = 1; i < size; i++) {
        key = *(arr + i);
        j = i - 1;

        while(j >= 0 && *(arr + j) < key) {
            *(arr + (j + 1)) = *(arr + j);
            j = j - 1;
        }
        *(arr + (j + 1)) = key;
    }
}

#pragma endregion

#pragma region Variante

void v8_1A(int *arr, int size) {
    int negPar = 0;

    int *clone = (int*)malloc(size * sizeof(int));
    clone_arr(arr, clone, size);

    for(int i = 0; i < size; i++) {
        if(*(arr + i) < 0 && i % 2 == 0) {
            negPar = 1;
            break;
        } else negPar = 0;
    }

    if(negPar) heap_sort(arr, size);
    else counting_sort(arr, size);

    print_arr(arr, clone, size);
    free(clone);
}

void v8_1B(int *arr, int size) {
    int sumPar = 0, sumImp = 0, impNum = 0, medImp;

    int *clone = (int*)malloc(size * sizeof(int));
    clone_arr(arr, clone, size);

    for(int i = 0; i < size; i++) {
        if(*(arr + i) % 2 == 0) sumPar += *(arr + i);
        else {
            sumImp += *(arr + i);
            impNum++;
        }
    }

    medImp = sumImp / impNum;

    if(sumPar < medImp) 
        radix_sort(arr, size);
    else
        comb_sort(arr, size);

    print_arr(arr, clone, size);
    free(clone);
}

void v8_1C(int *arr, int size) {
    int primes = 0;

    int *clone = (int*)malloc(size * sizeof(int));
    clone_arr(arr, clone, size);

    for(int i = 0; i < size; i++)
        if(isPrime(*(arr + i))) primes++;
    
    if(primes > 1) {
        mergeSort(arr, 0, size - 1);
    } else {
        bubble_sort(arr, size);
    }

    print_arr(arr, clone, size);
    free(clone);
}

void v8_2A(int **mat, int size, int *arr) {
    int prod = 1;

    int *clone = (int*)malloc(size * size * sizeof(int));
    clone_mat(mat, clone, size);

    for(int i = 0; i < size; i++) 
        prod *= *(*(mat + i));

    if(prod >= k) {
        // Diagonala principala
        for(int i = 0; i < size; i++)
            *(arr + i) = *(*(mat + i) + i);
        
        quicksort(arr, size);
        
        for(int i = 0; i < size; i++)
            *(*(mat + i) + i) = *(arr + i);
    } else {
        // Diagonala secundara
        for(int i = 0; i < size; i++) 
            *(arr + i) = *(*(mat + i) + (size - 1 - i));
        
        shell(arr, size);
        
        for(int i = 0; i < size; i++) 
        *(*(mat + i) + (size - 1 - i)) = *(arr + i);
    }

    print_mat(mat, clone, size);
    free(clone);
}

void v8_2B(int **mat, int size, int *arr) {
    int isNegOnOdd = 0, isLowest = 0, line, lowestLine, min = 999;

    int *clone = (int*)malloc(size * size * sizeof(int));
    clone_mat(mat, clone, size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(*(*(mat + i) + j) < 0 && i % 2 == 1) {
                isNegOnOdd = 1;
                line = i;
                printf("%d on %d\n", *(*(mat + i) + j), i);
            }
            if(*(*(mat + i) + j) <= min) {
                min = *(*(mat + i) + j);
                isLowest = 1;
                lowestLine = i;
            }
        }
    }

    if(isNegOnOdd) {
        for(int j = 0; j < size; j++) 
            *(arr +j) = *(*(mat + line) + j);
        
        selection_sort(arr, size);

        for(int j = 0; j < size; j++) 
            *(*(mat + line) + j) = *(arr + j);
    } else {
        if(isLowest)
            for(int j = 0; j < size; j++) 
                *(arr + j) = *(*(mat + lowestLine) + j);

        insertion_sort(arr, size);

        for(int j = 0; j < size; j++) 
            *(*(mat + lowestLine) + j) = *(arr + j);
    }
    
    print_mat(mat, clone, size);
    free(clone);
}

#pragma endregion

// Meniu
void menu(int *arr, int **mat, int size) {
    int option;

    // Printarea variantelor de problema
    printf("\nMENIU\n");
    
    printf("\n1) V8.1 - Alocarea memoriei\n");
    printf("2) V8.1 - Introducerea valorilor de la tastatura\n");
    printf("3) V8.1 - Completarea array-ului cu valori random\n");
    printf("4) V8.1 - Subprogramul A\n");
    printf("5) V8.1 - Subprogramul B\n");
    printf("6) V8.1 - Subprogramul C\n");

    printf("\n7) V8.2 - Alocarea memoriei\n");
    printf("8) V8.2 - Introducerea valorilor de la tastatura\n");
    printf("9) V8.2 - Completarea array-ului cu valori random\n");
    printf("10) V8.2 - Subprogramul A\n");
    printf("11) V8.2 - Subprogramul B\n");

    printf("\n99) Eliberarea memoriei\n");
    printf("\n0) Finisarea programului\n");
    printf("\nAlegeti programul: ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            clrscr();
            while(size < 0 || size % 2 != 1) {
                printf("Introduceti dimensiunea array-ului: ");
                scanf("%d", &size);
            }

            arr = mem_alloc(size);
            break;
        
        case 2:
            clrscr();
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                input8_1(arr, size);
            break;
        
        case 3:
            clrscr();
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else
                random_fill(arr, size);
            break;
        
        case 4:
            clrscr();
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                v8_1A(arr, size);
            break;

        case 5:
            clrscr();
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                v8_1B(arr, size);
            break;

        case 6:
            clrscr();
            if(arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                v8_1C(arr, size);
            break;

        case 7:
            clrscr();
            while(size < 0) {
                printf("Introduceti dimensiunea matricei: ");
                scanf("%d", &size);
            }

            *mat = mem_alloc_mat(size);
            arr = mem_alloc(size);
            break;

        case 8:
            clrscr();
            if(mat == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                input8_2(mat, size);
            break;
        
        case 9:
            clrscr();
            if(mat == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                random_fill_mat(mat, size);
            break;

        case 10:
            clrscr();
            if(mat == NULL || arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                v8_2A(mat, size, arr);
            break;

        case 11:
            clrscr();
            if(mat == NULL || arr == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else 
                v8_2B(mat, size, arr);
            break;

        case 99:
            clrscr();
            if(arr == NULL && mat == NULL)
                printf("Error! Array-ul nu a fost alocat.\n");
            else free_mem(arr, mat);
            break;
        case 0:
            exit(0);
        default:
            clrscr();
            printf("Invalid subprogram!\n");
            break;
    }

    menu(arr, mat, size);
}

int main() {
    int *arr = NULL, **mat = NULL;
    int size = -1;
    
    printf("Laborator 1 - SDA\n");

    menu(arr, mat, size);

    return 0;
}