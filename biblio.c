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
