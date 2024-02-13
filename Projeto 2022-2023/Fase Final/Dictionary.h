/******************************************************************************
 * (C) AED Projeto
 * 
 * Francisco Apolinário 
 * Inês Mesquita
 *
 * NAME
 *   Dictionary.h
 *
 * DESCRIPTION
 *   
 ******************************************************************************/
#include <stdio.h>
#include "heap.h"

#ifndef _PALAVRA_H
#define _PALAVRA_H

typedef struct _st_dict 
{
    char ***palavras;
    int tam_dif; 
    int  n_palavras_tam [100];  
} st_dict;

void ends_withDict (const char* nome);
void ends_withPals(const char* nome);
void AlocaTab (char *ficheiro, st_dict *t);
void LePals (char *ficheiro, st_dict *t);
void LibertaTabela (st_dict *t);

#endif