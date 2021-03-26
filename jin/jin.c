#include<string.h>
#include<stdlib.h>
#include<stdio.h>

/*추가-삭제함수완료
  에러: 평점 평균이 마지막에 입력한 이수학점만 받음.
  <만들어야 할 것>
  선택정렬로 평정평균 기준 내림차순 정렬 - swap
 */

//과목의 정보(이름,점수, 학점)를 담고 있는 구조체
typedef struct subject_grade{
	char subject[16];
	int grade[5];//grade[0]은 2자리 성적, grade[1]은 10*평점, grade[2],grade[3]은 등급의 아스키 코드값을 담게 할 것
	double complete;
	struct subject_grade *next;
}subject;

//학생의 정보(학번, 이름, 비밀번호, 과목head주소-subhead)를 담고 있는 구조체
typedef struct all_node{
	int student_id;
	char name[16];
	char password[16];
	subject *subhead; //과목구조체의 head를 가리키게 하여 순환을 시작하는 역할
	double sum_of_completes;
	double sum_of_multiplies;// 평점*이수학점의 합
	double grades_average;
	struct all_node *next;//다음 학생과 연결해주는 역할
}student;

student *head;

int menu(void);
void show_grades(student *, int);
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
		//printf("Error\n");
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
			delete_student();//학생정보삭제
			break;
		case 0:
			printf("프로그램을 종료합니다.\n");
			return;
	}

	return;
}

// 1.성적확인
void show_grades(student * cur,int ranking){

	subject *scur; // 선택된 학번의 subhead를 가지는 변수

	scur = cur->subhead;


	//int num = 0, sum_completes = 0; // sum_completes: 이수학점의 합
	//double sum_grades; 
	// 성적입력이 아무것도 없을 때
	if(cur->subhead == NULL){
		printf("There's nothing saved. Go to [Menu]\n");
		return;
	}

	printf("<%s>님의 성적\n", cur->name);
	while(scur != NULL){
		printf("%s : %c%c\n", scur->subject, scur->grade[2], scur->grade[3]);
		scur = scur->next;
	}

	printf("\n이수학점: %.f\n",cur->sum_of_completes);//student노드의 이수학점합으로 바꿔줄것
	printf("평점평균: %.1f\n", cur->grades_average);
	printf("전체석차: %d\n", ranking);
	printf("확인: %f\n",cur->sum_of_completes);
	//ranking변수 추가할 것...
	//전체석차 .....평점 평균을 성적 입력할 때에 구해서 저장해주고 난 후 학생 노드들을 재 배열 한다..?
	//ranking는 성적 출력에서 처음에 0으로 시작해서 현재 노드보다 다음 노드의 평점 평균이 크다면 +1을, 같다면 0을 더하도록 하고
	//num_of_sameaverage변수에 1을 더하도록 하여 공동 순위를 표현하도록 하였다.


	return ;
}

//성적 확인함수
void check_grades(){
	int stu_id, check=1;
	char pw[16]; 
	student *cur;
	int num_of_same_average=0, ranking=1;

	if(head==NULL){
		printf("저장된 정보가 없습니다.\n");
		return;
	}
	cur = head;
	printf("학번: ");
	scanf("%d", &stu_id);
	while(cur!=NULL){
		//여기서 계산?
		if(cur->student_id==stu_id){
			while(1){
				printf("비밀번호: ");
				scanf("%s", pw);
				if(strcmp(cur->password, pw) != 0)
					printf("비밀번호가 일치하지 않습니다!\n");
				else 
					break;
			}
			show_grades(cur,ranking);

			return;
		}
		//printf("error\n");
		if(cur->next!=NULL){
			if(cur->next->grades_average<cur->grades_average){
				ranking += num_of_same_average;
				ranking ++;
			}	
			else if(cur->next->grades_average==cur->grades_average){
				num_of_same_average++;
			}
		}
		cur = cur -> next;
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
	/*cur->sum_of_completes=0;
	cur->sum_of_multiplies=0;
	cur->grades_average=0;*/

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

	subject *subcur; // student의 subhead를 가지고 있는 cur

	while(contnum){
		subject *newNode; // 새로운 subject 노드를 가질 변수

		// 학번에 대한 성적이 아무것도 없을 때
		if(cur->subhead == NULL){ // cur->subhead는 학생노드에서 과목구조체의 head를 접근
			newNode = add_subject(); // 함수에 리턴값으로 성적노드를 새롭게 받음
			cur->subhead = newNode; // cur->subhead에 새로운 성적노드 연결
			cur->sum_of_completes+=newNode->complete;
			cur->sum_of_multiplies+=((newNode->grade[1])/10.0)*(newNode->complete);
		}
		else{
			subcur = cur->subhead; 

			while(subcur->next != NULL){
				subcur = subcur->next;
			}

			newNode = add_subject();
			subcur->next = newNode; // 성적노드를 연결
			cur->sum_of_completes+=newNode->complete;
			cur->sum_of_multiplies+=((newNode->grade[1])/10.0)*(newNode->complete);
		}
		cur->grades_average=(cur->sum_of_multiplies)/(cur->sum_of_completes);	
		printf("성적을 더 입력하시려면 1, 그만 입력하시려면 0을 입력하시오: <1 or 0입력>\n");
		getchar();
		scanf("%d", &contnum);
	}

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
	scanf("%lf", &tmp->complete);
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


void rearrange_nodes(void){	//grade_average를 기준으로 내림차순 정렬
	student * sort_cur = (student *)malloc(sizeof(student));
	while(sort_cur!=NULL){
		double biggest_average;
		student * prev_biggest_node;
		while(){
			= sort_cur;
		}		
		student * tmp; tmp = NULL;
		swap_data(tmp, a);//a바뀌기
		swap_data(a, b);//a, b바꾸기
		swap_data(b, tmp);//b 바꾸기
		//next 바꾸기도 추가
		sort_cur = sort_cur->next;
	}
	return;
}

void swap_data(student * node1, student node2){ //노드 데이터 전환환
	student * node1 = (student *)malloc(sizeof(studnt *));
	student * node2 = (student *)malloc(sizeof(studnt *));

	node1 -> student_id = node2 -> student_id;
	strcpy(node1->name, node2->name);
	strcpy(node1->password, node2->password);
	node1->sum_of_completes = node2->sum_of_completes;
	node1->sum_of_multiplies = node2->sum_of_multiplies;
	node1->grades_average = node2->grades_average;

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

	return;
}

///*
//4. 학생정보삭제
void delete_student(void){
	student * cur;/* = (student *)malloc(sizeof(student));*/
	student * prev;
	char admin_pwd[18] = "admin1234";//관리자 비밀번호
	char check_admin[18];
	char tmp_name[10];
	char yorn;
	int del_stu_id;
	if(head!=NULL){
		cur = head;
		printf("관리자 비밀번호: ");
		scanf("%s", check_admin);
		if(strcmp(admin_pwd, check_admin)==0){
			while(1){
				printf("학번: ");
				scanf("%d", &del_stu_id);
				while(cur!= NULL){
					if(cur->student_id== del_stu_id){
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
				if(cur==NULL){
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
