#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#define FILE_INPUT "test.txt"
int i,j,k;
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

void insertTrie(T ** troot,char *word){
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

int compare(T *troot, char *q){
	T *tmp = troot;
	int i=0, k;
	int n = strlen(q);
	while(q[i]){
		k = q[i] - '-';
		if (tmp->next[k]){tmp = tmp->next[k];}
		else{return 3;}	//doesn't have the same prefix
		i++;
	}
	if(tmp->isword){return 1;}	//same as word1
	else{return 2;}
}

char *input[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",
".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-",
"...-",".--","-..-","-.--","--.."};

void encode_out(char *plt,char *mc){		//encode into morse code
	char ch;
	int a;
	int n=strlen(plt);
//	printf("%s\n",plt);
    for(i=0;i<n;i++){
        ch = plt[i];	//ch represents an alphabet of the plaintext string
        a = (ch-65);	//the corresponding number of morse code
        if(ch == '\0'){break;}
        if(i==0){strcpy(mc, input[a]);}
		else{strcat(mc, input[a]);}
    }
    printf("%s\n",mc);
}

int main(void){
	int num,query;
	T *root;
    root=create();	//initialize the trie root
    
	FILE *fp;
	fp = fopen(FILE_INPUT,"r");			// read the file only by pointer
	char str[500];
	fscanf(fp, "%s", str);
//	printf("%s\n",str);
	char morse[1000];
	encode_out(str,morse);
	insertTrie(&root, morse); /*build the trie*/
	
	fscanf(fp, "%d", &query);
	for(j=0;j<query;j++){
	char qs[600],ms[1000];
	fscanf(fp, "%s", qs);
	encode_out(qs,ms);
	/*search the trie*/
	printf("%s ",qs);
	int ans=compare(root, ms);
	if(ans==1){printf("is the same as %s.\n",str);}
	else if(ans==2){printf("has the same prefix as %s.\n",str);}
	else{printf("doesn¡¦t have the same prefix as %s.\n",str);}
	}

	
	fclose(fp);

    printf("\n");
    return 0;
}
