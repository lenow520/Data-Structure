#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#define FILE_INPUT "test.txt"
#define MAX_SIZE 10
#define MAX_STRING 2
int i,j,k;
typedef struct Name{
	char c1,c2;
}name;
name V[MAX_SIZE];
name E[MAX_SIZE][MAX_SIZE];
int ind[MAX_SIZE]={0};	
int vex_num,eq;
bool cycle;

int find(char ch[2],int n){ //return the index of a specific variable
	int i;
	for (i = 0; i <n; i++) {if (V[i].c1 == ch[0] && V[i].c2 == ch[1]) {return i;}}
	return -1;
}

void init(int n){
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {E[i][j].c1 = '/'; E[i][j].c2 = '/';}	//self
			else{E[i][j].c1 = '*'; E[i][j].c2 = '*';}	//initialization
		}
	}
}

bool self_ref(int n){
	for (i = 0; i < n; i++) {
		 if(E[i][i].c1 != '/' || E[i][i].c2 != '/') {return true;}
	}
	return false;
}

void dfs(int start,int n,int flag){
		if(!cycle){
		for (j = 0; j < n; j++) {	//scan the out-degrees
		if(j!=start &&(E[start][j].c1 !='*') && (E[start][j].c2 !='*')){	//if exists an edge
			if(j==flag){
			cycle=true;
			break;
			}
			else {
			dfs(j,n,flag);}
		}
		}
	}
}

		
int main(void){
	vex_num=eq=0;
	char c;
	FILE *fp;
	fp = fopen(FILE_INPUT,"r");			// read the file only by pointer
	fscanf(fp, "%d",&vex_num);
	init(vex_num);
	char n[2];
	for(i=0;i<vex_num;i++){
		fscanf(fp, "%s",&n);
		V[i].c1=n[0];
		V[i].c2=n[1];
	}
	fscanf(fp, "%d",&eq);	//number of equations 
	char str[2],s[2],d[2];
	int dest,src;
	for(i=0;i<eq;i++){
		fscanf(fp, "%s",&d);	//name of the dest
		dest = find(d,vex_num);
		fscanf(fp, "%s",&str); //pass the '='
		fscanf(fp, "%s",&str); //name of the reference
		fscanf(fp, "%s",&s); //pass the '('
		fscanf(fp, "%s",&s); //name of the src
		src = find(s,vex_num);
		E[src][dest].c1=str[0];
		E[src][dest].c2=str[1];
		ind[dest]++; 
		fscanf(fp, "%s",&s); //name of the src
		if(s[0]!=')' && s[1]!=')'){
		src = find(s,vex_num);
		E[src][dest].c1=str[0];
		E[src][dest].c2=str[1];
		ind[dest]++;
		fscanf(fp, "%s",&s); //pass the ')'
		}
	}
	
	fclose(fp);

	
	if(self_ref(vex_num)){printf("No solution(self reference).\n");}
	else{
		cycle=false;
		for(i=0;i<vex_num;i++){
		int flag=i;
		if(cycle){
		printf("No solution(circular reference).\n");
		break;
		}
		dfs(i,vex_num,flag);
		}
		
		if(!cycle){	 //has solution
			for(i=0;i<vex_num;i++){
			if(ind[i]==0){printf("%c%c -> %c%c\n",V[i].c1,V[i].c2,V[i].c1,V[i].c2);}
			if(ind[i]==1){
			int ref[2],s,d;
			for(k=0;k<vex_num;k++){
				if(k!=i &&(E[k][i].c1 !='*') && (E[k][i].c2 !='*')){
					ref[0]=E[k][i].c1;
					ref[1]=E[k][i].c2;
					s=k; d=i;
					break;
				}
			}
			printf("%c%c -> %c%c ( %c%c )\n",V[d].c1,V[d].c2,ref[0],ref[1],V[s].c1,V[s].c2);
			}

			}
			
		}
	}
	
	return 0;
} 
