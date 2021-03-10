#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/*추가
<만들어야 할 것>
전체 석차를 위해 정렬하는 함수
헤드를 받아 null까지 free하는 함수-문제: 자료형이 다다름->함수 취소
질문: student안의 subject도 차례차례 free하는 과정이 필요한가요?
파일 입출력 
*/

//과목의 정보(이름,점수, 학점)를 담고 있는 구조체
typedef struct subject_grade{
	char * subject;
	int grade[5]={0,};//grade[0]은 2자리 성적, grade[1]은 10*평점, grade[2]~'\0'까지는 등급의 아스키 코드값을 담게 할 것
	int complete;
	struct subject_grade *next;
}subject;

//학생의 정보(학번, 이름, 비밀번호, 과목head주소-subhead)를 담고 있는 구조체
typedef struct all_node{
	int student_id;
	char * name;
	char * password;
	subject * subhead; //과목구조체의 head를 가리키게 하여 순환을 시작하는 역할
	struct all_node *next;//다음 학생과 연결해주는 역할
}student;



//메뉴 출력해주는 함수
int menu(void){
	int num;
	do{
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

// 1.성적확인

void show_grades(student * cur){
	//바로바로 업데이트된 정보를 확인해야 하기 때문에 여기에도 파일포인터를 이용해야함. 연결리스트만으로 하면 한계가 있음.
	//아님 여기서 다시 업로드를 하는 방법을 취할 것!
	student * cur = (student *)malloc(sizeof(studnet));
	subject * scur = (subject *)malloc(sizeof(subject));
	scur = cur -> subject;
	int num = 0,sum_complete = 0;//num: 과목개수, sum_complete: 이수학점의 합
	double sum_grades;//sum_grade: 평점 평균구하기 위한 평점*학점의 합
	printf("<%s>님의 성적\n", cur->name);
	while(scur != NULL){
		printf("%s: %s\n", scur->subject, char_grade(scur->grade[2]));
		sum_complete += scur->complete;
		sum_grade += (double)((scur->grade[1]/10))*(scur->complete);
		scur = scur->next;
		num++;
	}
	printf("이수학점: %d", sum_complete;
	printf("평점평균: %.f\n", (sum_grade/(double)sum_complete));
	//전체석차 나중에 구현
	return ;
}

//성적 확인함수
void check_grades(student * head){
    int stu_id, check=1;
    char * pw; 
    student* cur = (student*)malloc(sizeof(student));
	cur = head -> next;
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
			show_grades(student * cur);	
            return;
        }
        cur = cur->next;
    }
    if(cur==NULL)
        printf("귀하의 학번 정보가 없습니다!\n");
    return;
}

//2. 성적 입력
void grade_array(int grade[]){
	if(grade/10>=9){
		grade[1]+=40; grade[2]+='A';
	}
	else if(grade/10==8){
		grade[1]+=30; grade[2]+='B';
	}
	else if(grade/10==7){
		grade[1]+=20; grade[2]+='C';
	}
	else if(grade/10==6){
		grade[1]+=10; grade[2]+='D';
	}
	else{
		grade[2]+='F';
	}
	if(grade!=0){
		if(grade%10>=7){
			grade[1]+=5; grade[3]+='+';
		}
		else if(grade%10>=4){
			grade[1]+=3; grade[3]+='0';
		}
		else
			grade[3]+='-';
	}
	return;
}

void add_subect(subject * cur){
	subject * cur = (subject *)malloc(sizeof(subject));
	subject * tmp = (subject *)malloc(sizeof(subject));
	printf("과목: ");
	scanf("%s",tmp->subject);
	printf("성적: ");
	scanf("%2d", tmp->grade);
	array_grade(tmp->grade);
	printf("(이수)학점 : ");
	scanf("%1d", &tmp->complete);
	cur -> next=tmp;
	tmp -> next = NULL;
	//Grade.txt파일에 입력하는 것 추가할 것!
	return;
}

//여기서 노드 포인터를 받아서 학번 순 자리에 넣을 것인지 아니면 이 함수에서 바로 넣어줄 것인지 결정해야 함....
void add_stu(student * prev, student * cur){
	subject *sub_head = (subject*)malloc(sizeof(subject));
	sub_head-> next = NULL;
	subjecgt * cur;
	cur = head;
	student * tmp = (student*)malloc(sizeof(student));
	int contnum=1;
	printf("학번: ");
	scanf("%d", &tmp->student_id);
	while(contnnum){
		add_subject(cur);
		printf("성적을 더 입력하시려면 1, 그만 입력하시려면 0을 입력하시오: <1 or 0입력>\n");
		scanf("%d", &contnum);
		if(contnum == 1){
			cur = cur->next;
		}
		break;
	}
	tmp->subhead = sub_head;
	//파일 입력 추가
	return;//노드를 리턴하는 것으로 바꿀지는 다음에 생각하자...
};


//3. 학생정보등록
void input_student(student * head){
	//우선 노드에 추가한 후,
	//파일에 쓰는 과정 넣을 것: 바로바로 업데이트
	//학번순이라고 생각해야하나?...
	student * cur = (student *)malloc(sizeof(student));
	cur = head -> next;
	student * tmp = (student *)malloc(sizeof(student));

	printf("학생이름: ");
	scanf("%s", tmp->name);
	printf("학번: ");
	scanf("%8d", &tmp->student_id);
	printf("비밀번호: ");
	scanf("%s", tmp->password);
	while(cur!=NULL)
		cur = cur->next;
	cur -> next = tmp;
	tmp->next = NULL;번호
	//FILE *fp = fopne("Student.txt", "a+");맞는지는 모르겠지만 일단은 뒤에 덧붙여주는 방식으로 파일에 추가해줄 것
	return;
}


//4. 학생정보삭제
void delete_student(student * head){
	student * cur = (student *)malloc(sizeof(student));
	student * prev;
	cur = head->next;
	char * admin_pwd = "admin1234";//관리자 비밀번호
	char * check_admin;
	char * tmp_name;
	char yorn;
	int del_stu_id;
	printf("관리자 비밀번호: ");
	scanf("%s", check_admin);
	if(strcmp(admin_pwd, check_admin)==0){
		while(1){
		printf("학번: ");
		scanf("%8d", &del_stu_id);
		while(cur!= NULL){
			if(strcmp(cur->sutdent_id, del_stu_id)==0){
				printf("<%s>님의 정보를 삭제하시겠습니까?<y or n>\n", cur->name);
				scanf("%c", &yorn);
				if(your == 'y' || yorn =='Y'){
					strpy(tmp_name, cur->name);
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
	printf("비밀번호가 올바르지 않습니다!\n");
	return ;
}
//FILE *fp = fopen("Student.txt", "w");
//FILE *fp = fopent("Grade.txt", "w");
//: 새로파일 다시 쓰게 해서 파일 초기화 해줄 것...


//메뉴별로 전환하는 함수 - switch문
void change_page(int num, student * head){
	switch(num){
		case 1:
			check_grades(student * head);
			break;
		case 2:
			input_grades(student * head);
			break;
		case 3:
			input_student(student * head);
			break;
		case 4:
			delete_student(student * head);
			break;
		case 0:
			printf("프로그램을 종료합니다.\n");
			break;
	}
	return;
}

//main함수
int main(void){
	// 파일에서 연결리스트로 불러오는 함수 추가할 것
	student *head = (student*)malloc(sizeof(student));
	while(1){
		int num = menu();
		change_page(num);
		if(num ==0)
			break;
	}
	student *fcur = (student*)malloc(sizeof(student));
	student *fpev = (student*)malloc(sizeof(student));
	fcur = head->next;
	while(fcur!=NULL){
		fprev->next = fcur ->next;
		free(fcur);
		fcur = fprev;
	}
	return 0;
}
