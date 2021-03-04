#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct Node {
    int data;
    struct Node* next;
} Node;
void insert(Node**, int);
void deleteNode(Node**, Node*, Node*);
void deleteOdd(Node**);
void output(Node*, int);
int main(void)
{
    Node* head = NULL;
    int num = 0;
    int w = 0; //몇개인지
    scanf("%d", &w);
    for (int i = 0; i < w; i++) {
        scanf("%d", &num);
        insert(&head, num);
    }
    deleteOdd(&head);
    output(head, w);
    return 0;
}
void insert(Node** head, int num) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        return;
    }
    p->data = num;
    p->next = NULL;
    if (*head == NULL)
        *head = p;
    else
    {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = p;
    }
}
void deleteOdd(Node** head) {
    Node* p = *head;
    if (p->next == NULL) {
        *head = (*head)->next;
    }
    else {
        deleteNode(head, NULL, p);
        p = p->next;
        while (p != NULL) {
            deleteNode(head, p, p->next);
            p = p->next;
        }
    }
}
void deleteNode(Node** head, Node* p, Node* deleted) {
    if (p == NULL) {
        *head = (*head)->next;
    }
    else {
        p->next = deleted->next;
        free(deleted);
    }
}
void output(Node* head, int w) {
    Node* curr = head;
    for (int i = 0; i < w / 2; i++) {
  //  while(curr!=NULL){
        printf("%d\t", curr->data);
        curr = curr->next;
    }
    printf("\n");
}