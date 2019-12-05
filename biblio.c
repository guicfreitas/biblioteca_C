#include <stdio.h>
#include <stdlib.h>


typedef struct matricula Matricula;
typedef struct espera Espera;
typedef struct exemplares Exemplares;
typedef struct livro Livro;
typedef struct lista ListaLivro;

//metodos para fila de espera
Espera* criarEspera();
void inserirEspera(Espera* fila, int matricula);
int retirarEspera(Espera* fila);
int esperaVazia(Espera* fila);
void liberarEspera(Espera* fila);



//metodos para pilha de exemplares
Exemplares* criarExemplares();
void pushExemplar(Exemplares* pilha, int exemplares);
int popExemplar(Exemplares* pilha);
int exemplarVazia(Exemplares* pilha);
void liberarExemplares(Exemplares* pilha);


//metodos para lista de livros
ListaLivro* criarListaLivro();
void inserirLivro_Ordenado(ListaLivro* livros, int anoPublicaco, char* autor, char* titulo, int qtdExemplares);
Livro* buscaLivro(ListaLivro* livros, char* titulo);
void liberarListaLivro(ListaLivro* livros);



struct matricula{
  int matricula;
  Matricula* prox;
};
struct espera{
  Matricula* inicio;
  Matricula* fim;
};



struct exemplares{
    int numExemplares;
    int dim;
    int* vetExemplares;
};



struct livro{
  int anoPublicaco;
  char autor[100];
  char titulo[100];
  int qtdExemplares;
  Livro* prox;
  Exemplares* pilhaExemplares;
  Espera* filaEspera;
};



struct lista {
  int tamanho;
  Livro* inicio;

};



Espera* criarEspera(){
  Espera* fila = (Espera*) malloc(sizeof(Espera));

  fila->inicio = NULL;
  fila->fim = NULL;

  return fila;
}

void inserirEspera(Espera* fila, int matricula){
  Matricula* novoMat = (Matricula*) malloc(sizeof(Matricula));
  novoMat->matricula = matricula;

  if(fila->inicio == NULL){

    fila->inicio = novoMat;
    fila->fim = novoMat;
    novoMat->prox = NULL;

  }else{

    fila->fim->prox = novoMat;
    novoMat->prox = NULL;
    fila->fim = novoMat;


  }

}
int retirarEspera(Espera* fila){

  Matricula* matTemp;

  if(esperaVazia(fila)!=1){

    matTemp = fila->inicio;
    int matRetirada = matTemp->matricula;
    fila->inicio = fila->inicio->prox;
    free(matTemp);

    return matRetirada;

  }else{

    return -1;

  }
}
int esperaVazia(Espera* fila){

  if(fila->inicio==NULL){
    rerturn 1;
  }else{
    return  0;
  }

}
void liberarEspera(Espera* fila){
  Matricula* atual = fila->inicio;
  Matricula* atualTemp;
  while(atual->prox != NULL){

    atualTemp=atual;
    atual = atual->prox;
    free(atualTemp);

  }

  free(fila);
}
