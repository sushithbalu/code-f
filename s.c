#include<string.h>
#include<stdlib.h>
#include<stdio.h>
struct data{
	char *date;
	char *close;
	char *volume;
	struct data *next;
};

#define MAX_SIZE 1024
#define MAX_LINES 5000
#define RAWS 6

void newnode(struct data **lineref, char *line, char *close, char *volume);

int main()
{
	struct data *table = NULL;
	struct data *current;
	int count, j = 1, i;
	char array[MAX_LINES][MAX_SIZE];
	char *ptr[RAWS];
	FILE *stream; 
	double vpt;
	double close;
	double pclose;
	double volume;

	if((stream = fopen("table.csv", "r")) == NULL){
		printf("file could not opened\n");
		exit(EXIT_FAILURE);
	}
	
	while((count < MAX_LINES)&&fgets(array[count], sizeof(array[0]), stream)){
		array[count][strlen(array[count])-1] = '\0';
		count++;
	}
	while(j < count){
		ptr[0] = strtok(array[j++], ",");
		for(i = 1; i <= RAWS; i++){
			ptr[i] = strtok(NULL, ",");
		}
		newnode(&table, ptr[0], ptr[4], ptr[5]);
	}
	current = table;
	vpt = 0;
	/* vpt for first date*/
//	printf("date:%s vpt = %f\n", current->date, vpt = 0);
	while(current != NULL){ 
		
		close = atof(current->next->close);
		pclose = atof(current->close);
		volume = atof(current->next->volume);
		vpt = vpt + volume*((close-pclose)/pclose);
		printf("vpt = %f\n", vpt);
		current = current->next;
	}

	return 0;
}

void newnode(struct data **lineref, char *line, char *close, char *volume)
{
	struct data* newnode = malloc(sizeof(struct data));
	newnode->date = line;
	newnode->close = close;
	newnode->volume = volume;
	newnode->next = *lineref;
	*lineref = newnode;
}
