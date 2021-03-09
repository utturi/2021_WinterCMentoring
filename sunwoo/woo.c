#include <stdio.h>
#include <stdlib.h>
//비밀번호.. ...

typedef struct student{
    char name[50];
    int code;
    char psd[20];
    struct student *next;
} Student;
   
typedef struct grade{
    int code;
    char class[20];
    int grade;
    int abcf;
    //int sum;
    struct grade *next;
} Grade;

Student *shead, *stail;
Grade *ghead, *gtail;

void checkgrade();
void inputgrade();
void inputstudent();
//void delete();
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
            //delete();
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
void checkgrade()
{
    Student *scur = shead;
    Grade *cur = ghead;
    char pw[20];
    int n;
    int a=0;

    printf("학번 : ");
    scanf("%d", &n);
    while(scur != NULL){
        if(scur->code == n){
            a++;
            while(a==1){
                printf("비밀번호 : ");
                scanf("%s", pw);
                if(pw == scur->psd){
                    while(cur != NULL){
                        if(n == cur->code){
                            printf("<%s>님의 성적\n", scur->name);
                            printf("이수학점 : %d", cur->sum);
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
    

    return;
}
void inputgrade()
{
    int n=1;
    Grade *newNode = (Grade *)malloc(sizeof(Grade));
    newNode->next = NULL;

    while(n == 1){
        if(ghead == NULL){
            ghead = newNode;
        }
        else{
            gtail->next = newNode;
        }

        gtail = newNode;

        printf("학번 : ");
        scanf("%d", &(newNode->code));
        printf("과목 : ");
        scanf("%s", newNode->class);
        printf("성적 : ");
        scanf("%d", &(newNode->grade));
        printf("학점 : ");
        scanf("%d", &(newNode->abcf));
        printf("성적을 더 입력하시려면 1, 그만 입력 받으려면 0을 입력하시오 : ");
        scanf("%d", &n);
        if(n == 0){
            break;
        }
    }

    return;
}
void inputstudent()
{
    Student *newNode = (Student *)malloc(sizeof(Student));
    newNode->next = NULL;

    if(shead == NULL){
        shead = newNode;
    }
    else{
        stail->next = newNode;
    }
    //stail = newNode;

    printf("학생이름 : ");
    scanf("%s", newNode->name);
    printf("학번 : ");
    scanf("%d", &(newNode->code));
    printf("비밀번호 : ");
    scanf("%s", newNode->psd);
    return;
}
