#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
1. 이대로 all_node에 묶는 방법
2. student 리스트 / grade 리스트를 만들은 다음 따로따로 사용하는 방법
*/

typedef struct subject_grade{
	char * subject;
	int score;
	int complete;
	struct subject_grade *next;
}subject;

typedef struct all_node{
	int student_id;
	char * name;
	char * password;
	subject * subhead;
	struct all_node *next;
}student;

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
char_grade();

void show_grades(student * cur){
	student * cur = (student *)malloc(sizeof(studnet));
	subject * scur = (subject *)malloc(sizeof(subject));
	scur = cur -> subject;
	int num = 0,sum_complete = 0;
	double sum_grades;
	printf("<%s>님의 성적\n", cur->name);
	while(scur != NULL){
		printf("%s: %s\n", scur->subject, char_grade(scur->score));
		sum_complete += scur->complete;
		scur = scur->next;
		num++;
		//평점 평균 고민해볼 것
	}
	printf("이수학점: %d", sum_grade);
	printf("평점평균: %.f\n", (/num));
	//전체석차도 나중에 구현
	return ;
}

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
subject * add_subect(subject * head){
	subject * ;
	printf("과목: ");
	scanf("%s",tmp->subject->subject);
	printf("성적: ");
	scanf("%d", tmp->subject->score);
	printf("(이수)학점 : ");
	printf("%d", tmp->subject->complete);

}

void add_stu(student * prev, student * cur){
	subject * subnode = (subject*)malloc(sizeof(subject));
	subnode -> next = NULL;
	student * tmp = (student*)malloc(sizeof(student));
	int contnum;
	printf("학번: ");
	scanf("%d", &tmp->student_id);
	while(1){
		add_subject(student * subnode);
		printf("성적을 더 입력하시려면 1, 그만 입력하시려면 0을 입력하시오: <1 or 0입력>\n");
		scanf("%d", &contnum);
		if(contnum == 1){
			tmp->subject->next = NULL;
		}
		tmp->subject->next = NULL;
		break;
	}
	//파일에 입력하는 함수 추가
	return;//노드를 리턴하는 것으로 바꿀지는 다음에 생각하자...
};


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

int main(void){
	// 파일에서 연결리스트로 불러오는 함수 추가할 것
	student *head = (student*)malloc(sizeof(student));
	while(1){
		int num = menu();
		change_page(num);
		if(num ==0)
			break;
	}
	return 0;
}
