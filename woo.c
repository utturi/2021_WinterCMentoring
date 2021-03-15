//성적입력하고 성적확인후에 다시 성적입력을 하면 입력(저장?)이 안되는듯.................. 
// 그냥 성적확인 이 안된다... !!!!

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
    double ave; // 평점저장
    //double realave;
    int abcf;
    int sum; // 이수학점
    struct grade *next;
} Grade;

Student *shead, *stail;
Grade *ghead, *gtail;

void checkgrade();
void inputgrade();
void inputstudent();
void delete();
void transgrade(int, Grade *);
void myflush();
int main()
{
    int n;

    FILE *gp, *sp;
    char *fname1 = "grade.txt";
    char *fname2 = "student.txt";
    if((gp = fopen(fname1, "w+")) == NULL){
        fprintf(stderr, "fopen error for %s\n", fname1);
        exit(1);
    }
    if((sp = fopen(fname2, "w+")) == NULL){
        fprintf(stderr, "fopen error for %s\n", fname2);
        exit(1);
    }

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
            printf("\n");
            continue;
        }
        printf("\n");
    }

    fclose(gp);
    fclose(sp);
    return 0;
}
void checkgrade() //성적확인
{
    Student *scur = shead;
    Grade *cur = ghead;
    char pw[20];
    int n, st;
    int a=0;
    //int b=1;

    printf("학번 : ");
    scanf("%d", &n);
    while(scur != NULL){
        if(scur->code == n){
            a++;
            while(a==1){
                printf("비밀번호 : ");
                scanf("%s", pw);
                st = strcmp(pw, scur->psd);
                if(st == 0){
                    while(cur != NULL){
                        if(cur->code == n){
                            printf("<%s>님의 성적\n", scur->name);
                            printf("%s : %s\n\n", cur->class, cur->grade);
                            printf("이수학점 : %d\n", cur->sum);
                            printf("평점평균 : %.1f\n", cur->ave);
                            //printf("전체석차 : %d\n");

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
void inputgrade() //성적입력
{
    int n=1;
    int gr;
    Grade *newNode = (Grade *)malloc(sizeof(Grade));
    newNode->next = NULL;

    while(n == 1){
        int a=0;
        Student *scur = shead;

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
        transgrade(gr, newNode);
        printf("학점 : ");
        scanf("%d", &(newNode->abcf));

        if(ghead == NULL){
            ghead = newNode;
            newNode->sum = 0;
        }
        else{
            gtail->next = newNode;
            //newNode->sum += newNode->abcf;
        }

        gtail = newNode;

        newNode->sum += newNode->abcf;

        printf("성적을 더 입력하시려면 1, 그만 입력 받으려면 0을 입력하시오 : ");
        scanf("%d", &n);
        
    }
    return;
}
void inputstudent() //학생정보등록
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
void delete() //학생정보삭제
{
    int p, c;
    int s=0;
    char yorn;
    Student *curs = shead;
    Student *prev = (Student *)malloc(sizeof(Student));

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
            curs = curs->next;
        }
        if(s != 1){
            printf("귀하의 학번정보가 없습니다!\n");
            curs = shead;
        }
    }
    
    printf("<%s>님의 정보를 삭제하시겠습니까? <y or n> ", curs->name);
    myflush();
    scanf("%c", &yorn);

    if(yorn == 'y'){
        if(curs == shead){
            shead = curs->next;
        }
        else{
            prev = curs;
            curs = curs->next;
            //free(prev);
        }
        printf("<%s>님의 정보를 삭제했습니다!\n", curs->name);
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
        Node->ave = 0;
    }
    else{
        return;
    }
    return;
}
void myflush()
{
    while(getchar() != '\n'){
        ;
    }
}
