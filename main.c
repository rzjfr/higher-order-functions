// CSS341, Fall 2011, Lecture 11

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// (We did not actually go through this file in any detail -- it is provided
//  for C programmers curious how to program with higher-order functions
//  in C.)
// (This file has not been tested.)

// The key point is that function pointers are only code pointers

// Rather than create structs for closures, which would work fine,
// we follow common C practice of having higher-order functions 
// take explicit environment fields as another argument
//  -- if they don't, then they are much less useful 

// void* requires lots of unchecked conversions between types,
// but C has no notion of type variables

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

// as in the Java version, we show simple recursive solutions because
// the loop-based ones require mutation and previous pointers.
// But the more important point is the explicit env field passed to the
// function pointer
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
