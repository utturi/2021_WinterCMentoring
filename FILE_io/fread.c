#include <stdio.h>
#include <stdlib.h>

struct node {
	char name[64];
	char psw[20];
};

int main()
{
	FILE *fp;
	struct node *test;
	char *fname = "example_file_1.txt";

	if((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}
	
	test = (struct node*)malloc(sizeof(struct node));

	if(fread(test, sizeof(struct node), 1, fp) != 1) {
		fprintf(stderr, "fread error");
		exit(1);
	}

	printf("name = %s, psw : %s\n", test->name, test->psw);
	
	fclose(fp);
	exit(0);
}
