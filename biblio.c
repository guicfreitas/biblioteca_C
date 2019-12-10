#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
void imprimirEspera(Espera* fila);


//metodos para pilha de exemplares
Exemplares* criarExemplares(int qtdExemplares);
void pushExemplar(Exemplares* pilha, int exemplares);
int popExemplar(Exemplares* pilha);
int exemplarVazia(Exemplares* pilha);
void liberarExemplares(Exemplares* pilha);
void imprimirExemplares(Exemplares* pilha);




//metodos para lista de livros
ListaLivro* criarListaLivro(int tamanho);
void inserirLivro_Ordenado(ListaLivro* livros, int anoPublicaco, char* autor, char* titulo, int qtdExemplares);
Livro* buscaLivro(ListaLivro* livros, char* titulo);
void liberarListaLivro(ListaLivro* livros);
void imprimirListaLivro(ListaLivro* livros);


//metodos para emprestar e devolver livros
void emprestarLivro(ListaLivro* livros, int  matricula, char* titulo);
void devolverLivro(ListaLivro* livros, char* titulo);
///////////////////////////////////////////////// IMPLEMENTACAO ///////////////////////////////////////////////


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
  char* autor;
  char* titulo;
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
    return 1;
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

Exemplares* criarExemplares(int qtdExemplares){
  Exemplares* pilha = (Exemplares*) malloc(sizeof(Exemplares));


  pilha->numExemplares = 0;
  pilha->dim = qtdExemplares;
  pilha->vetExemplares = (int*) calloc(qtdExemplares,sizeof(int));

  return pilha;

}
void pushExemplar(Exemplares* pilha, int exemplares){

  pilha->vetExemplares[pilha->numExemplares] = exemplares;
  pilha->numExemplares = pilha->numExemplares + 1;

}

int popExemplar(Exemplares* pilha){
  int desempilha;
  if(exemplarVazia(pilha)!=1){

    desempilha = pilha->vetExemplares[pilha->numExemplares-1];
    pilha->numExemplares = pilha->numExemplares - 1;
    return desempilha;

  }else{

    return -1;

  }
}
int exemplarVazia(Exemplares* pilha){
  if(pilha->numExemplares == 0){
    return 1;
  }else{
    return 0;
  }
}
void liberarExemplares(Exemplares* pilha){
  free(pilha->vetExemplares);
  free(pilha);
}

ListaLivro* criarListaLivro(int tamanho){
  ListaLivro*  lista = (ListaLivro*) malloc(sizeof(ListaLivro));

  lista->tamanho = 0;
  lista->inicio = NULL;

  return lista;
}
void inserirLivro_Ordenado(ListaLivro* livros, int anoPublicaco, char* autor, char* titulo, int qtdExemplares){
  int cont,contLista=0;
  Livro* novoLivro = (Livro*) malloc(sizeof(Livro*));

  char* autorTemp = (char*) malloc(100*sizeof(char));
  char* tituloTemp = (char*) malloc(150*sizeof(char));

  novoLivro->anoPublicaco = anoPublicaco;
  novoLivro->qtdExemplares = qtdExemplares;

  Livro* atual = livros->inicio;
  Livro* anterior = NULL;

  if(livros->inicio==NULL){
    livros->inicio = novoLivro;
    novoLivro->prox = NULL;
  }else{
    if(livros->tamanho == 1){
      if(anoPublicaco > livros->inicio-> anoPublicaco){
        livros->inicio->prox = novoLivro;
        novoLivro->prox = NULL;
      }else{
        novoLivro->prox = livros->inicio;
      }
    }else{
      while(contLista < livros->tamanho && atual->anoPublicaco < anoPublicaco){
        anterior = atual;
        atual = atual->prox;
        contLista++;
      }

      anterior->prox = novoLivro;
      novoLivro->prox = atual;
    }
  }

  strcpy(autorTemp,autor);
  strcpy(tituloTemp,titulo);

  novoLivro->autor = autorTemp;
  novoLivro->titulo = tituloTemp;
  novoLivro->filaEspera = criarEspera();
  Exemplares* pilhaExemp = criarExemplares(qtdExemplares);
  for(cont=1;cont<=qtdExemplares;cont++){
    pushExemplar(pilhaExemp,cont);
  }
  novoLivro->pilhaExemplares = pilhaExemp;
  livros->tamanho=livros->tamanho+1;


}

