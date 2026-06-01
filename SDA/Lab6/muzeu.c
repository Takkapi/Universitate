#include "muzeu.h"

void createList(Node** head) {
    if(*head != NULL) freeMemory(head);
    *head = NULL;
    printf("Lista a fost creata / initializata in memoria dinamica!\n");
}

void insertElements(Node** head) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        printf("Memoria nu a putut fi alocata!\n");
        return;
    }

    printf("\n--- Introduceti datele noului Muzeu ---\n");
    printf("Denumirea: ");
    scanf(" %[^\n]", newNode->data.name);
    printf("Adresa: ");
    scanf(" %[^\n]", newNode->data.address);
    printf("Telefonul: ");
    scanf(" %[^\n]", newNode->data.phone);
    printf("Numarul de exponate: ");
    scanf("%d", &newNode->data.exhibits);
    printf("Pretul biletului: ");
    scanf("%f", &newNode->data.ticket_price);

    newNode->next = NULL;

    if(*head == NULL) *head = newNode;
    else {
        Node* temp = *head;
        while(temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
    printf("Muzeul a fost adaugat in lista!\n");
}

void showList(Node* head) {
    if(head == NULL) {
        printf("Lista este goala!\n");
        return;
    }

    Node* temp = head;
    int i = 1;
    printf("%-3s | %-20s | %-20s | %-12s | %-10s | %-10s\n",
            "Nr", "Denumire", "Adresa", "Telefon", "Exponate", "Pret");
    while(temp != NULL) {
        printf("%-3d | %-20s | %-20s | %-12s | %-10d | %-20.2f\n",
                i++, temp->data.name, temp->data.address,
                temp->data.phone, temp->data.exhibits, temp->data.ticket_price);
        temp = temp->next;
    }
}

void searchElement(Node* head) {
    if(head == NULL) {
        printf("Lista este goala!\n");
        return;
    }

    char searchedName[50];
    printf("Introduceti denumirea muzeului cautat: ");
    scanf(" %[^\n]", searchedName);

    Node* temp = head;
    int found = 0;
    while(temp != NULL) {
        if(strcasecmp(temp->data.name, searchedName) == 0) {
            printf("\nMuzeu: %s | Adresa: %s | Exponate: %d | Pret: %.2f\n",
                    temp->data.name, temp->data.address, temp->data.exhibits, temp->data.ticket_price);
            found = 1;
        }
        temp = temp->next;
    }

    if(!found) printf("Nu s-a gasit niciun muzeu cu aceasta denumire.\n");
}

void modifyElements(Node* head) {
    int len = listLength(head);
    if(len == 0) {
        printf("Lista este goala!\n");
        return;
    }

    int pos;
    printf("Introduceti pozitia muzeului pe care doriti sa-l modificati (1 - %d): ", len);
    scanf("%d", &pos);

    if(pos < 1 || pos > len) {
        printf("Pozitie invalida!\n");
        return;
    }

    Node* temp = head;
    for(int i = 1; i < pos; i++) temp = temp->next;

    printf("\n--- Introduceti NOILE date pentru muzeul de pe pozitia %d ---\n", pos);
    printf("Denumirea: ");
    scanf(" %[^\n]", temp->data.name);
    printf("Addesa: ");
    scanf(" %[^\n]", temp->data.address);
    printf("Telefonul: ");
    scanf(" %[^\n]", temp->data.phone);
    printf("Numarul de exponate: ");
    scanf("%d", &temp->data.exhibits);
    printf("Pretul biletului: ");
    scanf("%f", &temp->data.ticket_price);

    printf("Datele au fost modificate!\n");
}

void lastElementAddress(Node* head) {
    if(head == NULL) {
        printf("Lista este goala!\n");
        return;
    }

    Node* temp = head;
    while(temp->next != NULL) temp = temp->next;
    printf("Adresa in memorie a ultimului element (%s) este: %p\n", temp->data.name, (void*)temp);
}

int listLength(Node* head) {
    int count = 0;
    Node* temp = head;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

void interchangeElements(Node* head) {
    int len = listLength(head);
    if(len < 2) {
        printf("Lista trebuie sa aiba cel putin 2 elemente pentru interschimbare!\n");
        return;
    }

    int pos1, pos2;
    printf("Introduceti pozitia primului element (1 - %d): ", len);
    scanf("%d", pos1);
    printf("Introduceti pozitia celui de-al doilea element (1 - %d): ", len);
    scanf("%d", pos2);
    
    if(pos1 < 1 || pos1 > len || pos2 < 1 || pos2 > len) {
        printf("Pozitii invalide!\n");
        return;
    }

    Node* node1 = head;
    Node* node2 = head;

    for(int i = 1; i < pos1; i++) node1 = node1->next;
    for(int i = 1; i < pos2; i++) node2 = node2->next;

    Museum temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;

    printf("Informatiile de la pozitiile %d si %d au fost interschimbate!\n", pos1, pos2);
}

void sortList(Node** head) {
    if(*head == NULL || (*head)->next == NULL) {
        printf("Lista are 0 sau 1 elemente, nu este necesara sortarea!\n");
        return;
    }

    Node* sorted = NULL;
    Node* current = *head;

    while(current != NULL) {
        Node* next = current->next;

        if(sorted == NULL || sorted->data.exhibits >= current->data.exhibits) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while(temp->next != NULL && temp->next->data.exhibits < current->data.exhibits) temp = temp->next;
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    *head = sorted;
    printf("Lista a fost sortata (Insertion Sort) crescator dupa Numarul de Exponate!\n");
}

void freeMemory(Node** head) {
    Node* current = *head;
    Node* nextNode;

    while(current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *head = NULL;
    printf("Memoria alocata listei a fost eliberata!\n");
}