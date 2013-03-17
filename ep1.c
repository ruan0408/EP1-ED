#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Ponto.h"

#define FALSE 0
#define TRUE 1
#define DEFAULT 13

int main(int argc, char* argv[])
{/*Procurar o ponto P mais proximo do ultimo elemento do grafo, ver se tem algum outro ponto do grafo
   que eh mais proximo de P, e se tiver, ligar P com ele*/

   int N,M,v,V,s, cont;
   float candMenorDist, menor, maiorMenores, d, somatoriaQuadrados;
   Ponto *cabPontos, *cabGrafo, *novoPontoGrafo, *i, *j, *k,*aux;
   cabGrafo = mallocSafe(sizeof(*cabPontos));

   M=1; d=-1; v=FALSE; V=FALSE; s=DEFAULT;

   for(i=0; i<argc; i++)
   {
      if(argv[i][0] == '-' && argv[i][1] == 'N')
      {
         N = atoi(&argv[i][2]);
      }
      if(argv[i][0] == '-' && argv[i][1] == 'M')
      {
         M = atoi(argv[i]+2);
      }
      if(argv[i][0] == '-' && argv[i][1] == 'd')
      {
         d = atof(argv[i]+2);
      }
      if(argv[i][0] == '-' && argv[i][1] == 'v')
      {
         v = TRUE;
      }
      if(argv[i][0] == '-' && argv[i][1] == 'V')
      {
         V = TRUE;
      }
      if(argv[i][0] == '-' && argv[i][1] == 's')
      {
         s = atoi(argv[i]+2);
      }
   }
   srand(s);
   for(cont = 0; cont < M; cont++)
   {
      cabPontos = geraPontos(N);
      if(V == TRUE)
      {
         int cont2;
         Pontos *p;
         Pontos *pontos = mallocSafe(N*sizeof(*pontos));
         for(p = cabPontos->prox, cont2 = 0; cont2 < N; cont2++, p = p->prox)
            pontos[cont2] = *p;
      }

      menor = 1000;
      maiorMenores = -1;
      somatoriaQuadrados = 0;

      if(N==1)maiorMenores = 0;
      else
      {
         aux = cabPontos->prox;
         cabPontos->prox = cabPontos->prox->prox;
         aux->prox->ant = cabPontos;

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
          somatoriaQuadrados += maiorMenores*maiorMenores;
          printf("Densidade normalizada crítica = %f\n", somatoriaQuadrados*N/log(N));
      }
   }
   return 0;
}

void imprimePontos(Pontos *cab)
{
   Pontos *p;
   for(p=cab->prox; p!=NULL ; p = p->prox)
      printf("(%f, %f)\n", p->x, p->y);
}

