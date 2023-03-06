#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define MAX 99999

/* afisarea drumului pornind de la nodul src */
void print_road (int i,int src, int *p)
{
    if (i != src) {
        print_road(p[i], src, p);
        printf(" %d", i);
    }
}

/* algoritm dijkstra */
void dijkstra (GrafP g, int dep, int f, int *p, double *dmin) 
{
    /* d = distantele minime */
    double *d = calloc(g.n, sizeof(double));
    /* s = noduri pentru care se stie distanta minima */
    int *s = calloc(g.n, sizeof(int));   

    int jmin, i, j;
    for (i = 0; i < g.n; i++) {
        p[i] = dep; 
        d[i] = g.c[dep][i]; 
    }

    s[dep] = 1;

    for (i = 0; i < g.n && s[f] == 0; i++) { 
        /* cauta nodul j pentru care d[j] este minim */
        *dmin = MAX;
        for (j = 0; j < g.n; j++)
            /* determina minimul dintre distantele d[j] */
            if (s[j] == 0 && *dmin > d[j] ) {
                *dmin = d[j]; 
                jmin = j;
            }

        s[jmin] = 1;

        for (j = 0; j < g.n; j++)
            /* recalculare distante noduri fata de sursa */
            if (d[j] > d[jmin] + g.c[jmin][j] ) {
                d[j] = d[jmin] + g.c[jmin][j];
                p[j] = jmin; // predecesorul lui j pe drumul minim
            }
    }

    free(s);
    free(d);
}

/* rezolvarea task #1 */
void e1 (int j, int nr_tasks, GrafP *g)
{
    int s, k, i;             // s = depozitul din care se incarca marfa
    scanf("%d%d", &s, &k);   // k = nr. de magazine ce vor fi aprovizionate
    
    double sum = 0;          // sum = cost total al traseului
    for (i = 0; i < k; i++) {
        int x;
        double dmin1 = 0, dmin2 = 0;
        
        scanf("%d", &x);     // x = id magazin ce va fi aprovizionat
        printf("%d\n", x);
    
        int *p = calloc(g->n, sizeof(int));
        dijkstra(*g, x, s, p, &dmin2);
        free(p);

        p = calloc(g->n, sizeof(int));
        dijkstra(*g, s, x, p, &dmin1); 
        printf("%.1lf %.1lf\n", dmin1, dmin2); // afisare costuri drumuri
        
        /* afisare traseu depozit - magazin */ 
        printf("%d",s);
        print_road(x, s, p);
        free(p);

        p = calloc(g->n, sizeof(int));
        dijkstra(*g, x, s, p, &dmin2);   

        /* afisare traseu magazin - depozit */ 
        print_road(s, x, p);
        printf("\n");
        free(p);

        sum += dmin1 + dmin2;
    }

    /* afisare cost total al traseului */
    printf("%.1lf", sum);
    if(j != nr_tasks - 1) 
        printf("\n");
}