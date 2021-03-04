#include<stdio.h>//아직 다 완성 못했습니다.
#include<string.h>
#include<stdlib.h>

typedef struct Node{
	char* student_name;
	int student_ID;
	char* password;
}student;

typedef struct node{
	int student_ID;
	char* subject;
	int score;
	double grade;

}grade;


int menu(void){
	int menu = 5;
	do{
		printf("[Menu]"\n);
		printf("1. 성적확인\n");
		printf("2. 성적입력\n");
		printf("3. 학생정보등록\n");
		printf("4. 학생정보삭제\n");
		printf("0. 프로그램종료\n");
	}while(menu<0||menu>4);
	return menu;
}

void check_grade(){

	return;
}

void input_grade(){
	while()
	printf("성적을 더 입력하시려면 1, 그만 입력 받으려면 0을 입력하십시오: <1 or 0 입력>");
	return;
}

void input_student(){
	return;
}

void delete_student(){
	return;
}

void show_grades(){
	FILE *fp;
	grade * grade = (grade *)malloc(sizeof(grade));
	char * fname =" Grade.txt"
	if((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	if(fread(test, sizeof(struct node), 1, fp) != 1) {
		fprintf(stderr, "fread error");
		exit(1);
	}
	
	char buffer[30];
	
	while(fgets(buffer, sizeof(buffer), fp)){
		char * ptr = strtok(buffer, "|");
		
		ptr = strtok(NULL, " ");
	}


	fclose();
	return;
}

void check_student(void){
	int stu_id, check=1;
	char * pw;
	student* cur = (student*)malloc(sizeof(student));//구조체가 아닌 파일 입출력으로? -> 연결리스트에 파일 읽어서 저장 먼저 할 것,,,
	printf("학번: ");
	scanf("%d",&stu_id);
	while(cur!=NULL){
		if(cur->student_id==stu_id){
			while(1){
			printf("비밀번호: ");
			scanf("%s", pw);
				if(strcmp(cur->password, pw)!=0)
					printf("비밀번호가 일치하지 않습니다!\n");
				else break;
			}
			//성적 출력
			return;
		}
		cur = cur->next;
	}
	if(cur==NULL)
		printf("귀하의 학번 정보가 없습니다!\n");
	return;
}

void chang_page(int menunum){
	switch(menunum){
case1:
		break;
case2:
		input_grade();
		break;
case3:
		break;
case4:
		break;
case0:
		break;
	}
	return;
}

int main(void){
	change_Page(menunum, head);
	return 0;
}
