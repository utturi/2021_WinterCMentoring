#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	char *fname = "example_file_1.txt";

	// w+ : 만일 지정된 파일이 존재하지 않으면 지정된 이름의 파일을 생성함. 해당파일이 이미 존재하면 해당 파일의 길이는 0이 되면서 원래의 자료는 모두 잃게 됨
	// r+ : 만일 지정된 파일이 존재하지 않으면 함수의 호출은 실패하고 NULL을 리턴. 해당 파일이 이미 존재하면 원래의 자료는 그대로 유지됨
	if((fp = fopen(fname, "w+")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}
	else {
		printf("Success!\n");
	}
	
	fclose(fp);
	exit(0);
}
