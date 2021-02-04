#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 22
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}}; //右下左上 
int i, j, n,next_i, next_j;
int sf[2][2];
char newm [MAX][MAX];
int mark[MAX][MAX];
bool found =false;
void find(int ,int,char[MAX][MAX],int[MAX][MAX]);

int main(void) {
	printf("Original maze:\n");
	FILE *fp;
	fp = fopen("test.txt","r");			// read the file only by pointer
	fscanf(fp, "%d", &n);				// the size of maze
	char c;	
	char ori[n][n];
	for(i = 0; i <n; i++){
		for(j = 0; j <n; j++){
			fscanf(fp, " %c", &c);			// read the characters one by one 
			ori[i][j] = c;
			printf("%c ", ori[i][j]);		//Show original map
			if(c=='S'){sf[0][0]=i+1; sf[0][1]=j+1;}		//紀錄起始點(S)座標 
			if(c=='F'){sf[1][0]=i+1; sf[1][1]=j+1;}		//紀錄終點(F)座標
		}
		printf("\n");
	}
	fclose(fp);								// close the file pointer
	

	for(i = 0; i <MAX; i++){				// initialize map and mark(set path to 1)
		for(j = 0; j <MAX; j++){
			mark[i][j]=0;
			if(i==0 || i> n||j==0 || j>n){newm[i][j]='X';}
			else{newm[i][j]=ori[i-1][j-1];}
			//printf("%c ",newm[i][j]);
		}	
		//printf("\n");
	}
	
	find(sf[0][0],sf[0][1],newm,mark);
	
	if(found){
		printf("Show path:\n");
		for(i = 1; i <n+1; i++){
		for(j = 1; j <n+1; j++){
		 printf("%c ",newm[i][j]);
		}
		printf("\n");
		}	
	}
	else{printf("No path existed.\n");}
	
	system("pause");
	return 0;
}

void find(int i ,int j,char map[MAX][MAX],int mk[MAX][MAX]){
	int k;
	//printf("visit %d,%d\n",i-1,j-1);
	map[i][j]='*';
	mk[i][j]=1;
	if (i == sf[1][0] && j == sf[1][1]){found=true;}
	
	for(k=0;k<4;k++){
		//printf("k= %d\n",k);
		next_i = i + dir[k][0];
		next_j = j + dir[k][1];
		if ((map[next_i][next_j]<88) && !mk[next_i][next_j] && !found){
		//printf("go to direction %d\n",k);
		find(next_i, next_j,map,mk);}
		//else{printf("direction %d is a dead end\n",k);}
	}
	if(!found){
	map[i][j] = 'O'; 
	mk[i][j]=0;
	//printf("return from %d,%d\n",i-1,j-1);
	}
	
}


