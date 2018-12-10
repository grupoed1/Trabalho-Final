#include <stdio.h>
#include <stdlib.h>
#include "via_2.h"

typedef struct CarroE{
    char tipov;
    int nveiculo;
    int origem;
    int instante;
    int dfinal;
    char estacionamento;
    int testacionamento;
    struct CarroE *prox;
}CarroE;

typedef struct Engarrafamento{
	struct CarroE *inicio;
    struct CarroE *fim;
}Engarrafamento;

void iniciarEngarrafamento(Engarrafamento* f){
    f->inicio=NULL;
    f->fim=NULL;
}

void iniciarCarro(Carro* P){
	P->tipov=' ';
	P->nveiculo=' ';
	P->origem=' ';
	P->instante=' ';
	P->dfinal=' ';
	P->estacionamento=' ';
	P->testacionamento=' ';
}

void entrarEngarrafamento(Engarrafamento* f,Carro c){
     CarroE* novo;
     novo = (CarroE*) malloc(sizeof(CarroE));

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

    printf("\nponto 1\n");   ////////////PONTO 1
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
        
		CarroE *aux=P->inicio;
		P->inicio=P->inicio->prox;
		if(P->inicio==NULL){
			P->fim=NULL;
		}
		free(aux);
	}
	printf("\nponto 2\n");      //////PONTO 2
	return C;
}

void verEngarrafamento(Engarrafamento* f){
	if(f->inicio==NULL){
		printf("\nFila Vazia");
		return;
	}
	
	CarroE* atual=f->inicio;
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
	CarroE* atual = (CarroE*) malloc(sizeof(CarroE));
	CarroE* aux = (CarroE*) malloc(sizeof(CarroE));
	CarroE* anterior = (CarroE*) malloc(sizeof(CarroE));
	atual=f->inicio;


	while(atual!=NULL){
		if(atual->tipov=='C'){
			anterior=atual;
			
			while(anterior==NULL || (anterior->prox != NULL && anterior->prox->tipov=='A')){
				if(anterior==NULL){
					return;
				}
				if(anterior->prox->tipov=='A'){
					aux=anterior->prox;
					anterior->prox=aux->prox;
					aux->prox=f->inicio;
					f->inicio=aux;
					atual=f->inicio;
					if (f->fim == aux)
						f->fim = anterior;
					break;
				}
				anterior=anterior->prox;
			}
		}
		atual=atual->prox;
	}
}
