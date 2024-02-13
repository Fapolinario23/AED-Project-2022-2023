/******************************************************************************
 * (C) AED Projeto
 * 
 * Francisco Apolinário 
 * Inês Mesquita
 *
 * NAME
 *   Heap.c
 *
 * DESCRIPTION
 *   Algorithms to make and insert elements in graph
 * 
 * COMMENTS
 *   This file was provided by teachers 
 *
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "Graph.h"

/* A heap is represented by a structure: */
typedef struct _heap {
  int (*less) (Item, Item, int*);
  int n_elements;               /* # elements in heap */
  int size;                     /* max size of the heap. */
  int *pos;
  Item *heapdata;               /* An array of Items. */
} _heap;

/*******************************************/

int IsEmpty(Heap *h)
{
  if (h -> n_elements == 0){
    return 1;
  } else {
    return 0;
  }
}

/******************************************************************************
 * FixUp()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixup
 * Returns:
 * Side-Effects: none
 *
 * Description: Performs fixup from index
 *
 *****************************************************************************/

void FixUp(Heap * h, int k, int* wt)
{
  Item t;

  while ((k > 0) && (h -> less) ((h -> heapdata)[(k - 1) / 2], (h -> heapdata)[k], wt)){

    h -> pos [((node*)((h -> heapdata)[k]))-> ID] = (k - 1)/2;
    h -> pos [((node*)((h -> heapdata)[(k - 1) / 2])) -> ID] = k;

    t = (h -> heapdata)[k];
    (h -> heapdata)[k] = (h -> heapdata)[(k - 1) / 2];
    (h -> heapdata)[(k - 1) / 2] = t;
    k = (k - 1) / 2;
  }
  return;
}

/******************************************************************************
 * FixDown()
 *
 * Arguments: h - pointer to heap structure
 *            k - index of element to fixdown
 * Returns:
 * Side-Effects: none
 *
 * Description: performs fixdown from index
 *
 *****************************************************************************/

void FixDown(Heap * h, int k, int* wt)
{
  int j;
  Item t;

  while ((2 * k + 1) < h -> n_elements){
    j = 2 * k + 1;
    if (((j + 1) < h -> n_elements) && (h -> less) (h -> heapdata[j], h -> heapdata[j + 1], wt)){
      /* second offspring is greater */
      j++;
    }
    if (!(h -> less) (h -> heapdata[k], h -> heapdata[j], wt)) {
      /* Elements are in correct order. */
      break;
    }
    /* the 2 elements are not correctly sorted, it is
       necessary to exchange them */

    h -> pos[((node*)((h -> heapdata)[k])) -> ID] = j ;
    h -> pos[((node*)((h -> heapdata)[j])) -> ID] = k;    

    t = (h -> heapdata)[k];
    (h -> heapdata)[k] = (h -> heapdata)[j];
    (h -> heapdata)[j] = t;
    k = j;
  }
  return;
}

/******************************************************************************
 * NewHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 * Side-Effects: none
 *
 * Description: allocates space for a new heap of specified size
 *
 *****************************************************************************/

Heap *NewHeap(int size, int (*less) (Item, Item, int*))
{
  Heap *h;
  int i;

  h = (Heap *) malloc(sizeof(Heap));
  if (h == ((Heap *) NULL)) {
    exit(0);
  }

  h -> n_elements = 0;
  h -> less = less;
  h -> size = size;
  h -> heapdata = (Item *) malloc(size * sizeof(Item));
  if (h -> heapdata == ((Item *) NULL)){
    exit(0);
  }

  h -> pos = (int*) malloc(size*sizeof(int));
  if (h -> pos == NULL){
    exit(0);
  }

  for (i = 0; i < size; i++){
    h -> pos[i] = -1;
  }

  return (h);
}

/******************************************************************************
 * NewHeap()
 *
 * Arguments: size - heapint  compareItems(Item it1, Item it2, int* wt)
{
    int i1, i2;

    i1 = ((node*)it1) -> ID;
    i2 = ((node*)it2) -> ID;

    if (wt[i1] > wt[i2]){
        return 1;
    } else {
        return 0;
    }
} space for a new heap of specified size
 *
 *****************************************************************************/

void FreeHeap (Heap *h)
{

  free(h -> heapdata);
  free(h);

  return;
}
/******************************************************************************
 * Insert()
 *
 * Arguments: h - pointer to heap
 *            element - pointer to new element
 * Returns: vopid
 * Side-Effects: none
 *
 * Description: add element at the end of heap and do fixup
 *
 *****************************************************************************/

int Insert(Heap * h, Item element, int* wt)
{
  if (h -> n_elements == h -> size){
    return 0;
  }
  h -> heapdata[h -> n_elements] = element;

  h -> pos[((node*)element) -> ID] = h -> n_elements;
  h -> n_elements++;

  FixUp (h, h -> n_elements - 1, wt);

  return 0;
}

/******************************************************************************
 * Modify()
 *
 * Arguments: h - pointer to heap
 *            index - index of element to modify
 *            newvalue - new element value
 * Returns: void
 * Side-Effects: none
 *
 * Description: compares new element with antecedent, if larger do a fixup
 *              otherwise do fixdown
 *
 *****************************************************************************/

void Modify(Heap * h, int index, int newvalue, int *wt)
{
    int x;

    x = h -> pos[index];

    if (index > h -> n_elements - 1){
      return;
    } else {
      wt[index] = newvalue;
      FixUp (h, x, wt);
    }
    
  return;
}

/******************************************************************************
 * RemoveMax()
 *
 * Arguments: h - pointer to heap
 * Returns: Item
 * Side-Effects: none
 *
 * Description: exchange first and last element of heap, remove last element
 *              (max element) from heap and maintain heap order by performing
 *              a fixdown of the first element
 *
 *****************************************************************************/

Item RemoveMax(Heap * h, int* wt)
{
  Item t;
  if (h -> n_elements > 0){
    h -> pos[((node*)((h -> heapdata)[0])) -> ID] = h -> n_elements - 1;
    h -> pos[((node*)((h -> heapdata)[h -> n_elements - 1])) -> ID] = 0;
    
    
    t = (h -> heapdata)[0];
    (h -> heapdata)[0] = (h -> heapdata)[h -> n_elements - 1];
    (h -> heapdata)[h -> n_elements - 1] = t;
    h -> n_elements--;
    
    FixDown(h, 0, wt);
    
    return t;
  }
  return NULL;
}