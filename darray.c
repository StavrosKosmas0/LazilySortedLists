#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Array {
  int *array;
  size_t used;
  size_t size;
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
  a->array[a->used++] = element;
}

void clearArray(Array *a) {
  a->used = a->size = 0;
  a->array = realloc(a->array, 0);
 

}


//Nodes

void addDump(struct Node *n, int element)
{
  insertArray(&(n->dump),element);
}

void initNode(struct Node *n) {
  n->left = NULL;
  n->right = NULL;
  initArray(&(n->dump),0);

}


void sortLeft(struct Node *n){

  if ((&(n->dump))->size == 0)
  {
    return;
  }
  n->pivot = (&(n->dump))->array[0];

}

void sortRight(struct Node *n){

}


//high level interaction
//check out . notation
Node create()
{
 Node n;
 initNode(&n);

return n;

}

void add(struct Node *n,int element)
{
insertArray(&(n->dump),element);
}

int find(struct Node *pn,int index)
{


  Array *pdump = &(pn -> dump);
  Array *pleft = &(pn -> left -> dump);
  Array *pright = &(pn -> right -> dump);

  if (pn->index == index){
    return(pn->pivot);
  }
  //initialise the nodes
  if (!(pn->isReady)){
    initNode(pn -> left);
    initNode(pn -> right);
    pn->isReady = true;
  }

  int i;
  for(i = 0; i < (pdump -> used) ; i++ )
  {
    if (pn->pivot > pdump-> array[i])
    {
      insertArray(pleft,pdump -> array[i]);
      pn -> index++;
    }

    else {
      insertArray(pleft,pdump -> array[i]);
      pn -> index--;
    }

  }

  if (pn->index > index)
  {
    return find(pn -> left,index);
  }

  return find(pn -> right,index);

  }








int main()
{
  printf("Found: %d", 1);

  struct Node n = create();
  struct Node* pn = &n;

  printf("Found: %d", 4);

  add(pn,3);
  add(pn,5);
  add(pn,7);
  add(pn,2);
  add(pn,19);
  add(pn,15);
 
  printf("Found: %d", find(pn,3));

	

	return 0;
}
