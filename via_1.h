#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "engarrafamento.h"
#define MAX 40


typedef struct{
  Carro Faixa1[MAX]; //Leste - Oeste
  Carro Faixa2[MAX]; //Oeste - Leste
  int inicio;
  int fim;
}Via_1;

evento defeito_v1;
int flag = 0;

void inicializarVia_1(Via_1* x){
  x->inicio = 0;
  x->fim = 0;
  int i;
  for(i=0; i < MAX; i++){
    x->Faixa1[i].tipov = ' ';
    x->Faixa1[i].nveiculo = 0;
    x->Faixa1[i].origem = 0;
    x->Faixa1[i].instante = 0;
    x->Faixa1[i].dfinal = 0;
    x->Faixa1[i].estacionamento = ' ';
    x->Faixa1[i].testacionamento = 0;
    
    x->Faixa2[i].tipov = ' ';
    x->Faixa2[i].nveiculo = 0;
    x->Faixa2[i].origem = 0;
    x->Faixa2[i].instante = 0;
    x->Faixa2[i].dfinal = 0;
    x->Faixa2[i].estacionamento = ' ';
    x->Faixa2[i].testacionamento = 0;
  }
}

bool isFull1(Via_1* x, Carro faixa){
  int i;
  if(faixa.origem == 1){
    for (i = 0; i < MAX; i++){
      if (x->Faixa1[i].tipov == ' '){
        return false;
          }
    }
    return true;
  }else if(faixa.origem == 2){
    for (i = 0; i < MAX; i++){
      if (x->Faixa2[i].tipov == ' '){
        return false;
          }
    }
    return true;
  }
  return true;
  }

void inserirVia_1(Via_1* x, Carro veiculo){
  switch(veiculo.origem)
  {
    case 2: //sentido Leste - Oeste (FAIXA 1)
      if(veiculo.tipov == 'A' && x->Faixa1[20].tipov == ' '){ //Ambulancia no Hospital
        x->Faixa1[20] = veiculo;
      }else{
        if(isFull1(x, veiculo)){
          flag = 1;
          printf("\n Pista cheia!\n");
        }else{
          if (veiculo.tipov == 'C' && (defeito_v1.via != 1 || defeito_v1.faixa != 1 || defeito_v1.posicao != MAX - 1 || x->Faixa1[defeito_v1.posicao].nveiculo == 0))
            x->Faixa1[MAX-1] = veiculo;
          else if (defeito_v1.posicao == MAX - 1 && x->Faixa1[defeito_v1.posicao].nveiculo != 0)
            x->Faixa1[MAX-2] = veiculo;
        }
      }
      x->fim = MAX-1; //obs
      break;
    case 1: //Sentido Oeste - Leste (FAIXA 2)
      if(veiculo.tipov == 'A' && x->Faixa2[0].tipov == ' '){
        x->Faixa2[0] = veiculo;
      }else{
        if(isFull1(x, veiculo)){
          printf("\n Pista cheia!\n");
        }else{
          if (veiculo.tipov == 'C' && (defeito_v1.via != 1 || defeito_v1.faixa != 2 || defeito_v1.posicao != 0 || x->Faixa2[defeito_v1.posicao].nveiculo == 0))
            x->Faixa2[0] = veiculo;
          else if (defeito_v1.posicao == 0 && x->Faixa2[defeito_v1.posicao].nveiculo != 0)
            x->Faixa2[1] = veiculo;
        }
      }
      x->fim = MAX-1; //obs
      break;
  }
}

int verificarAmbulanciaFaixa1(int indice, Via_1* v){
  int i;
  for(i = indice ; i <= 20; i++){
    if(v->Faixa1[i].tipov == 'A'){
      return i;
    }
  }
  return -1;
}

int verificarAmbulanciaFaixa2(int indice, Via_1* v){
  int i;
  for(i = indice; i >=0; i--){
    if(v->Faixa2[i].tipov== 'A'){
      return i;
    }
  }
  return -1;
}

