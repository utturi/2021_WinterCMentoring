#include<string.h>
#include<stdlib.h>
#include<stdio.h>

/*추가
  <만들어야 할 것>
  1. 학생정보 입력은 정상적으로 작동하지만, 학생의 성적이 제대로 연결되지 않음. 성적입력을 통해 학생 구조체 내의 과목 정보를 연결하는 부분이 잘 안되는 것 같음.
  2. 전체 석차를 위해 정렬하는 함수?
  3. 파일 입출력
 */

//과목의 정보(이름,점수, 학점)를 담고 있는 구조체
typedef struct subject_grade{
	char subject[16];
	int grade[5];//grade[0]은 2자리 성적, grade[1]은 10*평점, grade[2],grade[3]은 등급의 아스키 코드값을 담게 할 것
	int complete;
	struct subject_grade *next;
}subject;

//학생의 정보(학번, 이름, 비밀번호, 과목head주소-subhead)를 담고 있는 구조체
typedef struct all_node{
	int student_id;
	char name[16];
	char password[16];
	subject *subhead; //과목구조체의 head를 가리키게 하여 순환을 시작하는 역할
	struct all_node *next;//다음 학생과 연결해주는 역할
}student;

student *head;

int menu(void);
void show_grades(student * cur);
void check_grades(void);
void grade_array(int grade[]);
subject* add_subject(void);
void input_grades();
void input_student(void);
void delete_student(void);
void change_page(int);

//main함수
int main(void){
	// 파일에서 연결리스트로 불러오는 함수 추가할 것
	head = NULL;
	while(1){
		int num = menu();
		change_page(num);
		if(num == 0){
			printf("프로그램 종료!\n");
			break;
		}
	}
	/*
	   student *cur =(student*)malloc(sizeof(student));
	   cur = head->next;
	   while(cur!=NULL){
	   printf("%d\n", cur->student_id);
	   }

	   student *fcur = (student*)malloc(sizeof(student));
	   student *fprev = (student*)malloc(sizeof(student));
	   fcur = head->next;
	   while(fcur!=NULL){
	   fprev->next = fcur ->next;
	   free(fcur);
	   fcur = fprev;
	   }*/
	return 0;
}

//메뉴 출력해주는 함수
int menu(void){
	int num;

	do{
		printf("=============================================\n");
		printf("[Menu]\n");
		printf("1.성적확인\n");
		printf("2.성적입력\n");
		printf("3.학생정보등록\n");
		printf("4.학생정보삭제\n");
		printf("0.프로그램 종료\n");
		printf("메뉴를 선택하세요(0~4): ");
		scanf("%d", &num);
	}while(num<0||num>4);

	return num;
}
//메뉴별로 전환하는 함수 - switch문
void change_page(int num){
	switch(num){
		case 1:
			check_grades();//성적확인
			break;
		case 2:
			input_grades();//성적입력
			break;
		case 3:
			input_student();//학생정보등록
			break;
		case 4:
			//delete_student();//학생정보삭제
			break;
		case 0:
			printf("프로그램을 종료합니다.\n");
			return;
	}

	return;
}

// 1.성적확인
void show_grades(student * cur){
	//바로바로 업데이트된 정보를 확인해야 하기 때문에 여기에도 파일포인터를 이용해야함. 연결리스트만으로 하면 한계가 있음.
	//아님 여기서 다시 업로드를 하는 방법을 취할 것!

	subject *scur; // 선택된 학번의 subhead를 가지는 변수

	scur = cur->subhead;

	int num = 0, sum_complete = 0; // num: 과목개수, sum_complete: 이수학점의 합
	double sum_grades; // sum_grade: 평점 평균구하기 위한 평점*학점의 합

	// 성적입력이 아무것도 없을 때
	if(cur->subhead == NULL){
		printf("There's nothing saved. Go to [Menu]\n");
		return;
	}

	printf("<%s>님의 성적\n", cur->name);
	while(scur != NULL){
		printf("%s : %c%c\n", scur->subject, scur->grade[2], scur->grade[3]);
		sum_complete += scur->complete;
		sum_grades += (double)((scur->grade[1]/10))*(scur->complete);
		scur = scur->next;
		num++;
	}

	printf("\n이수학점: %d\n", sum_complete);
	printf("평점평균: %.f\n", (sum_grades/(double)sum_complete));
	//전체석차 나중에 구현

	return ;
}

//성적 확인함수
void check_grades(){
	int stu_id, check=1;
	char pw[16]; 
	student *cur;

	if(head==NULL){
		printf("not saved infomation -> need to change to korean\n");
		return;
	}

	cur = head;
	printf("학번: ");
	scanf("%d", &stu_id);
	while(cur!=NULL){
		if(cur->student_id==stu_id){
			while(1){
				printf("비밀번호: ");
				scanf("%s", pw);
				if(strcmp(cur->password, pw) != 0)
					printf("비밀번호가 일치하지 않습니다!\n");
				else 
					break;
			}
			show_grades(cur);
			return;
		}
		cur = cur->next;
	}

	if(cur == NULL)
		printf("귀하의 학번 정보가 없습니다!\n");
	
	return;
}

