#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#define FILE_INPUT "test.txt"
int i,j,k,ac;
typedef struct Trie
{
    struct Trie *next[2];	//next[0] represents dash, and next[1] represents dot
    bool isword;         //mark the end of a word
}T;

T *create(){
    T *root = (T*)malloc(sizeof(T));
	root -> next[0] = NULL;
	root -> next[1] = NULL;
    root -> isword = false;
    return root;
}

void insertTrie(T ** troot, char *word){
	T *tmp = *troot;
	int i, k;
	int n = strlen(word);
//	printf("%d,%s\n",n,word);
	for(i=0;i<n;i++){
		k = word[i] - '-'; 
		if (!tmp->next[k]){tmp->next[k] = create();}
		tmp = tmp->next[k];
		if(i==n-1){tmp->isword=true;}
	}
 
}

bool searchTrie(T *troot, char *q){
	T *tmp = troot;
	int i, k;
	int n = strlen(q);
//	printf("%d,%s\n",n,q);
	for(i=0;i<n;i++){
		k = q[i] - '-';
		if (tmp->next[k]){tmp = tmp->next[k];}
		else{return false;}
	}
	return tmp->isword; 
}


char *input[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",
".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-",
"...-",".--","-..-","-.--","--.."};

char *encode_out(char *plt, char *mc){
	char ch;
	int a;
	int n=strlen(plt);
    for(i=0;i<n;i++){
        ch = plt[i];	//ch represents an alphabet of the plaintext string
        a = (ch-65);	//the corresponding number of morse code
        if(ch == '\0'){break;}
        if(i==0){strcpy(mc, input[a]);}
		else{strcat(mc, input[a]);}
    }
//    printf("%s\n",mc);
    return mc;
}

int main(void){
	int num,query;
	T *p,*root;
    root=create();	//initialize the trie root
    
	FILE *fp;
	fp = fopen(FILE_INPUT,"r");			// read the file only by pointer
	fscanf(fp, "%d", &num);
	for(j=0;j<num;j++){
	char str[100];
	fscanf(fp, "%s", str);
	char *morse=encode_out(str ,morse);
	/*build the trie*/
	insertTrie(&root, morse);
	}
	
	fscanf(fp, "%d", &query);
	for(j=0;j<query;j++){
	char qs[1000];
	fscanf(fp, "%s", qs);
	/*search the trie*/
	printf("%s ",qs);
	if(searchTrie(root, qs)){printf("is found in dictionary.\n");}
	else{printf("is not found in dictionary.\n");}
	}

	
	fclose(fp);

    printf("\n");
    return 0;
}
