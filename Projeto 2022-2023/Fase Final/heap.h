
/******************************************************************************
 *
 * File Name: heap.h
 *	      (c) 2010 AED
 * Author:    AED team
 * Revision:  v2.3 ACR
 * NAME
 *     heap.h - prototypes
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <string.h>
 *
 * DESCRIPTION
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include "Item.h"

typedef struct _heap Heap;

int IsEmpty (Heap *h);
Heap *NewHeap(int size, int (*less) (Item, Item, int*));
void FreeHeap(Heap * h);
int Insert(Heap * h, Item element, int* wt);
void Modify(Heap * h, int indice, int newvalue, int* wt);
Item RemoveMax(Heap * h, int* wt);
int PrintHeap(Heap * h);