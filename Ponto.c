#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"Ponto.h"

Ponto *geraPontos(int N)
{
   Ponto *p;
   Ponto *cabPontos = mallocSafe(sizeof(*cabPontos));
   cabPontos->ant = NULL;
   cabPontos->prox = NULL;
   while(N > 0)
   {
      p = mallocSafe(sizeof(*p));
      p->x = 1.0*rand()/RAND_MAX;
      p->y = 1.0*rand()/RAND_MAX;
      if(cabPontos->prox != NULL)cabPontos->prox->ant = p;
      p->ant = cabPontos;
      p->prox = cabPontos->prox;
      cabPontos->prox = p;
      N--;
   }
   return cabPontos;
}

float calculaDistancia(Ponto a, Ponto b)
{
   return sqrt((a.x*a.x - b.x*b.x)+(a.y*a.y - b.y*b.y));
}

void *mallocSafe (size_t n)
{
  void * pt;
  pt = malloc(n);
  if (pt == NULL) {
    printf("ERRO na alocacao de memoria.\n\n");
    exit(-1);
  }
  return pt;
}
