#include <stdio.h>
#include <stdlib.h> // 하다 말았어요......

typedef struct student{
    char name[50];
    int code;
    char psd[20];
} Student;
   
typedef struct grade{
    int code;
    char class[20];
    int grade;
    int abcf;
    //int sum;
} Grade;
  
void checkgrade();
void inputgrade();
void inputstudent();
int main()
{
    int n;
 
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
        else{
            continue;
        }
        printf("\n");
    }
    return 0;
}
void checkgrade()
{
    int n;
    char pw;
    FILE *fp1;

    printf("학번 : ");
    scanf("%d", &n);
    printf("비밀번호 : ");
    scanf("%s", &pw);
    

    return;
}
void inputgrade()
{
    FILE *fp;
    Grade *test1;
    char *fname = "grade.txt";

    if((fp = fopen(fname, "w+")) == NULL){
        fprintf(stderr, "fopen error for %s\n", fname);
        exit(1);
    }
    test1 = (Grade *)malloc(sizeof(Grade));

    printf("학번 : ");
    scanf("%d", test1->code);
    printf("과목 : ");
    scanf("%s", test1->class);
    printf("성적 : ");
    scanf("%d", test1->grade);
    printf("학점 : ");
    scanf("%d", test1->abcf);
    
    fclose(fp);
    exit(0);
    return;
}
void inputstudent()
{
    FILE *fpp;
    Student *test2;
    char *fname2 = "student.txt";

    if((fpp = fopen(fname2, "w+")) == NULL){
        fprintf(stderr, "fopen error for %s\n", fname2);
        exit(1);
    }
    test2 = (Student *)malloc(sizeof(Student));

    printf("학생이름 : ");
    scanf("%s", test2->name);
    printf("학번 : ");
    scanf("%d", test2->code);
    printf("비밀번호 : ");
    scanf("%s", test2->psd);

    fclose(fpp);
    exit(0);
    return;
}
