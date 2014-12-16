/* 
 * Volume-Price Trend Indicator 
 *
 *	VPT = VPTprev + VOLUME*((CLOSE-CLOSEprev)/CLOSEprev)
 *
 * Assumtion: VPT for First date is zero
 *
 */

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<assert.h>

struct data{
	char *date;
	char *close;
	char *volume;
	struct data *next;
};

#define MAX_SIZE 1024
#define MAX_LINES 5000
#define ROWS 6

void push(struct data **lineref, char *date, char *close, char *volume);

int main()
{
	int count, i, j = 1;
	char array[MAX_LINES][MAX_SIZE]; /*two dimesional array*/
	char *ptr[ROWS];
	double vpt;
	double close;
	double close_prev;
	double volume;
	FILE *stream; /*input file handler*/
	FILE *output; /*output file handler*/
	struct data *table = NULL; 
	struct data *current;

	/*open input file*/
	if((stream = fopen("table.csv", "r")) == NULL){
		fprintf(stderr, "file could not open: errno(%d)\n", errno);
		exit(EXIT_FAILURE);
	}	
	/*store datas into a 2D array*/
	while((count < MAX_LINES) && fgets(array[count], sizeof(array[0]), stream)){
		array[count][strlen(array[count])-1] = '\0';
		count++;
	}
	fclose(stream); /*close input file*/

	while(j < count){
		ptr[0] = strtok(array[j++], ",");
		for(i = 1; i <= ROWS; i++){
			ptr[i] = strtok(NULL, ",");
		}
		/*push Date, Close and Volume values into a linked list*/ 
		push(&table, ptr[0], ptr[4], ptr[5]); 
	}

	current = table;
	output = fopen("output.txt", "w"); /*open output file*/

	fprintf(output, "date: 1998-04-23  vpt = 0\n");	/* vpt for first date*/
	while(current->next != NULL){ 
			/*convert charecter values to float*/
		close = atof(current->next->close); 
		close_prev = atof(current->close);
		volume = atof(current->next->volume);
		assert(close_prev != 0); /*handle divison by zero case*/ 

		vpt = vpt + volume*((close-close_prev)/close_prev);
			/*write output values to the file output.txt*/
		fprintf(output,"date: %s  vpt = %f\n", current->next->date, vpt);
		current = current->next;
	}
	free(current);	
	fclose(output); /*close output file*/
	return 0;
}

/*function for pushing datas into linked list*/
void push(struct data **lineref, char *date, char *close, char *volume)
{
	struct data* newnode = malloc(sizeof(struct data));

	newnode->date = date;
	newnode->close = close;
	newnode->volume = volume;
	newnode->next = *lineref;
	*lineref = newnode;
}
