/******************************************************************************
 * (C) AED Projeto
 * 
 * Francisco Apolinário 
 * Inês Mesquita
 *
 * NAME
 *   Dictionary.c
 *
 * DESCRIPTION
 *   Algorithms to read and organize dictionary
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _st_dict 
{
    char ***palavras;
    int  n_palavras_tam[100];
} st_dict;

/******************************************************************************
 * ends_withDict()
 * 
 * Arguments: nome - nome do ficheiro de entrada
 *
 * Returns: 
 * 
 * Description: 
 *   Verifica se o ficheiro tem  a extensão .dict
 * 
 *****************************************************************************/

void ends_withDict (const char* nome)
{
    char* point = strrchr(nome, '.');
    if (point != NULL)
    {
        if (strcmp (point, ".dict") != 0)
            exit (0);
    }
}

/******************************************************************************
 * ends_withPals()
 * 
 * Arguments: nome - nome do ficheiro de entrada
 *
 * Returns: 
 * 
 * Description: 
 *   Verifica se o ficheiro tem  a extensão .pals
 * 
 *****************************************************************************/

void ends_withPals(const char* nome)
{
    char* point = strrchr(nome, '.');
    if (point != NULL)
    {
        if (strcmp (point, ".pals") != 0)
            exit (0);
    }
}

/******************************************************************************
 * AbreFicheiro()
 *
 * Arguments: nome - pointer to string holding name of file to open
 *            mode - pointer to string with 'r'/'w' etc mode for file open
 * Returns: pointer to opened file
 * Side-Effects: exits if given file cannot be opened with given mode
 *
 * Description:
 *   Open named file in requested mode, message stderr and exit if open fails
 *****************************************************************************/

FILE *AbreFicheiro (char *nome, char *mode)
{
    FILE *fp = NULL;
    fp = fopen (nome, mode);
    if (fp == NULL){
        exit (0);
    }
    return (fp);
}

/******************************************************************************
 * FechaFicheiro()
 *
 * Arguments: f - pointer to file
 * 
 * Returns: (none)
 *
 * Description:
 *   Close a file
 *****************************************************************************/

void FechaFicheiro (FILE *fp){
    fclose (fp);
}

/******************************************************************************
 * LeDict()
 *
 * Arguments: f - pointer to file where word will be read
 * Returns:  pointer to word just read
 * Side-Effects: none
 *
 * Description:
 *   Return pointer to local buffer with word, or NULL if file read failed
 *   Maximum word size MAX_STR
 *****************************************************************************/

char *LeDict (FILE *f)
{
    static char palavra[100];

    if (fscanf (f, "%s", palavra) == 1){
        return (palavra);
    } else {
        return ((char *) NULL);
    }
}

/******************************************************************************
 * swap()
 * 
 * Arguments:  
 * 
 * Returns: 
 * 
 * Description:
 *    This function swap positions
 * 
 *****************************************************************************/

