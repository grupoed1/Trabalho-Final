#include "via_1.h"
#include "estacionamento.h"

int main(){
	
	int ciclo = 0;
	Via_1* via1 = (Via_1*) malloc(sizeof(Via_1));
	Via_2* faixa_1 = (Via_2*) malloc(sizeof(Via_2));
	Via_2* faixa_2 = (Via_2*) malloc(sizeof(Via_2));
	Estacionamento* ES = (Estacionamento*) malloc(sizeof(Estacionamento));
	Engarrafamento* EN1 = (Engarrafamento*) malloc(sizeof(Engarrafamento));
	Engarrafamento* EN2 = (Engarrafamento*) malloc(sizeof(Engarrafamento));;
	Carro novo, saidav1[2], saidav2_1, saidav2_2, saidaes, saidaen1, saidaen2;

	FILE* veiculos;

	char carro_atual[23];
	char buffer[4];
	int i = 2, p = 0;
	char t = '&';

	inicializarVia_1(via1);
	inicializar(faixa_1);
	inicializar(faixa_2);
	inicializarES(ES);
	iniciarEngarrafamento(EN1);
	iniciarEngarrafamento(EN2);

		ciclo++;
		saidav2_1 = Desenfileirar(faixa_1, 1);
		saidav2_2 = Desenfileirar(faixa_2, 2);
		saidav1[0] = CicloVia_1(via1)[0];
		saidav1[1] = CicloVia_1(via1)[1];
		saidaen1 = sairEngarrafamento(EN1);
		saidaen2 = sairEngarrafamento(EN2);
		atualizarEstacionamento(ES);

		veiculos = fopen("veiculos.txt", "r");
		fgets(carro_atual, 23, (FILE*) veiculos);

		novo.tipov = carro_atual[0];
		do{
			t = carro_atual[i];
			if (t != ' ')
				buffer[i - 2] = t;
			else
				break;
			i++;
		}while (i < 6);
		novo.nveiculo = atoi(buffer);
		strcpy(buffer, "   ");
		i++;
		novo.origem = atoi(&carro_atual[i]);
		i += 2;
		p = 0;
		do{
			t = carro_atual[i];
			if (t != ' ')
				buffer[p] = t;
			else
				break;
			i++;
			p++;
		}while (p < 4);
		buffer[p] = '\0';
		novo.instante = atoi(buffer);
		i++;
		novo.dfinal = atoi(&carro_atual[i]);
		i += 2;
		novo.estacionamento = carro_atual[i];
		i += 2;
		strcpy(buffer, "   ");
		p = 0;
		do{
			t = carro_atual[i];
			if (t != ' ')
				buffer[p] = t;
			else
				break;
			i++;
			p++;
		}while (p < 4 && i < strlen(carro_atual));
		buffer[p] = '\0';
		novo.testacionamento = atoi(buffer);
		strcpy(buffer, "   ");

		if (saidaen1.dfinal == 1 || saidaen1.dfinal == 2){
			if (saidaen1.estacionamento == 'N' && saidaen1.dfinal == 1){
				if (ES->vet[ES->topo].dfinal == 2){
					saidaes = ControleSaidaES(ES);
					if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
						Enfileirar(faixa_2, saidaes, 2);
					else
						Enfileirar(faixa_1, saidaes, 1);
				}
				inserirVia_1(via1, saidaen1);
			}else if (saidaen1.estacionamento == 'N' && saidaen1.dfinal == 2){
				saidaes = ControleSaidaES(ES);
				if (saidaes.dfinal == 1)
					inserirVia_1(via1, saidaes);
				else if (saidaes.dfinal == 2){
					if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
						Enfileirar(faixa_2, saidaes, 2);
					else
						Enfileirar(faixa_1, saidaes, 1);
				}
				if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
					Enfileirar(faixa_2, saidaen1, 2);
				else
					Enfileirar(faixa_1, saidaen1, 1);
			}else if (saidaen1.estacionamento == 'S'){
				saidaes = ControleSaidaES(ES);
				if (saidaes.dfinal == 1)
					inserirVia_1(via1, saidaes);
				else if (saidaes.dfinal == 2){
					if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
						Enfileirar(faixa_2, saidaes, 2);
					else
						Enfileirar(faixa_1, saidaes, 1);
				}
				p = ControleEntradaES(ES, saidaen1, saidav1[0]);
				if (p < 1){
					if (saidaen1.dfinal == 1)
						inserirVia_1(via1, saidaen1);
					else if (saidaen1.dfinal == 2){
						if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
							Enfileirar(faixa_2, saidaen1, 2);
						else
							Enfileirar(faixa_1, saidaen1, 1);
					}
				}
			}
			if (novo.origem == 1)
				entrarEngarrafamento(EN1, novo);
		}else{
			if (novo.origem == 1){
				if (novo.estacionamento == 'N' && novo.dfinal == 1){
					if (ES->vet[ES->topo].dfinal == 2){
						saidaes = ControleSaidaES(ES);
						if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
							Enfileirar(faixa_2, saidaes, 2);
						else
							Enfileirar(faixa_1, saidaes, 1);
					}
					inserirVia_1(via1, novo); 
				}else if (novo.estacionamento == 'N' && novo.dfinal == 2){
					saidaes = ControleSaidaES(ES);
					if (saidaes.dfinal == 1)
						inserirVia_1(via1, saidaes);
					else if (saidaes.dfinal == 2){
						if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
							Enfileirar(faixa_2, saidaes, 2);
						else
							Enfileirar(faixa_1, saidaes, 1);
					}
					if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
						Enfileirar(faixa_2, novo, 2);
					else
						Enfileirar(faixa_1, novo, 1);
				}else if (novo.estacionamento == 'S'){
					saidaes = ControleSaidaES(ES);
					if (saidaes.dfinal == 1)
						inserirVia_1(via1, saidaes);
					else if (saidaes.dfinal == 2){
						if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
							Enfileirar(faixa_2, saidaes, 2);
						else
							Enfileirar(faixa_1, saidaes, 1);

					}
					p = ControleEntradaES(ES, novo, saidav1[0]);
					if (p < 1){
						if (novo.dfinal == 1)
							inserirVia_1(via1, novo);
						else if (novo.dfinal == 2){
							if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
								Enfileirar(faixa_2, novo, 2);
							else
								Enfileirar(faixa_1, novo, 1);
						}
					}
				}
			}

		}

		if (saidaen2.dfinal == 1 || saidaen2.dfinal == 2){
			inserirVia_1(via1, saidaen2);
			if (novo.origem == 2){
				entrarEngarrafamento(EN2, novo);
			}
		}else{
			if (novo.origem == 2)
				inserirVia_1(via1, novo);
		}
		//Falta controlar saidav1[0]

	
	return 0;
}
