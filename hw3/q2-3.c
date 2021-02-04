#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#define FILE_INPUT "test.txt"
int i,j,k;
typedef struct Trie
{
    struct Trie *next[2];	//next[0] represents dash, and next[1] represents dot
    bool end;         //mark the end of a word
}T;

T *create(){
    T *root = (T*)malloc(sizeof(T));
	root -> next[0] = NULL;
	root -> next[1] = NULL;
    root -> end = false;
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
		if(i==n-1){tmp->end=true;}
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
	if(tmp->end){return 1;}	//same as word1
	else{return 2;}	//prefix
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
//    printf("%s\n",mc);
}

int main(void){
	int num=0,query,nsize=0,rsize=0;
	T *root,*rr;
    root=create();	//initialize the trie root
    rr=create();
    char *norm[100000],*rev[100000];
	FILE *fp;
	fp = fopen(FILE_INPUT,"r");			// read the file only by pointer
	char str[500];
	fscanf(fp, "%s", str);
	insertTrie(&root, str); /*build the trie*/
	strrev(str);
	insertTrie(&rr, str); /*build the reversed trie*/
	
	fscanf(fp, "%d", &query);
	for(j=0;j<query;j++){
	char qs[600],ms[1000];
	fscanf(fp, "%s", qs);
	encode_out(qs,ms);
	/*search the trie*/
	int ans=compare(root, ms);
	if(ans==1){num++;}
	else if(ans==2){	//prefix
	strcpy(norm[nsize],ms);
	nsize++;
	}
	
	
	ans=compare(rr, strrev(ms));
	if(ans==2){	//postfix
	rev[rsize]=*ms;
	rsize++;
	}
	}
	fclose(fp);
	
	for(i=0;i<nsize;i++){	//find out combinations that constitute the required code
		for(k=0;k<rsize;k++){
		char cat[100000];
		strcpy(cat,norm[i]);
		strcat(cat,rev[k]);
		int a=compare(root, cat);
		if(a==1){num++;}
	}
	}
	
	printf("%d\n",num);
    return 0;
}
