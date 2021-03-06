#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Y 20

typedef struct {
    char tipov;
    int nveiculo;
    int origem;
    int instante;
    int dfinal;
    char estacionamento;
    int testacionamento;
} Carro;

typedef struct{
	char tipo;
	int instante;
	int duracao;
	int via;
	int faixa;
	int posicao;
} evento;

typedef struct{
	Carro Faixa[Y];
	int inicio;
	int fim;
} Via_2;

evento defeito_v2;
int Qtecarros(Via_2* x);

void inicializar(Via_2* x){
	int i;
	x->inicio = 0;
	x->fim = 0;
	
	for (i = 0; i <= Y - 1; i++){
		x->Faixa[i].tipov = ' ';
		x->Faixa[i].nveiculo = 0;
		x->Faixa[i].origem = 0;
		x->Faixa[i].instante = 0;
		x->Faixa[i].dfinal = 0;
		x->Faixa[i].estacionamento = ' ';
		x->Faixa[i].testacionamento = 0;
	}
}

bool isFull(Via_2* x){
	int i;
	for (i = 0; i < Y; i++){
		if (x->Faixa[i].tipov == ' '){
			return false;
		}
	}
	return true;
}

bool isEmpty(Via_2* x){
	if (x->inicio == x->fim)
		return true;
	else
		return false;
}

void Enfileirar(Via_2* x, Carro c, int faixa){
	if (isFull(x))
		printf("A faixa esta cheia\n");
	else{
		if (defeito_v2.faixa != faixa || defeito_v2.posicao != Y - 1){
			x->Faixa[Y - 1] = c;
		}
		else if (defeito_v2.posicao == Y - 1)
			x->Faixa[Y - 2] = c;
		x->fim = Y - 1;
	}
}

