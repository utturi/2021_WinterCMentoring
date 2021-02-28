#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
	struct Node * next;
	char name[10];
	double programming;
	double commath1;
	double commath2;
	double avg;
}student;

int menu(void){
	int menu;
	do{
		printf("[Menu]\n");
		printf("1. 성적 입력\n");
		printf("2. 성적 확인\n");
		printf("3. 종료\n");
		printf("---------------------\n");
		printf("번호를 입력하세요 : ");
		scanf("%d", &menu);

	}while(menu<1||menu>3);
	return menu;
}

double grade(int grade){
	double res = 0;
	if((grade>=0&&grade<=100)!=1){
		printf("알맞지 않은 값이 입력되었습니다.\n");
		return 1;
	}
	if(grade/10>=9){
		res += 4;
	}
	else if(grade/10==8){
		res += 3;
	}
	else if(grade/10==7){
		res += 2;
	}
	else if(grade/10==6){
		res += 1;
	}
	else
		res = 0;
	if(res>=1)
		res += (grade%10>=7)?0.5:(grade%10>=4)?0.3:0;
	return res;
}

student *inputstu(void){
	student *new = (student *)malloc(sizeof(student));
	char name[10];
	int programming;
	int commath1;
	int commath2;
	printf("학생 이름: ");
	scanf("%s", name);
	strcpy(new->name,name);
	printf("프로그래밍 및 실습1: ");
	scanf("%d", &programming);
	if(grade(programming)!=1){
		new->programming = grade(programming);
		printf("컴퓨터수학1: ");
		scanf("%d", &commath1);
		if(grade(commath1)!=1){
			new->commath1 = grade(commath1);
			printf("컴퓨터수학2: ");
			scanf("%d", &commath2);
			if(grade(commath2)!=1){
				new->commath2 = grade(commath2);
				new->avg = (new->programming + new->commath1 + new->commath2)/3;
				return new;
			}
		}
	}
	return NULL;
}

void newnode(student * new, student * head){
	if(new==NULL){
		printf("올바른 값이 입력되지 않아 저장되지 않았습니다.\n");
		return;
	}
	student *cur = (student*)malloc(sizeof(student));
	student *prev;
	cur = head -> next;
	prev = head;
	while(cur!=NULL){
		if(cur->avg<new->avg){
			prev->next = new;
			new->next = cur;
			return;
		}
		prev = cur;
		cur = prev -> next;
	}
	if(cur==NULL){
		prev -> next = new;
		new -> next = NULL;
	}
	return;
}

char * chargrade(double score){
	char * grade = (char *)malloc(sizeof(char));
		if((int)score/1==4){
			strcpy(grade, "A");
		}
		else if((int)score/1==3){
			strcpy(grade, "B");
		}
		else if((int)score/1==2){
			strcpy(grade, "C");
		}
		else if((int)score/1==1){
			strcpy(grade, "D");
		}
	strcat(grade,((score-(int)score/1)==0.5)?"+":((score-(int)score/1)==0.3)?"0":"-");
	if(score == 0){
		strcpy(grade,"F");
	}
	return grade;
}

void showgrade(student * head){
	int i = 1;
	student * cur = head -> next;
	printf("-----------------------------------------------------------------------\n");
	printf("  이름	 프로그래밍 및 실습1	 컴퓨터수학1	 컴퓨터수학2	 등수\n");
	printf("-----------------------------------------------------------------------\n");
	if(cur==NULL){
		printf("저장된 정보가 없습니다.\n");
		return;
	}
	while(cur!=NULL){
		printf(" %5s", cur->name);
		printf("%16s", chargrade(cur->programming));
		printf("%19s", chargrade(cur->commath1));
		printf("%13s", chargrade(cur->commath2));
		printf("%14d", i);
		i++;
		printf("\n");
		cur = cur->next;
	}
	return;
}

void pages(int num, student * head){
	switch(num){
		case 1:
			newnode(inputstu(),head);
			break;
		case 2:
			showgrade(head);
			break;
		case 3:
			break;
	}
	return;
}

int main(void){
	student *head = (student *)malloc(sizeof(student));
	student *fcur, *fprev;
	head -> next = NULL;
	int menunum = 0;
	while(menunum!=3){
		menunum = menu();
		pages(menunum, head);
	}
	fcur = head->next;
	fprev = head;
	while(fcur!=NULL){
		fprev = fcur;
		free(fcur);
		fcur = fprev -> next;		
	}
	free(head);
	return 0;
}
