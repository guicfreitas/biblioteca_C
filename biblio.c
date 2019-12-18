#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//possui a matricula do tipo int e um ponteiro para a proxima matricula da fila
typedef struct matricula Matricula;

//possui dois ponterios que apontam pro inicio e pro fim da fila
typedef struct espera Espera;

//possui o numero de exemplares no momento do tipo int, uma dimensao da pilha do tipo int e um array para um vetor de exemplares
typedef struct exemplares Exemplares;

//possui todas as informacoes do livro, incluindo dois ponterios para duas estruturas de dados a fila e a pilha
typedef struct livro Livro;

//possui um tamanho do tipo int e dois ponteiro um para o inicio e outra para o fim da lista de livros
typedef struct lista ListaLivro;

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
  char titulo[150];
  int qtdExemplares;
  Livro* prox;
  Exemplares* pilhaExemplares;
  Espera* filaEspera;
};



struct lista {
  int tamanho;
  Livro* inicio;
  Livro* fim;

};

//metodos para fila de espera
// metodo para alocar dinamicamente memoria para struct de fila de espera, retorna um ponteiro do tipo Espera
Espera* criarEspera();

// metodo para inserir uma matricula dos alunos na fila
void inserirEspera(Espera* fila, int matricula);

//metodo para retirar uma matricula que foi inserida na fila tem como retorno a propria matricula
int retirarEspera(Espera* fila);

//metodo de verificacao se a fila esta vazia retorna 1 se estiver vazia e 0 se estiver populada
int esperaVazia(Espera* fila);

//metodo para liberar a memoria alocada pela fila
void liberarEspera(Espera* fila);

//metodo para imprimir o estado atual da fila de espera
void imprimirEspera(Espera* fila);


//metodos para pilha de exemplares
// metodo para alocar dinamicamente memoria para struct de pilha de exemplares, retorna um ponteiro do tipo Exemplares
Exemplares* criarExemplares(int qtdExemplares);

// metodo para empilhar um livro
void pushExemplar(Exemplares* pilha, int exemplares);

// metodo para desimpilhar um livro tem como retorno o numero desempilhado que corresponde a qtd de livros na pilha
int popExemplar(Exemplares* pilha);

//metodo de verificacao se a pilha esta vazia retorna 1 se estiver vazia e 0 se estiver populada
int exemplarVazia(Exemplares* pilha);

//metodo para liberar a memoria alocada pela pilha
void liberarExemplares(Exemplares* pilha);

//metodo para imprimir o estado atual da pilha de exemplares
void imprimirExemplares(Exemplares* pilha);




//metodos para lista de livros
// metodo para alocar dinamicamente memoria para struct de uma struct de lista, retorna um ponteiro do tipo Livros
ListaLivro* criarListaLivro(int tamanho);

//metodo para a insersao ordenada de um livro, dentro de cada livro eh chamada a funcao de criacao de
// pilha de exemplares e fila de espera, eh registrado tambem todas as informacoes necessarias
void inserirLivro_Ordenado(ListaLivro* livros, int anoPublicaco, char autor[], char titulo[], int qtdExemplares);

// metodo para a busca de um livro por um array de char passado por parametro que corresponde ao titulo do livro
// retorna um ponteiro de um no do tipo livro
Livro* buscaLivro(ListaLivro* livros, char titulo[]);

//metodo para liberacao da memoria alocada, tanto das listas quanto das filas
void liberarListaLivro(ListaLivro* livros);

//metodo para impressao do estado atual da lista do livro, informando:
//ano,titulo,autor,quantidade de exemplares presentes e a quantidade de matriculas e as respectivas matriculas
void imprimirListaLivro(ListaLivro* livros);

//metodo que converte um caracter passado por parametro em minuscula
int toLower(char letra);

//metodo para trocar um no por outro no na lista
void troca(ListaLivro* livros, Livro* livro1,Livro* livro2,Livro* anterior);

//metodo para baseado em bubbleSort para ordenacao de livros com ano igual, a partir do autor do livro
void ordenacaoPorNome(ListaLivro* livros);


//metodos para emprestar e devolver livros
//metodo para emprestar livros, se a pilha tiver populada nada acontece,
// porem se estiver vazia coloca a matriucla do aluno na fila de espera
void emprestarLivro(ListaLivro* livros, int  matricula, char titulo[]);

//metodo para devolver um livro emprestado, se a pilha tiver vazia e tiver alguem na fila ele retira a matricula da fila,
//se a fila estiver vazia, faz um push na pilha de livro
void devolverLivro(ListaLivro* livros, char* titulo);


