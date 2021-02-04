#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 22
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}}; //右下左上 
int i, j, n,sf[2][2],count=0;
char newm [MAX][MAX];

struct position
{
int x;
int y;
int d;					//d is the direction it's going to.
}visit[400],sp[400];	//stack sp[] keeps track of the nodes in shortest path, visit[] saves locations it has gone to. 		

void bfs();

int main(void) {
	printf("Original maze:\n");
	FILE *fp;
	fp = fopen("test.txt","r");			// read the file only by pointer
	fscanf(fp, "%d", &n);				// the size of maze
	char c;
	char ori[n][n];
	for(i = 0; i <n; i++)
	{
		for(j = 0; j <n; j++)
		{
			fscanf(fp, " %c", &c);			// read the characters one by one 
			ori[i][j] = c;
			printf("%c ", ori[i][j]);		//show original map
			if(c=='S'){sf[0][0]=i+1; sf[0][1]=j+1;}		//紀錄起始點(S)座標 
			if(c=='F'){sf[1][0]=i+1; sf[1][1]=j+1;}		//紀錄終點(F)座標
		}
		printf("\n");
	}
	fclose(fp);								// close the file pointer
	
	for(i = 0; i <MAX; i++){				// initialize map
		for(j = 0; j <MAX; j++){
			if(i==0 || i> n||j==0 || j>n || (ori[i-1][j-1]=='X')){ newm[i][j]= 'X'; }
			else{newm[i][j]= 'O';}
			//printf("%d ",newm[i][j]);
		}	
		//printf("\n");
	}
	
	bfs();
	
	if(0 != count){			//set the elements in shortest path to'*'
	for(i=0;i<count;i++){
	newm[sp[i].x][sp[i].y] = '*';
	}
	printf("Show path:\n");
	for(i=1;i<n+1;i++){
		for(j=1;j<n+1;j++){printf("%c ",newm[i][j]);}
		printf("\n");
		}
	printf("Shortest path length:%d\n",count-1);
	}
	else{printf("No path existed.\n");}

	system("pause");
	return 0;
}

void bfs(){
	int top=0;
	int x,y,d = -1;
	bool v=false;	//set to true if the position is visitable
	int min=9999;

	visit[top].x=sf[0][0];
	visit[top].y=sf[0][1];
	newm[sf[0][0]][sf[0][1]] = '$';	//mark the visited position

	while(top>-1){
	if(visit[top].x==sf[1][0] && visit[top].y==sf[1][1]) {
	if(min > top){
	min = top;
	for(count=0;count<=top;count++){
	sp[count].d=visit[count].d;
	sp[count].x=visit[count].x;
	sp[count].y=visit[count].y;
	}
	}
	}

	while(d < 4 && !v){
	d++;
	switch(d){
	case 0:
	x = visit[top].x + dir[d][0];
	y = visit[top].y + dir[d][1];
	break;
	case 1:
	x = visit[top].x + dir[d][0];
	y = visit[top].y + dir[d][1];
	break;
	case 2:
	x = visit[top].x + dir[d][0];
	y = visit[top].y + dir[d][1];
	break;
	case 3:
	x = visit[top].x + dir[d][0];
	y = visit[top].y + dir[d][1];
	}
	if(newm[x][y] == 'O'){v=true;} //if the direction is visitable, then leave the loop
	}
	
	if(v){ 		//push the current location to stack 
	visit[top].d = d;
	top++;
	visit[top].x = x;
	visit[top].y = y;
	newm[x][y] = '$';
	d = -1;
	v=false;		 
	}
	else{ 			//pop stack
	newm[visit[top].x][visit[top].y] = 'O';
	top--;
	d = visit[top].d;
	}
	}
	
}
