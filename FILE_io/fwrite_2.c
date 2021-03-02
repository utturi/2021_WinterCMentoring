#include <stdio.h>
#include <stdlib.h>

struct node {
	char name[64];
	char psw[20];
};

int main()
{
	FILE *fp;
	struct node *test1;
	char *fname = "example_file_1.txt";

	if((fp = fopen(fname, "w+")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	for(int i = 0; i < 3; i++) {
		test1 = (struct node*)malloc(sizeof(struct node));

		printf("이름을 입력하시오 : ");
		scanf("%s", test1->name);
		printf("비밀번호를 입력하시오 : ");
		scanf("%s", test1->psw);

		if(fwrite(test1, sizeof(struct node), 1, fp) != 1) {
			fprintf(stderr, "fwrite error\n");
			exit(1);
		}
	}

	fclose(fp);
	exit(0);
}
