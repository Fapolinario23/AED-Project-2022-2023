/******************************************************************************
 * (C) AED Projeto
 * 
 * Francisco Apolinário 
 * Inês Mesquita
 *
 * NAME
 *   main.c
 *
 * DESCRIPTION
 *   Main program for unique word finding with lists
 * 
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dictionary.h"

/******************************************************************************
 * main ()
 *
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 * 
 * Returns: int status
 *
 * Description: main Program
 * 
 *****************************************************************************/

int main(int argc, char **argv){
    st_dict st_palavras;
    
    if (argc != 3) {
        exit(0);
    }
    ends_withDict (argv[1]);
    ends_withPals (argv[2]);

    AlocaTab (argv[1], &st_palavras);
    LePals (argv[2], &st_palavras);
    LibertaTabela (&st_palavras);

    return 0;
}