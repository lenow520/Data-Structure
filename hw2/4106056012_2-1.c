#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#define FILE_INPUT "test.txt" //define input filename
#define MAX 1500000
char move[MAX];
int i,j;
typedef struct node
{
    int data;
    struct node *next; // Pointer to next node
    struct node *prev; // Pointer to previous node
}platform;
platform *pf[20];

void trolley(void){
	char out;
	j=0;
	for(i=0;i<20;i++){	//initialize the platforms
		pf[i] = (platform*)malloc(sizeof(platform));
		pf[i]->data=0;
	}
	pf[0]->next=pf[1];
	pf[0]->prev=pf[19];
	pf[19]->next=pf[0];
	pf[19]->prev=pf[18];
	for(i=1;i<19;i++){
		pf[i]->next=pf[i+1];
		pf[i]->prev=pf[i-1];
	}
	
	platform *ptr=(platform*)malloc(sizeof(platform));
	ptr=pf[0];

	while(move[j]!='#'){
		switch(move[j]){
			case '+':
			ptr->data++;
			break;
			
			case '-':
			ptr->data--;	
			break;
			
			case '>':
			ptr=ptr->next; 
			break;
			
			case '<':
			ptr=ptr->prev; 	
			break;
			
			case '.':
			out=(ptr->data+270)%27 +64; 
			if(out=='@'){printf(" ");}
			else{printf("%c",out);}
			break;
		}
		j++;
	}
	
	
	
}

int main(void){
	char c;
	int size=0;
	FILE *fp;
	fp = fopen(FILE_INPUT,"r");			// read the file only by pointer
	while(!feof(fp)){
		fscanf(fp, "%c", &c);
		move[size++]=c; 
	}
	move[size-1]='#';
	fclose(fp);

	trolley();
    printf("\n");
    return 0;
}
