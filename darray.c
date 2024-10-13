#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//Structures 

typedef struct Array {
  int *array;
  int used;
  int size;
} Array;

typedef struct Node {
  bool isReady;
  int pivot;
  int index;
  struct Node *left;
  struct Node *right;
  struct Node *parent;
  Array dump;
} Node;



bool Real(struct Node *pn)
{
  //printf("index: %d", pn -> index); //here
  if (pn == NULL){
    return false;
  }
  return true;
}

void PrintTree(struct Node *pn)
{
  printf("index: %d ", pn -> index);
  printf("pivot: %d ", pn -> pivot);
  printf("dump: %d ", (&(pn->dump))->used);
  
  printf("\n");

  if (Real(pn->left))
    {
      PrintTree(pn ->left);

    }
  if (Real(pn->right))
    {
      PrintTree(pn->right);
    }
  
  
  
}
void GetTreeTopAndPrintTree(struct Node *pn)
{
  printf("start\n");
  while (pn -> parent != NULL)
    {
      pn = pn-> parent;
    }

  PrintTree(pn);
  

}

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
  n -> parent = NULL;
  initArray(&(n -> dump),0);
  return n;
}


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

void IncrementAllChildrenOf(struct Node *pn)
{
  
  (pn -> index)++; //taking in empty nodes is problem
  if (Real(pn->left))
  {
    IncrementAllChildrenOf(pn ->left);

  }
  if (Real(pn->right))
  {
    IncrementAllChildrenOf(pn->right);
  }
}

void IncrementAllIndexesRightOf(struct Node *pn)
{
  
  if (pn->parent != NULL)
    {
      (pn->parent->index)++;
      if (Real(pn->parent->right))
      {
      IncrementAllChildrenOf(pn->parent->right);
      }
      IncrementAllIndexesRightOf(pn->parent);
      
    }
}

void SplitDumpArrayToLeftAndRight(struct Node *pn, Array *pdump)
{

  int i =0;
  for(i = 0; i < (pdump -> used) ; i++ )
  {


    if (pdump-> array[i] < pn->pivot)
    {

      add(pn -> left,pdump->array[i]);

      (pn -> index)++;
      IncrementAllIndexesRightOf(pn);
    }

    else {
      add(pn -> right,pdump->array[i]);
    }
  }

  pn -> left -> index = pn -> index -1;
  pn -> right -> index = pn -> index + 1;

  clearArray(pdump);
  
}

const int LEFT = -1;
const int FOUND = 0;
const int RIGHT = 1;
const int NOT_FOUND = 2;

int DetermineWhatDirectionTargetIndexisAt(struct Node *pn, int targetIndex)
{
  
  if (pn->index > targetIndex)
    {
      if ((pn -> left) -> pivot == -1)
      {
          return NOT_FOUND;
      }
      else{
      return LEFT;
      }
    }
  
  if (pn ->index == targetIndex){
    return FOUND;
  }

  if ((pn -> right) -> pivot == -1)
  {
    return NOT_FOUND;
  }
  return RIGHT;
  

}

int find(struct Node *pn,int index)
{

  //Initialisations 
  
  Array *pdump = &(pn -> dump);


    pn -> left = initNode();
    pn -> left -> parent = pn;
    pn -> right = initNode();
    pn -> right -> parent = pn;
    pn-> isReady = true;


  Array *pleft = &(pn -> left -> dump);
  Array *pright = &(pn -> right -> dump);

  int i;


  //Logic


  SplitDumpArrayToLeftAndRight(pn,pdump);



  GetTreeTopAndPrintTree(pn);
  int direction = DetermineWhatDirectionTargetIndexisAt(pn,index);

  if (direction == LEFT)
  {
    return find(pn -> left,index);
  }

  if (direction == FOUND)
  {
    return pn -> pivot;
  }

  if (direction == RIGHT)
  {
    return find(pn -> right,index);
  }

  return -1;

}

int main()
{
  setbuf(stdout, NULL);

  struct Node* pn = initNode();




  add(pn,7); //6
  add(pn,1); //0
  add(pn,3); //3
  add(pn,11); //9
  add(pn,13); //11
  add(pn,5); //4
  add(pn,6); //5
  add(pn,8); //7
  add(pn,4); //3
  add(pn,10); //8
  add(pn,2); //1
  add(pn,12); //10


  //pn -> pivot = pop_back(&(pn -> dump));
  //int a = pn -> pivot

  pn -> index = 0;
  pn -> parent = NULL;
  int i;
      printf("Found: %d", find(pn,6));
  



  //not found



  return 0;
}
