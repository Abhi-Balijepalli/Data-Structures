/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Abhi Balijepalli
 * Email: balijepn@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "pq.h"
#include "dynarray.h"

void Bottom_percolation(struct pq* pq, int i);
void swap(struct pq* pq, int x, int y);
void top_percolation(struct pq* pq, int i);

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq {
  struct dynarray* x;
  struct dynarray *p1;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  pq->x = dynarray_create();
  pq->p1 = dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  dynarray_free(pq->x);
  dynarray_free(pq->p1);
  free(pq);
}



/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  return(dynarray_size(pq->x)==0);
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  dynarray_insert(pq->x,value);
  dynarray_insert(pq->p1,priority);
  int i = dynarray_size(pq->x) - 1;

  while (i != 0 && dynarray_get(pq->p1,1) < dynarray_get(pq->p1,(i-1)/2)){
    void* t1 = dynarray_get(pq->x,(i-1)/2);
    void* t2 = dynarray_get(pq->p1,(i-1)/2);
    dynarray_set(pq->p1,(i-1)/2,(int)priority);
    dynarray_set(pq->x,(i-1)/2,value);
    dynarray_set(pq->p1,i,t1);
    dynarray_set(pq->x,i,t2);
    i = (i-1)/2;
  }
  
  return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  return (dynarray_get(pq->x, 0));
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
 // this will return the priority number
  void* x = dynarray_get(pq->p1,0);
  return x;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  void* val1 = dynarray_get(pq->x,0);
  int last = dynarray_size(pq->x) -1;
  swap(pq,0,last);
  //dynarray_remove(pq->x,-1);
  //last = 0;
  //dynarray_remove(pq->xq,n-1);
  int value = 0;
  if(dynarray_size(pq->x) > 0) {
    Bottom_percolation(pq,0);
  }
  dynarray_remove(pq->x,dynarray_size(pq->x)-1);
  dynarray_remove(pq->p1,dynarray_size(pq->p1)-1);
  return val1;
}

void Bottom_percolation(struct pq* pq, int i) {
  int left = (2 * i) +1;
  int right = (2 * i) + 2;
  int min = 0;
  if(left > dynarray_size(pq->x) - 1) {
    return;
  }
  if(left == dynarray_size(pq->x) - 1) {
    min = left;
  } else {
   // void* priority_left = dynarray_get(pq->p1,left);
    //void* priority_right = dynarray_get(pq->p1, right);
    if (dynarray_get(pq->p1,left) <= dynarray_get(pq->p1, right)) {
      min = left;
    } else {
      min = right;
    }
  }
  if (dynarray_get(pq->p1,i) > dynarray_get(pq->p1, min)) {
    swap(pq,min,i);
    i = min;
    Bottom_percolation(pq,min);
  }
  //printf("p1_key: %d", dynarray_get(pq->p1,i));
}

void swap(struct pq* pq, int x, int y) {
  void* temp = dynarray_get(pq->x,x);
  void* temp2 = dynarray_get(pq->p1,x);
  dynarray_set(pq->x, x, dynarray_get(pq->x, y));
  dynarray_set(pq->p1, x, dynarray_get(pq->p1, y));
  dynarray_set(pq->x, y, temp);
  dynarray_set(pq->p1,y,temp2);
}
