#include <stdio.h>
#include <stdlib.h>
#include <conio.h>   // biblioteca chamada para apenas utilizar a função getchar().
#include <locale.h>  // biblioteca chamada para utilização de caracteres especiais (no caso, acentos).
#include <windows.h> // biblioteca chamada para utilização da função Sleep().

struct desafio{
	char Name[30];
	float quant_atual;
	float price;
	int mouth_valid;
	int year_valid;
};

FILE *pfile;

void EntraDados(struct desafio *p)
{
	int conta; //  Váriavel de incremento.

	pfile = fopen("DADOS_REGISTRADO.txt", "a+");

	system("cls");

	if(pfile == NULL){ // Se o arquivo não for aberto corretamente, o usuáro será informado e o programa, fechado.

		printf("\n\n\tErro ao criar arquivo.");
		Sleep(2000);
		system("cls");	system("color 6");

		for(int conta = 3; conta!=0; --conta)
		{
			system("cls");	printf("\n\n\t\tEncerrandoo programa em %d segundos." , conta);
			Sleep(1000);
		}

		system("cls");
		system("color 7");
		exit(1);
	}

	else{

		printf("\nInsira o nome do produto: ");
		scanf("%s", p->Name);

		printf("\nInsira a quantidade do  produto: ");
		scanf("%f", &p->quant_atual);

		printf( "\nColoque ',' em vez de '.'.");
		printf("\nInsira o preço do produto: ");
		scanf("%f", &p->price);

		printf("\nInsira a validade do produto (primeiro mês, depois ano): ");
		scanf("%d %d", &p->mouth_valid, &p->year_valid);

		fwrite(&(*p), sizeof(struct desafio), 1, pfile);

		printf("\n\n----------------DADOS ARMAZENADOS COM SUCESSO----------------\n");
	}

	Sleep(1500);
	fclose(pfile);
}

void Lista_dados(struct desafio *p)
{
	int variavel;

	pfile = fopen("DADOS_REGISTRADO.txt", "r");

	system("cls");

	printf("\n\n----------------DADOS ARMAZENADOS----------------\n\n");

	while(1){

		variavel = fread(&(*p), sizeof(struct desafio), 1, pfile);

		if(variavel == 0) break;

		printf("\tProduto: %s\n", p->Name);
		printf("\tQuantidade: %.2f\n", p->quant_atual);
		printf("\tPreço: %.2f\n", p->price);
		printf("\tValidade: %d/%d\n\n", p->mouth_valid, p->year_valid);
	}

    fclose(pfile);
}

void Lista_preco(struct desafio *p)
{
	int variavel;
	float price_min, price_max;

	pfile = fopen("DADOS_REGISTRADO.txt", "r");

	system("cls");

	printf("\nInsira um valor minímo e um máximo: ");
	scanf("%f %f", &price_min, &price_max);

	system("cls");

	printf("\n\n\n------PREÇOS ENTRE %.2f E %.2f------\n\n", price_min, price_max);

	while(1){

		variavel = fread(&(*p), sizeof(struct desafio), 1, pfile);

		if(variavel == 0){
			break;
		}

		if(p->price >= price_min && p->price <= price_max){
			printf("\nProduto: %s\n", p->Name);
			printf("Quantidade: %.2f\n", p->quant_atual);
			printf("Preço: %.2f\n", p->price);
			printf("Validade: %d/%d\n", p->mouth_valid, p->year_valid);
		}
	}

	fclose(pfile);
}

int pesquisar(struct desafio *p)
{
	char Name_aux[30];
	int i = 0, j, variavel;

	pfile = fopen("DADOS_REGISTRADO.txt", "r");

	printf("\nInsira um nome para pesquisar pelo produto: ");
	scanf("%s", Name_aux);

	while(1){

		variavel = fread(&(*p), sizeof(struct desafio), 1, pfile);

		for(j = 0; p->Name[j] != '\0'; j++)
		{
			if(Name_aux[j] != p->Name[j]) break;
		}

		if(variavel == 0) break;

		if(Name_aux[j] == '\0' && p->Name[j] == '\0')
		{
			printf("\n\n\t--------Produto encontrado--------\n");

			printf("\n\tProduto: %s\n", p->Name);
			printf("\tQuantidade: %.2f\n", p->quant_atual);
			printf("\tPreço: %.2f\n", p->price);
			printf("\tValidade: %d/%d\n", p->mouth_valid, p->year_valid);
			fclose(pfile);
			return i;
		}
		i++;
	}

	fclose(pfile);

	return -1;
}

void P_Name(struct desafio *p)
{

	int pesquisa;

	pfile = fopen("DADOS_REGISTRADO.txt", "r");

	pesquisa = pesquisar(p);

	if(pesquisa == -1)
	{
		system("cls"); system("color 76");
		printf("\n\n\n\t\nNenhum Produto encontrado.");
	}
	else{

	}

	fclose(pfile);
}

void Pesq_valid(struct desafio *p)
{
	int variavel, mouth, year;

	pfile = fopen("DADOS_REGISTRADO.txt", "r");

	printf("\n\nInsira o mês e o ano que deseja pesquisar: ");
	scanf("%d %d", &mouth, &year);

	system("cls");

	printf("\n\n\n\n\t--------Produto encontrado--------\n")	;

	while(1){

		variavel = fread(&(*p), sizeof(struct desafio), 1, pfile);

		if(variavel == 0) break;

		if(mouth == p->mouth_valid && year == p->year_valid){

			printf("\n\tProduto: %s\n", p->Name);
			printf("\tQuantidade: %.2f\n", p->quant_atual);
			printf("\tPreço: %.2f\n", p->price);
			printf("\tValidade: %d/%d\n", p->mouth_valid, p->year_valid);
		}
	}

	fclose(pfile);
}

