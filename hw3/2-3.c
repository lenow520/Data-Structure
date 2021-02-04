#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *morse[26] = {".-","-...","-.-.","-..",".","..-.","--.",
					"....","..",".---","-.-",".-..","--","-.",
					"---",".--.","--.-",".-.","...","-","..-",
					"...-",".--","-..-","-.--","--.."};

typedef struct DDT DDT; //(dash-dot tree)
struct DDT{
	char m; 
	long long leaf;
	long long times;
	struct DDT *dash; 
	struct DDT *dot; 
};

typedef struct s s;
struct s{
	char m;
	long long times;
};

long long trav(DDT*, s[], int); //cannot use int 
void push(DDT*, char[]);
DDT* newNode(char, DDT*);

int len;
char word_morse[100000][80]; //建在heap, 若在stack會爆掉 

int main(int argc, char *argv[]) {
	
	char dict_num[6];
	char word[20];
	s seq[100000];
	int j, k, l; 
	
	FILE *fp = fopen("test4.txt", "r"); 
	for(k = 0; k < 100000; k++){
		seq[k].m = fgetc(fp);
		seq[k].times = 0;
		if(seq[k].m == '\n'){
			len = k;
			break;
		}
	}
	
	fgets(dict_num, 6, fp);
	int i = atoi(dict_num);
	
	for(j = 0; j < i; j++){
		fgets(word, 20, fp);
		memset(word_morse[j], '\0', sizeof(word_morse[j]));
		for(l = 0; l < strlen(word)-1; l++){
			strcat(word_morse[j], morse[(int)word[l]-65]);
		}
		if(j == i - 1){ 
			strcat(word_morse[j], morse[(int)word[l]-65]);
		}
	}

	DDT *root = malloc(sizeof(DDT));	
	root->dot = NULL;
	root->dash = NULL;
	root->leaf = 0;
	root->times = 0;
	
	DDT *tmp = root;	
	for(k = 0; k < i; k++){ 
		push(root, word_morse[k]);
	}
		
	long long o = trav(root, seq, -1);
	printf("%lld ", o);

	fclose(fp);	
	return 0;
}

void push(DDT* root, char morse[100000]){ //construct trie tree 
	int i;
	for(i = 0; i < 100000; i++){
		if(morse[i] == '.'){
			if(root->dot == NULL){
				root = newNode('.', root);				
			}
			else{
				root = root->dot;
			}
		}
		else if(morse[i] == '-'){
			if(root->dash == NULL){
				root = newNode('-', root);
			}
			else{
				root = root->dash;
			}
		}
		else{
			break;
		}
	}
	root->leaf += 1; 
}

long long trav(DDT* root, s seq[100000], int index){
	if(index == -1){ 
		index = 0;
	}
	if(seq[index].times != 0){ //dynamic programming
		return seq[index].times;
	}
	if(index == 0){ 
		index = -1;
	}

	DDT *tmp = root;
	int i;
	for(i = index+1; i < len; i++){ //exists word
		//printf("%d ",i);
		if(seq[i].m == '.'){
			if(root->dot == NULL){
				break;			
			}
			else{
				root = root->dot;
			}
		}
		else if(seq[i].m == '-'){
			if(root->dash == NULL){
				break;
			}
			else{
				root = root->dash;
			}
		}
		if(i == len-1 && root->leaf != 0){ //the end of the morse code 
			if(index == -1){ 
				index = 0;
			}
			seq[index].times += root->leaf;
			break;
		}
		else if(root->leaf != 0 && i != len-1){ //exists a word if root->leaf !=0
			if(index == -1){  
				index = 0;
			}
			seq[index].times += root->leaf*trav(tmp, seq, i);
		}
	}
	if(index == -1){ //冗 
		index = 0;
	}
	return seq[index].times;
}

DDT* newNode(char m, DDT *root) {
	DDT* node = malloc(sizeof(DDT));
	node->m = m;
	node->dash = NULL;
	node->dot = NULL;
	node->leaf = 0;
	node->times = 0;
	if(m == '.'){
		root->dot = node;
	}
	else if(m == '-'){
		root->dash = node;
	}
	return node;
}





