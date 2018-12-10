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

	char carro_atual[23];
	char evento_atual[18];
	char buffer[4];
	int i = 2, p = -1, flag1 = 0, flag2 = 0;
	char t = '&';
	char* r;
	Carro* subst = (Carro*) malloc(sizeof(Carro)*2);
	
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
	r = fgets(carro_atual, 23, (FILE*) veiculos);

		while(r != NULL || Qtecarros(faixa_1) != 0 || Qtecarros(faixa_2) != 0 || Qtecarros1(via1, 1) != 0 || Qtecarros1(via1, 2) != 0 || ES->vet[ES->topo].tipov != ' '){
			ciclo++;
			saidav2_1 = Desenfileirar(faixa_1, 1);
			saidav2_2 = Desenfileirar(faixa_2, 2);
			flag1 = 0;
			flag2 = 0;
			p = -1;
			if (EN2->inicio != NULL && EN2->inicio->tipov == 'A' && (via1->Faixa1[21].tipov == 'C' || via1->Faixa1[17].tipov == 'A')){
				subst = CicloAmb1(via1);
				saidav1[0] = subst[0];
				saidav1[1] = subst[1];
			}else{
				subst = CicloVia_1(via1);
				saidav1[0] = subst[0];
				saidav1[1] = subst[1];
			}
			saidaen1 = sairEngarrafamento(EN1);
			if (saidaen1.tipov != ' ')
				flag1 = 1;
			saidaen2 = sairEngarrafamento(EN2);
			if (saidaen2.tipov != ' ')
				flag2 = 1;
			atualizarEstacionamento(ES);
			iniciarCarro(&saidaes);
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
				i = 2;
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
				}while (p < 2 && i < strlen(evento_atual));
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
					fseek(eventos, -strlen(evento_atual), SEEK_CUR);
			}

			if (r != NULL){
				i = 2;
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
					fseek(veiculos, -strlen(carro_atual), SEEK_CUR);
				}
			}

			if (saidaen1.dfinal == 1 || saidaen1.dfinal == 2){
				if (saidaen1.tipov == 'A')
					inserirVia_1(via1, saidaen1);
				else if (saidaen1.estacionamento == 'N' && saidaen1.dfinal == 1){
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
				if (r != NULL && novo.origem == 1){
					entrarEngarrafamento(EN1, novo);
				}
			}else{
				if (r != NULL && novo.origem == 1){
					if (novo.tipov == 'A')
						inserirVia_1(via1, novo);
					else if (novo.estacionamento == 'N' && novo.dfinal == 1){
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
			if (r != NULL && novo.origem == 1)
				flag1 = 1;
			if (r != NULL && novo.origem == 2)
				flag2 = 1;
			if (saidav1[0].estacionamento == 'S' && p == -1){
				ControleEntradaES(ES, &saidaen1, &saidav1[0]);
			}
			else if ((saidav1[0].estacionamento == 'S' && (p == 0 || p == 1)) || saidav1[0].estacionamento == 'N'){
				if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
					Enfileirar(faixa_2, saidav1[0], 2);
				else
					Enfileirar(faixa_1, saidav1[0], 1);
			}

			if (saidaen2.dfinal == 1 || saidaen2.dfinal == 2){
				inserirVia_1(via1, saidaen2);
				if ((r != NULL && novo.origem == 2 && novo.tipov == 'C') || (r != NULL && novo.tipov == 'A' && novo.origem == 2 && via1->Faixa1[20].tipov != ' ')){
					entrarEngarrafamento(EN2, novo);
				}else if (r != NULL && novo.tipov == 'A' && novo.origem == 2)
					inserirVia_1(via1, novo);
			}else{
				if (r != NULL && novo.origem == 2){
					if (novo.tipov == 'C' || via1->Faixa1[20].tipov == ' ')
						inserirVia_1(via1, novo);
					else
						entrarEngarrafamento(EN2, novo);
				}
			}

			while (r != NULL && novo.instante == ciclo){
				r = fgets(carro_atual, 23, (FILE*) veiculos);
				i = 2;
				if (r != NULL){
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
						fseek(veiculos, -strlen(carro_atual), SEEK_CUR);
					}else{
						if (novo.origem == 1){
							if (flag1 == 1){
								entrarEngarrafamento(EN1, novo);
							}
							else{
								if (novo.tipov == 'A')
									inserirVia_1(via1, novo);
								else if (novo.estacionamento == 'N' && novo.dfinal == 1){
									if (ES->vet[ES->topo].dfinal == 2){
										saidaes = ControleSaidaES(ES);
										if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
											Enfileirar(faixa_2, saidaes, 2);
										else
											Enfileirar(faixa_1, saidaes, 1);
									}
									inserirVia_1(via1, novo);
								}
								else if (novo.estacionamento == 'N' && novo.dfinal == 2){
									saidaes = ControleSaidaES(ES);
									if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
										Enfileirar(faixa_2, novo, 2);
									else
										Enfileirar(faixa_1, novo, 1);
									if (saidaes.dfinal == 1)
										inserirVia_1(via1, saidaes);
									else if (saidaes.dfinal == 2){
										if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
											Enfileirar(faixa_2, saidaes, 2);
										else
											Enfileirar(faixa_1, saidaes, 1);
									}
								}else{
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
								flag1 = 1;
							}		

						}else if (novo.origem == 2){
							if (flag2 == 1)
								entrarEngarrafamento(EN2, novo);
							else{
								inserirVia_1(via1, novo);
								flag2 = 1;
							}

						}
					}
				}

			}

			if (saidaes.tipov == ' '){
				if (ES->vet[ES->topo].dfinal == 2 && ((faixa_1->Faixa[Y - 1].tipov == ' ' && (defeito_v2.faixa != 1 || defeito_v2.posicao != Y - 1)) || (faixa_1->Faixa[Y - 2].tipov == ' ' && (defeito_v2.faixa == 1 && defeito_v2.posicao == Y - 1)) || (faixa_2->Faixa[Y - 1].tipov == ' ' && (defeito_v2.faixa != 2 || defeito_v2.posicao != Y - 1)) || (faixa_2->Faixa[Y - 2].tipov == ' ' && (defeito_v2.faixa == 2 && defeito_v2.posicao == Y - 1)))){
					saidaes = ControleSaidaES(ES);
					if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
						Enfileirar(faixa_2, saidaes, 2);
					else
						Enfileirar(faixa_1, saidaes, 1);
				}else if (ES->vet[ES->topo].dfinal == 1 && ((via1->Faixa2[0].tipov == ' ' && (defeito_v1.faixa != 2 || defeito_v1.posicao != 0)) || (via1->Faixa2[1].tipov == ' ' && (defeito_v1.faixa == 2 && defeito_v1.posicao == 0)))){
					saidaes = ControleSaidaES(ES);
					inserirVia_1(via1, saidaes);
				}
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

			atualizarEngarrafamento(EN1);
			atualizarEngarrafamento(EN2);


			r = fgets(carro_atual, 23, (FILE*) veiculos);

			verTudo(via1, faixa_1, faixa_2, ES);

		}

	
	return 0;
}
