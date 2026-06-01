#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_FILE "stiva.txt"
#define QUEUE_FILE "queue.txt"

/// Laboratorul nr. 5 la Structuri de Date si Algoritm
/// Realizat de Smolenschi Petru, TI-252FR

/// Sarcina lucrarii:
/*
Sa se scrie un program in limbajul C pentru implementarea si utilizarea
tipului abstract de date "Stiva" si "Sir in asteptare" cu asigurarea
operatiilor de prelucrare de baza. Functia main() va afisa la ecran urmatorul
meniu de optiuni de baza:
    1. Crearea unei stive dinamice.
    2. Citirea datelor referitoare la elementele stivei de la tastatura.
    3. Afisarea datelor stivei intr-un fisier stiva.txt/stiva.bin.
    4. Cautarea elementului maximal din staiva dupa un camp numeric.
    5. Copierea datelor din stiva intr-un sir de astepatare (queue).
    6. Afisarea datelor sirului in asteptare intr-un fisier queue.txt/queue.bin
    7. Determinarea lungimii stivei (numarul de elemente).
    8. Modificarea campurilor unui element din stiva.
    9. Afisarea(Adaugarea) datelor modificate a elementului din stiva la sfarsitul
        fisierului stiva.txt/stiva.bin.
    10. Eliberarea memoriei alocate pentru stiva.
    11. Eliberarea memoriei alocate pentru Queue.
    0. Iesire din program.

! Varianta 8
Structura Automobil cu campurile: marca, anul producerii, tip combustibil, tip caroserie,
capacitate motor, culoare.
*/

typedef struct {
    char name[50];
    int prod_year;
    char fuel_type[30];
    char wheel_type[30];
    float engine;
    char color[30];
} Vehicle;

typedef struct Node {
    Vehicle data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void push(Node** top, Vehicle auto_data);
void showNodeFile(Node* top);
void searchMaxNode(Node* top);
int nodeSize(Node* top);
void modifyNodeElement(Node* top);
void addModifiedElementFile(Node* top);
void freeNode(Node** top);

void initQueue(Queue* q);
void enqueue(Queue* q, Vehicle auto_data);
void copyNodeInQueue(Node* top, Queue* q);
void showQueueFile(Queue* q);
void freeQueue(Queue* q);

Vehicle readVehicle();
void showVehicleConsole(Vehicle v);
void writeVehicleFile(FILE* f, Vehicle v);

int main() {
    Node* node = NULL;
    Queue queue;
    initQueue(&queue);

    int option;

    do {
        printf("\n============================ MENIU ============================\n");
        printf("1. Crearea unei stive dinamice\n");
        printf("2. Citirea datelor referitoare la elementele stivei de la tastatura\n");
        printf("3. Afisarea datelor stivei intr-un fisier %s\n", STACK_FILE);
        printf("4. Cautarea elementului maximal din stiva (dupa capacitate motor)\n");
        printf("5. Copierea datelor din stiva intr-un sir in asteptare (queue)\n"); // 
        printf("6. Afisarea datelor sirului in asteptare in fisierul %s\n", QUEUE_FILE);
        printf("7. Determinarea lungimii stivei\n");
        printf("8. Modificarea campurilor unui element din stiva\n");
        printf("9. Adaugarea datelor modificate la sfarsitul fisierului %s\n", STACK_FILE);
        printf("10. Eliberarea memoriei alocate pentru stiva\n");
        printf("11. Eliberarea memoriei alocate pentru Queue\n");
        printf("0. Iesire din program\n");
        printf("===============================================================\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                freeNode(&node);
                printf("Stiva dinamica a fost creata / initializata.\n");
                break;
            case 2:
                push(&node, readVehicle());
                printf("Automobil adaugat in stiva!\n");
                break;
            case 3:
                showNodeFile(node);
                break;
            case 4:
                searchMaxNode(node);
                break;
            case 5:
                copyNodeInQueue(node, &queue);
                break;
            case 6:
                showQueueFile(&queue);
                break;
            case 7:
                printf("Numarul de elemente din stiva: %d\n", nodeSize(node));
                break;
            case 8:
                modifyNodeElement(node);
                break;
            case 9:
                addModifiedElementFile(node);
                break;
            case 10:
                freeNode(&node);
                break;
            case 11:
                freeQueue(&queue);
                break;
            case 0:
                printf("Iesire din pogram...\n");
                freeNode(&node);
                freeQueue(&queue);
                break;
            default:
                printf("Optiune invalida!\n");
        }
    } while(option != 0);

    return 0;
}

Vehicle readVehicle() {
    Vehicle v;
    printf("\n--- Introduceti datele automobilului ---\n");
    printf("Marca: ");
    scanf(" %[^\n]", v.name);
    printf("Anul producerii: ");
    scanf("%d", &v.prod_year);
    printf("Tip combustibil: ");
    scanf(" %[^\n]", v.fuel_type);
    printf("Tip caroserie: ");
    scanf(" %[^\n]", v.wheel_type);
    printf("Capacitate motor (litri): ");
    scanf("%f", &v.engine);
    printf("Culoare: ");
    scanf(" %[^\n]", v.color);
    return v;
}

void writeVehicleFile(FILE* f, Vehicle v) {
    fprintf(f, "Marca: %s | An: %d | Combustibil: %s | Caroserie: %s | Motor: %.1f | Culoare: %s\n",
            v.name, v.prod_year, v.fuel_type, v.wheel_type, v.engine, v.color);
}

void showVehicleConsole(Vehicle v) {
    printf("Marca: %s | An: %d | Motor: %.1f L | Culoare: %s\n",
            v.name, v.prod_year, v.engine, v.color);
}

void push(Node** top, Vehicle auto_data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        printf("Eroare de alocare memorie!\n");
        return;
    }
    newNode->data = auto_data;
    newNode->next = *top;
    *top = newNode;
}

