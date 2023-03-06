#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define MAX 99999 

/* verifica daca nodul x este un depozit */
int is_deposit (int x, int *deposits, int d)
{
    int i;
    for (i=0; i<d; i++)
        if (deposits[i] == x)
            return 1;
    return 0;
}

/* parcurgerea in adancime in orientarea arcelor */
void DFS_nor (int x, GrafP *g, int *viz, int *deposits, int d)
{
    viz[x] = 1; // marcare nod vizitat
    int i;
    for (i = 0; i < g->n; i++) {
        /* verifica daca nodul n-a fost vizitat, nu este depozit si daca 
        exista arc */
        if (viz[i] != 1 && g->c[x][i] != MAX && is_deposit(i,deposits,d) == 0) 
            DFS_nor(i, g, viz, deposits, d);
    }
}

/* parcurgerea in adancime in orientarea inversa arcelor */
void DFS_inv (int x, GrafP *g, int *viz, int *deposits, int d)
{
    viz[x] = 2; // marcare nod vizitat
    int i;
    for(i = 0; i < g->n; i++) {
        /* verifica daca nodul a fost vizitat in primul DFS, nu este depozit si
        daca exista arc */
        if(viz[i] == 1 && g->c[i][x] != MAX && is_deposit(i,deposits,d)==0) 
            DFS_inv(i, g, viz, deposits, d);
    }
}

/* rezolvarea task #2 */
void e2 (GrafP *g, int d, int *deposits)
{
    int i;
    int nr = 0; // numarul componentelor tari conexe
    // vector de indici de componente tari conexe
    int *fr = calloc(g->n, sizeof(int)); 
    for (i = 0; i < g->n; i++) {
        /* daca nu are asociat o componenta tare conexa, atunci mai exista o 
        componenta tare conexa */
        if (is_deposit(i, deposits, d) == 0 && fr[i] == 0) {
            nr++;
            // vector de vizite
            int *viz = calloc(g->n, sizeof(int));
            DFS_nor(i, g, viz, deposits, d);
            DFS_inv(i, g, viz, deposits, d);

            int j;
            for(j = 0; j < g->n; j++)
                if(viz[j] == 2)
                    fr[j] = nr; // a fost adaugat intr-o componenta
    
            free(viz);
        }
    }

    printf("%d\n", nr);   // afisare numarul componentelor tari conexe
    for (i = 1; i<= nr; i++) {
        int j, ok = 0;    // ok = 1, daca nu este primul elem. dintr-o comp 
        for (j = 0; j < g->n; j++)
            if(fr[j] == i) {
                if (ok == 0) {
                    ok = 1;
                    printf("%d", j);
                }
                else 
                    printf(" %d", j);
            }
        if(i != nr)
            printf("\n");
    }
    free(fr);
}