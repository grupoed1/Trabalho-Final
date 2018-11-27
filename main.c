#include "via_2.h"
#include "estacionamento.h"
#include "engarrafamento.h"

int main(){
	
	int ciclo = 0;
	Via_2* faixa_1;
	Via_2* faixa_2;
	Estacionamento* ES;
	Engarrafamento* EN;
	Carro novo;

	char resp, resp2;


	do{	
		ciclo++;
		Desenfileirar(faixa_1, 1);
		Desenfileirar(faixa_2, 2);
		printf("Adicionar carro?\n");
		scanf(" %c", &resp);

		if (resp == 's'){
			printf("Digite o tipo\n");
			scanf(" %c", &novo.tipov);	
			printf("Digite o numero\n");
			scanf("%d", &novo.nveiculo);	
			printf("Digite a origem\n");
			scanf("%d", &novo.origem);	
			novo.instante = ciclo;
			printf("Digite o destino final\n");
			scanf("%d", &novo.dfinal);
			printf("Estacionamento?\n");
			scanf(" %c", &novo.estacionamento);
			printf("Digite o tempo no estacionamento\n");
			scanf("%d", &novo.testacionamento);

			if (novo.origem == 1){
				if (novo.estacionamento == 'S'){
					if (ES->topo != Z-1)
						empilhar(ES, novo);
					else{
						if (novo.dfinal == 2){
							if (Qtecarros(faixa_1) <= Qtecarros(faixa_2))
								Empilhar(faixa_1, novo, 1);
							else
								Empilhar(faixa_2, novo, 2);
						}
						else{

						}
					}
				}
				else{
					if (novo.dfinal == 2){
						if (Qtecarros(faixa_1) <= Qtecarros(faixa_2))
							Empilhar(faixa_1, novo, 1);
						else
							Empilhar(faixa_2, novo, 2);
					}
					else{
				
					}
				}
			}
			else{

			}
		}

		printf("Continuar?\n");
		scanf(" %c", &resp);
	}while (resp == 's');

	
	return 0;
}
