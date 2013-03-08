// CSS341, Fall 2011, Lecture 11

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct List list_t;
struct List {
  void * head;
  list_t * tail;
};

list_t * makelist (void * x, list_t * xs) {
  list_t * ans = (list_t *)malloc(sizeof(list_t));
  ans->head = x;
  ans->tail = xs;
  return ans;
}

list_t * map(void* (*f)(void*,void*), void* env, list_t * xs) {
  if(xs==NULL)
    return NULL;
  return makelist(f(env,xs->head), map(f,env,xs->tail));
}

list_t * filter(bool (*f)(void*,void*), void* env, list_t * xs) {
  if(xs==NULL)
    return NULL;
  if(f(env,xs->head))
    return makelist(xs->head, filter(f,env,xs->tail));
  return filter(f,env,xs->tail);
}

int length(list_t* xs) {
  int ans = 0;
  while(xs != NULL) {
    ++ans;
    xs = xs->tail;
  }
  return ans;
}

//signed integer type that is big enough to hold a pointer
// awful type casts to match what map expects
void* doubleInt(void* ignore, void* i) {
  return (void*)(((intptr_t)i)*2);
}

// assumes list holds intptr_t fields
list_t * doubleAll(list_t * xs) {
  return map(doubleInt, NULL, xs);
}

// awful type casts to match what filter expects
bool isN(void* n, void* i) {
  return ((intptr_t)n)==((intptr_t)i);
}

// assumes list hold intptr_t fields
int countNs(list_t * xs, intptr_t n) {
  return length(filter(isN, (void*)n, xs));
}

void* dec(void* ignore, void* i) {
  return (void*)(((intptr_t)i)-1);
}

list_t * decAll(list_t * xs) {
    return map(dec, NULL, xs);
}

void main()
{
  //testing link list
/*  list_t* x=NULL;*/
/*  list_t * ans = (list_t *)malloc(sizeof(list_t));*/
/*  ans->head = 1;*/
/*  ans->tail = x;*/
/*  x=ans;
/*printf("%d",x->head);*/

  // creats a list named z
  list_t* y= makelist(9,NULL);
  list_t* z= makelist(10,y);

  int len= length(z);
  printf("\nlength of list : %d\n",len);

  printf("our list    : [%d,",z->head);
  printf(" %d]\n",z->tail->head);

  list_t* l= decAll(z); // mapping dec fucntion to list z
  printf("mapped list : [%d,",l->head);
  printf(" %d]",l->tail->head);
  
  printf("\n");
  return 0;
}
