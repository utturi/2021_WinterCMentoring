#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct info {
	char name[20];
	int programming;
	char programming_GPA[3];
	int math1;
	char math1_GPA[3];
	int math2;
	char math2_GPA[3];
	int total; //총점
	int order;
}Info;

typedef struct node {
	Info student;
	struct node* next;
}Node;


int mainprogram(Node*, Node*, Info);
void addNode(Node**, Node**, Info*);
void Order(Node*, Info*);
void input(Info*);
void gradecheck(char*, int);
void check(Node*);
void Sort(Node**, Node**);

int main(void) {
	int ret = 0;
	Node* head = (Node*)malloc(sizeof(Node));
	Node* tail = (Node*)malloc(sizeof(Node));
	Info curr;
	head->next = NULL;

	while (1) {
		ret = mainprogram(head, tail, curr);
		if (ret == 1) {
			break;
		}
		else if (ret == 0) {
			continue;
		}
		else if (ret == 2) {
			printf("\n\n제대로 된 번호를 입력해주세요. (1~3)\n\n");
			continue;
		}
		else { ; }
	}
	Node* d = head->next;
	while (head != NULL) {
		//d = head->next;
		free(head);
		head = d;
	}
	free(d);
	return 0;
}

int mainprogram(Node* head, Node* tail, Info curr) {
	int n = 0;
	printf("[ Menu ]\n1. 성적 입력\n2. 성적 확인\n3. 종료 \n---------------\n번호를 입력하세요 : ");
	scanf("%d", &n);
	printf("\n");
	if (n == 1) { //성적 입력
		input(&curr);
		Order(head, &curr);
		addNode(&head, &tail, &curr);
		return 0;
	}
	else if (n == 2) { //성적 확인
		check(head);
		return 0;
	}
	else if (n == 3) { //프로그램 종료
		return 1;
	}
	else { return 2; }
}

void addNode(Node** head, Node** tail, Info* curr) {
	if (*head != NULL) {
		(*tail)->next = (Node*)malloc(sizeof(Node));
		*tail = (*tail)->next;
	}
	else {
		*head = (Node*)malloc(sizeof(Node));
		*tail = *head;
	}
}

void Order(Node* head, Info* curr) {
	Node* p = head;
	while (p != NULL) {
		if (curr->total < p->student.total) {
			curr->order++;
		}
		else {
			p->student.order++;
		}
		p = p->next;
	}
}

void input(Info* curr) { //성적 입력
	printf("학생 이름 : ");
	scanf("%s", curr->name);
	int n = 0;
	printf("프로그래밍 및 실습1 : ");
	while (1) {             //수정해야함
		n = 0;
		n = scanf("%d", &curr->programming);
		if (n == 1) {
			break;
		}
		else {
			printf("점수를 제대로 입력하세요.\n");
			continue;
		}
	}
	//	scanf("%d", &curr->programming);
	gradecheck(curr->programming_GPA, curr->programming);

	printf("컴퓨터수학1 : ");
	//	scanf("%d", &curr->math1);
	while (1) {
		n = 0;
		n = scanf("%d", &curr->math2);
		if (n == 1) {
			break;
		}
		else {
			printf("점수를 제대로 입력하세요.\n");
			continue;
		}
	}
	gradecheck(curr->math1_GPA, curr->math1);

	printf("컴퓨터수학2 : ");
	//scanf("%d", &curr->math2);
	while (1) {
		n = 0;
		n = scanf("%d", &curr->math2);
		if (n == 1) {
			break;
		}
		else {
			printf("점수를 제대로 입력하세요.\n");
			continue;
		}
	}
	gradecheck(curr->math2_GPA, curr->math2);
	printf("\n");

	curr->total = (curr->programming) + (curr->math1) + (curr->math2);
	curr->order = 1;
}

void gradecheck(char* curr, int grade) { //성적 입력 -> 학점
	if (grade >= 97 && grade <= 100) {
		strcpy(curr, "A+");
	}
	else if (grade <= 94 && grade >= 96) {
		strcpy(curr, "A0");
	}
	else if (grade <= 90 && grade >= 93) {
		strcpy(curr, "A-");
	}
	else if (grade <= 87 && grade >= 89) {
		strcpy(curr, "B+");
	}
	else if (grade <= 84 && grade >= 86) {
		strcpy(curr, "B0");
	}
	else if (grade <= 80 && grade >= 83) {
		strcpy(curr, "B-");
	}
	else if (grade <= 77 && grade >= 79) {
		strcpy(curr, "C+");
	}
	else if (grade <= 74 && grade >= 76) {
		strcpy(curr, "C0");
	}
	else if (grade <= 70 && grade >= 73) {
		strcpy(curr, "C-");
	}
	else if (grade <= 67 && grade >= 69) {
		strcpy(curr, "D+");
	}
	else if (grade <= 64 && grade >= 66) {
		strcpy(curr, "D0");
	}
	else if (grade <= 60 && grade >= 63) {
		strcpy(curr, "D-");
	}
	else {
		strcpy(curr, "F");
	}
}
void check(Node* head) { // 성적 확인       
	Node* curr = head;
	printf("-----------------------------------------------------------------------------\n\n");
	printf("      이름     프로그래밍 및 실습1     컴퓨터수학1     컴퓨터수학2     등수\n\n");
	printf("-----------------------------------------------------------------------------\n\n");
	while (1) { //노드연결 수정해야함
		printf("\t%s\t %s\t %s\t %s\t %5d\n", curr->student.name, curr->student.programming_GPA, curr->student.math1_GPA, curr->student.math2_GPA, curr->student.order);
		curr = curr->next;
		if (curr == NULL) {
			break;
		}
	}
	printf("\n");
}

void Sort(Node** head, Node** tail) { //등수 정렬
	;
}

