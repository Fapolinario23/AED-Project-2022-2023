/******************************************************************************
 * (C) AED Projeto
 * 
 * Francisco Apolinário 
 * Inês Mesquita
 *
 * NAME
 *   Graph.h
 *
 * DESCRIPTION
 *   
 ******************************************************************************/

#include <stdio.h>

#ifndef _PALAVRA_H
#define _PALAVRA_H

typedef struct node
{
  char *palavra;
  int custo;
  int ID;
  struct node* next;
} node;

typedef struct Graph
{
  int numVertices;
  node** adjLists;
} Graph;

Graph* createAGraph(int vertices);
void addEdge (Graph* graph, int peso, int s, int d);
void free_Graph (Graph* graph);

#endif