Carro* CicloVia_1(Via_1* x){
  int j = 0, k = 0;
  int amb1 = verificarAmbulanciaFaixa1(0, x);
  int amb2 = verificarAmbulanciaFaixa2(20, x);
  Carro aux[2];
  aux[0] = x->Faixa1[x->inicio];
  aux[1] = x->Faixa2[MAX-1];
  x->fim = MAX - 1;
    if(defeito_v1.faixa != 1 || x->Faixa1[defeito_v1.posicao].nveiculo == 0){
      while(amb1 >= 0){
        for(j = k; j <= amb1-3; j++){
          x->Faixa1[j] = x->Faixa1[j+1];
        }
        if(amb1-3 >= 0){
          x->Faixa1[amb1-3] = x->Faixa1[amb1];
        }else{
          x->Faixa1[amb1].tipov = ' ';
          x->Faixa1[amb1].nveiculo = 0;
          x->Faixa1[amb1].origem = 0;
          x->Faixa1[amb1].instante = 0;
          x->Faixa1[amb1].dfinal = 0;
          x->Faixa1[amb1].estacionamento = ' ';
          x->Faixa1[amb1].testacionamento = 0;
        }
        k = amb1;
        amb1 = verificarAmbulanciaFaixa1(amb1, x);
      }
      if (k > 0){
        for(j = k; j < MAX-1; j++){
            x->Faixa1[j] = x->Faixa1[j+1];
        }
      }else{
        for(j = 0; j < MAX-1; j++){
          x->Faixa1[j] = x->Faixa1[j+1];
        }
      }
      x->Faixa1[MAX - 1].tipov = ' ';
      x->Faixa1[MAX - 1].nveiculo = 0;
      x->Faixa1[MAX - 1].origem = 0;
      x->Faixa1[MAX - 1].instante = 0;
      x->Faixa1[MAX - 1].dfinal = 0;
      x->Faixa1[MAX - 1].estacionamento = ' ';
      x->Faixa1[MAX - 1].testacionamento = 0;
    }else{
      while (amb1 >= 0){
        for(j = k; j <= amb1-3; j++){
          if(defeito_v1.posicao == j && j-1 >= 0){
            x->Faixa1[j-1] = x->Faixa1[j+1];
          }else{
            if(defeito_v1.posicao == j && j-1 < 0){
              aux[0] = x->Faixa1[x->inicio + 1];
              x->Faixa1[j+1].tipov = ' ';
              x->Faixa1[j+1].nveiculo = 0;
              x->Faixa1[j+1].origem = 0;
              x->Faixa1[j+1].instante = 0;
              x->Faixa1[j+1].dfinal = 0;
              x->Faixa1[j+1].estacionamento = ' ';
              x->Faixa1[j+1].testacionamento = 0;
            }else{
            x->Faixa1[j] = x->Faixa1[j+1];
          }
          }
        }
        if(amb1-3 >= 0){
          x->Faixa1[amb1-3] = x->Faixa1[amb1];
        }else{
          x->Faixa1[amb1].tipov = ' ';
          x->Faixa1[amb1].nveiculo = 0;
          x->Faixa1[amb1].origem = 0;
          x->Faixa1[amb1].instante = 0;
          x->Faixa1[amb1].dfinal = 0;
          x->Faixa1[amb1].estacionamento = ' ';
          x->Faixa1[amb1].testacionamento = 0;
        }
        k = amb1;
        amb1 = verificarAmbulanciaFaixa1(amb1, x);
      }
      if (k > 0){
        for(j = k; j < MAX-1; j++){
          if(defeito_v1.posicao == j && j-1 >= 0){
            x->Faixa1[j-1] = x->Faixa1[j+1];
          }else{
            if(defeito_v1.posicao == j && j-1 < 0){
              aux[0] = x->Faixa1[x->inicio + 1];
              x->Faixa1[j+1].tipov = ' ';
              x->Faixa1[j+1].nveiculo = 0;
              x->Faixa1[j+1].origem = 0;
              x->Faixa1[j+1].instante = 0;
              x->Faixa1[j+1].dfinal = 0;
              x->Faixa1[j+1].estacionamento = ' ';
              x->Faixa1[j+1].testacionamento = 0;
            }else{
            x->Faixa1[j] = x->Faixa1[j+1];
            }
          }
        }
      }else{
        for(j = 0; j < MAX-1; j++){
          if(defeito_v1.posicao == j && j-1 >= 0){
            x->Faixa1[j-1] = x->Faixa1[j+1];
          }
          else{
            if(defeito_v1.posicao == j && j-1 < 0){
              aux[0] = x->Faixa1[x->inicio + 1];
              x->Faixa1[j+1].tipov = ' ';
              x->Faixa1[j+1].nveiculo = 0;
              x->Faixa1[j+1].origem = 0;
              x->Faixa1[j+1].instante = 0;
              x->Faixa1[j+1].dfinal = 0;
              x->Faixa1[j+1].estacionamento = ' ';
              x->Faixa1[j+1].testacionamento = 0;
            }else{
            x->Faixa1[j] = x->Faixa1[j+1];
            }
          }
          
        }
      }
          if (defeito_v1.posicao != MAX - 1){
            x->Faixa1[MAX-1].tipov = ' ';
            x->Faixa1[MAX-1].nveiculo = 0;
            x->Faixa1[MAX-1].origem = 0;
            x->Faixa1[MAX-1].instante = 0;
            x->Faixa1[MAX-1].dfinal = 0;
            x->Faixa1[MAX-1].estacionamento = ' ';
            x->Faixa1[MAX-1].testacionamento = 0;
          }else{
            x->Faixa1[MAX-2].tipov = ' ';
            x->Faixa1[MAX-2].nveiculo = 0;
            x->Faixa1[MAX-2].origem = 0;
            x->Faixa1[MAX-2].instante = 0;
            x->Faixa1[MAX-2].dfinal = 0;
            x->Faixa1[MAX-2].estacionamento = ' ';
            x->Faixa1[MAX-2].testacionamento = 0;
          }
      }
    
    //Via 1 Oeste - Leste
    k = MAX - 1;
    if(defeito_v1.faixa != 2 || x->Faixa2[defeito_v1.posicao].nveiculo == 0){
      while (amb2 >= 0){
        if (amb2 >= 0 && amb2 < 17){
          for(j = k; j >= amb2+3; j--){
            x->Faixa2[j] = x->Faixa2[j-1];
          }
          
           x->Faixa2[amb2+3] = x->Faixa2[amb2];

        }else{
          if (amb2 >= 17){
            x->Faixa2[amb2].tipov = ' ';
            x->Faixa2[amb2].nveiculo = 0;
            x->Faixa2[amb2].origem = 0;
            x->Faixa2[amb2].instante = 0;
            x->Faixa2[amb2].dfinal = 0;
            x->Faixa2[amb2].estacionamento = ' ';
            x->Faixa2[amb2].testacionamento = 0;
          }
          
        }
        k = amb2;
        amb2 = verificarAmbulanciaFaixa2(amb2, x);
      }
      if (k < MAX - 1){
        for (j = k; j > 0; j--){
          x->Faixa2[j] = x->Faixa2[j-1];
        }
      }else{
        for(j = MAX-1; j > 0; j--){
            x->Faixa2[j] = x->Faixa2[j-1];
        }
      }
      x->Faixa2[0].tipov = ' ';
      x->Faixa2[0].nveiculo = 0;
      x->Faixa2[0].origem = 0;
      x->Faixa2[0].instante = 0;
      x->Faixa2[0].dfinal = 0;
      x->Faixa2[0].estacionamento = ' ';
      x->Faixa2[0].testacionamento = 0;
    }else{
      while (amb2 >= 0){
        if(amb2 >= 0 && amb2 < 17){
          for(j = MAX-1; j >= amb2+3; j--){
            if(defeito_v1.posicao == j && j != MAX - 1){
              x->Faixa2[j+1] = x->Faixa2[j-1];
            }else if (j == MAX - 1){
              aux[1] = x->Faixa2[j-1];
              x->Faixa2[j-1].tipov = ' ';
              x->Faixa2[j-1].nveiculo = 0;
              x->Faixa2[j-1].origem = 0;
              x->Faixa2[j-1].instante = 0;
              x->Faixa2[j-1].dfinal = 0;
              x->Faixa2[j-1].estacionamento = ' ';
              x->Faixa2[j-1].testacionamento = 0;
            }else{
              
              x->Faixa2[j] = x->Faixa2[j-1];
            }
          }
          if (defeito_v1.posicao != amb2+3)
            x->Faixa2[amb2+3] = x->Faixa2[amb2];
          else{
            x->Faixa2[amb2+4] = x->Faixa2[amb2];
          }

        }else{
          if (amb2 >= 17){
            x->Faixa2[amb2].tipov = ' ';
            x->Faixa2[amb2].nveiculo = 0;
            x->Faixa2[amb2].origem = 0;
            x->Faixa2[amb2].instante = 0;
            x->Faixa2[amb2].dfinal = 0;
            x->Faixa2[amb2].estacionamento = ' ';
            x->Faixa2[amb2].testacionamento = 0;
          }
        
        }
        k = amb2;
        amb2 = verificarAmbulanciaFaixa2(amb2, x);
      }
      if (k < MAX - 1){
        for(j = k; j > 0; j--){
            if(defeito_v1.posicao == j){
              x->Faixa2[j+1] = x->Faixa2[j-1];
            }else{
              x->Faixa2[j] = x->Faixa2[j-1];
            }
          }
      }else{
        for(j = MAX-1; j > 0; j--){
          if(defeito_v1.posicao == j && j != MAX - 1){
            x->Faixa2[j+1] = x->Faixa2[j-1];
          }else if (j == MAX - 1){
            aux[1] = x->Faixa2[j-1];
            x->Faixa2[j-1].tipov = ' ';
            x->Faixa2[j-1].nveiculo = 0;
            x->Faixa2[j-1].origem = 0;
            x->Faixa2[j-1].instante = 0;
            x->Faixa2[j-1].dfinal = 0;
            x->Faixa2[j-1].estacionamento = ' ';
            x->Faixa2[j-1].testacionamento = 0;
          }
          else{
            x->Faixa2[j] = x->Faixa2[j-1];
          }
        }

      }
      

      if (defeito_v1.posicao != 0){
          x->Faixa2[0].tipov = ' ';
          x->Faixa2[0].nveiculo = 0;
          x->Faixa2[0].origem = 0;
          x->Faixa2[0].instante = 0;
          x->Faixa2[0].dfinal = 0;
          x->Faixa2[0].estacionamento = ' ';
          x->Faixa2[0].testacionamento = 0;
      }else{
          x->Faixa2[1].tipov = ' ';
          x->Faixa2[1].nveiculo = 0;
          x->Faixa2[1].origem = 0;
          x->Faixa2[1].instante = 0;
          x->Faixa2[1].dfinal = 0;
          x->Faixa2[1].estacionamento = ' ';
          x->Faixa2[1].testacionamento = 0;
      }
      
    }
    return aux;
  }

