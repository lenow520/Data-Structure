#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <math.h>
#define FILE_INPUT "test.txt" //define input filename
#define MAX 15001
int nodes[MAX]; 
int i,j,size,front,rear,cost,pstorder;

typedef struct BTNode{
	int dp[3];
    int data;
    struct BTNode *left;
    struct BTNode *right;
}TreeNode;
TreeNode *Q[MAX];

TreeNode *buildtree(void){
	front = rear = 0;
	i=size;
	int n = size-1;
    int ld,rd;
    TreeNode *last, *tree_root, *child;
    
	tree_root = (TreeNode*)malloc(sizeof(TreeNode)); //initialize tree root
    tree_root->data = nodes[i--];
    tree_root->right = tree_root->left = NULL;
    tree_root->dp[0]=tree_root->dp[1]=tree_root->dp[2]=0;
    Q[rear++] = tree_root;
    
    while(n-1){
        last = Q[front++];			//dequeue a node(the last available node)
        ld = nodes[i--];
        rd = nodes[i--];
        
        if(ld == -1){break;}	//the end of nodes
        if(ld>=0){
            child = (TreeNode*)malloc(sizeof(TreeNode));	//create new node for d1 and set it as left child of last node
            child->data = ld;
            child->right = child->left = NULL;
            child->dp[0] =child->dp[1]=child->dp[2]=0;
            last->left = child;
            Q[rear++] = child;	//enqueue the node for declaring its children later
            n--;
        }
        else{last->left = NULL;}
        
        if(rd == -1){break;} 	//the end of nodes
        if(rd>=0){
            child = (TreeNode*)malloc(sizeof(TreeNode));	//create new node for d2 and set it as right child of last node
            child->data = rd;
            child->right = child->left = NULL;	//enqueue the node for declaring its children later
            child->dp[0] =child->dp[1]=child->dp[2]=0;
            last->right = child;
            Q[rear++] = child;
            n--;
        }
        else{last->right = NULL;}
    }
    
    return tree_root; //return the built tree
}

void minbase(TreeNode *node){
	int c1=0,c2=0;
	if(node->left){minbase(node->left);}	//go to left subtree
    if(node->right){minbase(node->right);}	//go to right subtree
    if(!node->left && !node->right){	//leaf nodes
	node->dp[0]=node->data;
	node->dp[1]=0;
	node->dp[2]=node->data;
	}
	else{	//node has at least one child
	int r0=0,r1=0,r2=0,l0=0,l1=0,l2=0;
	if(node->right){
	r0=node->right->dp[0];
	r1=node->right->dp[1];
	r2=node->right->dp[2];
	}
	if(node->left){
	l0=node->left->dp[0];
	l1=node->left->dp[1];
	l2=node->left->dp[2];
	}

	//compute dp[2]=the min dominent set including node itself
	node->dp[2]=node->data +l1+r1;
	
	//compute dp[0]=the current  min dominent set
	c1=node->dp[2];
	if(node->left&&node->right){c2= ((l2+r0) < (r2+l0))? (l2+r0):(r2+l0);}
	else{	
    if(node->left){	//node only has left child.
    c2=node->left->dp[2];
    }
    if(node->right){	//node only has right child.
    c2=node->right->dp[2];
    }
    }
    node->dp[0] = (c1 < c2)? c1:c2;
	
	//compute dp[1]=the min dominent set not including node itself	
	c1=node->dp[2];	
    if(node->left&&node->right){c2=l0+r0;}
	else{
    if(node->right){	//node only has right child.
    c2=r0;
    }
    if(node->left){	//node only has left child.
    c2=l0;
    }
    }
	node->dp[1] = (c1 < c2)? c1:c2;
	
	}
//	printf("for node%d dp[0]=%d\n",node->data,node->dp[0]);
//	printf("for node%d dp[1]=%d\n",node->data,node->dp[1]);
//	printf("for node%d dp[2]=%d\n",node->data,node->dp[2]);
}

int main(void) {
	FILE *fp;
	fp = fopen(FILE_INPUT,"r");			// read the file only by pointer
	char c;
	int arr[MAX*10];
	int count=0;
	while(!feof(fp)){
		fscanf(fp, "%c", &c);
		if(c>47&&c<58){	//valid node
		arr[count++]=c-48;
//		printf("%d ",arr[i-1]);
		}
		if(c==110){	//null nodes
		arr[count++]=-2;
//		printf("%d ",arr[i-1]);
		}
		if(c==','|| c==']'|| c=='['){arr[count++]=-1;}
	}
	fclose(fp);
//	printf("%d\n",count);
	
	//¤Ï§Ç±½arr«Ø¥ßnodes[] 
	int sum=0,dec=0;
	for(j=count-1;j>=0;j--){
		if(arr[j]>=0){
		sum+=arr[j]*pow(10,dec);
		dec++;
		}
		else if(arr[j]==-2){sum=-2;}
		else{
		nodes[size++]=sum;
		sum=0;
		dec=0;
		}
	}
	nodes[0]=-1;	
	size--;
    TreeNode *tree;	//initialize tree root
    int num=0,cost=0;
	if(size>=1){	//check whether the tree is not empty
	tree=buildtree();
	minbase(tree);
	cost=tree->dp[0];
	printf("cost=%d\n",cost);
	}
	else{printf("It's an empty tree.\n");}

	system("pause");
	return 0;
}




