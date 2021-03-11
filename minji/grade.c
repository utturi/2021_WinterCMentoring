#include <stdio.h>
#include <stdlib.h>

typedef struct stnode{
    char name[10];
    int stnum;
    char pwd[10];
    struct stnode *next;
}stnode;

typedef struct node{
    int stnum;
    char subject[15];
    int grade;
    int credit;
    struct node *next;
}node;
stnode *heads;
node *headg;

int menu();
/*
   void confirm_grade(){
   stnode *=(stnode *)malloc(sizeof(stnode));
   head-=list;
   stnode *cur;
   cur->next=list;

   stnode a;
   printf("학번 : ");
   scanf("%d",&a.stnum);

   while (1){
   if (strcmp(a.stnum,cur->stnum)!=0){
   break;
   }
   else if (cur==NULL){
   printf("귀하의 학번 정보가 없습니다!");
   menu();
   }
   else
   cur=cur->next;
   }
   printf("\n비밀번호 : ");
   scanf("%d",a.pwd);

   while(1){
   if (strcmp (a.pwd, cur->pwd)==0)
   break;
   else {
   printf("비밀번호가 일치하지 않습니다!\n");
   printf("비밀번호 : ");
   scanf("%d",a.pwd);
   }
   }

   printf("<%s>님의 성적\n",cur->name);
   node *list
   printf("%s : %s\n%s : %s\n%s : %s\n",cur->subject, cur->s);

   }
 */
void add_grade(){
    while(1){
        stnode *curs;
        curs=heads;

        node *glist=(node *)malloc(sizeof(node));
        node *curg;
        glist->next=NULL;

        printf("학번 : ");
        scanf("%d",&glist->stnum);

        if (curs==NULL){
            free(glist);
            printf("등록된 학번이 아닙니다!");
            menu();
        }

        while(1){
            if (curs->stnum==glist->stnum)
                break;
            else {
                free(glist);
                printf("등록된 학번이 아닙니다!\n");
                menu();
            }
            curs=curs->next;
        }

        printf("과목 : ");
        scanf("%s",glist->subject);
        printf("성적 : ");
        scanf("%d",&glist->grade);
        printf("학점 : ");
        scanf("%d",&glist->credit);

        if (headg==NULL)
            headg=glist;
        else{
            curg=headg;
            while(curg->next!=NULL){
                curg=curg->next;
            }
            curg->next=glist;
        }

        // FILE *fp=fopen("Grade.txt","w");
        // fprintf("학번 : %d 과목 :  %s 성적 : %d 학점 :  %d",&list->stnum,list->subject,&list->grade,&list->credit);
        // fclose(fp);

        printf("성적을 더 입력하시려면 1, 그만 입력 받으려면 0을 입력하시오 : <1 or 0 입력>\n");
        int a;
        scanf("%d",&a);
        if(a==1)
            continue;
        else
            printf("성적입력 종료\n");
        break;
    }
}


void add_student(){
    stnode *list=(stnode *)malloc(sizeof(stnode));
    stnode *cur;
    // head->next=list;
    list->next=NULL;

    printf("학생이름 : ");
    scanf("%s",list->name);
    printf("학번 : ");
    scanf("%d",&list->stnum);
    printf("비밀번호 : ");
    scanf("%s",list->pwd);

    if (heads==NULL){
        heads=list;
    }
    else {
        cur = heads;
        while(cur->next != NULL){
            cur=cur->next;
        }
        cur->next=list;

        // FILE *fp=fopen("student.txt","wb");
        // fwrite(&list,sizeof(list ),1 , fp);
        // fclose(fp);
    }
}
/*
   void delete_student(){

   }
 */

int menu (){
    while (1){
        printf("[Menu]\n1. 성적확인 2. 성적입력 3. 학생정보등록 4. 학생정보삭제 0. 프로그램 종료\n");
        int a;
        scanf("%d",&a);
        switch(a){
            //    case 1:
            //        confirm_grade();
            case 2:
                add_grade();
                break;
            case 3:
                add_student();
                break;
                //    case 4:
                //          delete_student();
            case 0:
                return 0;
        }
    }
}

int main()
{
    heads=NULL;
    headg=NULL; 
    menu();
    return 0;
}