Carro* CicloAmb1(Via_1* x){
  int j, k = 0;
  int amb1 = verificarAmbulanciaFaixa1(0, x);
  int amb2 = verificarAmbulanciaFaixa2(20, x);
  Carro aux[2];
  aux[0] = x->Faixa1[x->inicio];
  aux[1] = x->Faixa2[MAX-1];
  x->fim = MAX - 1;
  if(defeito_v1.faixa != 1 || x->Faixa1[defeito_v1.posicao].nveiculo == 0){
      while (amb1 >= 0){
        for(j = 0; j <= amb1-3; j++){
          x->Faixa1[j] = x->Faixa1[j+1];
        }
        if(amb1-3 >= 0){
          x->Faixa1[amb1-3] = x->Faixa1[amb1];
        }else{
          aux[0] = x->Faixa1[amb1];
          x->Faixa1[amb1].tipov = ' ';
          x->Faixa1[amb1].nveiculo = 0;
          x->Faixa1[amb1].origem = 0;
          x->Faixa1[amb1].instante = 0;
          x->Faixa1[amb1].dfinal = 0;
          x->Faixa1[amb1].estacionamento = ' ';
          x->Faixa1[amb1].testacionamento = 0;
        }
        k = amb1;
        amb1 = verificarAmbulanciaFaixa1(amb1, x);
      }
      if (k > 0){
        for(j = k; j < 20; j++){
          x->Faixa1[j] = x->Faixa1[j+1];
        }
      }else{
        for(j = 0; j < 20; j++){
          x->Faixa1[j] = x->Faixa1[j+1];
        }
      }
      x->Faixa1[20].tipov = ' ';
      x->Faixa1[20].nveiculo = 0;
      x->Faixa1[20].origem = 0;
      x->Faixa1[20].instante = 0;
      x->Faixa1[20].dfinal = 0;
      x->Faixa1[20].estacionamento = ' ';
      x->Faixa1[20].testacionamento = 0;
    }else{
      while(amb1 >= 0){
        for(j = 0; j <= amb1-3; j++){
          if(defeito_v1.posicao == j && j-1 >= 0){
            x->Faixa1[j-1] = x->Faixa1[j+1];
          }else{
            if(defeito_v1.posicao == j && j-1 < 0){
              aux[0] = x->Faixa1[j+1];
              x->Faixa1[j+1].tipov = ' ';
              x->Faixa1[j+1].nveiculo = 0;
              x->Faixa1[j+1].origem = 0;
              x->Faixa1[j+1].instante = 0;
              x->Faixa1[j+1].dfinal = 0;
              x->Faixa1[j+1].estacionamento = ' ';
              x->Faixa1[j+1].testacionamento = 0;
            }else{
            x->Faixa1[j] = x->Faixa1[j+1];
          }
          }
        }
        if(amb1-3 >= 0){
          x->Faixa1[amb1-3] = x->Faixa1[amb1];
        }else{
          aux[0] = x->Faixa1[amb1];
          x->Faixa1[amb1].tipov = ' ';
          x->Faixa1[amb1].nveiculo = 0;
          x->Faixa1[amb1].origem = 0;
          x->Faixa1[amb1].instante = 0;
          x->Faixa1[amb1].dfinal = 0;
          x->Faixa1[amb1].estacionamento = ' ';
          x->Faixa1[amb1].testacionamento = 0;
        }
        k = amb1;
        amb1 = verificarAmbulanciaFaixa1(amb1, x);
      }
      if (k > 0){
        for(j = k; j < 20; j++){
          if(defeito_v1.posicao == j && j-1 >= 0){
            x->Faixa1[j-1] = x->Faixa1[j+1];
          }else{
            if(defeito_v1.posicao == j && j-1 < 0){
              aux[0] = x->Faixa1[j+1];
              x->Faixa1[j+1].tipov = ' ';
              x->Faixa1[j+1].nveiculo = 0;
              x->Faixa1[j+1].origem = 0;
              x->Faixa1[j+1].instante = 0;
              x->Faixa1[j+1].dfinal = 0;
              x->Faixa1[j+1].estacionamento = ' ';
              x->Faixa1[j+1].testacionamento = 0;
            }else{
            x->Faixa1[j] = x->Faixa1[j+1];
            }
          }
        }
      }else{
        for(j = 0; j < 20; j++){
          if(defeito_v1.posicao == j && j-1 >= 0){
            x->Faixa1[j-1] = x->Faixa1[j+1];
          }
          else{
            if(defeito_v1.posicao == j && j-1 < 0){
              aux[0] = x->Faixa1[j+1];
              x->Faixa1[j+1].tipov = ' ';
              x->Faixa1[j+1].nveiculo = 0;
              x->Faixa1[j+1].origem = 0;
              x->Faixa1[j+1].instante = 0;
              x->Faixa1[j+1].dfinal = 0;
              x->Faixa1[j+1].estacionamento = ' ';
              x->Faixa1[j+1].testacionamento = 0;
            }else{
            x->Faixa1[j] = x->Faixa1[j+1];
          }
        } 
      }
    }
    x->Faixa1[20].tipov = ' ';
    x->Faixa1[20].nveiculo = 0;
    x->Faixa1[20].origem = 0;
    x->Faixa1[20].instante = 0;
    x->Faixa1[20].dfinal = 0;
    x->Faixa1[20].estacionamento = ' ';
    x->Faixa1[20].testacionamento = 0;
  }

    //Via 1 Oeste - Leste
    k = MAX - 1;
    if(defeito_v1.faixa != 2 || x->Faixa2[defeito_v1.posicao].nveiculo == 0){
      while (amb2 >= 0){
        if (amb2 >= 0 && amb2 < 17){
          for(j = k; j >= amb2+3; j--){
            x->Faixa2[j] = x->Faixa2[j-1];
          }
          
           x->Faixa2[amb2+3] = x->Faixa2[amb2];

        }else{
          if (amb2 >= 17){
            x->Faixa2[amb2].tipov = ' ';
            x->Faixa2[amb2].nveiculo = 0;
            x->Faixa2[amb2].origem = 0;
            x->Faixa2[amb2].instante = 0;
            x->Faixa2[amb2].dfinal = 0;
            x->Faixa2[amb2].estacionamento = ' ';
            x->Faixa2[amb2].testacionamento = 0;
          }
          
        }
        k = amb2;
        amb2 = verificarAmbulanciaFaixa2(amb2, x);
      }
      if (k < MAX - 1){
        for (j = k; j > 0; j--){
          x->Faixa2[j] = x->Faixa2[j-1];
        }
      }else{
        for(j = MAX-1; j > 0; j--){
            x->Faixa2[j] = x->Faixa2[j-1];
        }
      }
      x->Faixa2[0].tipov = ' ';
      x->Faixa2[0].nveiculo = 0;
      x->Faixa2[0].origem = 0;
      x->Faixa2[0].instante = 0;
      x->Faixa2[0].dfinal = 0;
      x->Faixa2[0].estacionamento = ' ';
      x->Faixa2[0].testacionamento = 0;
    }else{
      while (amb2 >= 0){
        if(amb2 >= 0 && amb2 < 17){
          for(j = MAX-1; j >= amb2+3; j--){
            if(defeito_v1.posicao == j && j != MAX - 1){
              x->Faixa2[j+1] = x->Faixa2[j-1];
            }else if (j == MAX - 1){
              aux[1] = x->Faixa2[j-1];
              x->Faixa2[j-1].tipov = ' ';
              x->Faixa2[j-1].nveiculo = 0;
              x->Faixa2[j-1].origem = 0;
              x->Faixa2[j-1].instante = 0;
              x->Faixa2[j-1].dfinal = 0;
              x->Faixa2[j-1].estacionamento = ' ';
              x->Faixa2[j-1].testacionamento = 0;
            }else{
              
              x->Faixa2[j] = x->Faixa2[j-1];
            }
          }
          if (defeito_v1.posicao != amb2+3)
            x->Faixa2[amb2+3] = x->Faixa2[amb2];
          else{
            x->Faixa2[amb2+4] = x->Faixa2[amb2];
          }

        }else{
          if (amb2 >= 17){
            x->Faixa2[amb2].tipov = ' ';
            x->Faixa2[amb2].nveiculo = 0;
            x->Faixa2[amb2].origem = 0;
            x->Faixa2[amb2].instante = 0;
            x->Faixa2[amb2].dfinal = 0;
            x->Faixa2[amb2].estacionamento = ' ';
            x->Faixa2[amb2].testacionamento = 0;
          }
        
        }
        k = amb2;
        amb2 = verificarAmbulanciaFaixa2(amb2, x);
      }
      if (k < MAX - 1){
        for(j = k; j > 0; j--){
            if(defeito_v1.posicao == j){
              x->Faixa2[j+1] = x->Faixa2[j-1];
            }else{
              x->Faixa2[j] = x->Faixa2[j-1];
            }
          }
      }else{
        for(j = MAX-1; j > 0; j--){
          if(defeito_v1.posicao == j && j != MAX - 1){
            x->Faixa2[j+1] = x->Faixa2[j-1];
          }else if (j == MAX - 1){
            aux[1] = x->Faixa2[j-1];
            x->Faixa2[j-1].tipov = ' ';
            x->Faixa2[j-1].nveiculo = 0;
            x->Faixa2[j-1].origem = 0;
            x->Faixa2[j-1].instante = 0;
            x->Faixa2[j-1].dfinal = 0;
            x->Faixa2[j-1].estacionamento = ' ';
            x->Faixa2[j-1].testacionamento = 0;
          }
          else{
            x->Faixa2[j] = x->Faixa2[j-1];
          }
        }

      }
      

      if (defeito_v1.posicao != 0){
          x->Faixa2[0].tipov = ' ';
          x->Faixa2[0].nveiculo = 0;
          x->Faixa2[0].origem = 0;
          x->Faixa2[0].instante = 0;
          x->Faixa2[0].dfinal = 0;
          x->Faixa2[0].estacionamento = ' ';
          x->Faixa2[0].testacionamento = 0;
      }else{
          x->Faixa2[1].tipov = ' ';
          x->Faixa2[1].nveiculo = 0;
          x->Faixa2[1].origem = 0;
          x->Faixa2[1].instante = 0;
          x->Faixa2[1].dfinal = 0;
          x->Faixa2[1].estacionamento = ' ';
          x->Faixa2[1].testacionamento = 0;
      }
      
    }
  return aux;
}


