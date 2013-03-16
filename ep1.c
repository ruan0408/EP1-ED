#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ponto{float x;
                       float y;
                       struct ponto *ant;
                       struct ponto *prox;}Ponto;

Ponto *geraPontos(int);
float calculaDistancia(Ponto, Ponto);
void *mallocSafe (size_t);

int main(int argc, char* argv[])
{/*Procurar o ponto P mais proximo do ultimo elemento do grafo, ver se tem algum outro ponto do grafo
   que eh mais proximo de P, e se tiver, ligar P com ele*/
   int N;
   float candMenorDist, menor, maiorMenores;
   Ponto *cabPontos, *cabGrafo, *novoPontoGrafo, *i, *j, *k,*aux;
   cabGrafo = mallocSafe(sizeof(*cabPontos));

   N = atoi(argv[1]);
   cabPontos = geraPontos(N);

   menor = 1000;
   maiorMenores = -1;

   aux = cabPontos->prox;
   cabPontos->prox = cabPontos->prox->prox;
   cabPontos->prox->prox->ant = cabPontos;

   aux->prox = NULL;
   aux->ant = cabGrafo;
   cabGrafo->prox = aux;
   cabGrafo->ant = NULL;


    for(i = cabGrafo->prox; i != NULL; i = i->prox)
    {
       for(j = cabPontos->prox; j != NULL; j = j->prox)
       {
          candMenorDist = calculaDistancia(*i,*j);
          if(candMenorDist < menor)
          {
            menor = candMenorDist;
            novoPontoGrafo = j;
          }
       }
       for(k = cabGrafo->prox; k != NULL; k = k->prox)
       {
          candMenorDist = calculaDistancia(*k,*novoPontoGrafo);
          if(candMenorDist < menor)menor = candMenorDist;
       }

       if(novoPontoGrafo->prox != NULL)novoPontoGrafo->prox->ant = novoPontoGrafo->ant;
       novoPontoGrafo->ant->prox = novoPontoGrafo->prox;

       i->prox = novoPontoGrafo;
       novoPontoGrafo->ant = i;
       novoPontoGrafo->prox = NULL;

       if(menor > maiorMenores)maiorMenores = menor;
    }
    printf("D = %f\n", maiorMenores);

   return 0;
}

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
