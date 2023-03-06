typedef struct grafP {
    int n, m;    //nr. de varfuri si nr. de muchii
    double **c;  //matrice de costuri
} GrafP;

GrafP* initG (int n, int m);

void e1(int j,int nr_tasks, GrafP *g);

void e2(GrafP *g, int d, int *deposits);

void e3(GrafP *g, int d, int *deposits);