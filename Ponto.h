typedef struct ponto{float x;
                       float y;
                       struct ponto *ant;
                       struct ponto *prox;}Ponto;

Ponto *geraPontos(int);
float calculaDistancia(Ponto, Ponto);
void *mallocSafe (size_t);