int Qtecarros1(Via_1* x, int faixa){
  int i, l = 0;
  if (faixa == 1){
    for (i = 0; i <= x->fim; i++){
      if (x->Faixa1[i].origem != 0)
        l++;
    }
  }
  else{
    for (i = 0; i <= x->fim; i++){
      if (x->Faixa2[i].origem != 0)
        l++;
  }
  }
  return l;
}

void verFaixa_v1(Via_1* x, int faixa){
  int i, l;
  l = Qtecarros1(x, faixa);
  printf("Numero de veiculos na faixa: %d", l);
  if (faixa == 1){
    for(i = 0; i <= x->fim; i++){
      printf("Tipo do veiculo: %c \n",x->Faixa1[i].tipov);
      printf("Numero do veiculo: %d \n",x->Faixa1[i].nveiculo);
      printf("Origem: %d \n",x->Faixa1[i].origem);
      printf("Instante: %d \n",x->Faixa1[i].instante);
      printf("Destino Final: %d \n",x->Faixa1[i].dfinal);
      printf("Estacionamento: %c \n",x->Faixa1[i].estacionamento);
      printf("Tempo de estacionamento: %d \n",x->Faixa1[i].testacionamento);
      printf("\n\n");
    }
  }else{
    for(i = 0; i <= x->fim; i++){
      printf("Tipo do veiculo: %c \n",x->Faixa2[i].tipov);
      printf("Numero do veiculo: %d \n",x->Faixa2[i].nveiculo);
      printf("Origem: %d \n",x->Faixa2[i].origem);
      printf("Instante: %d \n",x->Faixa2[i].instante);
      printf("Destino Final: %d \n",x->Faixa2[i].dfinal);
      printf("Estacionamento: %c \n",x->Faixa2[i].estacionamento);
      printf("Tempo de estacionamento: %d \n",x->Faixa2[i].testacionamento);
      printf("\n\n");
    }     
  }
}
