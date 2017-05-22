#include <stdlib.h>
#include <time.h>

#include "snopt_cwrap.h"

inline double closed_interval_rand(double x0, double x1)
{
    return x0 + (x1 - x0) * rand() / ((double)RAND_MAX);
}

void snInit(snProblem *prob, char *name, char *prtfile, int summOn){};

int setIntParameter(snProblem *prob, char stropt[], int opt)
{
    return 1;
};

int setRealParameter(snProblem *prob, char stropt[], double opt)
{
    return 1;
};

void deleteSNOPT(snProblem *prob){};

// The following routine fakes the snOptA interface and generates 100 random vectors. It will not touch the input
// decision vector
int solveA(snProblem *prob, int start, int nF, int n, double ObjAdd, int ObjRow, snFunA usrfun, int neA, int *iAfun,
           int *jAvar, double *A, int neG, int *iGfun, int *jGvar, double *xlow, double *xupp, double *Flow,
           double *Fupp, double *x, int *xstate, double *xmul, double *F, int *Fstate, double *Fmul, int *nS, int *nInf,
           double *sInf)
{
    double x_new[n];
    int *Status = 0;
    int needF = 1;
    int needG = 1;
    char cu[1];
    int lencu = 0;
    double G[nF * n];
    srand(time(NULL));
    for (int i = 0; i < 100; ++i) {
        // Random vector
        for (int j = 0; j < n; ++j) {
            x_new[j] = closed_interval_rand(xlow[j], xupp[j]);
        }
        // Call usrfun (will call both fitness and gradient)
        usrfun(Status, &n, x_new, &needF, &nF, F, &needG, &neG, G, cu, &lencu, prob->iu, &(prob->leniu), prob->ru,
               &(prob->lenru));
    }
    return 1;
};