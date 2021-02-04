#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define FILE_INPUT "test.txt"
#define MAX_SIZE 10001
int i,j,k,front,rear;
char *start,*end;
bool dead[MAX_SIZE] = {false},visit[MAX_SIZE] = {false};	//dead sets deadend password to true, visit set the visited number to true
int path[MAX_SIZE]={0}; //record the number the node is from
char q[MAX_SIZE][4];

void add(char pop[4],int i){	//adding the digits by one
	int a;
	for(a=i-1;a<=i+1;a++){
		if(a>-1 &&a<4){
		if(pop[a] == '9'){pop[a] = '0';}
    	else{pop[a]++;}
    	}
	}
}

void sub(char pop[4],int i){	//reduce the digits by one
	int a;
	for(a=i-1;a<=i+1;a++){
		if(a>-1 &&a<4){
    	if(pop[a] == '0') {pop[a] = '9';}
    	else{pop[a]--;}
		}
	}
}

void sol(char *st,char *en){
	front=-1,rear=-1;	//front points to the index "before" the first, and rear points to the last element 
    int s = atoi(st);
    int e = atoi(en);
	visit[s]=true;
	path[s]=-1;
	path[e]=-1;
    strncpy(q[++rear],st,4); 		//enqueue the start number
    while(!visit[e]){
    	if(front==rear){break;} 
    	char temp[4],ad[4],su[4];	
    	int a,b,t;
    	strncpy(temp,q[++front],4);	//dequeue
        t= atoi(temp);
        visit[t]=true;
//      printf("dequeue: %d=%.4s,front=%d, rear=%d\n",t,temp,front,rear);
        for(j=0;j<4;j++){
        	strncpy(ad,temp,4);
        	add(ad,j);
        	a= atoi(ad);
        	if(a==e){	//reached the end point
			path[a]=t;
			visit[a]=true;
			break;
			}
        	if((!dead[a])&& (!visit[a])){
			strncpy(q[++rear],ad,4);
			path[a]=t;		//put its previous number in the array
			visit[a]=true;
//			printf("enqueue %d ch%d: %.4s, front=%d, rear=%d, path=%d\n",a,j,ad,front,rear,path[a]);
			}
			
			strncpy(su,temp,4);
			sub(su,j);
        	b= atoi(su);
        	if(b==e){	//reached the end point
			path[b]=t;
			visit[b]=true;
			break;
			}
        	if((!dead[b])&& (!visit[b])){
			strncpy(q[++rear],su,4);
			path[b]=t;
			visit[b]=true;
//			printf("enqueue %d ch%d: %.4s, front=%d, rear=%d, path=%d\n",b,j,su,front,rear,path[b]);
			}
        	
		}
    }
}





int main(void){
	int n;
	char temp[4],start[4],end[4];
	FILE *fp;
	fp = fopen(FILE_INPUT,"r");			// read the file only by pointer
	for(i=0;i<4;i++){fscanf(fp, " %c",&start[i]);}
	for(i=0;i<4;i++){fscanf(fp, " %c",&end[i]);}
	fscanf(fp, "%d",&n);	//number of the forbidden passwords
	for(j=0;j<n;j++){
		for(i=0;i<4;i++){fscanf(fp, " %c",&temp[i]);}
		int dd = atoi(temp);
		dead[dd]=true;			//set to true indocates the password is invalid
	}
	fclose(fp);
	
	//printf("start:%d, end=%d\n ",atoi(start),atoi(end));
	sol(start,end);
	int s = atoi(start);
    int e = atoi(end);
    
    
    if(!visit[e]){printf("Impossible!\n");}
    else{
    	int tmp[MAX_SIZE];
    	k=0;
    	tmp[0]=e;
    	while(path[tmp[k]]>-1){
    		tmp[k+1] = path[tmp[k]];
    		k++;
		}
		printf("steps=%d\n",k);
		k--;
		while(k>=0){
			printf("%d",(tmp[k]/1000));
			printf("%d",(tmp[k]%1000)/100);
			printf("%d", (tmp[k]%100)/10);
			printf("%d",(tmp[k]%10));
			printf("\n");
			k--;
		}
	 
	}
	
	return 0;
} 