Livro* buscaLivro(ListaLivro* livros, char* titulo){
  int cont;
  Livro* atual = livros->inicio;
  if(atual->prox==NULL){
    if(strcmp(titulo,atual->titulo)==0){
      return atual;
    }
  }

  while(cont < livros->tamanho){
    if(strcmp(titulo,atual->titulo)==0){
      return atual;
    }
      atual= atual->prox;
  }
  return NULL;

}
void liberarListaLivro(ListaLivro* livros){
  Livro* atual = livros->inicio;
  Livro* atualTemp;

  while(atual->prox != NULL){

    atualTemp=atual;
    atual = atual->prox;
    free(atualTemp);

  }

  free(livros);
}

void imprimirListaLivro(ListaLivro* livros){
  Livro* atual=livros->inicio;
  int cont;

  for(cont=0;cont<livros->tamanho;cont++){
    printf("%d\n",atual->anoPublicaco);
    printf("%s\n",atual->autor);
    printf("%s\n",atual->titulo);
    imprimirExemplares(atual->pilhaExemplares);
    imprimirEspera(atual->filaEspera);
    atual=atual->prox;
  }

}

void emprestarLivro(ListaLivro* livros, int  matricula, char* titulo){
  Livro* result = buscaLivro(livros,titulo);

    if(result != NULL){
        if(exemplarVazia(result->pilhaExemplares)==1){
          inserirEspera(result->filaEspera,matricula);
        }else{
          if(esperaVazia(result->filaEspera)==1){
            popExemplar(result->pilhaExemplares);
          }else{
            retirarEspera(result->filaEspera);
            inserirEspera(result->filaEspera,matricula);
          }
        }
    }

}
void devolverLivro(ListaLivro* livros, char* titulo){
    Livro* result = buscaLivro(livros,titulo);
    if(result!=NULL){
      pushExemplar(result->pilhaExemplares,((result->pilhaExemplares->vetExemplares[result->pilhaExemplares->numExemplares-1])+1));
    }
}

void imprimirEspera(Espera* fila){
  if(esperaVazia(fila)==1){
    printf("fila vazia\n");
  }else{
    Matricula* atual=fila->inicio;
    printf("%d",atual->matricula);

    for(atual;atual!=NULL;atual=atual->prox){
        printf(",%d",atual->matricula);
    }
    printf("\n");
  }
}
void imprimirExemplares(Exemplares* pilha){
  if(exemplarVazia(pilha)==1){
    printf("pilha vazia\n");
  }else{
    printf("%d\n",pilha->vetExemplares[pilha->numExemplares-1]);
  }
}
int main(){
  int qtdLivros,cont,ano,qtdExemplares,matricula;
  char casoLivro;
  char* autor = (char*) malloc(100*sizeof(char));
  char* titulo = (char*) malloc(150*sizeof(char));
  char* tituloConsulta = (char*) malloc(150*sizeof(char));

  //leitura da quantidade de livros
  scanf("%d",&qtdLivros);
  ListaLivro* livros = criarListaLivro(qtdLivros);

  for(cont=0;cont<qtdLivros;cont++){

    scanf("%d",&ano);
    scanf("%s",autor);
    scanf("%s",titulo);
    scanf("%d",&qtdExemplares);

    inserirLivro_Ordenado(livros,ano,autor,titulo,qtdExemplares);

  }
  imprimirListaLivro(livros);

  while(scanf("%d",&matricula)!=EOF){
    scanf("%s",tituloConsulta);
    scanf(" %c",&casoLivro);

    switch (casoLivro) {
      case 'E':
        emprestarLivro(livros,matricula,tituloConsulta);
        break;
      case 'D':
        devolverLivro(livros,tituloConsulta);
        break;
    }
  }

  imprimirListaLivro(livros);
  return 0;
}
