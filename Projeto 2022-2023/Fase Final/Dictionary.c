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
#include <math.h>

#include "Graph.h"
#include "heap.h"

#define MAX 9999

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
    static char palavra[100];       /* note static local buffer returned */

    if (fscanf (f, "%s", palavra) == 1){
        return (palavra);
    } else {
        return ((char *) NULL);
    }
}

/******************************************************************************
 * cmp()
 *
 * Arguments: *a - pointer
 *            *b - pointer
 * Returns: (none)
 *
 * Description:
 *   compare two arguments.
 *****************************************************************************/

int cmp (const void * a, const void * b) {

    return (strcmp(*(const char**) a, *(const char**) b));
}

int  compareItems(Item it1, Item it2, int* wt)
{
    int i1, i2;

    i1 = ((node*)it1) -> ID;
    i2 = ((node*)it2) -> ID;

    return (wt[i1] > wt[i2]);
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
    while (high >= low){
        int mid = (low + high)/2;
        int aux = strcmp (x, arr[mid]);
        
        if (aux == 0){
            return mid;
        }
        if (aux < 0){
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}


/******************************************************************************
 * Dijkstra()
 * 
 * Arguments:
 *
 * Returns: 
 * 
 * Description: 
 *   
 * 
 *****************************************************************************/

int Dijkstra (Graph* graph, int start, int end, int max_mut, int* st, int* wt, int* vist, int size)
{
    int v = -1, c;
    node *n, *start_n;
    Heap *h;

    /* Nó de partida */
    start_n = (node*) malloc(sizeof(node));
    if (start_n == NULL){
        exit(0);
    }
    start_n -> ID = start;
    start_n -> custo = 0;
    start_n -> next = NULL;

    h = NewHeap(size, compareItems);
    for (v = 0; v < size; v++) {
        st[v] = -1;
        wt[v] = MAX;
        vist[v] = 0;
    }

    wt[start] = 0;
    vist[start] = 1;
    Insert(h, (Item)start_n, wt);

    while (!(IsEmpty(h)) && (v = ((node*)RemoveMax(h, wt))-> ID) != end){
        vist[v] = 1;
        for (n = graph -> adjLists[v]; n != NULL; n = n -> next){
            if (vist[n -> ID] == 0){
                c = wt[v] + (n -> custo)*(n -> custo);
                if ((c < wt[n -> ID]) && (n -> custo <= max_mut)){
                    if(st[n -> ID] == -1){ 
                        wt[n -> ID] = c; 
                        Insert(h, (Item)n, wt); 
                        st[n -> ID] = v;
                    } else {
                        
                        wt[n -> ID] = c;
                        Modify(h, n -> ID, c, wt);

                    }   
                }
            }
        }
    }
    free(start_n);
    FreeHeap(h);

    return wt[end];
}


/******************************************************************************
 * Ve_Peso()
 * 
 * Arguments:
 *
 * Returns: 
 * 
 * Description: 
 *   
 * 
 *****************************************************************************/

void Ve_Peso (int size, int n, char** palavras, int mut, Graph* graph)
{
  int dif_Letters = 0, custo = 0;
  int i, j, k;
    for(i = 0; i < n; i++){
        for (j = i + 1; j < n; j++){
            dif_Letters = 0;
            for(k = 0; k < (size); k++){
                if(palavras[j][k] != palavras[i][k]){
                    dif_Letters++;
                    if (dif_Letters > mut){
                        break;
                    }
                }
            }
            if (0 < dif_Letters && dif_Letters <= mut){
                custo = dif_Letters;
                addEdge (graph, custo, i, j);
            }
        }
    }
  return;
}

void print_pals (int *st, int custo, int end, FILE* file, char** pals)
{
    if(st[end] != -1){
        print_pals (st, custo, st[end], file, pals);
        fprintf (file, "%s\n", pals[st[end]]);
    }
    if(st[end] == -1){
        fprintf (file, "%s %d\n", pals[end], custo);
    }
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

void EscreveFicheiro (st_dict *t, FILE* file, char *pal1, char *pal2, int numb, int mut, int prob, int prob2, Graph **graph)
{

    int size1 = strlen(pal1);
    int size2 = strlen(pal2);
    int t1 = -1, t2 = -1, count = 0, i, custo = 0;
    static int sorted[40] = {0};
    static int c_graph[40] = {0};
    int *st, *wt, *vist;

    if (sorted[size1 - 1] == 0){
        qsort (t -> palavras[size1 - 1], t -> n_palavras_tam[size1 - 1], sizeof(char*), cmp);       /* Quicksort */ 
        sorted[size1 - 1]++;
    }
    if (t -> palavras[size1-1] != NULL){
        t1 = binarySearch (t -> palavras[size1 - 1], pal1, 0, t -> n_palavras_tam[size1 - 1] - 1);
        t2 = binarySearch (t -> palavras[size2 - 1], pal2, 0, t -> n_palavras_tam[size2 - 1] - 1);
    }
    for (i = 0; i < size1; i++){
        if (pal1[i] != pal2 [i]){
            count++;
        }
    }

    if (size1 != size2 || t1 < 0 || t2 < 0 || numb < 0){
        fprintf (file, "%s -1\n%s\n\n", pal1, pal2);
    } else {
        if (t1 == t2){                                          /* Mesma palavra o custo de mutação é 0 */
            fprintf (file, "%s 0\n%s\n\n", pal1, pal2);
        } else {
            if (numb == 0){
                fprintf (file, "%s -1\n%s\n\n", pal1, pal2);
            } else {
                if (count == 1){                                    /* As palvras distam 1 letra custo de mutação 1 */
                    fprintf (file, "%s 1\n%s\n\n", pal1, pal2);
                } else {
                    if (c_graph[size1 - 1] == 0){                   /* Cria grafo e calcula custo par as palavras de tamanho n apenas se ainda não o tiver feito */
                        graph[size1 - 1] = createAGraph(t -> n_palavras_tam[size1 - 1]);
                        Ve_Peso(size1, t -> n_palavras_tam[size1 - 1], t -> palavras[size1 - 1], mut, graph[size1 - 1]);
                        c_graph[size1 - 1]++;
                    }
                    st = (int*) malloc((t -> n_palavras_tam[size1 - 1])*sizeof(int));
                    wt = (int*) malloc((t -> n_palavras_tam[size1 - 1])*sizeof(int));
                    vist = (int*) malloc((t -> n_palavras_tam[size1 - 1])*sizeof(int));

                    custo = Dijkstra (graph[size1 - 1], t1, t2, numb, st, wt, vist, t ->n_palavras_tam[size1 - 1]);

                    if (custo == MAX){        /* Não foi encontrado caminho */
                        fprintf (file, "%s -1\n%s\n\n", pal1, pal2);
                    } else {
                        print_pals (st, custo, t2, file, t -> palavras[size1 - 1]);
                        fprintf (file, "\n");             
                    }
                    free(st);
                    free(wt);
                    free(vist);
                }
            }
        }
    }

    if (prob == prob2 && c_graph[size1 - 1] != 0){
        free_Graph(graph[size1 - 1]);
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

    Graph **graph;
    FILE *fp, *f;
    char pal1[100], pal2[100];
    int numb = 0, tam = 0;
    char *nome = NULL;
    char *p;
    static int mut_max[40] = {0};
    static int prob[40] = {0};
    static int prob2[40] = {0};

    fp = AbreFicheiro (ficheiro, "r");
    nome =  (char*)malloc((strlen(ficheiro) + 2)*sizeof(char));
    if (nome == NULL) {
        exit (0);
    }
    strcpy (nome, ficheiro);
    p = strrchr (nome, '.');
    *p = '\0';
    strcat (nome, ".paths");
    f = AbreFicheiro (nome, "w");
    
    while (fscanf(fp, "%s %s %d", pal1, pal2, &numb) != EOF){   /* Le o ficheiro das palavras uma vez para ver qual o numero maximo de mutações por tamnaho de palavra */
        tam = strlen(pal1);
        if (numb > mut_max[tam - 1] && numb <= tam){
            mut_max[tam - 1] = numb;
        }
        prob[tam - 1]++;
    }

    graph = (Graph**) malloc(40*sizeof(Graph*));
    if (graph == NULL){
        exit(0);
    }

    rewind (fp);

    while (fscanf(fp, "%s %s %d", pal1, pal2, &numb) != EOF){
        tam = strlen(pal1);
        prob2[tam - 1]++;
        EscreveFicheiro (t, f, pal1, pal2, numb, mut_max[tam - 1], prob[tam - 1], prob2[tam - 1], graph);      /* mut_max[tam - 1] - 1 pois no caso das maiores mutaçoes o melhor caso sera a "mutaçao direta" */
    }

    free (graph);
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
        t->palavras[i]=NULL;
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