void showNodeFile(Node* top) {
    if(top == NULL) {
        printf("Stiva este goala!\n");
        return;
    }

    FILE *f = fopen(STACK_FILE, "w");
    if(!f) {
        printf("Nu se poate deschide fisierul %s!\n", STACK_FILE);
        return;
    }

    Node* temp = top;
    fprintf(f, "==== ELEMENTELE STIVEI ===\n");
    while(temp != NULL) {
        writeVehicleFile(f, temp->data);
        temp = temp->next;
    }

    fclose(f);
    printf("Datele stivei au fost salvate in fisierul %s.\n", STACK_FILE);
}

void searchMaxNode(Node* top) {
    if(top == NULL) {
        printf("Stiva este goala!\n");
        return;
    }

    Node* temp = top;
    Vehicle max_auto = temp->data;

    while(temp != NULL) {
        if(temp->data.engine > max_auto.engine) max_auto = temp->data;
        temp = temp->next;
    }

    printf("\nElementul cu capacitatea motorului maxima (%.1f L) este:\n", max_auto.engine);
    showVehicleConsole(max_auto);
}

int nodeSize(Node* top) {
    int count = 0;
    Node* temp = top;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void modifyNodeElement(Node* top) {
    int len = nodeSize(top);
    if(len == 0) {
        printf("Stiva este goala!\n");
        return;
    }

    int pos;
    printf("Introduceti pozitia elementului pe care doriti sa-l modificati (1 - %d, unde 1 este varful stivei): ", len);
    scanf("%d", &pos);

    if(pos < 1 || pos > len) {
        printf("Pozitie invalida!\n");
        return;
    }

    Node* temp = top;
    for(int i = 1; i < pos; i++) temp = temp->next;

    printf("\nAutomobilul actual la pozitia %d:\n", pos);
    showVehicleConsole(temp->data);

    printf("\nIntroduceti noile date:\n");
    temp->data = readVehicle();
    printf("Elementul a fost modificat!\n");
}

void addModifiedElementFile(Node* top) {
    int len = nodeSize(top);
    if(len == 0) {
        printf("Stiva este goala!\n");
        return;
    }

    int pos;
    printf("Introduceti pozitia elementului (1 - %d) pe care doriti sa-l adaugati la sfarsitul fisierului %s: ", len, STACK_FILE);
    scanf("%d", &pos);

    if(pos < 1 || pos > len) {
        printf("Pozitie invalida!\n");
        return;
    }

    Node* temp = top;
    for(int i = 1; i < pos; i++) temp = temp->next;

    FILE *f = fopen(STACK_FILE, "a");
    if(!f) {
        printf("Nu se poate deschide fisierul %s in modul append!\n", STACK_FILE);
        return;
    }

    fprintf(f, "--- ADAUGAT (MODIFICAT) ---\n");
    writeVehicleFile(f, temp->data);
    fclose(f);
    printf("Datele elementului au fost adaugate la sfarsitul fisierului %s!\n", STACK_FILE);
}

void freeNode(Node** top) {
    if(*top == NULL) return;
    Node* temp;
    while(*top != NULL) {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
    printf("Memoria stivei a fost eliberata.\n");
}

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueue(Queue* q, Vehicle auto_data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        printf("Eroare de alocare memorie pentru coada!\n");
        return;
    }

    newNode->data = auto_data;
    newNode->next = NULL;

    if(q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void copyNodeInQueue(Node* top, Queue* q) {
    if(top == NULL) {
        printf("Stiva este goala, nu aveti ce copia in coada.\n");
        return;
    }

    freeQueue(q);

    Node* temp = top;
    while(temp != NULL) {
        enqueue(q, temp->data);
        temp = temp->next;
    }

    printf("Elementele din stiva au fost copiate in sirul de asteptare (Queue)!\n");
}

void showQueueFile(Queue* q) {
    if(q->front == NULL){
        printf("Coada este goala!\n");
        return;
    }

    FILE* f = fopen(QUEUE_FILE, "w");
    if(!f) {
        printf("Nu se poate deschide fisierul %s!\n", QUEUE_FILE);
        return;
    }

    Node* temp = q->front;
    fprintf(f, "=== ELEMENTELE SIRULUI DE ASTEPTARE ===\n");
    while(temp != NULL) {
        writeVehicleFile(f, temp->data);
        temp = temp->next;
    }

    fclose(f);
    printf("Datele cozii au fost stalvate in fisierul %s.\n", QUEUE_FILE);
}

void freeQueue(Queue* q) {
    if(q->front == NULL) return;
    Node* temp;
    while(q->front != NULL) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
    printf("Memoria sirului de asteptare (Queue) a fost eliberata.\n");
}