Carro Desenfileirar(Via_2* x, int faixa){
	int i;
	Carro aux;
	aux.tipov=' ';
	aux.nveiculo= 0;
	aux.origem= 0;
	aux.instante= 0;
	aux.dfinal= 0;
	aux.estacionamento=' ';
	aux.testacionamento= 0;
	if (Qtecarros(x) == 0){
		printf("A faixa esta vazia\n");
	}
	else{
		if (defeito_v2.faixa != faixa || x->Faixa[defeito_v2.posicao].origem == 0){
			aux = x->Faixa[x->inicio];
			for (i = 0; i < x->fim; i++){
				x->Faixa[i].tipov = x->Faixa[i + 1].tipov;
				x->Faixa[i].nveiculo = x->Faixa[i + 1].nveiculo;
				x->Faixa[i].origem = x->Faixa[i + 1].origem;
				x->Faixa[i].instante = x->Faixa[i + 1].instante;
				x->Faixa[i].dfinal = x->Faixa[i + 1].dfinal;
				x->Faixa[i].estacionamento = x->Faixa[i + 1].estacionamento;
				x->Faixa[i].testacionamento = x->Faixa[i + 1].testacionamento;
			}
			x->Faixa[Y - 1].tipov = ' ';
			x->Faixa[Y - 1].nveiculo = 0;
			x->Faixa[Y - 1].origem = 0;
			x->Faixa[Y - 1].instante = 0;
			x->Faixa[Y - 1].dfinal = 0;
			x->Faixa[Y - 1].estacionamento = ' ';
			x->Faixa[Y - 1].testacionamento = 0;
		}
		else{
			if (defeito_v2.posicao == x->inicio){
				aux = x->Faixa[x->inicio + 1];
				for (i = 1; i < x->fim; i++){
					x->Faixa[i].tipov = x->Faixa[i + 1].tipov;
					x->Faixa[i].nveiculo = x->Faixa[i + 1].nveiculo;
					x->Faixa[i].origem = x->Faixa[i + 1].origem;
					x->Faixa[i].instante = x->Faixa[i + 1].instante;
					x->Faixa[i].dfinal = x->Faixa[i + 1].dfinal;
					x->Faixa[i].estacionamento = x->Faixa[i + 1].estacionamento;
					x->Faixa[i].testacionamento = x->Faixa[i + 1].testacionamento;
				}
				x->Faixa[Y - 1].tipov = ' ';
				x->Faixa[Y - 1].nveiculo = 0;
				x->Faixa[Y - 1].origem = 0;
				x->Faixa[Y - 1].instante = 0;
				x->Faixa[Y - 1].dfinal = 0;
				x->Faixa[Y - 1].estacionamento = ' ';
				x->Faixa[Y - 1].testacionamento = 0;
			}
			else{
				aux = x->Faixa[x->inicio];
				for (i = 0; i < x->fim; i++){
					if (defeito_v2.posicao != i + 1){
						x->Faixa[i].tipov = x->Faixa[i + 1].tipov;
						x->Faixa[i].nveiculo = x->Faixa[i + 1].nveiculo;
						x->Faixa[i].origem = x->Faixa[i + 1].origem;
						x->Faixa[i].instante = x->Faixa[i + 1].instante;
						x->Faixa[i].dfinal = x->Faixa[i + 1].dfinal;
						x->Faixa[i].estacionamento = x->Faixa[i + 1].estacionamento;
						x->Faixa[i].testacionamento = x->Faixa[i + 1].testacionamento;
					}
					else{
						if (i != Y - 2){
							x->Faixa[i].tipov = x->Faixa[i + 2].tipov;
							x->Faixa[i].nveiculo = x->Faixa[i + 2].nveiculo;
							x->Faixa[i].origem = x->Faixa[i + 2].origem;
							x->Faixa[i].instante = x->Faixa[i + 2].instante;
							x->Faixa[i].dfinal = x->Faixa[i + 2].dfinal;
							x->Faixa[i].estacionamento = x->Faixa[i + 2].estacionamento;
							x->Faixa[i].testacionamento = x->Faixa[i + 2].testacionamento;

							i++;
						}
						else{
							x->Faixa[Y - 2].tipov = ' ';
							x->Faixa[Y - 2].nveiculo = 0;
							x->Faixa[Y - 2].origem = 0;
							x->Faixa[Y - 2].instante = 0;
							x->Faixa[Y - 2].dfinal = 0;
							x->Faixa[Y - 2].estacionamento = ' ';
							x->Faixa[Y - 2].testacionamento = 0;
						}
						
					}
				}
				if (defeito_v2.posicao != Y - 1){
					x->Faixa[Y - 1].tipov = ' ';
					x->Faixa[Y - 1].nveiculo = 0;
					x->Faixa[Y - 1].origem = 0;
					x->Faixa[Y - 1].instante = 0;
					x->Faixa[Y - 1].dfinal = 0;
					x->Faixa[Y - 1].estacionamento = ' ';
					x->Faixa[Y - 1].testacionamento = 0;
				}
			}
		}
	}
	return aux;
}

int Qtecarros(Via_2* x){
	int i, l = 0;
	for (i = 0; i <= x->fim; i++){
		if (x->Faixa[i].origem != 0)
			l++;
	}
	return l;
}

void verFaixa(Via_2* x){
	int i, l;
	l = Qtecarros(x);
	printf("Numero de veiculos na faixa: %d", l);
	for(i = 0; i <= x->fim; i++){
		printf("Tipo do veiculo: %c \n",x->Faixa[i].tipov);
		printf("Numero do veiculo: %d \n",x->Faixa[i].nveiculo);
		printf("Origem: %d \n",x->Faixa[i].origem);
		printf("Instante: %d \n",x->Faixa[i].instante);
		printf("Destino Final: %d \n",x->Faixa[i].dfinal);
		printf("Estacionamento: %c \n",x->Faixa[i].estacionamento);
		printf("Tempo de estacionamento: %d \n",x->Faixa[i].testacionamento);
		printf("\n\n");
	}	   	
}
