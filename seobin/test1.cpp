#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct Node {     
    int data;
    struct Node* next;
} Node;
void insert(Node**, int);
int maxcheck(Node*);
int mincheck(Node*);
int main(void)
{
    Node* head = NULL;
    int num = 0;
    int max = 0, min = 0;
    int w = 0; //몇개인지
    scanf("%d", &w);
    for (int i = 0; i < w; i++){
        scanf("%d", &num);
        insert(&head, num);
    }
    min = mincheck(head);
    max = maxcheck(head);
    printf("%d\t%d\n", max, min);
    return 0;
}
void insert(Node** head, int num){
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
int mincheck(Node* head){
    Node* temp = head;
    int min = temp->data;
    for (temp; temp != NULL; temp = temp->next)
        if (min > temp->data)
            min = temp->data;
    return min;
}
int maxcheck(Node* head){
    Node* temp = head;
    int max = temp->data;
    for (temp; temp != NULL; temp = temp->next)
        if (max < temp->data)
            max = temp->data;
    return max;
}