//연결리스트를......어케......써야할지 몰겟다...........

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct student {
	char name[20]; //학생이름
	int ID; //학번
	char password[30]; //비밀번호
	struct student* next;
}Student;

typedef struct grade {
	int ID; //학번
	char classname[20]; //과목이름
	int grade; //성적
	int credit; //학점
	struct grade* next;
}Grade;

Student* stu_head, * stu_tail;
Grade* grd_head, * grd_tail;

void connect(Student* newNode);

void registerInfo(void);

int main(void) {
	int res = 0;
	FILE* ifp_s;
	FILE* ifp_g;
	ifp_s = fopen("student.txt", "w+");
	ifp_g = fopen("grade.txt", "w+");
	
	stu_head = NULL;
	stu_tail = NULL;
	grd_head = NULL;
	grd_tail = NULL;

	while (1) {
		printf("[ Menu ]\n1. 성적확인\t2. 성적입력\t3. 학생정보등록\t4. 학생정보삭제\t0. 프로그램 종료\n");
		scanf("%d", &res);
		switch (res) {
		case1:gradecheck(); //1. 성적확인
			break;
		case2:gradeinput(ifp_g); //2. 성적입력
			break;
		case3:registerInfo(ifp_s); //3. 학생정보등록
			break;
		case4:deleteInfo(); //4. 학생정보삭제
			break;
		default: //0. 프로그램 종료
			break;
		};
	}
}

void connect(Student* newNode) {
	if (stu_head == NULL)
	{
		stu_head = newNode;
	}
	else {
		Student* p = stu_head;
		while (p->next != NULL)
			p = p->next;
		p->next = newNode;
	}
}

void registerInfo(FILE* ifp_s) {
	Student* newNode;

	printf("학생이름 : ");
	scanf("%s", newNode->name);

	printf("학번 : ");
	scanf("%d", &(newNode->ID));

	printf("비밀번호 : ");
	scanf("%s", newNode->password);
	connect(newNode);
	fwrite(newNode, sizeof(Student), 1, ifp_s);
}
void gradecheck() {
	Grade* tmp_grade;
	Student* tmp_std;
	int total_credit = 0, total_grade=0, rank=1, cnt=0;
	int ID = 0;
	char password[30];

	printf("학번 : ");
	scanf("%d", ID);

	if (ID) {//없는 학번일 경우
		printf("귀하의 학번 정보가 없습니다!\n");
	}
	else {
		while (1) {
			printf("비밀번호 : ");
			scanf("%s", password);
			if (password) { //비밀번호가 맞을 경우
				printf("<%s>님의 성적\n", tmp_std->name);
				while (tmp_grade != NULL) {
					printf("%s : %s\n", tmp_grade->classname, tmp_grade->grade);
					total_credit += *(tmp_grade->credit);
					total_grade += *(tmp_grade->grade);
					cnt++;
					// fseek으로 이동하는 코드
					// 전체석차 코드
				}

				printf("\n이수학점 : %d\n", total_credit);
				printf("평점평균 : %.1lf\n", (double)total_grade / cnt);
				printf("전체석차 : %d\n", rank);
				break;
			}
			else { //비밀번호가 틀릴 경우
				printf("비밀번호가 일치하지 않습니다!\n");
			}
		}
	}
}


int gradeinput(FILE* ifp_g) {
	int  num = 0;
	Student* curr;
	curr = stu_head;
	Grade *tmp=(Grade*)malloc(sizeof(Grade));
	while (1) {
			printf("학번 : ");
			scanf("%d", &(tmp->ID));
			for (curr = stu_head; curr != NULL; curr = curr->next) {
				if (curr->ID == tmp->ID) {
					break;
				}
				else {
					printf("귀하의 학번 정보가 없습니다!\n");
					free(tmp);
					return -1;
				}
			}

		printf("과목 : ");
		scanf("%s", tmp->classname);
		
		printf("성적 : ");
		while (1) {
			scanf("%d", &(tmp->grade));
			if (tmp->grade >= 0 && tmp->grade <= 100) {
				break;
			}
			else {
				printf("1~100 사이의 수를 입력해주세요.\n");
				continue;
			}
		}
		
		printf("학점 : ");
		while (1) {
			scanf("%d", &(tmp->credit));
			if (tmp->credit >= 1 && tmp->credit <= 9) {
				break;
			}
			else { 
				printf("1~9 사이의 수를 입력해주세요.\n");
				continue;
			}
		}
		fwrite(tmp, sizeof(Grade), 1, ifp_g);
		printf("성적을 더 입력하시려면 1, 그만 입력 받으려면 0을 입력하시오 : ");
		scanf("%d", &num);
		if (num == 0) {
			break;
		}
		else {
			continue;
		}
	}
	return 0;
}

void deleteInfo(){

}



//void gradecheck(char* curr, int grade) { //성적 입력 -> 학점
//	if (grade >= 97 && grade <= 100) {
//		strcpy(curr, "A+");
//	}
//	else if (grade <= 94 && grade >= 96) {
//		strcpy(curr, "A0");
//	}
//	else if (grade <= 90 && grade >= 93) {
//		strcpy(curr, "A-");
//	}
//	else if (grade <= 87 && grade >= 89) {
//		strcpy(curr, "B+");
//	}
//	else if (grade <= 84 && grade >= 86) {
//		strcpy(curr, "B0");
//	}
//	else if (grade <= 80 && grade >= 83) {
//		strcpy(curr, "B-");
//	}
//	else if (grade <= 77 && grade >= 79) {
//		strcpy(curr, "C+");
//	}
//	else if (grade <= 74 && grade >= 76) {
//		strcpy(curr, "C0");
//	}
//	else if (grade <= 70 && grade >= 73) {
//		strcpy(curr, "C-");
//	}
//	else if (grade <= 67 && grade >= 69) {
//		strcpy(curr, "D+");
//	}
//	else if (grade <= 64 && grade >= 66) {
//		strcpy(curr, "D0");
//	}
//	else if (grade <= 60 && grade >= 63) {
//		strcpy(curr, "D-");
//	}
//	else {
//		strcpy(curr, "F");
//	}
//}
