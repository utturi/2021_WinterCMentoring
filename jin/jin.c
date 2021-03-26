#include<string.h>
#include<stdlib.h>
#include<stdio.h>

//과목의 정보(이름,점수, 학점)를 담고 있는 구조체
typedef struct subject_grade{
	char subject[16];//과목명
	int grade[5];//grade[0]은 2자리 성적, grade[1]은 10*평점, grade[2],grade[3]은 등급의 아스키 코드값을 담게 할 것
	double complete;//이수학점
	struct subject_grade *next;
}subject;

//학생의 정보(학번, 이름, 비밀번호, 과목head주소-subhead)를 담고 있는 구조체
typedef struct all_node{
	int student_id;//학번
	char name[16];//학생의 이름
	char password[16];//비밀번호
	subject *subhead; //과목구조체의 head를 가리키게 하여 순환을 시작하는 역할

	double sum_of_completes;//이수학점들의 합
	double sum_of_multiplies;// 평점*이수학점의 합
	double grades_average;
	int ranking;//전체 석차
	struct all_node *next;//다음 학생과 연결해주는 역할
}student;

student *head;

int menu(void);//menu(1. 성적확인 2. 성적입력 3. 학생정보등록 4. 학생정보삭제 0.프로그램 종료)를 출력해주는 함수
void change_page(int);//swithc문으로 num에 해당하는 함수를 실행하는 함수
void check_grades(void);//성적 확인을 위해 학번과 비밀번호를 입력하는 함수
int ranking(student *); //student 노드를 받아 해당 노드의 전체석차를 구하는 함수
void show_grades(student *);//성적, 이수학점, 평점평균, 전체석차를 출력해주 함수 
subject* add_subject(void);//새로운 subject 노드를 추가하는 함수
void grade_array(int grade[]);//grade 배열에 자료형별로 변환하여 저장하는 함수
void input_grades();//subject 노드의 내용(과목명, 성적, 이수학점)을 입력하고 평점 평균을 구하는 함수
void input_student(void);//학생의 정보(이름, 학번, 비밀번호)를 입력하는 함수
void delete_student(void);//student노드를 삭제하는 함수

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
	}while(num<0||num>4);//입력한 값이 0~4가 아닐 때 반복
	return num;
}

//메뉴별로 전환하는 함수 - switch문
void change_page(int num){
	switch(num){
		case 1:
			check_grades();//1.성적확인
			break;
		case 2:
			input_grades();//2.성적입력
			break;
		case 3:
			input_student();//3.학생정보등록
			break;
		case 4:
			delete_student();//4.학생정보삭제
			break;
		case 0:
			printf("프로그램을 종료합니다.\n");
			return;
	}

	return;
}

// 1.성적확인
void check_grades(){
	int stu_id, check=1;
	char pw[16];
	student *cur;

	if(head==NULL){//저장된 정보가 없을 때
		printf("저장된 정보가 없습니다.\n");
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
		cur = cur -> next;
	}
	if(cur == NULL)//끝까지 다 돌았을 때
		printf("귀하의 학번 정보가 없습니다!\n");
	return;
}

// 선택된 학생의 석차를 계산해주는 함수
int ranking(student *cur)
{
	student *tmp;
	int cnt = 1; // 등수 계산 변수

	tmp = head;
	while(tmp != NULL) {
		// 선택된 학생보다 점수 높으면 ++
		if(tmp->grades_average > cur->grades_average) {
			cnt++;
		}
		else;

		tmp = tmp->next;
	}

	return cnt;
}

//성적 출력 함수
void show_grades(student * student_cur){
	subject *scur; // 선택된 학번의 subhead를 가지는 변수
	int rank;

	scur = student_cur->subhead;

	// 성적입력이 아무것도 없을 때
	if(student_cur->subhead == NULL){
		printf("저장된 정보가 없으므로 [Menu]로 돌아갑니다.\n");
		return;
	}

	printf("<%s>님의 성적\n", student_cur->name);
	while(scur != NULL){
		printf("%s : %c%c\n", scur->subject, scur->grade[2], scur->grade[3]);
		scur = scur->next;
	}

	rank = ranking(student_cur); // 석차계산

	printf("\n이수학점: %.f\n",student_cur->sum_of_completes);
	printf("평점평균: %.1f\n", student_cur->grades_average);
	printf("전체석차: %d\n", rank);
	return ;
}

