#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

FILE *arquivo;

/*############################# PROTOTIPOS ############################# */

void MENU();
void CADASTRARVEICULO();
void CONSULTARVEICULO();
void CADASTRARCLIENTE();
void LOCACAO();
void DEVOLUCAO();
void MENUCONSULTA();
void MOSTRARTODOS();
void MOSTRAR_DISPONIVEIS();
void MOSTRAR_POR_CATEGORIA();
/*############################# STRUCTS ############################# */
struct Veiculo{
    	char renavan[12];
		char marca[30];
    	char modelo[30];
    	char placa[10];
    	int ano;
    	char combustivel[10];
    	char cor[15];
    	char categoria[12];  
  	};
   	


struct cliente
  {
    char nome[100];
    char nasc[10];
    char modelo[30];
    char placa[10];
    int ano;
    char combustivel[10];
    char cor[15];
    char categoria[12];  
  };

/*############################# MENU PRINCIPAL ############################# */

int main(){
	MENU();
}

/*############################# PROCEDURES ############################# */
void MOSTRAR_DISPONIVEIS(int categoria){
	return;
}
void MOSTRAR_POR_CATEGORIA(){
	int op;
	char categoria[15];
	printf("Categoria: ");
	printf("Informe a Categoria: \n\n\t1- ECONOMICA\n\t2- INTERMEDIARIA \n\t3- LUXO\n");
	scanf("%d",&op);
	MOSTRAR_POR_CATEGORIA(op);
}
void MENUCONSULTAR(){
	int opcao;
	system("cls");
	printf("Informe a opcao desejada: \n\n\t1- DISPONIVEIS\n\t2- DISPONIVEIS POR CATEGORIA \n\t3- MOSTRAR TODOS\n");
	scanf("%i",&opcao);
	switch(opcao){
		case 1:
			 system("cls");
			 MOSTRAR_DISPONIVEIS();
			 main();
			 break;
		case 2:
			 system("cls");
			 printf("Informe a Categoria: \n\n\t1- ECONOMICA\n\t2- INTERMEDIARIA \n\t3- LUXO\n");
			 main();
			 break;
		case 3:
			 system("cls");
			 MOSTRARTODOS();
			 main();
			 break;
		default:
			system("cls");
			printf("Opcao Invalida.");
			main();
			break;
	}
}
void MENU(){
	int opcao;
	system("cls");
	printf("Informe a opcao desejada: \n\n\t1- CADASTRAR VEICULO\n\t2- CADASTRAR CLIENTE \n\t3- LOCAR VEICULO \n\t4- DEVOLUCAO\n\t5- CONSULTAR VEICULO\n");
	scanf("%i",&opcao);
	switch(opcao){
		case 1:
			 system("cls");
			 CADASTRARVEICULO();
			 main();
			 break;
		case 2:
			 system("cls");
			 CADASTRARCLIENTE();
			 main();
			 break;
		case 3:
			 system("cls");
			 LOCACAO();
			 main();
			 break;
		case 4:
			 system("cls");
			 DEVOLUCAO();
			 main();
			 break;
		case 5:
			system("cls");
			MENUCONSULTAR();
			main();
		default:
			system("cls");
			printf("Opcao Invalida.");
			main();
			break;
	}
}


/*###################################################*/

void MOSTRARTODOS(){
	
	int reg;
	struct Veiculo carro;
	
	if((arquivo = fopen("dados.dat","rb")) == NULL){
		printf("ERRO AO ABRIR ARQUIVO");
		system("pause");
		exit(0);
	}
	// posiciona o arquivo no inicio
	fseek(arquivo,0,SEEK_SET);
	
	reg=0;
	do {
	// le registro
	fread(&carro, sizeof(struct Veiculo), 1, arquivo);
	
	// se chegou ao fim, para
	if (feof(arquivo)) break;
	
	// mostra dados
	printf ("Registro numero: %d\n\n",reg);
	printf ("RENAVAN: %s",carro.renavan);
	printf ("MARCA: %s",carro.marca);
	printf ("MODELO: %s",carro.modelo);
	printf ("PLACA: %s",carro.placa);
	printf ("ANO: %d\n",carro.ano);
	printf ("COMBUSTIVEL: %s\n",carro.combustivel);		
	printf ("COR: %s",carro.cor);
	printf ("CATEGORIA: %s\n",carro.categoria);
	printf ("--------------------------------\n");
	
	reg++;
	} while(!feof(arquivo)); // repete enquanto nao chegar ao fim
	getch();
}
void CONSULTARVEICULO(){
    struct Veiculo carro[100];
    int i = 0;
	if((arquivo = fopen("dados.dat","rb")) == NULL){
		printf("ERRO AO ABRIR ARQUIVO");
		system("pause");
		exit(0);
	}
	while(!feof(arquivo)){
		if(fread(&carro,sizeof(Veiculo),1,arquivo) == 1){
			printf("RENAVAN: %s"	  ,carro[i].renavan);
			printf("MARCA: %s"		  ,carro[i].marca);
			printf("MODELO: %s"		  ,carro[i].modelo);
			printf("PLACA: %s"        ,carro[i].placa);
			printf("ANO: %d\n"        ,carro[i].ano);
			printf("COMBUSTIVEL: %s\n",carro[i].combustivel);
			printf("COR: %s"      	  ,carro[i].cor);
			printf("CATEGORIA: %s\n"  ,carro[i].categoria);
		}
		i++;
	}
	fclose(arquivo);
	getch();
}