//2. 성적 입력
void input_grades(){
	student * cur;
	int contnum = 1;
	int id;

	printf("=============================================\n");
	printf("[성적입력]\n");

	// 학생정보가 아무것도 없을 때
	if(head==NULL){
		printf("학생 정보를 먼저 저장해주십시오.\n");
		printf("저장된 정보가 없으므로 [Menu]로 돌아갑니다.\n");
		return;
	}

	printf("학번: ");
	scanf("%d", &id);

	cur = head; // 여기서 cur은 학생정보들의 cur
	while(cur!=NULL){
		if(cur->student_id==id)
			break;

		cur=cur->next;
	}

	if(cur==NULL){
		printf("입력하신 학번의 정보가 존재하지 않습니다\n");
		printf("[Menu]로 돌아갑니다.\n");
		return;
	}

	//성적 추가하는 것 tmp를 반환해서 추가할 것인지 이대로 add_subject에서 추가할 것인지 결정해야 함
	subject *subcur; // student의 subhead를 가지고 있는 cur

	while(contnum){
		subject *newNode; // 새로운 subject 노드를 가질 변수

		// 학번에 대한 성적이 아무것도 없을 때
		if(cur->subhead == NULL){ // cur->subhead는 학생노드에서 과목구조체의 head를 접근
			newNode = add_subject(); // 함수에 리턴값으로 성적노드를 새롭게 받음
			cur->subhead = newNode; // cur->subhead에 새로운 성적노드 연결
		}
		else{
			subcur = cur->subhead; 

			while(subcur->next != NULL){
				subcur = subcur->next;
			}

			newNode = add_subject();
			subcur->next = newNode; // 성적노드를 연결
		}

		printf("성적을 더 입력하시려면 1, 그만 입력하시려면 0을 입력하시오: <1 or 0입력>\n");
		getchar();
		scanf("%d", &contnum);
		if(contnum == 0)
			break;
	}
	//파일 입력 추가

	return;
};

// 성적노드를 리턴받는 것으로 교체
subject* add_subject(){
	subject * tmp = (subject *)malloc(sizeof(subject));

	printf("과목: ");
	scanf("%s",tmp->subject);
	printf("성적: ");
	scanf("%d", &tmp->grade[0]);
	grade_array(tmp->grade);
	printf("(이수)학점 : ");
	scanf("%d", &tmp->complete);
	tmp -> next = NULL;

	//Grade.txt파일에 입력하는 것 추가할 것!
	return tmp;
}

void grade_array(int grade[]){
	if(grade[0]/10>=9){
		grade[1]+=40; grade[2]+='A';
	}
	else if(grade[0]/10==8){
		grade[1]+=30; grade[2]+='B';
	}
	else if(grade[0]/10==7){
		grade[1]+=20; grade[2]+='C';
	}
	else if(grade[0]/10==6){
		grade[1]+=10; grade[2]+='D';
	}
	else{
		grade[2]+='F';
	}
	if(grade[1]!=0){
		if(grade[0]%10>=7){
			grade[1]+=5; grade[3]+='+';
		}
		else if(grade[0]%10>=4){
			grade[1]+=3; grade[3]+='0';
		}
		else
			grade[3]+='-';
	}

	return;
}


//3. 학생정보등록
void input_student(void){
	//우선 노드에 추가한 후,
	//파일에 쓰는 과정 넣을 것: 바로바로 업데이트

	student * cur;
	student * tmp = (student *)malloc(sizeof(student));
	printf("=============================================\n");
	printf("[학생정보등록]\n");

	printf("학생이름: ");
	scanf("%s", tmp->name);
	printf("학번: ");
	scanf("%d", &tmp->student_id);
	printf("비밀번호: ");
	scanf("%s", tmp->password);
	if(head != NULL){
		cur = head;
		while(cur->next!=NULL){
			cur = cur->next;
		}
		cur->next = tmp;
		tmp->next = NULL;

	}
	// 정보입력이 처음일 때
	else{
		head = tmp;
		tmp->next = NULL;
	}
	tmp->subhead = NULL; // subhead도 NULL로 초기화 필요

	//FILE *fp = fopen("Student.txt", "a+");맞는지는 모르겠지만 일단은 뒤에 덧붙여주는 방식으로 파일에 추가해줄 것
	return;
}

/*
//4. 학생정보삭제
void delete_student(void){
student * cur = (student *)malloc(sizeof(student));
student * prev;
char * admin_pwd = "admin1234";//관리자 비밀번호
char * check_admin;
char * tmp_name;
char yorn;
int del_stu_id;
if(head!=NULL){
cur = head->next;
printf("관리자 비밀번호: ");
scanf("%s", check_admin);
if(strcmp(admin_pwd, check_admin)==0){
while(1){
printf("학번: ");
scanf("%d", &del_stu_id);
while(cur!= NULL){
if(cur->student_id== del_stu_id){
printf("<%s>님의 정보를 삭제하시겠습니까?<y or n>\n", cur->name);
scanf("%c", &yorn);
if(yorn == 'y' || yorn =='Y'){
strcpy(tmp_name, cur->name);
prev->next = cur->next;
free(cur);
printf("<%s>님의 정보를 삭제했습니다.", tmp_name);
}
else
printf("<%s>님의 정보를 삭제하지 않았습니다.", cur->name);
return;
}
prev = cur;
cur = cur->next;
}
if(cur==NULL)
printf("귀하의 학번 정보가 올바르지 않습니다!\n");
}
}
printf("비밀번호가 올바르지 않습니다!\n");
return;
}
printf("저장된 정보가 없으므로 [Menu]로 돌아갑니다.\n");
return ;
}
//FILE *fp = fopen("Student.txt", "w");
//FILE *fp = fopent("Grade.txt", "w");
//: 새로파일 다시 쓰게 해서 파일 초기화 해줄 것...
 */
