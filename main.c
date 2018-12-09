#include "via_1.h"
#include "estacionamento.h"

void verTudo(Via_1* x, Via_2* f1, Via_2* f2, Estacionamento* e){
	int i;
	for (i = 0; i < 14; i++){
		printf("  |%c|\n", e->vet[i].tipov);
	}
	printf("  |%c|                    H\n", e->vet[Z-1].tipov);
	printf("     ");
	for (i = 0; i < MAX; i++){
		printf("—");
	}
	printf("\n");
	printf("     ");
	for (i = 0; i < MAX; i++){
		printf("%c", x->Faixa1[i].tipov);
	}
	printf("\n");
	printf("     ");
	for (i = 0; i < MAX; i++){
		printf("—");
	}
	printf("\n");
	printf("S    ");
	for (i = 0; i < MAX; i++){
		printf("%c", x->Faixa2[i].tipov);
	}
	printf("\n");
	printf("     ");
	for (i = 0; i < MAX; i++){
		printf("—");
	}
	printf("\n");
	for (i = 0; i < Y; i++){
		printf(" |%c|%c|\n", f1->Faixa[Y- 1- i].tipov, f2->Faixa[Y - 1 - i].tipov);
	}

}

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
	FILE* eventos;
	FILE* saida;

	long offset = 0L;

	char carro_atual[23];
	char evento_atual[18];
	char buffer[4];
	int i = 2, p = 0;
	char t = '&';
	char* r = fgets(carro_atual, 23, (FILE*) veiculos);
	evento e;

	defeito_v1.duracao = 0;
	defeito_v2.duracao = 0;

	inicializarVia_1(via1);
	inicializar(faixa_1);
	inicializar(faixa_2);
	inicializarES(ES);
	iniciarEngarrafamento(EN1);
	iniciarEngarrafamento(EN2);
	eventos = fopen("eventos.txt", "r");
	veiculos = fopen("veiculos.txt", "r");
	saida = fopen("saida.txt", "w");

		while(r != NULL || Qtecarros(faixa_1) != 0 || Qtecarros(faixa_2) != 0 || Qtecarros1(via1, 1) != 0 || Qtecarros1(via1, 2) != 0 || ES->topo != 0){
			ciclo++;
			saidav2_1 = Desenfileirar(faixa_1, 1);
			saidav2_2 = Desenfileirar(faixa_2, 2);
			if (EN2->inicio != NULL && EN2->inicio->tipov == 'A' && (via1->Faixa1[21].tipov == 'C' || via1->Faixa1[17].tipov == 'A')){
				saidav1[0] = CicloAmb1(via1)[0];
				saidav1[1] = CicloAmb1(via1)[1];
			}else{
				saidav1[0] = CicloVia_1(via1)[0];
				saidav1[1] = CicloVia_1(via1)[1];
			}
			atualizarEngarrafamento(EN1);
			atualizarEngarrafamento(EN2);
			saidaen1 = sairEngarrafamento(EN1);
			saidaen2 = sairEngarrafamento(EN2);
			atualizarEstacionamento(ES);
			defeito_v1.duracao--;
			defeito_v2.duracao--;
			if (defeito_v1.duracao <= 0){
				defeito_v1.tipo = 'D';
				defeito_v1.instante = 0;
				defeito_v1.duracao = 0;
				defeito_v1.via = 0;
				defeito_v1.faixa = 0;
				defeito_v1.posicao = 0;
			}
			if (defeito_v2.duracao <= 0){
				defeito_v2.tipo = 'D';
				defeito_v2.instante = 0;
				defeito_v2.duracao = 0;
				defeito_v2.via = 0;
				defeito_v2.faixa = 0;
				defeito_v2.posicao = 0;
			}

			if (fgets(evento_atual, 18, (FILE*) eventos) != NULL){
				offset = ftell(eventos);
				e.tipo = evento_atual[0];
				do{
					t = evento_atual[i];
					if (t != ' ')
						buffer[i - 2] = t;
					else
						break;
					i++;
				}while (i < 6);
				e.instante = atoi(buffer);
				strcpy(buffer, "   ");
				i++;
				p = 0;
				do{
					t = evento_atual[i];
					if (t != ' ')
						buffer[p] = t;
					else
						break;
					i++;
					p++;
				}while (p < 4);
				buffer[p] = '\0';
				e.duracao = atoi(buffer);
				i++;
				e.via = atoi(&evento_atual[i]);
				i += 2;
				e.faixa = atoi(&evento_atual[i]);
				i += 2;
				strcpy(buffer, "   ");
				p = 0;
				do{
					t = evento_atual[i];
					if (t != ' ')
						buffer[p] = t;
					else
						break;
					i++;
					p++;
				}while (p < 2 && i < strlen(carro_atual));
				buffer[p] = '\0';
				e.posicao = atoi(buffer);
				p = 0;
				i = 2;
				strcpy(buffer, "   ");
				if (e.instante == ciclo && e.via == 1 && ((e.faixa == 1 && via1->Faixa1[e.posicao].tipov != ' ') ||(e.faixa == 2 && via1->Faixa2[e.posicao].tipov != ' ')))
					defeito_v1 = e;
				else if (e.instante == ciclo && e.via == 2 && ((e.faixa == 1 && faixa_1->Faixa[e.posicao].tipov != ' ') ||(e.faixa == 2 && faixa_2->Faixa[e.posicao].tipov != ' ')))
					defeito_v2 = e;
				else if (e.instante != ciclo)
					fseek(eventos, offset, SEEK_SET);
			}

			if (r != NULL){
				offset = ftell(veiculos);
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
				p = - 1;
				if (novo.instante != ciclo){
					novo.tipov = ' ';
					novo.nveiculo = 0;
					novo.origem = 0;
					novo.instante = 0;
					novo.dfinal = 0;
					novo.estacionamento = ' ';
					novo.testacionamento = 0;
					fseek(veiculos, offset, SEEK_SET);
				}
			}

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
					if (saidav1[0].dfinal != 2 || saidav1[0].estacionamento == 'S'){
						saidaes = ControleSaidaES(ES);
						if (saidaes.dfinal == 1)
							inserirVia_1(via1, saidaes);
						else if (saidaes.dfinal == 2){
							if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
								Enfileirar(faixa_2, saidaes, 2);
							else
								Enfileirar(faixa_1, saidaes, 1);
						}
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
					p = ControleEntradaES(ES, &saidaen1, &saidav1[0]);
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
				if (r != NULL && novo.origem == 1)
					entrarEngarrafamento(EN1, novo);
			}else{
				if (r != NULL && novo.origem == 1){
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
						if (saidav1[0].dfinal != 2 || saidav1[0].estacionamento == 'S'){
							saidaes = ControleSaidaES(ES);
							if (saidaes.dfinal == 1)
								inserirVia_1(via1, saidaes);
							else if (saidaes.dfinal == 2){
								if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
									Enfileirar(faixa_2, saidaes, 2);
								else
									Enfileirar(faixa_1, saidaes, 1);
							}
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
						p = ControleEntradaES(ES, &novo, &saidav1[0]);
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

			if (saidav1[0].estacionamento == 'S' && p == -1)
				ControleEntradaES(ES, &saidaen1, &saidav1[0]);
			else if ((saidav1[0].estacionamento == 'S' && (p == 0 || p == 1)) || saidav1[0].estacionamento == 'N'){
				if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
					Enfileirar(faixa_2, saidav1[0], 2);
				else
					Enfileirar(faixa_1, saidav1[0], 1);
			}

			if (saidaen2.dfinal == 1 || saidaen2.dfinal == 2){
				inserirVia_1(via1, saidaen2);
				if (r != NULL && novo.origem == 2){
					entrarEngarrafamento(EN2, novo);
				}
			}else{
				if (r != NULL && novo.origem == 2)
					inserirVia_1(via1, novo);
			}

			if (saidav1[1].tipov != ' '){
				fprintf(saida, "%c %d %d\n", saidav1[1].tipov, saidav1[1].nveiculo, ciclo);
			}
			if (saidav2_1.tipov != ' '){
				fprintf(saida, "%c %d %d\n", saidav2_1.tipov, saidav2_1.nveiculo, ciclo);
			}
			if (saidav2_2.tipov != ' '){
				fprintf(saida, "%c %d %d\n", saidav2_2.tipov, saidav2_2.nveiculo, ciclo);
			}

			r = fgets(carro_atual, 23, (FILE*) veiculos);

		}


	
	return 0;
}
