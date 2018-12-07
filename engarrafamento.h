#include <stdio.h>
#include <stdlib.h>

typedef struct CarroEN{
    char tipov;
    int nveiculo;
    int origem;
    int instante;
    int dfinal;
    char estacionamento;
    int testacionamento;
    struct CarroEN *prox;
}CarroEN;

typedef struct Engarrafamento{
	struct CarroEN *inicio;
    struct CarroEN *fim;
}Engarrafamento;

void iniciarEngarrafamento(Engarrafamento* f){
    f->inicio=NULL;
    f->fim=NULL;
}

void iniciarCarro(Carro* P){
	P->tipov=' ';
	P->nveiculo=0;
	P->origem=0;
	P->instante=0;
	P->dfinal=0;
	P->estacionamento=' ';
	P->testacionamento=0;
}

void entrarEngarrafamento(Engarrafamento* f,Carro c){
     CarroEN* novo;
     novo = (CarroEN*) malloc(sizeof(CarroEN));

    if(novo == NULL){
        printf("\nMemoria Insufiente");
        printf("\n\n");
		system("pause");
		system("cls");
        return; 
    }
    novo->tipov=c.tipov;
    novo->nveiculo=c.nveiculo;
    novo->origem=c.origem;
    novo->instante=c.instante;
    novo->dfinal=c.dfinal;
    novo->estacionamento=c.estacionamento;
    novo->testacionamento=c.testacionamento;
    
    novo->prox=NULL;

  	if(f->inicio==NULL){
        f->inicio=novo;
	}else{
       	f->fim->prox= novo; 
    }
 	f->fim=novo;
}

Carro sairEngarrafamento(Engarrafamento* P){
	Carro C;
	iniciarCarro(&C);
	if(P->inicio==NULL){
		printf("\nFila Vazia");
		
	}else{
		C.tipov=P->inicio->tipov;
        C.nveiculo=P->inicio->nveiculo;
        C.origem=P->inicio->origem;
        C.instante=P->inicio->instante;
        C.dfinal=P->inicio->dfinal;
        C.estacionamento=P->inicio->estacionamento;
        C.testacionamento=P->inicio->testacionamento;
        
		CarroEN *aux=P->inicio;
		P->inicio=P->inicio->prox;
		if(P->inicio==NULL){
			P->fim=NULL;
		}
		free(aux);
	}
	return C;
}

void verEngarrafamento(Engarrafamento* f){
	if(f->inicio==NULL){
		printf("\nFila Vazia");
		return;
	}
	
	CarroEN* atual=f->inicio;
	int tamanho=0;
	
	while(atual!=NULL){
		tamanho++;
		atual=atual->prox;
	}
	printf("\nTamanho do Engarrafamento: %d\n",tamanho);
	
	atual=f->inicio;
	while(atual!=NULL){
		printf("Tipo do veiculo: %c \n",atual->tipov);
		printf("Numero do veiculo: %d \n",atual->nveiculo);
		printf("Origem: %d \n",atual->origem);
		printf("Instante: %d \n",atual->instante);
		printf("Destino Final: %d \n",atual->dfinal);
		printf("Estacionamento: %c \n",atual->estacionamento);
		printf("Tempo de estacionamento: %d \n",atual->testacionamento);
		printf("\n\n");
		atual=atual->prox;
	}
}

void atualizarEngarrafamento(Engarrafamento* f){
	CarroEN* atual;
	CarroEN* aux;
	CarroEN* anterior;
	atual=f->inicio;
	
	while(atual!=NULL){
		if(atual->tipov=='C'){
			anterior=atual;
			
			while(anterior->prox->tipov=='A' || anterior==NULL){
				if(anterior==NULL){
					return;
				}
				if(anterior->prox->tipov=='A'){
					aux=anterior->prox;
					anterior->prox=aux->prox;
					aux->prox=f->inicio;
					f->inicio=aux;
					atual=f->inicio;
					break;
				}
				anterior=anterior->prox;
			}
		}
		atual=atual->prox;
	}
}
