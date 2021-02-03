# Linear Data Structure

:::info
* Date: 7/16 + 7/23
* Highlight: Array/Queue/Stack/Linked List
* Reference: [Data structure lectured by Wen-Chih Peng](https://hiskio.com/courses/126)
:::



## :pushpin: Array
### *Introduction*
![](https://i.imgur.com/wWV7SvV.jpg =70%x)

* **Object:** pairs of <index,value>
* **Operation:** 
    * retrieve value 
    * store value to array
* **Note:** use consecutive memory

```
class ADTofArray {
- objects: A set of pairs <index, value>.

- opeation:
Array Create(j, list) ::
return a j dimensional array;
// the kth dimension is given by the kth element of list
// data type(item) undefined 
:: 

Item Retrieve(A, i)::
if (i is in the index set of array A) return the item associated with i;
else signal an error;
::

void Store(A, i, x)::
if (i is in the index set of array A) 
delete the present <i, y> and insert the new pair <i, x>;
else signal an error;
::
}
```
### *Application*
#### Polynomial
```
class ADTofPolynomial {
- objects: A set of pairs <coeffcient, exponent>.

- opeation:
Polynomial Zero():: 
return the polynomial p(x) = 0; 
:: 

Boolean IsZero(poly)::
if(poly) return TRUE;
else return FALSE;
:: 

Coefficient Coef(poly, e)::
return the coefficient of exponent e in the polynomial;
::

Exponent LeadExp(poly)::
return the largest exponent in the polynomial;
::

Polynomial Attach(poly, coef, e)::
if(e is in poly) signal an error;
else return poly that has inserted <coef, e>;
::

Polynomial Remove(poly, e)::
if(e is in poly) return poly that has deleted <coef, e>;
else signal an error; 
::

Polynomial Add(poly1, poly2)::
return the sum of poly1 and poly2;
::

Polynomial Mult(poly1, poly2)::
return the product of poly1 and poly2;
::

float Eval(poly, float f)::
Evaluate poly at f and return the result
::
}
```
* representation 1 (brute force)
![](https://i.imgur.com/TwH4Run.png =80%x)
```
#define MAX_DEGREE 100
typedef struct{
    int degree; //degree < MAX_DEGREE
    float coef[MAX_DEGREE+1];
    } polynomial;
```

* representation 2
:bulb: idea:  use one global array to store all polynomials 
    * impractical when all items are nonzero since it requires **twice** as much space as *representation 1*
    
![](https://i.imgur.com/Ifvelr2.png =70%x)
```
#define MAX_TERMS 100 //size of the golbal array
typedef struct{
    int expon; 
    float coef;
    } polynomial;
polynomial terms[MAX_TERMS];
int avail=0; //initialize 0 as the first index of free space
```

#### Sparse matrix
:bulb: idea: only keep track of **nonzero elements**
```
class ADTofSparseMatrix {
- objects: A set of triples <row, column, value>.

- opeation:
SparseMatrix(int MaxRow, int MaxCol)::
creates a SparseMatrix that can hold up to MaxInterms = MaxRow x MaxCol and whose maximum row size is MaxRow 
::

SparseMatrix Transpose(matrix)::
returns the SparseMatrix obtained by interchanging the row and column value of every triple in matrix
::

SparseMatrix Add(SparseMatrix a, SparseMatrix b)::
if(the dimensions of a and b are the same) 
return the matrix produced by adding corresponding items;
else signal an error;
::

SparseMatrix Multiply(SparseMatrix b)::
if(number of columns in a (*this) equals number of rows in b) 
return the matrix produced by multiplying a by b;
else signal an error;
::
}
```
:pencil: *on transposing a sparse matrix*
* method 1 (brute force)
**for each row i** take element <i, j, value> and store it in element <j, i, value> of the transpose. 
    * difficulty: where to put <j, i, value> 
     (0, 0, 15) ====> (0, 0, 15) 
     (0, 3, 22) ====> (3, 0, 22) 
     (0, 5, -15) ====> (5, 0, -15)
     (1, 1, 11) ====> **<font color=red>(1, 1, 11)</font>**
     Move elements down very often. 
    
* method 2
:bulb: idea: scan the sparse matrix i times to find the elements on column i 
**for all elements in column j**, place element <i, j, value> in element <j, i, value>.
```
SparseMatrix Transpose(SparseMatrix a){
    SparseMatrix b;
    b.Rows = a.Cols; // rows in b = columns in a 
    b.Cols = a.Rows; // columns in b = rows in a 
    b.Terms = a.Terms; // terms in b = terms in a 

    if (a.Terms > 0) // nonzero matrix   
    { 
    int CurrentB = 0; 
    for (int i= 0; i < Cols; i++) // transpose by columns
        for (int j = 0; j< Terms; j++)
        if (smArray[j].col == i) { // find elements in column i
        b.smArray[CurrentB].row = i; 
        b.smArray[CurrentB].col = smArray[j].row;           
        b.smArray[CurrentB].value = smArray[j].value; 
        CurrentB++;  
    }
    
    return b; 
}
```
Time Complexity = **<font color=red>O(terms*cols)</font>**

* method 3 (Fast transpose)
:bulb: idea: use array **RowSize[i]** to keep track of the number of element in the ith column of original matrix a. **RowStart[j]** refers to the starting position of jth row in the new matrix b.
```
SparseMatrix FastTranspose(SparseMatrix a){
    int RowSize = new int[Cols]; // RowSize[i] = number of terms in row i of b
    int RowStart = new int[Cols]; // RowStart[i] = starting position of row i in b
    SparseMatrix b;
    b.Rows = a.Cols; // rows in b = columns in a 
    b.Cols = a.Rows; // columns in b = rows in a 
    b.Terms = a.Terms; // terms in b = terms in a
    int i;
    
    if (Terms > 0) // nonzero matrix
    {
    RowStart[0] = 0;
    for (i = 0; i < Cols; i++) RowSize[i] = 0; // Initialize
    for (i = 0; i < Terms; i++) RowSize[smArray[i].col]++;
    for (i = 1; i < Cols; i++) RowStart[i] = RowStart[i-1] + RowSize[i-1];
    for (i =0; i < Terms; i++) // move from to b 
    {
    int j = RowStart[smArray[i].col];
    b.smArray[j].row = smArray[i].col;
    b.smArray[j].col = smArray[i].row;
    b.smArray[j].value = smArray[i].value;
    RowStart[smArray[i].col]++;}
    }
    
    delete [] RowSize;
    delete [] RowStart;
    return b;
}
```
Time Complexity = O(terms)= **O(row * column)** :+1: 

---
## :pushpin: Stack & Queue
### *Introduction*
### Stack
* a Last-In-First-Out (LIFO) list
![](https://i.imgur.com/7NdCXyk.png)

```
class ADTofStack {
-objects: A finite ordered list with zero or more elements.

-operations: 
Stack (int MaxStackSize)::
//Creates an empty stack whose maximum size is MaxStackSize.
::

Boolean IsFull(stack)::
If(number of elements in stack equals to the maximum size of the stack)
return TRUE;
else return FALSE;
::

void Push(stack,item)::
if (IsFull(stack)) then StackFull(); 
else return insert the item on top of the stack;
::

Boolean IsEmpty(stack)::
if(number of elements in the stack== 0)
return TRUE;
else return FALSE;
::

Element Pop(stack)::
if (IsEmpty(stack))StackEmpty() and return 0; 
else remove and return a pointer to the top element of the stack;
::
}
```

### Queue
* a First-In-First-Out (FIFO) list
![](https://i.imgur.com/CCg7UXz.png =70%x)

```
class ADTofQueue {
-objects: A finite ordered list with zero or more elements.

-operations:
Queue(int MaxQueueSize = DefaultSize)::
// Creates an empty queue whose maximum size is MaxQueueSize
::

Boolean IsFull(queue)::
If(number of elements in queue equals to the maximum size of the queue)
return TRUE;
else return FALSE;
::

void Add(queue,item)::
if (IsFull(queue)) then QueueFull(); 
else insert item at rear of the queue;
::

Boolean IsEmpty(queue)::
if(number of elements in the queue== 0)
return TRUE;
else return FALSE;
::

Element Delete(queue)::
if (IsEmpty(queue)) QueueEmpty() and return 0; 
else remove the item at the front queue and return a pointer to it;
::
```
* implementation
    * using **array**
        * problem: there may be available space when QueueFull is true.  i.e, <font color=red>data movements are required.</font>
    ```
    Add(element item){ // add an item to queue
    if (IsFull(queue)) QueueFull( ); 
    else queue[++rear]=x; 
    }
    
    Delete(queue) { // return the top element at the front of queue
    if (IsEmpty()) { // returns and error key 
    QueueEmpty( ); 
    return 0; 
    } 
    x=queue[++front]; 
    return x; 
    }
    ```

    * regard an array as a **circular queue**   
        * problem: one space is left when queue is full

    front: one position counterclockwise from the first element
    rear: current end
 ![](https://i.imgur.com/S4A8Le0.png =70%x)
![](https://i.imgur.com/fXJpYB7.png =65%x)
```
    Add(element item){ // add an item to queue
    int newrear=(rear+1)%MaxSize; 
    if (front==newrear) QueueFull( ); 
    else queue[rear=newrear]= item; 
    }
    
    Delete(queue) { // return the top element at the front of queue
    if (front == rear) { 
    QueueEmpty(); 
    return 0; } 
    front = (front+1) % MaxSize; 
    return queue[front];  
    }
 ```

### *Application*
#### Mazing Problem


#### Infix/Postfix conversion

---
## :pushpin: Linked List
### *Introduction*
![](https://i.imgur.com/aEhpTa8.png)

Each node is composed of data & link (i.e. pointer to the next node), so we can use struct to declare nodes in C.
* create a linked list
![](https://i.imgur.com/ycgZxn4.png)

```
typedef struct listNode *listPointer
typedef struct listNode {
  int data;
  listPointer link;
  }
  
listPointer create2(){
    listPointer first, second;
    MALLOC (first, sizeof(*first));
    MALLOC (second, sizeof(*second));
    second→link = NULL;
    second→data = 20;
    first→link = second;
    first→data = 10;
    return first;
}

```

* insert a node
![](https://i.imgur.com/dJm9nrv.png)
```
void insert(listPointer * first, listPointer x){
	listPointer t;
	MALLOC (t, sizeof(*t));
	t→data = 50;
	
    if (*first) { // list not empty
    t→link=x→link; 
    x→link=t;
    } 

    else{ // when list is empty, let t be the first node
	t→link=NULL;
	*first=t; 
    }
}

```

* delete a node
![](https://i.imgur.com/jJ0P44f.png)

```
void delete(listPointer * first, listPointer trail, listPointer x){
	// trail points to the node before x
    if (trail) { trail→link=x→link; } 
    else{*first=*first→link; }
    free(x);
}

```
### *Application*
#### 
