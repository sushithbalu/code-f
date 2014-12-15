/*program to calculate volume-price trend*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 1024
#define MAX_LINES 5000

int main()
{
	int i, j = 0, k = 0;
	char line[MAX_SIZE];
	char *arg[MAX_LINES];
	FILE* stream = fopen("table.csv", "r");
	double close[MAX_LINES];
	double volume[MAX_LINES];
	double vpt[MAX_LINES];
	
	if(stream == NULL){
		printf("no such file\n");
		exit(EXIT_FAILURE);
	}
	while(fgets(line, sizeof(line), stream)){
		arg[0] = strtok(line, ",");
		for(i = 1; i < 7; i++){
			arg[i] = strtok(NULL, ",\n");
		}
//		printf("%s\t", arg[4]);
		close[j++] = atof(arg[4]);
		volume[k++] = atof(arg[5]);
	}
		for(i = MAX_LINES-1; i > 0; i--){
			vpt[i] = vpt[i] + volume[i]*((close[i] - close[i+1])/close[i+1]);
			printf("close = %f, volume = %f, vpt = %f\n", close[i], volume[i], vpt[i]);
		}
	return 0;
}
