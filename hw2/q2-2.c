#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <math.h>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define FILE_INPUT "test.txt" //define input filename
#define MAX 1500000
char input[MAX];
int i,j,count;
typedef struct node
{
    int data;
    struct node *next; // Pointer to next node
    struct node *prev; // Pointer to previous node
}platform;
platform *pf[20];

void trolley(void){
	j=0,count=0;
	int l,r,d,m;
	for(i=0;i<20;i++){	//initialize the platforms
		pf[i] = (platform*)malloc(sizeof(platform));
		pf[i]->data=270;
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

	while(input[j]!='#'){	//讀進字母 看自己,左,右邊的月台哪個離字母最近
		d=cstshift(ptr->data,input[j]);
//		printf("%c d=%d\n",input[j],d);
		l=cstshift(ptr->prev->data,input[j]);
//		printf("%c l=%d\n",input[j],l);
		r=cstshift(ptr->next->data,input[j]);
//		printf("%c r=%d\n",input[j],r);
		m=MIN(abs(r)+1,abs(l)+1);	//+1 because shift right/left needed
		m=MIN(abs(d),m);
		
		if(m!=abs(d)){
		if(m==abs(l)+1){	//ptr->prev所需偏移量最少 
		ptr=ptr->prev;
		printf("<");
		count++;	
		m=l;
		}
		else if(m==abs(r)+1){	//ptr->next所需偏移量最少 
		ptr=ptr->next;
		printf(">");
		count++;
		m=r;	
		}
		}
		else{m=d;}	//ptr所需偏移量最少 
		
		if(m>0){	//plus
			for(i=0;i<m;i++){
			printf("+");
			count++;
		}
//			printf("plus%d\n",m);
		}
		else{		//minus
			for(i=m;i<0;i++){
			printf("-");
			count++;
		}
//			printf("minus%d\n",-m);
		}
		ptr->data +=m;	//shift
		printf(".");	//depart from platform
//		printf("%c",((ptr->data+540)%27+64));
		count++;
		j++;
	}
	
}

int cstshift(int a,int b){	//compute the least shift needed to the destination
	int plus,minus;
	b-=64;	//空白對應到0,A對應到1,etc. 
	a=(a+270)%27;	//platform目前對應到的city 
	if(b-a>=0){
	plus= b-a;
	minus=plus-27;
	}
	else{
	minus= b-a;
	plus= minus+27;
	}
	int shift = (abs(plus)<abs(minus))? plus : minus;
	return shift;
}

int main(void){
	char c;
	int size=0;
	FILE *fp;
	fp = fopen(FILE_INPUT,"r");			// read the file only by pointer
	while(!feof(fp)){
		fscanf(fp, "%c", &c);
		if(c==32){c='@';}				//mark the blank space
		input[size++]=c; 
	}
	input[size-1]='#';	//mark the end of input
	fclose(fp);
	
//	for(i=0;i<=size;i++){
//		printf("%d%c\n",i,input[i]);
//	}
	trolley();
    printf("\ncount:%d\n",count);
    return 0;
}
