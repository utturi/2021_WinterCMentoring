#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct student {
	char name[20]; //학생이름
	char ID[9]; //학번
	char password[30]; //비밀번호
}Student;

typedef struct grade {
	char ID[9]; //학번
	char classname[20]; //과목이름
	char grade[3]; //성적
	char credit[2]; //학점
}Grade;


int main(void) {
	int res = 0;
	while (1) {
		printf("[ Menu ]\n1. 성적확인\t2. 성적입력\t3. 학생정보등록\t4. 학생정보삭제\t0. 프로그램 종료\n");
		scanf("%d", &res);
		switch (res) {
		case1:gradecheck(); //1. 성적확인
			break;
		case2:gradeinput(); //2. 성적입력
			break;
		case3:registerInfo(); //3. 학생정보등록
			break;
		case4:deleteInfo(); //4. 학생정보삭제
			break;
		default: //0. 프로그램 종료
			break;
		};
	}
}

void gradecheck() {
	FILE* ifp_std;
	FILE* ifp_grade;
	ifp_std = fopen("student.txt", "r"); //student.txt : 학생이름, 학번, 비밀번호
	ifp_grade = fopen("grade.txt", "r"); //grade.txt : 학번, 과목이름, 성적, 학점
	Grade* tmp_grade;
	Student* tmp_std;
	int total_credit = 0, total_grade=0, rank=1, cnt=0;
	char ID[9], password[30];

	printf("학번 : ");
	scanf("%s", ID);
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

				printf("\n이수학점 : %d", total_credit);
				printf("평점평균 : %.1lf", (double)total_grade / cnt);
				printf("전체석차 : %d", rank);
				break;
			}
			else { //비밀번호가 틀릴 경우
				printf("비밀번호가 일치하지 않습니다!\n");
			}
		}
	}
	fclose(ifp_std);
	fclose(ifp_grade);
}


void gradeinput() {
	FILE* ifp;
	ifp = fopen("grade.txt", "w+"); //학번, 과목이름, 성적, 학점
	int g = 0, num = 0;
	Grade *tmp=(Grade*)malloc(sizeof(Grade));
	while (1) {
		printf("학번 : ");
		scanf("%s", tmp->ID);
		Alignfile(tmp->ID); //파일 정렬
		printf("과목 : ");
		scanf("%s", tmp->classname);
		printf("성적 : ");
		while (1) {
			g = scanf("%s", tmp->grade);
			if (g != 0) {
				break;
			}
			else { ; }
		}
		printf("학점 : ");
		while (1) {
			scanf("%s", tmp->credit);
			if (*(tmp->credit) >= '1' || *(tmp->credit) <= '9') {
				break;
			}
			else { 
				printf("1~9 사이의 수를 입력해주세요.\n"); 
			}
		}
		fwrite(tmp, sizeof(Grade), 1, ifp);
		printf("성적을 더 입력하시려면 1, 그만 입력 받으려면 0을 입력하시오 : ");
		scanf("%d", &num);
		if (num == 0) {
			break;
		}
		else {
			continue;
		}
	}
	fclose(ifp);
}

void Alignfile(char* ID) {
}

void registerInfo(){}
void deleteInfo(){}
