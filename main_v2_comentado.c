#include <unistd.h>
#include "via_1.h"
#include "estacionamento.h"

void verTudo(Via_1* x, Via_2* f1, Via_2* f2, Estacionamento* e){ //Funcao para visualizar o sistema
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

	char buffer[4];
	int i = 2, k = 2, p = -1, flag1 = 0, flag2 = 0, evento_f = 0;
	char t = '&';
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
	eventos = fopen("eventos.txt", "r"); //Abre arquivos
	veiculos = fopen("veiculos.txt", "r");
	saida = fopen("saida.txt", "w");
	
	fseek(eventos, 0 , SEEK_END); //Procura o fim do arquivo
	long fsize1 = ftell(eventos); //Armazena o fim do arquivo numa variavel
	fseek(eventos, 0, SEEK_SET); //Volta pro inicio do arquivo
	char *lista_e = malloc(fsize1 + 1); //Cria uma string do tamanho do arquivo + 1
	fread(lista_e, 1, fsize1, eventos); //Le o arquivo e coloca tudo na string criada
	fclose(eventos);
	lista_e[fsize1] = 0;
	int mark1 = 0;

	fseek(veiculos, 0 , SEEK_END); //Idem
	long fsize2 = ftell(veiculos);
	fseek(veiculos, 0, SEEK_SET);
	char *lista_v = malloc(fsize2 + 1);
	fread(lista_v, 1, fsize2, veiculos);
	fclose(veiculos);
	lista_v[fsize2] = 0;
	int mark2 = 0;
	int mark2_f = mark2;


		while(mark2 < strlen(lista_v) || Qtecarros(faixa_1) != 0 || Qtecarros(faixa_2) != 0 || Qtecarros1(via1, 1) != 0 || Qtecarros1(via1, 2) != 0 || ES->vet[ES->topo].tipov != ' '){
			ciclo++;
			saidav2_1 = Desenfileirar(faixa_1, 1); //Saidas da via 2
			saidav2_2 = Desenfileirar(faixa_2, 2);
			if (mark2 > strlen(lista_v)) //Se a variavel que indica a posicao da leitura da string ja tiver ultrapassado o tamanho desta,
				mark2_f = mark2; //o flag e igualado a ela para que o programa saiba que nao ha mais nenhum veiculo a se ler
			flag1 = 0; //Flag para indicar se houve a adicao de um novo veiculo na via 1
			flag2 = 0; //Idem para a via 1
			evento_f = 0; //Flag para indicar se houve um evento lido
			p = -1;
			if (EN2->inicio != NULL && EN2->inicio->tipov == 'A' && (via1->Faixa1[21].tipov == 'C' || via1->Faixa1[17].tipov == 'A')){
				subst = CicloAmb1(via1); //Ciclo especial para caso um carro esteja ocupando a posicao do hospital e uma ambulancia quiser entrar
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
			if (defeito_v1.duracao <= 0){ //Se o periodo do defeito acabou, ele e zerado
				defeito_v1.tipo = 'D';
				defeito_v1.instante = 0;
				defeito_v1.duracao = 0;
				defeito_v1.via = 0;
				defeito_v1.faixa = 0;
				defeito_v1.posicao = 0;
			}
			if (defeito_v2.duracao <= 0){ //Idem
				defeito_v2.tipo = 'D';
				defeito_v2.instante = 0;
				defeito_v2.duracao = 0;
				defeito_v2.via = 0;
				defeito_v2.faixa = 0;
				defeito_v2.posicao = 0;
			}
			if (mark1 < strlen(lista_e)){ //Enquanto nao chegou ao fim da string...
				p = 0;       //Aqui dentro 'uma linha' da string e lida e os resultados sao passados para a variavel e
				evento_f = 1;
				i = mark1 + 2;
				e.tipo = lista_e[mark1];
				do{
					t = lista_e[i];
					if (t != ' ')
						buffer[p] = t;
					else
						break;
					i++;
					p++;
				}while (i < mark1 + 6);
				e.instante = atoi(buffer);
				strcpy(buffer, "   ");
				i++;
				p = 0;
				do{
					t = lista_e[i];
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
				e.via = atoi(&lista_e[i]);
				i += 2;
				e.faixa = atoi(&lista_e[i]);
				i += 2;
				strcpy(buffer, "   ");
				p = 0;
				do{
					t = lista_e[i];
					if (t != ' ')
						buffer[p] = t;
					else
						break;
					i++;
					p++;
				}while (p < 2 && i < fsize1 && lista_e[i + 1] != 'D');
				i++;
				if (e.instante == ciclo)
					mark1 = i;
				buffer[p] = '\0';
				e.posicao = atoi(buffer);
				strcpy(buffer, "   ");
				p = -1;
			}

			if (mark2 < strlen(lista_v)){ //Idem a anterior, exceto que aqui um veiculo e lido, em vez de um evento
				p = 0;
				i = 2 + mark2;
				novo.tipov = lista_v[mark2];
				do{
					t = lista_v[i];
					if (t != ' ')
						buffer[p] = t;
					else
						break;
					i++;
					p++;
				}while (p < 4);
				novo.nveiculo = atoi(buffer);
				strcpy(buffer, "   ");
				i++;
				novo.origem = atoi(&lista_v[i]);
				i += 2;
				p = 0;
				do{
					t = lista_v[i];
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
				novo.dfinal = atoi(&lista_v[i]);
				i += 2;
				novo.estacionamento = lista_v[i];
				i += 2;
				strcpy(buffer, "   ");
				p = 0;
				do{
					t = lista_v[i];
					if (t != ' ')
						buffer[p] = t;
					else
						break;
					i++;
					p++;
				}while (p < 4 && i < fsize2 && lista_v[i + 1] != 'C' && lista_v[i + 1] != 'A');
				i++;
				buffer[p] = '\0';
				novo.testacionamento = atoi(buffer);
				strcpy(buffer, "   ");
				p = - 1;
				if (novo.instante != ciclo){ //Se o instante do veiculo nao for o ciclo atual, novo e zerado
					novo.tipov = ' ';
					novo.nveiculo = 0;
					novo.origem = 0;
					novo.instante = 0;
					novo.dfinal = 0;
					novo.estacionamento = ' ';
					novo.testacionamento = 0;
				}else{ //Se for, entao mark2 e atualizado para a proxima linha
					mark2 = i;
					if (mark2 < strlen(lista_v)) //mark_f e usado para indicar se um veiculo novo foi lido. 
						mark2_f = mark2; //Ele continua sendo < strlen(lista_v) na primeira vez que mark2 a ultrapassa, pq mark2 sera > strlen(lista_v) qnd o ultimo
				}                                //veiculo for adicionado
			}

			if (saidaen1.dfinal == 1 || saidaen1.dfinal == 2){ //Se saiu alguma coisa do primeiro engarrafamento, essa saida sera encaminhada
				if (saidaen1.tipov == 'A')                 //para o seu destino
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
				if (mark2_f < strlen(lista_v) && novo.origem == 1){ //E o novo veiculo (se existir) sera colocado no engarrafamento
					entrarEngarrafamento(EN1, novo);
				}
			}else{ //Do contrario, o novo veiculo (se existir) sera encaminhado para seu destino
				if (mark2_f < strlen(lista_v) && novo.origem == 1){
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
			if (mark2_f < strlen(lista_v) && novo.origem == 1) //se um novo foi adicionado na entrada 1 ou eng1
				flag1 = 1;
			if (mark2_f < strlen(lista_v) && novo.origem == 2) //se um novo foi adicionado na entrada 2 ou eng2
				flag2 = 1;
			if (saidav1[0].estacionamento == 'S' && p == -1){ //Agora a saida da faixa 1 da via 1 e encaminhada ao destino
				ControleEntradaES(ES, &saidaen1, &saidav1[0]);
			}
			else if ((saidav1[0].estacionamento == 'S' && (p == 0 || p == 1)) || saidav1[0].estacionamento == 'N'){
				if (Qtecarros(faixa_2) <= Qtecarros(faixa_1))
					Enfileirar(faixa_2, saidav1[0], 2);
				else
					Enfileirar(faixa_1, saidav1[0], 1);
			}

			if (saidaen2.dfinal == 1 || saidaen2.dfinal == 2){ //Faz-se o msm que se fez com a saida do eng1, agora com o eng2
				inserirVia_1(via1, saidaen2);
				if ((mark2_f < strlen(lista_v) && novo.origem == 2 && novo.tipov == 'C') || (mark2_f < strlen(lista_v) && novo.tipov == 'A' && novo.origem == 2 && via1->Faixa1[20].tipov != ' ')){
					entrarEngarrafamento(EN2, novo);
				}else if (mark2_f < strlen(lista_v) && novo.tipov == 'A' && novo.origem == 2)
					inserirVia_1(via1, novo);
			}else{ //Se nao havia nada no estacionamento, o novo veiculo da entrada 2 entra no sistema
				if (mark2_f < strlen(lista_v) && novo.origem == 2){
					if (novo.tipov == 'C' || via1->Faixa1[20].tipov == ' ')
						inserirVia_1(via1, novo);
					else
						entrarEngarrafamento(EN2, novo);
				}
			}

			while (mark2 < strlen(lista_v) && novo.instante == ciclo){ //O programa vai tirando as informacoes de carros da string
				i = 2 + mark2;                                     //ate que o primeiro veiculo n seja mais daquele ciclo
				p = 0;
				if (mark2 < strlen(lista_v)){
					novo.tipov = lista_v[mark2];
					do{
						t = lista_v[i];
						if (t != ' ')
							buffer[p] = t;
						else
							break;
						i++;
						p++;
					}while (p < 4);
					novo.nveiculo = atoi(buffer);
					strcpy(buffer, "   ");
					i++;
					novo.origem = atoi(&lista_v[i]);
					i += 2;
					p = 0;
					do{
						t = lista_v[i];
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
					novo.dfinal = atoi(&lista_v[i]);
					i += 2;
					novo.estacionamento = lista_v[i];
					i += 2;
					strcpy(buffer, "   ");
					p = 0;
					do{
						t = lista_v[i];
						if (t != ' ')
							buffer[p] = t;
						else
							break;
						i++;
						p++;
					}while (p < 4 && i < fsize2 && lista_v[i + 1] != 'C' && lista_v[i + 1] != 'A');
					i++;
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
					}else{
						mark2 = i;
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

			if (saidaes.tipov == ' '){       //Se nao saiu nda do estacionamento ainda, ou seja, nenhum carro quis entrar e invocou a saida, verifica-se se da pra sair carro de la
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
			//O condicional seguinte verifica se o evento lido no comeco do programa pertence ao ciclo atual e se tem algum veiculo naquela posicao
			if (e.instante == ciclo && e.via == 1 && ((e.faixa == 1 && via1->Faixa1[e.posicao].tipov != ' ') ||(e.faixa == 2 && via1->Faixa2[e.posicao].tipov != ' ')))
				defeito_v1 = e;
			else if (e.instante == ciclo && e.via == 2 && ((e.faixa == 1 && faixa_1->Faixa[e.posicao].tipov != ' ') ||(e.faixa == 2 && faixa_2->Faixa[e.posicao].tipov != ' ')))
				defeito_v2 = e;
			//Agora as saidas sao registradas no arquivo
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


			verTudo(via1, faixa_1, faixa_2, ES);

		}

	usleep(1000000);
	return 0;
}
