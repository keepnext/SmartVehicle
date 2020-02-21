#include <stdio.h> 
#include "student.h"
int main(int argc, char* argv[])  
{ 
	struct student rec;
	FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "사용법: %s 파일이름\n",argv[0]);
		exit(1); 
	}

	fp = fopen(argv[1], "wb");
	printf("%-9s %-7s %-4s\n", "학번", "이름", "점수"); 


	while (scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3) {
		// 작업 구조체 파일 쓰기 -----
	}

	fclose(fp);
	exit(0);
} 
