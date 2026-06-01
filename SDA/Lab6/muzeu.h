#ifndef MUZEU_H
#define MUZEU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char address[100];
    char phone[20];
    int exhibits;
    float ticket_price;
} Museum;

typedef struct Node {
    Museum data;
    struct Node* next;
} Node;

void createList(Node** head);
void insertElements(Node** head);
void showList(Node* head);
void showElement(Node* head);
void modifyElements(Node* head);
void lastElementAddress(Node* head);
int listLength(Node* head);
void interchangeElements(Node* head);
void sortList(Node** head);
void freeMemory(Node** head);

#endif