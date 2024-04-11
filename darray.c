#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Array {
  int *array;
  int used;
  int size;
  /*size_t used;
  size_t size;*/
} Array;

typedef struct Node {
  bool isReady;
  int pivot;
  int index;
  struct Node *left;
  struct Node *right;
  Array dump;
} Node;

//Arrays

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->size++;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used] = element;
  (a->used)++;
}

void clearArray(Array *a) {
  a->used = 0;
  a->size = 0;
  a->array = realloc(a->array, 0);


}


//Nodes

void addDump(struct Node *n, int element)
{
  insertArray(&(n->dump),element);
}

struct Node* initNode() {
  struct Node* n = (struct Node*)malloc(sizeof(struct Node));
  n -> isReady = false;
  n -> pivot = -1;
  n -> index = 0;
  n -> left = NULL;
  n -> right = NULL;
  initArray(&(n -> dump),0);
  return n;
}

/*
void sortLeft(struct Node *n){

  if ((&(n->dump))->size == 0)
  {
    return;
  }
  n->pivot = (&(n->dump))->array[0];

}

void sortRight(struct Node *n){

}

*/
//high level interaction
//check out . notation

void add(struct Node *n,int element)
{
  if ( n-> pivot == -1)
  {
    n->pivot = element;
  }
  else{
  insertArray(&(n->dump),element);
  }
}

int pop_back(Array *a){
  int element = a->array[a->used];
  a->used--;
  return element;
}

int find(struct Node *pn,int index)
{




  Array *pdump = &(pn -> dump);


  //printf("pn->index: %d", pn->index); // 0
  //printf("index: %d", index);
  if (pn->index == index)
  {  
    return(pn -> pivot);
  }

  if (!(pn->isReady))
  {
    pn -> left = initNode();
    pn -> right = initNode();
    pn-> isReady = true;
  }

  //wrong pivoting
  /*
  if (pdump -> used >= 1)
  {
    pn -> left -> pivot = pop_back(pdump);
    pn -> left -> index = pn -> index - 1;
  }
  if (pdump -> used >= 1)
  {
    pn -> right -> pivot = pop_back(pdump);
    pn -> right -> index = pn -> index + 1;
  }*/

  Array *pleft = &(pn -> left -> dump);
  Array *pright = &(pn -> right -> dump);

  int i;

  //printf("pdump -> used: %d", pdump->used); //0
  //use add instead of insertarray
  for(i = 0; i < (pdump -> used) ; i++ )
  {
    

    if (pdump-> array[i] < pn->pivot)
    {

      add(pn -> left,pdump->array[i]);
      //printf("UP"); //no trigger
      (pn -> index)++;
    }

    else {
      add(pn -> right,pdump->array[i]);
    }
  }

  clearArray(pdump);

  //int a = (pn->index);
  //printf("Index: %d", a); //index is empty or smth = 0


  printf("index: %d", index);
  printf("pn -> index: %d", pn -> index);
  if (pn->index > index)
  {
    pn -> left -> index = pn -> index -1;
    return find(pn -> left,index);
    
  }

  pn -> right -> index = pn -> index + 1;
  return find(pn -> right,index);

  //need to initialise untill find

  }








int main()
{
  setbuf(stdout, NULL);

  struct Node* pn = initNode();
  



  add(pn,3);
  add(pn,5);
  add(pn,7);
  add(pn,2);
  add(pn,19);
  add(pn,15);

  pn -> pivot = pop_back(&(pn -> dump));
  int a = pn -> pivot;

  printf("Found: %d", find(pn,1));
  

  //not found



  return 0;
}
