#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include<stdbool.h>
#include<string.h>
#define MAX 15 
#define MAX_height 7 
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}}; //右下左上 
int i, j, n,k,count,base_size,map_num;
char newm[MAX_height][MAX][MAX];
bool found =false;
void readmap(int);
void pyramid();
void print(int);

struct position
{
int floor;				//the base floor is 0
int x;
int y;
int d;					//d is the direction it's going to.
}sf[2],visit[800],sp[800];	//stack sp[] keeps track of the nodes in shortest path, visit[] saves locations it has gone to. 	

int main(void){
	for(k=1;k<101;k++){
	printf("running data#%d....\n",k);
	count=0;
	base_size=0;
	map_num=0;
	found=false;	
	
	readmap(k);
	print(k);
	pyramid();
	if(count){			//set the elements in shortest path to'*'
	printf("data#%d, shortest path found!\n",k);
	found=true;
	print(k);
	}
	else{printf("data#%d, no path exists.\n",k);}
	}
	system("pause");
	return 0;
}
void readmap(int i){
	char in[50];
	sprintf(in,"test%d.txt", i );
	char c;
	FILE *fp;
	fp = fopen(in,"r");			// read the file only by pointer
	if(fp == NULL) {printf("Error in opening file\n");}
	while(!feof(fp)){
	fscanf(fp, "%c", &c);
	base_size++;						//find out the base size
	if(c=='\n'){goto here;}
	}
	here:
	base_size =(base_size-1)/2;
	rewind(fp);							//reset file pointer
	
	map_num= (base_size+1)/2; //the number of floors in this pyramid
	
	for(n=0;n<map_num;n++){					//initialize the map 
		for(i = 0; i <MAX; i++){
			for(j = 0; j <MAX; j++){
			newm[n][i][j] ='X'; 
			}
		}
	}
	
	for(n=1;n<=map_num;n++){
		for(i = n; i <(base_size-n+2); i++){
		for(j = n; j <(base_size-n+2); j++){
			fscanf(fp, " %c", &c);				// read the characters one by one 
			newm[n-1][i][j] = c;
//			printf("%c ",c);
			if(c=='S'){
			sf[0].floor=n-1; sf[0].x=i; sf[0].y=j;}		//紀錄起始點(S)座標 
			if(c=='F'){
			sf[1].floor=n-1; sf[1].x=i; sf[1].y=j;}		//紀錄終點(F)座標
		}
//			printf("\n");
		}	
//		printf("\n");
	}
	
	fclose(fp);								// close the file pointer
}

void pyramid(){
	int top=0;
	char ch;
	int x,y,fl,d = -1;
	bool v=false;	//set to true if the position is visitable
	int min=99999;

	visit[top].x=sf[0].x;
	visit[top].y=sf[0].y;
	visit[top].floor=sf[0].floor;
	newm[sf[0].floor][sf[0].x][sf[0].y] = '$';	//mark the visited position

	while(top>-1){
	if(visit[top].floor==sf[1].floor && visit[top].x==sf[1].x && visit[top].y==sf[1].y) {
	if(min > top){
	min = top;
	for(count=0;count<=top;count++){
	sp[count].d=visit[count].d;
	sp[count].x=visit[count].x;
	sp[count].y=visit[count].y;
	sp[count].floor=visit[count].floor;
	}
	}
	}

	while(d <4 && !v){
	d++;
	switch(d){
	case 0:
	x = visit[top].x + dir[d][0];
	y = visit[top].y + dir[d][1];
	fl = visit[top].floor;
	ch=newm[fl][x][y];
	break;
	case 1:
	x = visit[top].x + dir[d][0];
	y = visit[top].y + dir[d][1];
	fl = visit[top].floor;
	ch=newm[fl][x][y];
	break;
	case 2:
	x = visit[top].x + dir[d][0];
	y = visit[top].y + dir[d][1];
	fl = visit[top].floor;
	ch=newm[fl][x][y];
	break;
	case 3:
	x = visit[top].x + dir[d][0];
	y = visit[top].y + dir[d][1];
	fl = visit[top].floor;
	ch=newm[fl][x][y];
	}
	if(ch =='U' ||ch =='D' || ch == 'O' ||ch == 'T'){v=true;}
	}
	
	
	
	if(v){ 		//push the current location to stack
	visit[top].d = d;
	top++;
	visit[top].floor = fl;
	visit[top].x = x;
	visit[top].y = y;
//	printf("push %d, %d, %d\n",fl,x,y);
	if(ch=='T'){
		for(i=0;i<2;i++){
			top++;
			visit[top].floor = fl;
			visit[top].x = x;
			visit[top].y = y;
		}
	}
	if(ch=='U'&&fl!=map_num&&newm[fl+1][x][y]!='$'&&newm[fl+1][x][y]!='X'){
			visit[top].d=4;
			top++;
			fl++;
			visit[top].floor = fl;
			visit[top].x = x;
			visit[top].y = y;
	}
	if(ch=='D'&&fl!=0&&newm[fl-1][x][y]!='$'&&newm[fl-1][x][y]!='X'){
			visit[top].d=5;
			top++;
			fl--;
			visit[top].floor = fl;
			visit[top].x = x;
			visit[top].y = y;
	}
	newm[fl][x][y] = '$';
	d = -1;
	v=false;
	}
	
	else{ 			//pop stack
//	printf("pop %d, %d, %d ,",visit[top].floor,visit[top].x,visit[top].y);
	if(visit[top].floor==visit[top-1].floor && visit[top].x==visit[top-1].x && visit[top].y==visit[top-1].y){
	newm[visit[top].floor][visit[top].x][visit[top].y] = 'T';
//	printf("and it's %c\n",'T');
	top=top-3;
	}
	else{
	if(visit[top-1].d==4){newm[visit[top].floor][visit[top].x][visit[top].y] = 'U';}
	else if(visit[top-1].d==5){newm[visit[top].floor][visit[top].x][visit[top].y] = 'D';}
	else{newm[visit[top].floor][visit[top].x][visit[top].y] = 'O';}
//	printf("and it's %c\n",newm[visit[top].floor][visit[top].x][visit[top].y]);
	top--;
	}
	d = visit[top].d;
	}
	}
	
	if(0 != count){			//set the elements in shortest path to'*'
	for(i=0;i<count;i++){
	newm[sp[i].floor][sp[i].x][sp[i].y] = '*';
	}
	}
	
}


void print(int i){
	char out[50];
	sprintf(out,"test%d_ans.txt", i );	
	FILE *fptr;
	if(found){
	fptr = fopen(out, "a");
	fprintf(fptr,"path length:%d\n======outMaze=====\n",count-1);	
	}
	else{fptr = fopen(out, "w");}
	
	for(n=1;n<=map_num;n++){
		for(i = n; i <(base_size-n+2); i++){
		for(j = n; j <(base_size-n+2); j++){
			fprintf(fptr,"%c ", newm[n-1][i][j]);		
		}
		fprintf(fptr,"\n");
		}
	fprintf(fptr,"\n");	
	}
	
	fclose(fptr);
	
}
