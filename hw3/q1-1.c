#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#define FILE_INPUT "test.txt"
#define MAX_SIZE 50000
#define MAX(a, b) (a > b ? a : b)

int arr[MAX_SIZE];
int i,j,k;
typedef struct seg{
	int left,right,subsum,max;
}Node;
Node segt[4* MAX_SIZE];

void merge(int node){	//calculate the node's info
	segt[node].subsum=segt[2*node].subsum+segt[2*node+1].subsum;
    segt[node].left=MAX(segt[2*node].left, segt[2*node].subsum+segt[2*node+1].left);
    segt[node].right=MAX(segt[2*node+1].right, segt[2*node+1].subsum+segt[2*node].right);
    segt[node].max=MAX(segt[node].left,MAX(segt[node].right,MAX(segt[2*node].max,MAX(segt[2*node+1].max,segt[2*node].right+segt[2*node+1].left))));
}

void build(int node,int l,int r){
    if(l==r){	//set leaf node
        segt[node].subsum=arr[l];
        segt[node].left=arr[l];
        segt[node].right=arr[l];
        segt[node].max=arr[l];
        return;
    }
    build(2*node,l,(l+r)/2);	//set left subtree
    build(2*node+1,(l+r)/2+1,r);	//set right subtree
    merge(node);
}

Node solution(int node,int l,int r,int x,int y){
	if(l>=x && r<=y){return segt[node];}	//range covered within x and y	
	
    if(l>r || l>y || r<x){					//boundary exceeded
        Node t;
        t.subsum=0;
        t.left=-987654321;
        t.right=-987654321;
        t.max=-987654321;
        return t;
    }
    
    int mid =(l+r)/2;
    Node q1=solution(2*node,l,mid,x,y);		//trace down to find the node needed in left subtree
    Node q2=solution(2*node+1,mid+1,r,x,y);	//trace down to find the node needed in right subtree
    Node res;
    res.subsum=q1.subsum+q2.subsum;
    res.left=MAX(q1.left,q1.subsum+q2.left);
    res.right=MAX(q2.right,q2.subsum+q1.right);
    res.max=MAX(res.left,MAX(res.right,MAX(q1.max,MAX(q2.max,q1.right+q2.left))));
    return res;
}
void update(int node, int l, int r, int pos, int val) {
    if (l == r) { //leaf node
    segt[node].subsum=val;
    segt[node].left=val;
    segt[node].right=val;
    segt[node].max=val;
    return;
	}
	else {
        int mid = (l + r) / 2;
        if (pos <= mid){update(node*2, l, mid, pos,val);}	//the target is in left subtree
        else{update(node*2+1, mid+1, r, pos, val);}			//the target is in right subtree
        merge(node);
    }
}

int main(void){
	int task=0,arr_size,query,in1,in2,ans;
	char q;
	FILE *fp;
	fp = fopen(FILE_INPUT,"r");			// read the file only by pointer
	fscanf(fp, "%d", &task); 			//the number of tasks
	for(i=0;i<task;i++){	//for each task
	fscanf(fp, "%d", &arr_size);	//read in array size and the elements
	for(j=1;j<=arr_size;j++){fscanf(fp, "%d", &arr[j]);}	

	build(1,1,arr_size); 		//build tree

	fscanf(fp, "%d", &query);		//the number of queries
	for(k=0;k<query;k++){			//read in instruction and call function 
	fscanf(fp," %c",&q);
	fscanf(fp, " %d",&in1);
	fscanf(fp, " %d",&in2);    
	if(q=='P'){
	Node ans = solution(1,1,arr_size,in1,in2);
  	printf("%d\n",ans.max);
	}
	if(q=='M'){update(1,1,arr_size,in1,in2);}
	}
	}
	fclose(fp);

    return 0;
}
