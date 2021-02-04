#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define FILE_INPUT "test.txt" //define input filename
#define MAX 15001
int nodes[MAX]; 
int i,size,front,rear;

typedef struct BTNode{
    int data;
    struct BTNode *left;
    struct BTNode *right;
}TreeNode;
TreeNode *Q[MAX];

TreeNode *buildtree(void){
	printf("creating binary tree...\n");
	front = rear = 0;
	i=0;
	int n = size-1;
    int ld,rd;
    TreeNode *last, *tree_root, *child;
    
	tree_root = (TreeNode*)malloc(sizeof(TreeNode)); //initialize tree root
    tree_root->data = nodes[i++];
    tree_root->right = tree_root->left = NULL;
    Q[rear++] = tree_root;
    
    while(n){
        last = Q[front++];			//dequeue a node(the last available node)
        ld = nodes[i++];
        rd = nodes[i++];
        
        if(ld == -1){break;}	//the end of nodes
        if(ld>=0){
            child = (TreeNode*)malloc(sizeof(TreeNode));	//create new node for d1 and set it as left child of last node
            child->data = ld;
            child->right = child->left = NULL;
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
            last->right = child;
            Q[rear++] = child;
            n--;
        }
        else{last->right = NULL;}
    }
    
    return tree_root; //return the built tree
}

int minbase(TreeNode *node,int *n){
    int l=0, r=0;
    if(node->left){l = minbase(node->left,n);}	//go to left subtree
    if(node->right){r = minbase(node->right,n);}	//go to right subtree
    if(!node->left && !node->right){return 1;}	//leaf nodes
    if(l+r>0){	//children needs to be protected
        (*n)++;
        node->data++;	//set the node as a base
        return 0;
    }

	if(((node->left && node->left->data == 0) || !node->left) &&((node->right && node->right->data == 0) || !node->right)){return 1;} //one or both child is not a b
    return 0;
}

int main(void) {
	FILE *fp;
	fp = fopen(FILE_INPUT,"r");			// read the file only by pointer
	char c;
	size=0;
	while(!feof(fp)){
		fscanf(fp, "%c", &c);
		if(c==48){			//valid nodes
		nodes[size++]=c-48; 
//		printf("%d\n",nodes[size]); 
		}
		else if(c==110){	//null nodes
		nodes[size++]=-2; 
//		printf("%d\n",nodes[size]); 
		}
	}
	fclose(fp);
	
	nodes[size]=-1;	//mark the end of the nodes
    TreeNode *tree;	//initialize tree root
    int num=0;
    
	if(size>1){	//check whether the tree is not empty
	tree=buildtree();
	int ans = minbase(tree,&num);
	ans += num;
	printf("min base:%d\n",ans);
	}
	else{printf("It's an empty tree.\n");}
	
	system("pause");
	return 0;
}




