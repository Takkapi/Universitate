#include <stdio.h>
#include <stdlib.h>

int *mem_alloc(int size) {
    int *arr = (int*)malloc(size * sizeof(int));
    if(arr == NULL) {
        printf("Nu s-a putut aloca memorie pentru array!.\n EXITING PROGRAM...");
        exit(-1);
    }

    return arr;
}

int main() {
    int n, *arr = NULL;

    scanf("%d", &n);

    arr = mem_alloc(n);

    for(int i = 0; i < n; i++) 
        scanf("%d", (arr + i));
    

    printf("Printing the fucking pointer array type shit: ");
    for(int i = 0; i < n; i++) 
        printf("%d ", *(arr + i));
    
    printf("\n");

    return 0;
}