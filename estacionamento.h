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
} CarroES;

typedef struct {
    CarroES vet[Z];
    int topo;
} Estacionamento;

void inicializarES(Estacionamento *P){
	P->topo=0;
    int i;
    for(i = 0; i < Z; i++){
        P->vet[i].tipov=' ';
		P->vet[i].nveiculo=0;
		P->vet[i].origem=0;
		P->vet[i].instante=0;
		P->vet[i].dfinal=0;
		P->vet[i].estacionamento=' ';
		P->vet[i].testacionamento=0;
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
  		C.nveiculo=0;
  		C.origem=0;
		C.instante=0;
		C.dfinal=0;
		C.estacionamento=' ';
  		C.testacionamento=0;	
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
  		P->vet[P->topo].nveiculo=0;
  		P->vet[P->topo].origem=0;
		P->vet[P->topo].instante=0;
		P->vet[P->topo].dfinal=0;
		P->vet[P->topo].estacionamento=' ';
  		P->vet[P->topo].testacionamento=0;
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

int ControleEntradaES(Estacionamento* e,Carro* a,Carro* b){
//obs: carro A é da entrada 2 e B da entrada 1	
	if(e->topo==Z-1){
		printf("estacionamento lotado");
		return 0;
	}if(e->topo==Z-2){
		if(a->estacionamento=='S'){
		  	  *a=empilhar(e,*a);
		  	  return 1;
		}else{
			if(b->estacionamento=='S'){
 	  	  	  *b=empilhar(e,*b);
 	  	  	  return 2;
			}
			return 0;
		}	
	}if(e->topo<Z-2){
		if(a->estacionamento=='S'&& b->estacionamento=='S'){
			if(a->origem==2){
		  	  *a=empilhar(e,*a);
		  	  *b=empilhar(e,*b);
		  	  return 3;
			}else{
		  	  *b=empilhar(e,*b);
		  	  *a=empilhar(e,*a);
		  	  return 3;
			}
		}else{           
			if(a->estacionamento=='S'){
		  	  *a=empilhar(e,*a);
		  	  return 1;
			}
			if(b->estacionamento=='S'){
 	  	  	  *b=empilhar(e,*b);
 	  	  	  return 2;
			}
		}	
	}
}

Carro ControleSaidaES(Estacionamento* e){
	Carro C;
 	if(e->vet[e->topo].testacionamento<=0){
 		C=desempilhar(e);
		 return C; 
	}else{
	 	C.tipov=' ';
  		C.nveiculo=0;
  		C.origem=0;
		C.instante=0;
		C.dfinal=0;
		C.estacionamento=' ';
  		C.testacionamento=0;
	}
	 return C;
}

void atualizarEstacionamento(Estacionamento* e){
	int i;
	for(i=0;i<e->topo;i++){
		e->vet[i].testacionamento--;
	}
}