void Alter_quant(struct desafio *p)
{
	float New_quant;
	int variavel, pesquisa;

	pfile = fopen("DADOS_REGISTRADO.txt", "r+");

	pesquisa = pesquisar(p);

	if(pesquisa == -1){

		system("cls"); system("color 76");
		printf("\n\n\n\t\nNenhum Produto encontrado.");
	}
	else{
	while(1){

		fseek(pfile, pesquisa * sizeof(struct desafio), 0);
		variavel = fread(&(*p), sizeof(struct desafio), 1, pfile);

		if(variavel == 0); break;
	}

		printf("\nInsira uma nova quantidade para o produto: ");
		scanf("%f", &New_quant);

		p->quant_atual += New_quant;

		fseek(pfile, pesquisa * sizeof(struct desafio) + sizeof(p->Name), 0);
		fwrite(&p->quant_atual, sizeof(p->quant_atual), 1, pfile);

		printf("\n%s %.2f %.2f %d/%d", p->Name, p->quant_atual, p->price, p->mouth_valid, p->year_valid);
	}

	fclose(pfile);

}

void Alter_price(struct desafio *p)
{
	float Price_aux;
	int variavel, pesquisa;

	pfile = fopen("DADOS_REGISTRADO.txt", "r+");

	pesquisa = pesquisar(p);

	if(pesquisa == -1) {
    	printf("\tNenhum registro encontrado.\n");
	}

	else{
		while(1){

		fseek(pfile, pesquisa * sizeof(struct desafio), 0);
		variavel = fread(&(*p), sizeof(struct desafio), 1, pfile);

		if(variavel == 1); break;
	}

		printf("\nInsira isso aí filhote: ");
		scanf("%f", &Price_aux);

		p->price = Price_aux;

		fseek(pfile, pesquisa * (sizeof(p->Name) + sizeof(p->quant_atual)), 0);
		fwrite(&p->price, sizeof(p->price), 1, pfile);

		printf("\n\n\n\nsafe");
	}

	fclose(pfile);
}


float Delete(struct desafio *p)
{
	int pesquisa, variavel;
	pesquisa = pesquisar(p);

	int mouth = NULL,	year = NULL;

	pfile = fopen("DADOS_REGISTRADO.txt", "r+");

	if(pesquisa == -1){

		system("cls"); system("color 76");
		printf("\n\n\n\t\nNenhum Produto encontrado.");
	}

	else{

		p->Name[0] = '*';
		//p->quant_atual = quant; p->price = price;
		p->mouth_valid = mouth;
		 p->year_valid = year;

		fseek(pfile, sizeof(struct desafio), 0);
		fwrite(&(*p), sizeof(struct desafio), 1, pfile);

		printf("\n\n\t\t-------------------PRODUTO EXCLUIDO-------------------");
	}

	fclose(pfile);
}

int main()
{
	int i, esc;
	setlocale(LC_ALL, "portuguese");

	struct desafio rui;
	struct desafio *p;
	p = &rui;

	do{
		system("cls");
		system("color 70");
		printf("\n\n\t\t\t _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
		printf("\n\t\t\t| 					                            |");
		printf("\n\t\t\t| 1 - Entrada de dados            				    |");
		printf("\n\t\t\t| 2 - Lista todos os dados tela  				    |");
		printf("\n\t\t\t| 3 - Lista produtos por faixa de preço  			    |");
		printf("\n\t\t\t| 4 - pesquisa um produto pelo nome completo   			    |");
		printf("\n\t\t\t| 5 - pesquisar por data de validade (mês/ano)			    |");
		printf("\n\t\t\t| 6 - altera quantidade em estoque pesquisado pelo nome 	    |");
		printf("\n\t\t\t| 7 - altera preço de um produto (nome completo)		    |");
		printf("\n\t\t\t| 8 - altera produto (pesquisa pelo nome)	     		    |");
		printf("\n\t\t\t| 9 - exclui produto (pesquisa pelo nome)  	 		    |");
		printf("\n\t\t\t| 10 - Sair do programa					            |");
		printf("\n\t\t\t|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|");
		printf("\n\n\t\t\t\tInsira um numero: ");
		scanf("%d", &esc);

		switch(esc){

			case 1:
				EntraDados(p);
			break;

			case 2:
				Lista_dados(p);
				getch();
			break;

			case 3:
				Lista_preco(p);
				getch();
			break;

			case 4:
				P_Name(p);
				getch();
			break;

			case 5:
				Pesq_valid(p);
				getch();
			break;

			case 6:
				Alter_quant(p);
				getch();
			break;

			case 7:
				Alter_price(p);
				getch();
			break;

			case 8:

			break;

			case 9:
				Delete(p);
				getch();
			break;

			case 10:
				system("cls");		system("color 72");

				printf("\n\t\t\t------------------------------ENCERRANDO O PROGRAMA------------------------------\n");
				printf("Obrigado por utilizar nosso software.\n desenvolvido em 06/2021.\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tDESENVOLVIDO POR ISAAC GERBONI & LUCAS GOMES\n\n\n\n\n");

				getch();
				exit(0);
			break;

			default:
					system("cls");		system("color 7C");
					 for(int Cont = 3; Cont!=0; Cont--)
					 {
						system("cls");
						printf("\n\n\t\tOpção não existente.");
						printf("\n\n\t\tRetornando em %d segundos" , Cont);
						Sleep(1000);
				 	 }
				break;
		}

	}while(esc != 10);

return 0;
}
