#include <stdio.h>

CADASTRARVEICULO(){
	char v[7][15] = {"Renavan", "Marca", "Modelo", "Placa", "Ano","Combustivel","Cor","Categoria"}; 
	char categoria[3][15] = {"economica","intermediaria","luxo"};
	char comb[3][15] = {"flex","gasolina","etanol"};
	printf("Preencha os seguintes campos:\n");
	fflush(stdin); 
    fgets(veiculo.disciplina, 40, stdin);
	
}

CADASTRARCLIENTE(){
	printf("Informe cliente");
	
}
LOCACAO(){
	printf("Locacao"); 
}
DEVOLUCAO(){
	printf("devolucao");
}
struct categoria
	{
		
	}
struct veiculo
  {
    char marca[50];
    char modelo[30];
    char placa[10];
    int ano;
    char combustivel[10];
    char cor[15];
    char categoria[12];  
  };
  
  struct veiculo veiculo[10];

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
  
  struct veiculo veiculo;  

int main(){
	int opcao;
	
	printf("Informe a opcao desejada: \n\t1- CADASTRAR VEICULO\n\t2- CADASTRAR CLIENTE \n\t3- LOCAR VEICULO \n\t4- DEVOLUCAO\n");
	scanf("%i",&opcao);
	switch(opcao){
		case 1:
			 CADASTRARVEICULO();
			 break;
		case 2:
			 CADASTRARCLIENTE();
			 break;
		case 3:
			 LOCACAO();
			 break;
		case 4:
			 DEVOLUCAO();
			 break;
		default:
			printf("Opcao Invalida.");
			break;
	}
}


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

