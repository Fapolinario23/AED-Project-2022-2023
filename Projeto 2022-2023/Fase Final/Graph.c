/******************************************************************************
 * (C) AED Projeto
 * 
 * Francisco Apolinário 
 * Inês Mesquita
 *
 * NAME
 *   Graph.c
 *
 * DESCRIPTION
 *   Algorithms to make and insert elements in graph
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "Graph.h"

node* createNode (int, int);

/******************************************************************************
 * createNode()
 * 
 * Arguments: 
 *
 * Returns: 
 * 
 * Description: 
 *   
 * 
 *****************************************************************************/

node* createNode (int peso, int ID)
{                   
  node* newNode = (node*)malloc(sizeof(node));
  if (newNode == NULL){
    exit(0);
  }
  newNode -> custo = peso;                   // peso será o peso que terá a respetiva mutação
  newNode -> ID = ID;
  newNode -> next = NULL;
  return newNode;
}

/******************************************************************************
 * createAGraph()
 * 
 * Arguments:
 *
 * Returns: 
 * 
 * Description: 
 *   
 * 
 *****************************************************************************/

Graph* createAGraph (int vertices)           // vertices - Numero de palavras do dicionario por tamanho
{
  int i;

  Graph* graph = malloc(sizeof(Graph));
  if (graph == NULL){
    exit(0);
  }
  graph -> numVertices = vertices;

  graph -> adjLists = malloc(vertices*sizeof(node*));
  for (i = 0; i < vertices; i++){         // Inicializa a lista de adjacencias
    graph -> adjLists[i] = NULL;
  }
  return graph;
}

/******************************************************************************
 * addEdge()
 * 
 * Arguments:
 *
 * Returns: 
 * 
 * Description: 
 *   
 * 
 *****************************************************************************/

node *add_to_list(node *head, node *new){

  if(head == NULL){
    return new;
  }
  new -> next = head;
  return new;
}

void addEdge (Graph* graph, int peso, int s, int d)
{
  // Add edge from s to d:
  graph -> adjLists[s] = add_to_list(graph -> adjLists[s], createNode(peso, d));
  graph -> adjLists[d] = add_to_list(graph -> adjLists[d], createNode(peso, s));
  return;
}

/******************************************************************************
 * free_Graph()
 * 
 * Arguments:
 *
 * Returns: 
 * 
 * Description: 
 *   
 * 
 *****************************************************************************/

void free_Graph (Graph* graph)
{
  int i;
  node *n1 = NULL, *n2 = NULL;

  for (i = 0; i < graph -> numVertices; i++){
    for (n1 = graph -> adjLists[i]; n1 != NULL;){
      n2 = n1;
      n1 = n1 -> next;
      free (n2);
    }
  }
  free (graph -> adjLists);
  free (graph);
}