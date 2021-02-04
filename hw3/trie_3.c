#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*使用trie tree
  1.轉morse 2.建trie 3.遞迴 
  遞迴:第一個morse開始到第n個morse成字之後, 從n+1開始往下遞迴, 找出n+1之後的總次數後, 會繼續看1~n+1 1~n+2 .... 是否成字 
*/

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

long long trav(DDT*, s[], int); //int會爆掉 
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
		if(j == i - 1){ //不知道為啥最後一個字的最後一個字元會跳過不做, 你可以刪掉試試看或幫我debug 
			strcat(word_morse[j], morse[(int)word[l]-65]);
		}
	}

	DDT *root = malloc(sizeof(DDT));	
	root->dot = NULL;
	root->dash = NULL;
	root->leaf = 0;
	root->times = 0;
	
	DDT *tmp = root;	
	for(k = 0; k < i; k++){ //建樹 
		push(root, word_morse[k]);
	}
		
	long long o = trav(root, seq, -1);
	printf("%lld ", o);

	fclose(fp);	
	return 0;
}

void push(DDT* root, char morse[100000]){ //建trie tree 
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
	root->leaf += 1;  //代表這段morse code"可能代表的字串+1" 
}

// seq[index].times:"這個點後面成字的所有可能性" 
long long trav(DDT* root, s seq[100000], int index){
	if(index == -1){ //避免seq[-1], 但拿掉好像也沒有bug, 後面這些if(index)都可以拿掉跑看看 
		index = 0;
	}
	if(seq[index].times != 0){ //dynamic programming, 不是0代表這個點已經跑過了, 直接回傳 
		return seq[index].times;
	}
	if(index == 0){ //冗 
		index = -1;
	}

	DDT *tmp = root;
	int i;
	for(i = index+1; i < len; i++){ //從某點到index為止有成字, 所以從index+1開始
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
		if(i == len-1 && root->leaf != 0){ //到了輸入的morse的尾端 
			if(index == -1){ //冗 
				index = 0;
			}
			seq[index].times += root->leaf;
			break;
		}
		else if(root->leaf != 0 && i != len-1){ //root->leaf不是0, 代表這段morse成字 
			if(index == -1){ //冗 
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





