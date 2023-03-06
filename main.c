#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define MAX 99999

/* initializarea unui graf cu n varfuri si m muchii */
GrafP* initG (int n, int m) 
{
    int i, j;
    GrafP *g = malloc (sizeof(GrafP));
    g->n = n; 
    g->m = m; 
    g->c = malloc(n * sizeof(double*));
    for (i = 0; i < n; i++)
        g->c[i] = calloc(n, sizeof(double));
    
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            g->c[i][j] = MAX;
    return g;
}

int main()
{
    int i;
    int n, m, d;
    scanf("%d%d%d", &n, &m, &d);
    GrafP *g = initG(n, m);     // crearea unui graf de n noduri si m muchii
    /* citirea si adaugarea de muchii */
    for (i = 0; i < m; i++) {
        int u, v;
        double w;
        scanf("%d%d%lf", &u, &v, &w);
        g->c[u][v] = w;
    }

    /* citirea nodurilor ce reprezinta depozite */
    int *deposits = calloc(d, sizeof(int));
    for (i = 0; i < d; i++)
        scanf("%d", &deposits[i]);

    /* nr_tasks reprez. numarul de cerinte ce trebuiesc rezolvate */
    int nr_tasks;
    scanf("%d", &nr_tasks);
    
    /* rezolvarea fiecarui task */
    for (i = 0; i < nr_tasks; i++) {
        char ID_task[3];
        scanf("%s", ID_task);  // task-ul dorit
        
        /* rezolvarea task-ului dorit */
        if (strcmp(ID_task, "e1") == 0)
            e1(i, nr_tasks, g);

        if (strcmp(ID_task, "e2") == 0)
            e2(g, d, deposits);

        if (strcmp(ID_task, "e3") == 0)
            e3(g, d, deposits);
    }

    /* eliberarea memoriei */
    for (i = 0; i < g->n; i++)
        free(g->c[i]);
    free(g->c);
    free(g);
    free(deposits);
}