///////////////////////////////////////////////// IMPLEMENTACAO ///////////////////////////////////////////////


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
  lista->fim = NULL;

  return lista;
}
int toLower(char letra){
  int result=0;
  if(letra>=65 && letra < 97){
      result=letra+32;
      return result;
  }else{
    result = letra;
    return result;
  }
}
void troca(ListaLivro* livros, Livro* livro1,Livro* livro2,Livro* anterior){
  if(livro1==livros->inicio){
    livro1->prox=livro2->prox;
    livro2->prox = livro1;
    livros->inicio=livro2;
  }else if(livro2->prox==NULL){
    anterior->prox=livro2;
    livro2->prox=livro1;
    livro1->prox=NULL;
    livros->fim = livro1;
  }else{
    anterior->prox=livro2;
    livro1->prox = livro2->prox;
    livro2->prox = livro1;
  }
}
void ordenacaoPorNome(ListaLivro* livros){
  char letraAnalise1,letraAnalise2;
  int letraToInt1,letraToInt2,cont,cont2=0,contLetra=0;
  Livro* atual = livros->inicio;
  Livro* anterior = NULL;

  for(cont=0;cont<livros->tamanho;cont++){
		for(atual=livros->inicio;atual!=NULL;){
      contLetra=0;
      if(atual->prox!=NULL && atual->anoPublicaco == atual->prox->anoPublicaco){

        letraToInt1=toLower(atual->autor[contLetra]);
        letraToInt2=toLower(atual->prox->autor[contLetra]);
        if(letraToInt1 > letraToInt2){
          troca(livros,atual,atual->prox,anterior);

        }else if(letraToInt1 == letraToInt2){
          contLetra++;
            letraToInt1=toLower(atual->autor[contLetra]);
            letraToInt2=toLower(atual->prox->autor[contLetra]);
          while(letraToInt1==letraToInt2){

            letraToInt1=toLower(atual->autor[contLetra]);
            letraToInt2=toLower(atual->prox->autor[contLetra]);
            contLetra++;

          }
          troca(livros,atual,atual->prox,anterior);

        }
      }
      anterior = atual;
      atual=atual->prox;
      cont2++;
		}
    cont2=0;
	}
}
void inserirLivro_Ordenado(ListaLivro* livros, int anoPublicaco, char autor[], char titulo[], int qtdExemplares){
  int cont,contLista=0;
  Livro* novoLivro = (Livro*) malloc(sizeof(Livro));

  novoLivro->anoPublicaco = anoPublicaco;
  novoLivro->qtdExemplares = qtdExemplares;

  Livro* atual = livros->inicio;
  Livro* anterior = NULL;

  if(livros->inicio==NULL){
    livros->inicio = novoLivro;
    novoLivro->prox = NULL;
  }else{
    if(livros->tamanho == 1){
      if(anoPublicaco >= livros->inicio-> anoPublicaco){
        livros->inicio->prox = novoLivro;
        novoLivro->prox = NULL;
      }else{
        novoLivro->prox = livros->inicio;
        livros->inicio->prox = NULL;
        livros->inicio=novoLivro;
      }
    }else{
      while(atual!=NULL && atual->anoPublicaco <= anoPublicaco){
        anterior = atual;
        atual = atual->prox;
        contLista++;
      }

      if(anterior==NULL){
        novoLivro->prox=livros->inicio;
        livros->inicio=novoLivro;
      }else{
         anterior->prox = novoLivro;
         novoLivro->prox = atual;
      }
    }
  }

  strcpy(novoLivro->autor,autor);
  strcpy(novoLivro->titulo,titulo);
  novoLivro->filaEspera = criarEspera();
  Exemplares* pilhaExemp = criarExemplares(qtdExemplares);
  for(cont=1;cont<=qtdExemplares;cont++){
    pushExemplar(pilhaExemp,cont);
  }
  novoLivro->pilhaExemplares = pilhaExemp;
  livros->tamanho=livros->tamanho+1;


}


Livro* buscaLivro(ListaLivro* livros, char titulo[]){
  int cont=0;
  Livro* atual = livros->inicio;
  if(atual->prox==NULL){
    if(strcmp(titulo,atual->titulo)==0){
      return atual;
    }
  }

  while(atual!=NULL){
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

    
    liberarEspera(atual->filaEspera);
    liberarExemplares(atual->pilhaExemplares);
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
		if(esperaVazia(result->filaEspera)==1){ 
      	pushExemplar(result->pilhaExemplares,((result->pilhaExemplares->vetExemplares[result->pilhaExemplares->numExemplares-1])+1));
		}else{
			retirarEspera(result->filaEspera);
		}    
	}
}

void imprimirEspera(Espera* fila){
  if(esperaVazia(fila)==1){
    printf("fila vazia\n");
  }else{
    Matricula* atual=fila->inicio;
    printf("%d",atual->matricula);
    atual=atual->prox;
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


//////////////////////////////////////////// MAIN /////////////////////////////////////////////////////
int main(){
  int qtdLivros,cont,ano,qtdExemplares,matricula;
  char casoLivro;
  //char* autor = (char*) malloc(100*sizeof(char));
  //char* titulo = (char*) malloc(150*sizeof(char));

  char autor[100];
  char titulo[150];
  char tituloConsulta[150];

  //char* tituloConsulta = (char*) malloc(150*sizeof(char));

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

  ordenacaoPorNome(livros);
  //imprimirListaLivro(livros);

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
  liberarListaLivro(livros);
  return 0;
}