void swap(char **str1, char **str2)
{
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

/******************************************************************************
 * quickSotr()
 * 
 * Arguments: **array - all the words with a specified size
 *            len - number of words with that size
 * 
 * Returns: 
 * 
 * Description:
 *    Sorts an array of strings using the quicksort algorithm E O(N*logN)
 * 
 *****************************************************************************/

void quickSort(char **arr, unsigned int len)
{
    unsigned int piv = 0;
    int i;

    if(len <= 1){
        return;
    }

    for(i = 0; i < len; i++){
        if(strcmp(arr[i], arr[len-1]) < 0){
            swap(arr + i, arr + piv++);
        }
    }

    swap(arr + piv, arr + len -1);
    quickSort(arr, piv++);
    quickSort(arr + piv, len - piv);
}

/******************************************************************************
 * binarysearch()
 * 
 * Arguments: **arr - all the words with a specified size
 *            x - the word we want to find
 *            low - the lower index in search
 *            high - the highest index in search  
 * 
 * Returns: return the word position in is size
 * 
 * Description:
 *    Finds the word pretended
 * 
 *****************************************************************************/

int binarySearch(char **arr, char *x, int low, int high)
{
    int mid = (low + high)/2;
    int aux = strcmp(arr[mid], x);

    do {
        if (aux == 0){
            return mid;
        } else {
            if (aux > 0){
                return binarySearch(arr, x, low, mid - 1);
            } else {
                return binarySearch(arr, x, mid + 1, high);
            }
        }
    } while (low <= high && aux != 0);
    return -1;
}

/******************************************************************************
 * EscreveFicheiro()
 *
 * Arguments: ficheiro - pointer to string holding name of file to save
 *            st_dict - pointer to structure where information is kept
 * Returns: (none)
 *
 * Description:
 *   Open output file, write table of words.
 *****************************************************************************/

void EscreveFicheiro (st_dict *t, FILE* file, char *pal1, char *pal2, int numb){

    int size1 = strlen(pal1);
    int size2 = strlen(pal2);
    int t1=-1, t2=-1;
    static int sorted[100] = {0};

    if (sorted[size1 - 1] == 0){
        quickSort (t -> palavras[size1 - 1], t -> n_palavras_tam[size1 - 1]);
        sorted[size1 - 1]++;
    }
    if(t->palavras[size1-1]!=NULL){
        t1 = binarySearch (t -> palavras[size1 - 1], pal1, 0, t -> n_palavras_tam[size1 - 1] - 1);
        t2 = binarySearch (t -> palavras[size2 - 1], pal2, 0, t -> n_palavras_tam[size2 - 1] - 1);
    }

    if (size1 != size2 || t1 < 0 || t2 < 0 || (numb != 2 && numb != 1)){
        fprintf (file, "%s %s %d\n\n", pal1, pal2, numb);
    } else {
        if (numb == 1)
        {
            fprintf (file, "%s %d\n\n", pal1, t -> n_palavras_tam[size1 -1]);
        } else {
            fprintf (file, "%s %d\n%s %d\n\n", pal1, t1, pal2, t2);
        }
    }

}

/******************************************************************************
 * LePals()
 *
 * Arguments: f - pointer to file where word will be read
 * 
 * Returns:  pointer to word just read
 *
 * Description:
 *   Return pointer to local buffer with word, or NULL if file read failed
 *   Maximum word size MAX_STR
 *****************************************************************************/

void LePals (char *ficheiro, st_dict *t)
{
    FILE *fp, *f;
    char pal1[100], pal2[100];
    int numb = 0;
    char *nome = NULL;
    char *p;

    fp = AbreFicheiro (ficheiro, "r");
    nome =  malloc(strlen(ficheiro) + 2);
    if (nome == NULL) { 
        exit (0);
    }
    strcpy (nome, ficheiro);
    p = strrchr (nome, '.');
    *p = '\0';
    strcat (nome, ".stats");
    f = AbreFicheiro (nome, "w");

    while (fscanf(fp, "%s %s %d", pal1, pal2, &numb) != EOF){
        EscreveFicheiro (t, f, pal1, pal2, numb);
    }

    FechaFicheiro (fp);
    FechaFicheiro (f);
    free (nome);
    return;
}

/******************************************************************************
 * PreencheTabelaPalavras()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            st_texto - pointer to structure where information will be saved
 * Returns: (none)
 *
 * Description:
 *
 *****************************************************************************/

void PreencheTabelaPalavras (st_dict *t, int* n_pal_tam,FILE *f)
{
    char *palavra;
    int pos_ocup[100] = {0};

    while ((palavra = LeDict (f)) != NULL){
        strcpy (t -> palavras[strlen(palavra) - 1][pos_ocup[strlen(palavra)]], palavra);
        pos_ocup[strlen(palavra)]++;
    }
}

/******************************************************************************
 * AlocaTab()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            st_texto - pointer to structure where information will be saved
 * 
 * Returns: (none)
 *
 * Description:
 *   Read input file to find dimensions, allocate and initialize tables
 *****************************************************************************/

void AlocaTab (char *ficheiro, st_dict *t)
{
    FILE *fp;
    char *palavra = NULL;
    int i, j, len;
    
    fp = AbreFicheiro (ficheiro, "r");

    for(i = 0; i < 100; i++){
        t -> n_palavras_tam[i] = 0;
    }
    
    while ((palavra = LeDict (fp)) != NULL) { 
        len = strlen (palavra);
        i = len - 1;                            /* i = tamnho - 1 */
        t -> n_palavras_tam[i]++;               /* o vetor incrementa para esse indice */
    }

    t -> palavras = NULL;
    t -> palavras = (char***) malloc(100*sizeof(char**));
    if (t -> palavras == NULL) {
        exit (0);
    }

    for (i = 0; i < 100; i++){
        t -> palavras[i]=NULL;
        if(t -> n_palavras_tam[i] > 0){
            t -> palavras[i] = (char**) malloc(t -> n_palavras_tam[i]*sizeof(char*));
            if (t -> palavras[i] == NULL) {
                exit (0);
            }
            for (j = 0; j < t -> n_palavras_tam[i]; j++){
                t -> palavras[i][j] = (char*) calloc(sizeof(char),(i+2));
                if (t -> palavras[i][j] == NULL) {
                    exit (0);
                }
                t -> palavras[i][j][0]='\0';
            }
        }
    }
    rewind(fp);
    PreencheTabelaPalavras (t, t -> n_palavras_tam, fp);
    FechaFicheiro (fp);
    
    return;
}

/******************************************************************************
 * LibertaTabela()
 *
 * Arguments: st_texto - pointer to structure where information will be saved
 * 
 * Returns: (none)
 *
 * Description:
 *   Free the table
 *****************************************************************************/

void LibertaTabela (st_dict *t)
{
    int i, j;
       
    for (i = 0; i < 100; i++){
       if(t -> n_palavras_tam[i] > 0){ 
            for (j = 0; j < t -> n_palavras_tam[i]; j++){
                free (t -> palavras[i][j]);
            }
            free (t -> palavras[i]);
        }
    }
    free (t -> palavras);
}
