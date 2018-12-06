#include "via_2.h"
#include "via_1.h"
#include "estacionamento.h"
#include "engarrafamento.h"

int main(){
	
	int ciclo = 0;
	Via_1* via1;
	Via_2* faixa_1;
	Via_2* faixa_2;
	Estacionamento* ES;
	Engarrafamento* EN1;
	Engarrafamento* EN2;
	Carro novo, saidav1[2], saidav2_1, saidav2_2, saidaes, saidaen1, saidaen2;

	FILE* veiculos;

	char carro_atual[23];
	char buffer[4];
	int i = 2, p = 0;
	char t = '&';

		ciclo++;
		saidav2_1 = Desenfileirar(faixa_1, 1);
		saidav2_2 = Desenfileirar(faixa_2, 2);
		saidav1 = CicloVia_1(via1);
		saidaes = ControleSaidaES(ES);
		saidaen1 = sairEngarrafamento(EN1);
		saidaen2 = sairEngarrafamento(EN2);
		atualizarestacionamento(ES);

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
		novo.nveiculo = int(buffer);
		strcpy(buffer, '    ');
		i++;
		novo.origem = int(carro_atual[i]);
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
		novo.instante = int(buffer);
		i++;
		novo.dfinal = int(carro_atual[i]);
		i += 2;
		novo.estacionamento = carro_atual[i];
		i += 2;
		strcpy(buffer, '    ');
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
		novo.testacionamento = int(buffer);

	
	return 0;
}
