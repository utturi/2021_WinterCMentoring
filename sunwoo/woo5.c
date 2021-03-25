#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
    char name[50];
    int code;
    char psd[20];
    struct student *next;
} Student;
   
typedef struct grade{
    int code;
    char class[20];
    char grade[5];
    double ave; // 평점저장 4.5 ~
    double realave; // 평점평균 * sum
    double average; // 평점평균
    int abcf; // 몇학점? 
    int sum; // 석차계산용 총 학점 저장 (F포함)
    int sum2; //  에프만 저장
    struct grade *next;
} Grade;

Student *shead, *stail;
Grade *ghead, *gtail;

void checkgrade(); // 1. 성적확인
void inputgrade(); // 2. 성적입력
void inputstudent(); // 3. 학생정보등록
void delete(); // 4. 학생정보삭제
void transgrade(int, Grade *); // 등급변환
void ave(Grade *, int); // 평점평균계산
int ranking(Grade *); // 성적확인하고자 하는 학생의 석차 계산
void myflush();
int main()
{
    int n;
    shead = NULL;
    stail = NULL;
    ghead = NULL;
    gtail = NULL;

    while(1){
        printf("[Menu]\n1. 성적확인  2. 성적입력  3. 학생정보등록  4. 학생정보삭제  0.프로그램종료\n");
        scanf("%d", &n);
        if(n==0){
            break;
        }
        else if(n == 1){
            checkgrade();
        }
        else if(n == 2){
            inputgrade();
        }
        else if(n == 3){
            inputstudent();
        }
        else if(n == 4){
            delete();
        }
        else{
            ;
        }
        printf("\n");
    }

    return 0;
}
void checkgrade() //1 성적확인
{
    Student *scur = shead;
    Grade *cur = ghead;
    Grade *gcur = (Grade *)malloc(sizeof(Grade));
    char pw[20];
    int n, st, rank;
    int a=0;

    printf("학번 : ");
    scanf("%d", &n);
    while(scur != NULL){
        if(scur->code == n){
            a++; // 학번이 일치하는 학생이 없으면 a=0유지: while문 돌지 않고 리턴
            while(a==1){
                printf("비밀번호 : ");
                scanf("%s", pw);
                st = strcmp(pw, scur->psd);
                if(st == 0){
                    while(cur != NULL){
                        if(cur->code == n){
                            printf("\n<%s>님의 성적\n", scur->name);
                            cur->realave = 0;
                            gcur = cur;
                            while(gcur != NULL){
                                if(gcur->code == n){
                                    printf("%s : %s\n", gcur->class, gcur->grade);
                                }
                                gcur = gcur->next;
                            }
                            printf("\n이수학점 : %d\n", cur->sum - cur->sum2);
                            printf("평점평균 : %.1f\n", cur->average); 
                            rank = ranking(cur);
                            printf("전체석차 : %d\n", rank);
                            a++;
                            break;
                        }
                        cur = cur->next;
                    }   
                }
                else{
                    printf("비밀번호가 일치하지 않습니다!\n");
                }
            }
            break;
        }
        scur = scur->next;
    }
    if(a==0){
        printf("귀하의 학번 정보가 없습니다!\n");
    }
    
    return;
}
void inputgrade() //2 성적입력
{
    int n=1;
    int gr;
    int k=0;
    while(n == 1){
        Student *scur = shead;
        Grade *newNode = (Grade *)malloc(sizeof(Grade));
        Grade *cur = ghead;
        newNode->next = NULL;
        int a=0;
        int b=0;

        printf("학번 : ");
        scanf("%d", &(newNode->code));
        while(scur != NULL){
            if(newNode->code == scur->code){
                a++;
            }
            scur = scur->next;
        }
        if(a==0){
            printf("등록된 학번이 아닙니다!\n");
            free(newNode);
            return;
        }

        printf("과목 : ");
        scanf("%s", newNode->class);
        printf("성적 : ");
        scanf("%d", &gr);
        transgrade(gr, newNode); // 점수입력받아서 바로 등급으로 변환저장
        printf("학점 : ");
        scanf("%d", &(newNode->abcf)); //몇학점?

        if(ghead == NULL){
            ghead = newNode;
            newNode->sum = 0; // 이수학점 누적저장(+=)위해 초기화
            newNode->sum2 = 0;
        }
        else{
            gtail->next = newNode;
        }
        gtail = newNode;

        while(cur != NULL){
            if(newNode->code == cur->code){
                cur->sum += newNode->abcf;
                if(newNode->ave == 0.0){  // F학점 저장
                    cur->sum2 += newNode->abcf;
                }
                b++;
                break;
            }
            cur = cur->next;
        }
        if(b == 0){
            newNode->sum += newNode->abcf;
            if(newNode->ave == 0.0){
                newNode->sum2 += newNode->abcf;
            }
        }
        ave(newNode, k);

        printf("성적을 더 입력하시려면 1, 그만 입력 받으려면 0을 입력하시오 : ");
        scanf("%d", &n);    
        if(n == 1){
            k++;
        }
    }
    return;
}
void inputstudent() //3 학생정보등록
{
    Student *newNode = (Student *)malloc(sizeof(Student));
    newNode->next = NULL;

    if(shead == NULL){
        shead = newNode;
    }
    else{
        stail->next = newNode;
    }
    stail = newNode;

    printf("학생이름 : ");
    scanf("%s", newNode->name);
    printf("학번 : ");
    scanf("%d", &(newNode->code));
    printf("비밀번호 : ");
    scanf("%s", newNode->psd);

    return;
}
void delete() //4 학생정보삭제
{
    int p, c;
    int s=0;
    char yorn;
    Student *curs = shead;
    Student *prev = (Student *)malloc(sizeof(Student));
    Grade *gcur = ghead;
    Grade *gprev = (Grade *)malloc(sizeof(Grade));

    printf("관리자 비밀번호 : "); // 관리자 비밀번호 1234
    scanf("%d", &p);
    if(p != 1234){
        printf("비밀번호가 일치하지 않습니다!\n");
        return;
    }
    while(s == 0){
        printf("학번 : ");
        scanf("%d", &c);
        while(curs != NULL){
            if(c == curs->code){
                s++;
                break;
            }
            prev = curs;
            curs = curs->next;
        }
        if(s != 1){
            printf("귀하의 학번정보가 없습니다!\n");
            curs = shead;
        }
    }
    while(gcur != NULL){ // 성적삭제위해
        if(gcur->code == curs->code){
            break;
        }
        gprev = gcur;
        gcur = gcur->next;
    }
    
    printf("<%s>님의 정보를 삭제하시겠습니까? <y or n> ", curs->name);
    myflush();
    scanf("%c", &yorn);

    if(yorn == 'y'){ 
        if(curs == shead){
            shead = curs->next; // 학생정보삭제
            ghead = gcur->next; // 성적삭제
        }
        else{
            prev->next = curs->next; //학생정보삭제
            gprev->next = gcur->next; //성적삭제
        }
        printf("<%s>님의 정보를 삭제했습니다!\n", curs->name);
        curs = curs->next;
        gcur = gcur->next;
    }
    else if(yorn == 'n'){
        printf("<%s>님의 정보를 삭제하지 않았습니다!\n", curs->name);
    }
    else{
        printf("잘못된 입력입니다!\n");
        return;
    }

    return;
}
void transgrade(int n, Grade *Node)
{
    if(n>=97 && n<=100){
        strcpy(Node->grade, "A+");
        Node->ave = 4.5;
    }
    else if(n<97 && n>93){
        strcpy(Node->grade, "A0");
        Node->ave = 4.3;
    }
    else if(n<94 && n>=90){
        strcpy(Node->grade, "A-");
        Node->ave = 4.0;
    }
    else if(n<90 && n>=87){
        strcpy(Node->grade, "B+");
        Node->ave = 3.5;
    }
    else if(n<87 && n>=84){
        strcpy(Node->grade, "B0");
        Node->ave = 3.3;
    }
    else if(n<84 && n>=80){
        strcpy(Node->grade, "B-");
        Node->ave = 3.0;
    }
    else if(n<80 && n>=77){
        strcpy(Node->grade, "C+");
        Node->ave = 2.5;
    }
    else if(n<77 && n>=74){
        strcpy(Node->grade, "C0");
        Node->ave = 2.3;
    }
    else if(n<74 && n>=70){
        strcpy(Node->grade, "C-");
        Node->ave = 2.0;
    }
    else if(n<70 && n>=67){
        strcpy(Node->grade, "D+");
        Node->ave = 1.5;
    }
    else if(n<67 && n>=64){
        strcpy(Node->grade, "D0");
        Node->ave = 1.3;
    }
    else if(n<64 && n>=60){
        strcpy(Node->grade, "D-");
        Node->ave = 1.0;
    }
    else if(n<60){
        strcpy(Node->grade, "F");
        Node->ave = 0.0;
    }
    else{
        ;
    }
    return;
}
void ave(Grade *cur, int n) //평점평균계산
{
    int a=0;
    Grade *gcur = ghead;
    while(gcur != NULL){
        if(gcur->code == cur->code && gcur->next != NULL){
            if(n == 0){
                gcur->realave += gcur->average*(gcur->sum-cur->abcf);
            }
            gcur->realave += (cur->abcf)*(cur->ave);
            gcur->average = (gcur->realave)/(gcur->sum);
            a++;
            break;
        }
        gcur = gcur->next;
    }
    if(a == 0){
        cur->realave = (cur->ave)*(cur->abcf);
        cur->average = (cur->realave)/(cur->sum);
    }

    return;
}
int ranking(Grade *cur) // 석차
{
    int r=1;
    Grade *gcur = ghead;
    while(gcur != NULL){
        if(cur->average < gcur->average){
            r++;
        }
        else if(cur->average == gcur->average){
            if(cur->sum < gcur->sum){
                r++;
            }
        }
        else{
            ;
        }
        gcur = gcur->next;
    }

    return r;
}
void myflush()
{
    while(getchar() != '\n'){
        ;
    }
}