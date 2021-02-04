# Tree 

[![hackmd-github-sync-badge](https://hackmd.io/sW3fRoHCRbicVnQ80OaonA/badge)](https://hackmd.io/sW3fRoHCRbicVnQ80OaonA)

:::info
* Date: 7/30
* Highlight: basic concept / binary tree
* Reference: [Data structure lectured by Wen-Chih Peng](https://hiskio.com/courses/126)
:::

## k-nary tree
***How to define the nodes***:question:  
**representation 1:**
Each node keeps track of k child  
![](https://i.imgur.com/Tc97j7d.png)  
-Problem: *zero* element takes up **nk-(n-1)=n(k-1)+1** of space
    
   **representation 2: left child right sibling**  
    Each node only has one *leftmost child* and one *closest sibling*.
    ![](https://i.imgur.com/2PdcoMi.png)
    
## binary tree
**sequential representation:** using array  
```
node i has left child whose index is 2i
node i has right child whose index is 2i+1
node i has parent whose index is ⌊i2⌋, with node i is not root node
```  

![](https://i.imgur.com/NEniur1.png)  
-Problem: space-wasting / no insertion and deletion allowed

**node representation:**   
![](https://i.imgur.com/jmwNJxB.png)  
![](https://i.imgur.com/xTNzgqw.png)  
```
typedef struct node *treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
};
```

* binary search tree

The keys in a nonempty left subtree (right subtree) are smaller (larger) than the key in the root of subtree.
The left and right subtrees are also binary search trees.
```
element* Search(treePointer root, int k){ // return the element with key==k
if(!root) return NULL;
if(k == root->data.key) return &(root->data);
if(k < root->data.key) return Search(root->leftChild, k);
return Search(root->rightChild, k);
}
```

:question: ***question: how to search the tree BY RANK***  
To search a binary search tree by the ranks of the elements in the tree, we need additional field “LeftSize”. LeftSize is the number of the elements in the left subtree of a node plus one.(i.e. the LeftSize of a node=the LeftSize of the node's leftChild+1)  
![](https://i.imgur.com/ILiLg5C.png)
```
element Searchbyrank(treePointer t,int k){ 
// Search the binary search tree for the kth smallest element
while(t){
if (k == t->LeftSize) return t;
if (k < t->LeftSize) t = t->leftChild;
else {
k -= t->LeftSize;
t = t->rightChild;
}
}
return 0;
}
```


## Application
### Satisfiablity problem
Given an expression, find out whether there is an assignment to make this expression true?
`e.g. x1 ∨ (x2 ∧ ¬x3)`

**define the node**
If the pointer points to child, the value of LeftThread/RightThread is set to FALSE.
![](https://i.imgur.com/i9KDtlf.png)
data: variable of the expression
value: TRUE/FALSE
```
typedef struct enum {not, and, or, true, false} logical;
typedef struct node *treePointer;
typedef struct node {
    treePointer leftChild, rightChild;
    logical data;
    short int value;
};
```

:bulb: idea
```
for (all 2^n possible truth value combinations){
generate the next combination;   
replace the variables by their values;  
evaluate the formula by traversing the tree it points to in postorder;  
if (root->value){
printf(<combination>);
return;
}
printf("No satisfiable combination\n");  
}
```

**evaluation of expression based on postorder traversal**

```
void PostOrderEval(treePointer s)
{
if (s) {
PostOrderEval(s->leftChild);
PostOrderEval(s->rightChild);
switch (s->data) {
case LogicalNot: s->value =!s->rightChild->value;
break;
case LogicalAnd: s->value = s->leftChild->value && s->rightChild->value;
break;
case LogicalOr: s->value = s->leftChild->value || s->rightChild->value;
break;
case LogicalTrue: s->value = TRUE; break;
case LogicalFalse: s->value = FALSE;
}
}
```

### Huffman code(used in data compression)
`a a a b b c d d d d d d e e e e e f f g g g g g g h h h h i i i`  
**To encode the content above**
* use ASCII Code-> each char takes 8 bits
* use Huffman code: the higher the frequency of a char is, the encoded length tend to be shorter

#### step 1
count the frequencies

| char | frequency | char    |       frequency    |
| ---- | --------- |-------|-----------|
| a    | 3         |     f | 2         |
| b    | 2         |   g   | 6         |
|  c    | 1        |   h   | 4         |
|  d    | 6        |   i   | 3         |
|   e   | 5         |

#### step 2
use the frequency as key to establish the nodes
![](https://i.imgur.com/cYfXxyh.png)

#### step 3
choose 2 nodes with smallest key, and merge them into a subtree, repeating this step until all nodes are merged into a tree  
![](https://i.imgur.com/R5SD9tU.png)  
![](https://i.imgur.com/6rHsFHt.png)  
![](https://i.imgur.com/EpvOfXK.png)

#### step 4
set the leftlink=0, rightlink=1  
![](https://i.imgur.com/jtKtL1K.png)

|char|Huffman code|char|Huffman code|
| ---- | --------- |-------|-----------|
| a    | 0100      |     f | 0001        |
| b    | 00000      |   g   | 11       |
|  c    | 00001     |   h   | 001        |
|  d    | 10    |   i   | 0101   |
|   e   | 011        |

**Evaluation**
| char | frequency | char    |       frequency    |
| ---- | --------- |-------|-----------|
| a    | 3         |     f | 2         |
| b    | 2         |   g   | 6         |
|  c    | 1        |   h   | 4         |
|  d    | 6        |   i   | 3         |
|   e   | 5         |total|32|
* ASCII code requires 8*32=256 bits 
* Huffman code only requires 108 bits :+1: 
