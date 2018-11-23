#include <stdio.h>
#include <stdlib.h>
#define Z 15

typedef struct {
    char tipov;
    int nveiculo;
    int origem;
    int instante;
    int dfinal;
    char estacionamento;
    int testacionamento;
} Carro;

typedef struct {
    Carro vet[Z];
    int topo;
} Estacionamento;

void inicializar(Estacionamento *P){
	P->topo=0;
    int i;
    for(i = 0; i < Z; i++){
        P->vet[i].tipov=' ';
		P->vet[i].nveiculo=' ';
		P->vet[i].origem=' ';
		P->vet[i].instante=' ';
		P->vet[i].dfinal=' ';
		P->vet[i].estacionamento=' ';
		P->vet[i].testacionamento=' ';
	}
	
}

Carro empilhar(Estacionamento *P,Carro C){
    if(P->topo==Z-1){
        return C;
    }else{
    	if(P->topo==0){
        	P->vet[P->topo].tipov=C.tipov;
        	P->vet[P->topo].nveiculo=C.nveiculo;
        	P->vet[P->topo].origem=C.origem;
        	P->vet[P->topo].instante=C.instante;
        	P->vet[P->topo].dfinal=C.dfinal;
			P->vet[P->topo].estacionamento=C.estacionamento;
        	P->vet[P->topo].testacionamento=C.testacionamento;
		}else{
			P->topo++;
        	P->vet[P->topo].tipov=C.tipov;
        	P->vet[P->topo].nveiculo=C.nveiculo;
        	P->vet[P->topo].origem=C.origem;
        	P->vet[P->topo].instante=C.instante;
        	P->vet[P->topo].dfinal=C.dfinal;
			P->vet[P->topo].estacionamento=C.estacionamento;
        	P->vet[P->topo].testacionamento=C.testacionamento;
		}
		C.tipov=' ';
  		C.nveiculo=' ';
  		C.origem=' ';
		C.instante=' ';
		C.dfinal=' ';
		C.estacionamento=' ';
  		C.testacionamento=' ';	
  		return C;
    }
}

Carro desempilhar(Estacionamento *P) {
	Carro C;
    if(P->topo==0){
        printf("Estacionamento vazio!\n");
    }else{
    	C.tipov=P->vet[P->topo].tipov;
        C.nveiculo=P->vet[P->topo].nveiculo;
        C.origem=P->vet[P->topo].origem;
        C.instante=P->vet[P->topo].instante;
        C.dfinal=P->vet[P->topo].dfinal;
        C.estacionamento=P->vet[P->topo].estacionamento;
        C.testacionamento=P->vet[P->topo].testacionamento;
       
        P->vet[P->topo].tipov=' ';
  		P->vet[P->topo].nveiculo=' ';
  		P->vet[P->topo].origem=' ';
		P->vet[P->topo].instante=' ';
		P->vet[P->topo].dfinal=' ';
		P->vet[P->topo].estacionamento=' ';
  		P->vet[P->topo].testacionamento=' ';
		P->topo--;
    }
    return C;
}

void verEstacionamento(Estacionamento e){
	int i;
	printf("Numero de veiculos estacionados: %d",e.topo);
	for(i=0;i<e.topo;i++){
		printf("Tipo do veiculo: %c \n",e.vet[i].tipov);
		printf("Numero do veiculo: %d \n",e.vet[i].nveiculo);
		printf("Origem: %d \n",e.vet[i].origem);
		printf("Instante: %d \n",e.vet[i].instante);
		printf("Destino Final: %d \n",e.vet[i].dfinal);
		printf("Estacionamento: %c \n",e.vet[i].estacionamento);
		printf("Tempo de estacionamento: %d \n",e.vet[i].testacionamento);
		printf("\n\n");
	}	   	
}

void ControleEntradaE(Estacionamento* e,Carro* a,Carro* b){
	
	if(a->estacionamento=='S'&&b->estacionamento=='S'){
		if(a->origem==2){
		  *a=empilhar(e,*a);
		  *b=empilhar(e,*b);
		}else{
		  *b=empilhar(e,*b);
		  *a=empilhar(e,*a);
		}
	}else{
		if(a->tipov=='C'){
		  *a=empilhar(e,*a);
		}
		if(b->tipov=='C'){
          *a=empilhar(e,*a);
		}
	}
}

void ControleSaidaE(Estacionamento* e,Carro* a,Carro* b){
	
}
