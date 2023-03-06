#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define MAX 99999

typedef struct elem {
    int x;
    double sum;
    int traseu;
    int *stare;
} elem;

typedef struct queue {
    elem *data;
    int cap, nr;
} queue;

/* returneaza 1 daca cei doi 2 vectori sunt identici, altfel 0 */
int is_equal (int n, int *array1, int *array2)
{
    int i;
    for (i = 0; i < n; i++)
        if (array1[i] != array2[i]) 
            return 0;
    return 1;
}

/* copiaza in array2 valorile lui array1 */
void copy (int n, int *array1, int *array2)
{
    int i;
    for (i = 0; i < n; i++)
        array2[i] = array1[i];
}

/* verifica daca in traseul actual s-a mai trecut anterior prin acelas nod,
avand aceeasi stare */
int before (queue *q, int poz, int *stare, int x, GrafP *g)
{
    int i;
    for(i = 0; i < poz; i++)
        if( x == q->data[i].x && is_equal(g->n, q->data[i].stare, stare)==1 && q->data[i].traseu == 1)
            return 1;
    return 0;
}

elem* mem(elem* data, int cap)
{
    data = realloc(data, cap*sizeof(elem));
    return data;
}

/* parcurgerea arborelui pentru a gasi un cost minim pentru o zona */
void BFS (GrafP *g, queue *q, int *poz, double *sumM, int des, int *zone) 
{
    int x = q->data[*poz].x;
    int p = *poz;
    *poz = *poz + 1;

    /* verificare daca s-a ajuns la finalul traseului */
    if(is_equal(g->n, q->data[p].stare, zone) == 1 && x == des) {
        /* verificare daca costul este mai mic */
        if(q->data[p].sum < *sumM) 
            *sumM = q->data[p].sum;
    }
    else {
        int i;    
        for (i = 0; i < g->n; i++) {
            /* crearea unei stari temporale pentru vecin */
            int *stare = calloc(g->n, sizeof(int));
            copy(g->n, q->data[p].stare, stare);
            stare[i] = 1;
            int s = q->data[p].sum + g->c[x][i];

            /* verific. daca se poate continua drumul prin vecinul respectiv */
            if ( s<*sumM && g->c[x][i] != MAX && zone[i] && before(q,p,stare,i,g)==0) { 
                /* adaugare element la coada */

                if(q->cap == q->nr) {
                    q->cap = q->cap + 3;
                    q->data = mem(q->data, q->cap);
                }

                int aux = q->nr;
                q->data[aux].x = i;
                q->data[aux].sum = q->data[p].sum + g->c[x][i];
                q->data[aux].stare = calloc(g->n, sizeof(int));
                copy(g->n, stare, q->data[aux].stare);
                q->data[aux].traseu = 1;
                q->nr = q->nr + 1;

                BFS(g, q, poz, sumM, des, zone);
                q->data[aux].traseu = 0;
            }
            free(stare);
        }
    }
}

/* rezolvarea task #3 */
void e3(GrafP *g, int d, int *deposits)
{
    int r, k;
    scanf("%d", &r);       // numarul de zone

    int i, j;
    for (i = 1; i <= r; i++) {
        /* vector de marcare a zonei */
        int *zone = calloc(g->n, sizeof(int));
        scanf("%d", &k);   // nr. de noduri dintr-o zona
        int x;
        for (j = 0; j < k; j++) {
            scanf("%d", &x);
            zone[x] = 1;   // marcare zona
        }

        double dmin = MAX; // costul traseului
        for(j = 0; j < d; j++) {
            zone[deposits[j]] = 1;
            double sumM = MAX;
            int poz = 0;
            queue q;
            q.cap = 3;
            q.nr = 1;
            q.data = calloc(3, sizeof(elem));
            q.data[0].x = deposits[j];
            q.data[0].sum = 0;
            q.data[0].stare = calloc(g->n, sizeof(int));
            q.data[0].stare[deposits[j]] = 1;
            q.data[0].traseu = 1;

            BFS(g, &q, &poz, &sumM, deposits[j], zone);

            /* verificare daca s-a gasit un cost mai mic */ 
            if (sumM < dmin) dmin = sumM;
            
            zone[deposits[j]] = 0;
          
            /* eliberare memorie */
            int k;
            for(k=0; k < q.nr; k++)
                free(q.data[k].stare);
            
            free(q.data);
            
        }

        /* afisare costul minim pentru o zona */
        if( i != r ) printf("%.1lf\n",dmin);
        else  printf("%.1lf",dmin);
        free(zone);
    }
}