//2. 성적 입력
void input_grades(){
	student * student_cur;
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

	student_cur = head;

	while(student_cur!=NULL){//student노드의 연결리스트의 마지막 노드까지 이동
		if(student_cur->student_id==id)
			break;

		student_cur=student_cur->next;
	}

	if(student_cur==NULL){
		printf("입력하신 학번의 정보가 존재하지 않습니다\n");
		printf("[Menu]로 돌아갑니다.\n");
		return;
	}

	subject *subcur; // student의 subhead를 가지고 있는 cur

	while(contnum){
		subject *newNode; // 새로운 subject 노드를 가질 변수

		// 학번에 대한 성적이 아무것도 없을 때
		if(student_cur->subhead == NULL){ // cur->subhead는 학생노드에서 과목구조체의 head를 접근
			newNode = add_subject(); // 함수에 리턴값으로 성적노드를 새롭게 받음
			student_cur->subhead = newNode; // cur->subhead에 새로운 성적노드 연결
		}
		else{
			subcur = student_cur->subhead; 

			while(subcur->next != NULL){
				subcur = subcur->next;
			}

			newNode = add_subject();
			subcur->next = newNode; // 성적노드를 연결
		}
		if(newNode->grade[2]!='F') student_cur->sum_of_completes+=newNode->complete;//성적 등급이 F일 경우 이수학점의 합은 전과 동일
			student_cur->sum_of_multiplies+=((newNode->grade[1])/10.0)*(newNode->complete);
		if(student_cur->sum_of_completes==0)
			student_cur->sum_of_completes += 1;//이수학점의 합이 0일 때에 평균을 구하기 위해 1을 더함
		student_cur->grades_average=(student_cur->sum_of_multiplies)/(student_cur->sum_of_completes);	
		printf("성적을 더 입력하시려면 1, 그만 입력하시려면 0을 입력하시오: <1 or 0입력>\n");
		getchar();
		scanf("%d", &contnum);
	}

	return;
};

// 성적노드의 정보(과목, 성적, 이수학점)을 입력받고 해당 노드를 반환
subject* add_subject(){
	subject * tmp = (subject *)malloc(sizeof(subject));

	printf("과목: ");
	scanf("%s",tmp->subject);
	printf("성적: ");
	scanf("%d", &tmp->grade[0]);
	grade_array(tmp->grade);
	printf("이수학점 : ");
	scanf("%lf", &tmp->complete);
	tmp -> next = NULL;

	return tmp;
}

//평점*10(grade[1])과 성적 등급(grade[2],grade[3])을 구하는 함수
/*A : 97~100 A0 : 94~96 A- : 90~93
B+ : 87~89 B0 : 84~86 B- : 80~83
C+ : 77~79 C0 : 74~76 C- : 70~73
D+ : 67~69 D0 : 64~66 D- : 60~63
F : 60
A+ : 4.5 A0 : 4.3 A- : 4.0
B+ : 3.5 B0 : 3.3 B- : 3.0
C+ : 2.5 C0 : 2.3 C- : 2.0
D+ : 1.5 D0 : 1.3 D- : 1.0
F : 0
*/
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
		if(grade[0]%10>=7||grade[0]==100){
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
	tmp->sum_of_multiplies=0;
	tmp->sum_of_completes=0;
	tmp->ranking = 0;

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
		//tmp->ranking = 1;
		tmp->next = NULL;
	}
	tmp->subhead = NULL; // subhead도 NULL로 초기화 필요

	return;
}

//4. 학생정보삭제
void delete_student(void){
	student * cur;
	student * prev;//삭제하는 노드의 다음노드와 이전 노드를 연결 시 사용
	char admin_pwd[18] = "admin1234";//관리자 비밀번호
	char check_admin[18];//관리자 비밀번호 확인
	char tmp_name[10];//삭제할 학생 노드의 이름을 임시로 저장
	char yorn;//y 또는 n을 받음
	int del_stu_id;
	if(head!=NULL){
		cur = head;
		printf("관리자 비밀번호: ");
		scanf("%s", check_admin);
		if(strcmp(admin_pwd, check_admin)==0){//관리자 비밀번호 확인
			while(1){
				printf("학번: ");
				scanf("%d", &del_stu_id);
				while(cur!= NULL){
					if(cur->student_id== del_stu_id){//삭제할 학번의 노드를 찾음
						printf("<%s>님의 정보를 삭제하시겠습니까?<y or n>\n", cur->name);
						getchar();
						yorn=getchar();
						if(yorn == 'y' || yorn =='Y'){
							strcpy(tmp_name, cur->name);
							if(cur==head)
								head = head->next;
							else
								prev->next = cur->next;
							free(cur);
							printf("<%s>님의 정보를 삭제했습니다.\n", tmp_name);
						}
						else
							printf("<%s>님의 정보를 삭제하지 않았습니다.\n", cur->name);
						return;
					}
					prev = cur;
					cur = cur->next;
				}
				if(cur==NULL){//해당 학번 정보가 없을 경우
					printf("귀하의 학번 정보가 올바르지 않습니다!\n");
					cur = head;
				}
			}
		}
		printf("비밀번호가 올바르지 않습니다!\n");
		return;
	}
	printf("저장된 정보가 없으므로 [Menu]로 돌아갑니다.\n");
	return ;
}