/*###################################################*/

void CADASTRARVEICULO(){
   struct Veiculo carro;
	int opcao01;
	
	if((arquivo = fopen("dados.dat","ab")) == NULL){
		printf("ERRO AO ABRIR ARQUIVO");
		system("pause");
		exit(0);
	}
	printf("Informe o Renavam:\n");
	fflush(stdin); 
	fgets(carro.renavan, 12, stdin);
	
	printf("Informe o Marca:\n");
	fflush(stdin); 
	fgets(carro.marca, 30, stdin);
	
	printf("Informe o Modelo:\n");
	fflush(stdin); 
	fgets(carro.modelo,30, stdin);
	
	printf("Informe o placa:\n");
	fflush(stdin); 
	fgets(carro.placa, 10, stdin);
	
	printf("Informe o ano:\n");
	fflush(stdin); 
	scanf("%d",&carro.ano);
	
	printf("Informe o combustivel:\n1-flex\n2-gasolina\n3-etanol: ");
	fflush(stdin); 
	scanf("%d",&opcao01);
	
	switch(opcao01){
		case 1:
			fflush(stdin); 
			strcpy(carro.combustivel,"flex");
			break;
		case 2:
			strcpy(carro.combustivel,"gasolina");
			break;
		case 3:
			strcpy(carro.combustivel,"etanol");
			break;
		default:
			printf("Opcao Invalida.");
			break;
	}
	
	printf("Informe o cor:\n");
	fflush(stdin); 
	fgets(carro.cor, 15, stdin);
	
	printf("Informe a categoria:\n1-economica\n2-intermediaria\n3-luxo: ");
	fflush(stdin); 
	scanf("%d",&opcao01);
	
	switch(opcao01){
		case 1:
			fflush(stdin); 
			strcpy(carro.categoria,"economica");
			break;
		case 2:
			fflush(stdin); 
			strcpy(carro.categoria,"intermediaria");
			break;
		case 3:
			fflush(stdin); 
			strcpy(carro.categoria,"luxo");
			break;
		default:
			printf("Opcao Invalida.");
			break;
	}
	
	if (fwrite(&carro,sizeof(struct Veiculo),1,arquivo) == 1){
		system("cls");
		printf("Cadastrado com Sucesso.\n");	
		fclose(arquivo);
		system("pause");	
	}else{
		system("cls");
		printf("ERRO AO EFETUAR CADASTRO.\n");
		fclose(arquivo);
	}
}
/*###################################################*/

void CADASTRARCLIENTE(){
	printf("cliente");
	
}

/*###################################################*/

void LOCACAO(){
	printf("Locacao"); 
}

/*###################################################*/

void DEVOLUCAO(){
	printf("devolucao");
}


/*############################# PROCEDURE MENU ############################# */  




//Criando a variável aluno que será do
//     tipo struct ficha_de_aluno       
//  struct ficha_de_aluno aluno;
// 
//  printf("\n---------- Cadastro de aluno -----------\n\n\n");
//   
//  printf("Nome do aluno ......: ");
//  fflush(stdin); 
// 
//  /*usaremos o comando fgets() para ler strings, no caso o nome
//   do aluno e a disciplina
//   fgets(variavel, tamanho da string, entrada)
//   como estamos lendo do teclado a entrada é stdin (entrada padrão),
//   porém em outro caso, a entrada tambem poderia ser um arquivo  */
// 
//  fgets(aluno.nome, 40, stdin);
//   
//  printf("Disciplina ......: ");
//  fflush(stdin); 
//  fgets(aluno.disciplina, 40, stdin);
//   
//  printf("Informe a 1a. nota ..: ");
//  scanf("%f", &aluno.nota_prova1);
//   
//  printf("Informe a 2a. nota ..: ");
//  scanf("%f", &aluno.nota_prova2);  
//   
//  printf("\n\n --------- Lendo os dados da struct ---------\n\n");
//  printf("Nome ...........: %s", aluno.nome);
//  printf("Disciplina .....: %s", aluno.disciplina);
//  printf("Nota da Prova 1 ...: %.2f\n" , aluno.nota_prova1);
//  printf("Nota da Prova 2 ...: %.2f\n" , aluno.nota_prova2);
//   
//  getch();
//  return(0);
//} 

