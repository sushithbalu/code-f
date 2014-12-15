#include<stdio.h>
#include<stdlib.h>

int main()
{
	char line[1024];
	FILE* stream = fopen("table.csv", "r");
	
	if(stream == NULL){
		printf("no such file\n");
		exit(EXIT_FAILURE);
	}

	while(fgets(line, 1024, stream)){
		printf("%s\n", line);
	}
	return 0;
}
