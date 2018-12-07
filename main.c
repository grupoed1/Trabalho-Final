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
		saidaes = ControleSaidaES(ES);
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

	
	return 0;
}
