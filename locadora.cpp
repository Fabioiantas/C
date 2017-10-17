#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*############################# GLOBAIS ############################# */
typedef struct {
	int dia;
	int mes;
	int ano;
} Data_2;

struct Data{
	int dia;
	int mes;
	int ano;
};
typedef struct Data date;

int bissexto (int ano);
unsigned long dist_dias (Data_2 inicio, Data_2 fim);

int dias_mes[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                       {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
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
void EXIBIRCLIENTE(int opcao);
void LOCARVEICULO();
bool VALIDACLIENTE(char cpf[15]);
bool VALIDAVEICULOLOC(char placa[9]);
bool ATUALIZARVEICULODEVOLUCAO(char placa[9],char cpf[15]);
bool VALIDADEVOLUCAO();
void MOSTRAR_POR_CATEGORIA(int op);
int EXIBIRCLIENTELOC(char categoria[15]);
int VALIDA_DATA(int dia, int mes, int ano);
int CALCULARDIAS(date dt_ini, date dt_fim);
int VERIFICAATRASO(char placa[9], Data_2 dt_dev);
int EXIBIRVEICULOSLOCADOS();
int BISSEXTO (int ano);
float VALORTOTAL(char placa[9]);
float VALORTOTALATRASO(char placa[9],Data_2 dt_dev);

/*############################# STRUCTS! ############################# */


struct Veiculo{
    char renavan[12];
	char marca[30];
    char modelo[30];
    char placa[10];
    int ano;
    char combustivel[10];
    char cor[15];
    char categoria[15];  
    char cpfcliente[15];
    date dt_ini;
    date dt_fim;
};
   	
struct Cliente{
    char nome[100];
    date nasc;
    char rg[10];
    char cpf[15];
    char nacionalidade[20];
    char cnh[20];
    date validadecnh;
};

/*############################# MENU PRINCIPAL ############################# */

int main(){
	
	MENU();
}

/*############################# PROCEDURES ############################# */

bool ATUALIZARVEICULODEVOLUCAO(char placa[9],char cpf[15]){
	struct Veiculo veiculo;
	date dt_ini;
	date dt_fim;
	char *substring;
	bool verificacao = false;
	int  cont = 0;
	int  valida,op;
	bool continuar = true;
	
	if( (arquivo = fopen("veiculo.dat","r+b"))==NULL){
		printf("Erro ao abrir arquivo cliente.dat.\n");
		system("pause");
		exit(1);
	}
	while(!feof(arquivo)){
		if(fread(&veiculo,sizeof(struct Veiculo),1, arquivo) == 1){
			substring = strstr(strupr(veiculo.placa),strupr(placa));
		if (substring != NULL){
				verificacao = true;
				break;
			}			 
		}
		cont++;
	}
	if (!verificacao){
		printf("\nVeiculo nao encontrado => %d.",cont);
	}else{
		strcpy(veiculo.cpfcliente,cpf);
		
		veiculo.dt_ini.dia = NULL;
		veiculo.dt_ini.mes = NULL;
		veiculo.dt_ini.ano = NULL;
		
		veiculo.dt_fim.dia = NULL;
		veiculo.dt_fim.mes = NULL;
		veiculo.dt_fim.ano = NULL;
		
		fseek(arquivo, sizeof(struct Veiculo) * cont, SEEK_SET);
		fwrite(&veiculo, sizeof(struct Veiculo), 1, arquivo);
		printf("\nAtualizado com sucesso pressione qualquer tecla para continuar.\n");
		getch();
	}
	fclose(arquivo);	
	return verificacao;
}

bool VALIDADEVOLUCAO(){
	char placa[9];
	char cpf[15];
	bool ret = true;
	Data_2 dt_dev;
	int atraso;
	
	printf("Informe a placa: ");
	fflush(stdin);
	fgets(placa,10,stdin);
	if(VALIDAVEICULOLOC(strtok(placa,"\n"))){
		system("cls");
		printf("Veiculo nao cadastrado ou nao esta em uso.\n");
		system("pause");
		return false;
	}else{
		printf("Informe a data de Devolucao no formato: dia/mes/ano\n");
		scanf("%d/%d/%d", &dt_dev.dia, &dt_dev.mes, &dt_dev.ano);
		atraso = VERIFICAATRASO(placa,dt_dev);
		if (atraso > 0){
			printf("Total: %f\n",VALORTOTAL(placa));
			printf("Multa por %d dia de atraso = %f\n",atraso,VALORTOTALATRASO(placa,dt_dev));
			printf("Total com Multa: %f\n ",VALORTOTAL(placa)+VALORTOTALATRASO(placa,dt_dev));
			strcpy(cpf,"disponivel");
			if(!ATUALIZARVEICULODEVOLUCAO(placa,cpf)){
				ret = false;
				system("cls");
				printf("Erro ao devolver veiculo/");
				system("pause");
				exit(0);
			}
		}else{
			printf("Total: %f\n",VALORTOTAL(placa));
			system("pause");
			if(!ATUALIZARVEICULODEVOLUCAO(placa,cpf)){
				ret = false;
				system("cls");
				printf("Erro ao devolver veiculo/");
				system("pause");
				exit(0);
			}
		}
	return ret;
	}
}

void DEVOLUCAO(){
	int op;
	float total;
	char placa[9];
	char cpf[15];
	Data_2 dt_dev;
	int atraso;
	printf("--------------------------DEVOLUCAO DE VEICULO--------------------------\nInforme a Opcao: \n\n\t1- INFORMAR PLACA\n\t2- MOSTRAR TODOS EM USO \n\t3- INFORMAR CPF\n");
	scanf("%d",&op);
	switch(op){
		case 1:
			printf("Informe a placa: ");
			fflush(stdin);
			fgets(placa,10,stdin);
			if(VALIDAVEICULOLOC(strtok(placa,"\n"))){
				system("cls");
				printf("Veiculo nao cadastrado ou nao esta em uso.\n");
				system("pause");
				return;
			}else{
				printf("Informe a data de Devolucao no formato: dia/mes/ano\n");
				scanf("%d/%d/%d", &dt_dev.dia, &dt_dev.mes, &dt_dev.ano);
				atraso = VERIFICAATRASO(placa,dt_dev);
				if (atraso > 0){
					printf("Total: %f\n",VALORTOTAL(placa));
					printf("Multa por %d dia de atraso = %f\n",atraso,VALORTOTALATRASO(placa,dt_dev));
					printf("Total com Multa: %f\n ",VALORTOTAL(placa)+VALORTOTALATRASO(placa,dt_dev));
					strcpy(cpf,"disponivel");
					if(!ATUALIZARVEICULODEVOLUCAO(placa,cpf)){
						system("cls");
						printf("Erro ao devolver veiculo/");
						system("pause");
						exit(0);
					}
					return;
				}else{
					printf("Total: %f\n",VALORTOTAL(placa));
					system("pause");
					if(!ATUALIZARVEICULODEVOLUCAO(placa,cpf)){
						system("cls");
						printf("Erro ao devolver veiculo/");
						system("pause");
						exit(0);
					}
					return;
				}
			}
			break;
		case 2:
			if (EXIBIRVEICULOSLOCADOS() < 1){
				system("cls");
				printf("Nao ha veiculos Locados.");
			}else
				VALIDADEVOLUCAO();
			break;
		case 3:
			NULL;
			break;
	}
}

int VERIFICAATRASO(char placa[9], Data_2 dt_dev){
	struct Veiculo veiculo;
	int igual;	
	Data_2 dt_f;
	int dias = 0;
	if( (arquivo = fopen("veiculo.dat","r+b"))==NULL){
		printf("Erro ao abrir arquivo cliente.dat.\n");
		system("pause");
		exit(1);
	}
	while(!feof(arquivo)){
		if(fread(&veiculo,sizeof(struct Veiculo),1, arquivo) == 1){
			igual = stricmp(placa,strtok(veiculo.placa,"\n"));
			if (igual == 0){
				dt_f.dia = veiculo.dt_fim.dia;
				dt_f.mes = veiculo.dt_fim.mes;
				dt_f.ano = veiculo.dt_fim.ano;
				dias = dist_dias(dt_f,dt_dev);
			}			 
		}
	}
	return dias;
}

float VALORTOTALATRASO(char placa[9], Data_2 dt_dev){
	
	float valor = 0;
	int reg;
	struct Veiculo veiculo;
	char categoria[15];
	char *substring;
	bool found, verificacao = false;
	int igual,iguald;	
	Data_2 dt_i, dt_f;
	float diaria;
	int dias;

	if( (arquivo = fopen("veiculo.dat","r+b"))==NULL){
		printf("Erro ao abrir arquivo cliente.dat.\n");
		system("pause");
		exit(1);
	}
	while(!feof(arquivo)){
		if(fread(&veiculo,sizeof(struct Veiculo),1, arquivo) == 1){
			igual = stricmp(placa,strtok(veiculo.placa,"\n"));
			if (igual == 0){
				if(stricmp("economica",strtok(veiculo.categoria,"\n")) == 0){
					diaria = 89.90;
				}else if(stricmp("intermediaria",strtok(veiculo.categoria,"\n")) == 0){
					diaria = 174.90;
				}else if(stricmp("luxo",strtok(veiculo.categoria,"\n")) == 0){
					diaria = 289.90;
				}else
					diaria = 0;
					
			    dt_f.dia = veiculo.dt_fim.dia;
				dt_f.mes = veiculo.dt_fim.mes;
				dt_f.ano = veiculo.dt_fim.ano;
				dias = dist_dias(dt_f,dt_dev);	
				
				diaria = diaria * 2;			
				
				valor = dias * diaria;
				
				break;
			}			 
		}
	}
	return valor;
}

float VALORTOTAL(char placa[9]){
	float valor = 0;
	int reg;
	struct Veiculo veiculo;
	char categoria[15];
	char *substring;
	bool found, verificacao = false;
	int igual,iguald;	
	Data_2 dt_i, dt_f;
	float diaria;
	int dias;

	if( (arquivo = fopen("veiculo.dat","r+b"))==NULL){
		printf("Erro ao abrir arquivo cliente.dat.\n");
		system("pause");
		exit(1);
	}
	while(!feof(arquivo)){
		if(fread(&veiculo,sizeof(struct Veiculo),1, arquivo) == 1){
			igual = stricmp(placa,strtok(veiculo.placa,"\n"));
			if (igual == 0){
				if(stricmp("economica",strtok(veiculo.categoria,"\n")) == 0){
					diaria = 89.90;
				}else if(stricmp("intermediaria",strtok(veiculo.categoria,"\n")) == 0){
					diaria = 174.90;
				}else if(stricmp("luxo",strtok(veiculo.categoria,"\n")) == 0){
					diaria = 289.90;
				}else
					diaria = 0;
					
				dt_i.dia = veiculo.dt_ini.dia;
				dt_i.mes = veiculo.dt_ini.mes;
				dt_i.ano = veiculo.dt_ini.ano;
				
				dt_f.dia = veiculo.dt_fim.dia;
				dt_f.mes = veiculo.dt_fim.mes;
				dt_f.ano = veiculo.dt_fim.ano;
				dias = dist_dias(dt_i,dt_f);				
				valor = dias * diaria;
				break;
			}			 
		}
	}
	return valor;
}

bool VALIDAVEICULOLOC(char placa[9]){
	int reg;
	struct Veiculo veiculo;
	char categoria[15];
	char *substring;
	bool found, verificacao = false;
	int igual,iguald;	
	if( (arquivo = fopen("veiculo.dat","r+b"))==NULL){
		printf("Erro ao abrir arquivo cliente.dat.\n");
		system("pause");
		exit(1);
	}
	while(!feof(arquivo)){
		if(fread(&veiculo,sizeof(struct Veiculo),1, arquivo) == 1){
			//substring = strstr(strupr(veiculo.placa),strupr(placa));
			igual = stricmp(placa,strtok(veiculo.placa,"\n"));
			iguald = stricmp("disponivel",strtok(veiculo.cpfcliente,"\n"));
		if ((igual == 0) && (iguald == 0) ){
				verificacao = true;
				break;
			}			 
		}
	}
	if (!verificacao){
		found = false;
	}else{
		found = true;
	}
	fclose(arquivo);	
	return found;
}

bool VALIDACLIENTE(char cpf[15]){
	int reg,igual;
	struct Cliente cliente;
	bool verificacao = false;
	char *substring = NULL;
	
	if( (arquivo = fopen("cliente.dat","r+b"))==NULL){
		printf("Erro ao abrir arquivo cliente.dat.\n");
		system("pause");
		exit(1);
	}
	while(!feof(arquivo)){
		if(fread(&cliente,sizeof(struct Cliente),1, arquivo) == 1){
			//substring = strstr(strupr(cliente.cpf),strupr(cpf));
			igual = stricmp(cpf,strtok(cliente.cpf,"\n"));
		if (igual == 0){
				verificacao = true;
				break;
			}			 
		}
	}
	fclose(arquivo);
	return verificacao;
}

void LOCARVEICULO(){
	struct Veiculo veiculo;
	date dt_ini;
	date dt_fim;
	char *substring;
	bool verificacao = false;
	int  cont = 0;
	int  valida,op;
	char placa[9];
	char cpf[15],categoria[15];
	bool continuar = true;
	do{
		printf("Informe a Categoria: \n\n\t1- ECONOMICA\n\t2- INTERMEDIARIA \n\t3- LUXO\n\t4- TODOS\n");
		scanf("%d",&op);
		system("cls");
		switch(op){
			case 1:
				strcpy(categoria,"economica");
				if (EXIBIRCLIENTELOC(categoria) < 1){
					system("cls");
					printf("Nao ha carros disponiveis\n");
					system("pause");
					return;
				}
				break;
			case 2:
				strcpy(categoria,"intermediaria");
				if (EXIBIRCLIENTELOC(categoria) < 1){
					system("cls");
					printf("Nao ha carros disponiveis\n");
					system("pause");
					return;
				}
				break;
			case 3:
				strcpy(categoria,"luxo");
				if (EXIBIRCLIENTELOC(categoria) < 1){
					system("cls");
					printf("Nao ha carros disponiveis\n");
					system("pause");
					return;
				}
				break;
			case 4:
				strcpy(categoria,"todos");
				if (EXIBIRCLIENTELOC(categoria) < 1){
					system("cls");
					printf("Nao ha carros disponiveis\n");
					system("pause");
					return;
				}
				break;
			default:
				system("cls");
				printf("Opcao invalida");
				system("pause");
				return;
		}
		printf("\nInforme a placa ou sair para cancelar: ");
		fflush(stdin); 
		fgets(placa, 9, stdin);
		if(strcmp(strtok(placa,"\n"),"sair") == 0){
			return;
		}
		if (!VALIDAVEICULOLOC(placa)){
			printf("Veiculo nao disponivel ou nao cadastrado, refaca a operacao.\n");
			system("pause");
			return;
		}
		printf("\nInforme o CPF ou sair para cancelar: ");
		fflush(stdin); 
	 	fgets(cpf, 15, stdin);
		if(strcmp(strtok(cpf,"\n"),"sair") == 0){
			return;
		}
		if (!VALIDACLIENTE(strtok(cpf,"\n"))){
			printf("Cliente nao cadastrado, refaca a operacao.\n");
			system("pause");
			return;
		}else
			break;
	}while(true);
	
	printf("Coloque data incial no formato: dia/mes/ano\n");
	scanf("%d/%d/%d", &dt_ini.dia, &dt_ini.mes, &dt_ini.ano);
	printf("Coloque data final no formato: dia/mes/ano\n");
	scanf("%d/%d/%d", &dt_fim.dia, &dt_fim.mes, &dt_fim.ano);
	
	if( (arquivo = fopen("veiculo.dat","r+b"))==NULL){
		printf("Erro ao abrir arquivo cliente.dat.\n");
		system("pause");
		exit(1);
	}
	while(!feof(arquivo)){
		if(fread(&veiculo,sizeof(struct Veiculo),1, arquivo) == 1){
			substring = strstr(strupr(veiculo.placa),strupr(placa));
		if (substring != NULL){
				verificacao = true;
				break;
			}			 
		}
		cont++;
	}
	if (!verificacao){
		printf("\nVeiculo nao encontrado => %d.",cont);
	}else{
		strcpy(veiculo.cpfcliente,cpf);
		
		veiculo.dt_ini.dia = dt_ini.dia;
		veiculo.dt_ini.mes = dt_ini.mes;
		veiculo.dt_ini.ano = dt_ini.ano;
		
		veiculo.dt_fim.dia = dt_fim.dia;
		veiculo.dt_fim.mes = dt_fim.mes;
		veiculo.dt_fim.ano = dt_fim.ano;
		
		fseek(arquivo, sizeof(struct Veiculo) * cont, SEEK_SET);
		fwrite(&veiculo, sizeof(struct Veiculo), 1, arquivo);
		printf("\nAtualizado com sucesso pressione qualquer tecla para continuar.\n");
		getch();
	}
	fclose(arquivo);	
}

void EXIBIRCLIENTE(int opcao){
	int reg;
	char cpf[15];
	struct Cliente cliente;
	system("cls");
	
	if((arquivo = fopen("cliente.dat","rb")) == NULL){
		printf("ERRO AO ABRIR ARQUIVO");
		system("pause");
		exit(0);
	}
	// posiciona o arquivo no inicio
	fseek(arquivo,0,SEEK_SET);
	
	reg=0;
	if(opcao == 1){
		do {
		// le registro
		fread(&cliente, sizeof(struct Cliente), 1, arquivo);
		
		// se chegou ao fim, para
		if (feof(arquivo)) break;
		
		// mostra dados
		printf ("--------------------------------\n");
		printf ("Registro numero: %d\n\n",reg);
		printf ("NOME: %s",cliente.nome);
		printf ("NASCIMENTO: %d/%d/%d",cliente.nasc.dia,cliente.nasc.mes,cliente.nasc.ano);
		printf ("\nRG: %s",cliente.rg);
		printf ("CPF: %s",cliente.cpf);
		printf ("NACIONALIDADE: %s",cliente.nacionalidade);
		printf ("REGISTRO CNH:  %s",cliente.cnh);		
		printf ("VALIDADE CNH: %d/%d/%d",cliente.validadecnh.dia,cliente.validadecnh.mes,cliente.validadecnh.ano);
		printf ("\n--------------------------------\n");		
		reg++;
	} while(!feof(arquivo)); // repete enquanto nao chegar ao fim
	}else{
		printf("Informe o CPF: ");
		fflush(stdin); 
	    fgets(cpf, 15, stdin);
	    system("cls");
	    do {
		// le registro
		fread(&cliente, sizeof(struct Cliente), 1, arquivo);
		
		// se chegou ao fim, para
		if (feof(arquivo)) break;
		
		// mostra dados
		if (strcmp(cpf,cliente.cpf) == 0){
	    	printf ("--------------------------------\n");
			printf ("Registro numero: %d\n\n",reg);
			printf ("NOME: %s",cliente.nome);
			printf ("NASCIMENTO: %d/%d/%d",cliente.nasc.dia,cliente.nasc.mes,cliente.nasc.ano);
			printf ("\nRG: %s",cliente.rg);
			printf ("CPF: %s",cliente.cpf);
			printf ("NACIONALIDADE: %s",cliente.nacionalidade);
			printf ("REGISTRO CNH:  %s",cliente.cnh);		
			printf ("VALIDADE CNH: %d/%d/%d",cliente.validadecnh.dia,cliente.validadecnh.mes,cliente.validadecnh.ano);
			printf ("\n--------------------------------\n");
			reg++;
		}
		}while(!feof(arquivo)); // repete enquanto nao chegar ao fim
	}
	fclose(arquivo);
	getch();
}

int EXIBIRCLIENTELOC(char categoria[15]){
	int reg;
	char nome[100], cpf[15], modelo[20], placa[9];
	struct Cliente cliente;
	struct Veiculo carro;
	if((arquivo = fopen("cliente.dat","rb")) == NULL){
		printf("ERRO AO ABRIR ARQUIVO");
		system("pause");
		exit(0);
	}
	// posiciona o arquivo no inicio
	fseek(arquivo,0,SEEK_SET);	
	reg=0;
	printf ("---------------------- Clientes Cadastrados ----------------------------------------\n");
	do {
		// le registro
		fread(&cliente, sizeof(struct Cliente), 1, arquivo);
		
		// se chegou ao fim, para
		if (feof(arquivo)) break;
		strcpy(nome,cliente.nome);
		strcpy(cpf,cliente.cpf);
		// mostra dados
		strtok(nome,"\n");
		strtok(cpf,"\n");
		printf ("NOME: %s ",nome);
		printf ("| CPF: %s\n",cpf);
		reg++;
	} while(!feof(arquivo)); // repete enquanto nao chegar ao fim
	fclose(arquivo);
	if((arquivo = fopen("veiculo.dat","rb")) == NULL){
		printf("ERRO AO ABRIR ARQUIVO");
		system("pause");
		exit(0);
	}
	// posiciona o arquivo no inicio
	fseek(arquivo,0,SEEK_SET);
	reg=0;
	printf ("\n---------------------------------------- Veiculos Disponiveis - %s ----------------------------------------\n\n",categoria);
	while(!feof(arquivo)){
		// le registro
		fread(&carro, sizeof(struct Veiculo), 1, arquivo);		
		// se chegou ao fim, para
		if (feof(arquivo)) break;
		// mostra dados
		if (strcmp (categoria,carro.categoria) == 0 && strcmp ("disponivel",carro.cpfcliente) == 0){
			reg++;
			strcpy(modelo,carro.modelo);
			strcpy(placa,carro.placa);
			strtok(modelo,"\n");
			strtok(placa,"\n");
			printf ("%d -> MODELO: %s",reg,modelo);
			printf (" | PLACA: %s\n",placa);
		}else if (strcmp ("disponivel",carro.cpfcliente) == 0 && strcmp ("todos",categoria) == 0){
			reg++;
			strcpy(modelo,carro.modelo);
			strcpy(placa,carro.placa);
			strtok(modelo,"\n");
			strtok(placa,"\n");
			printf ("%d -> MODELO: %s",reg,modelo);
			printf (" | PLACA: %s\n",placa);
		}
	}
	printf ("\n------------------------------------------------------------------------------------------------------------------------\n");	
	fclose(arquivo);
	return reg;
}

int EXIBIRVEICULOSLOCADOS(){
	int reg;
	struct Veiculo carro;
	char nome[100], cpf[15], modelo[20], placa[9];
	
	if((arquivo = fopen("veiculo.dat","rb")) == NULL){
		printf("ERRO AO ABRIR ARQUIVO");
		system("pause");
		exit(0);
	}
	// posiciona o arquivo no inicio
	fseek(arquivo,0,SEEK_SET);
	reg=0;
	printf ("\n-------------------------- Veiculos Locados --------------------------\n\n");
	while(!feof(arquivo)){
		// le registro
		fread(&carro, sizeof(struct Veiculo), 1, arquivo);		
		// se chegou ao fim, para
		if (feof(arquivo)) break;
		// mostra dados
		if (strcmp ("disponivel",carro.cpfcliente) != 0){
			reg++;
			strcpy(modelo,carro.modelo);
			strcpy(placa,carro.placa);
			strtok(modelo,"\n");
			strtok(placa,"\n");
			printf ("%d -> MODELO: %s",reg,modelo);
			printf (" | PLACA: %s",placa);
			printf (" | CPF: %s\n",carro.cpfcliente);
	}
	printf ("\n----------------------------------------------------\n");	
	fclose(arquivo);
	getch();
	return reg;
	}
}

void MOSTRAR_DISPONIVEIS(){
	int reg;
	struct Veiculo carro;
	char categoria[15];
	int cont = 0; 
	system("cls");
	if((arquivo = fopen("veiculo.dat","rb")) == NULL){
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
		if (strcmp("disponivel",carro.cpfcliente) == 0){
			cont++;
			printf ("--------------------------------\n");
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
		}
	} while(!feof(arquivo)); // repete enquanto nao chegar ao fim
	if (cont == 0){
		printf("Nao ha veiculos disponiveis.");
	}
	fclose(arquivo);
	getch();
}

void MOSTRAR_POR_CATEGORIA(int op){
	int reg;
	struct Veiculo carro;
	char categoria[15];
	
	if (op == 1){
		strcpy(categoria,"economica");
	}
	else if (op == 2){
		strcpy(categoria,"intermediaria");
	}
	else{
		strcpy(categoria,"luxo");
	}
		
	if((arquivo = fopen("veiculo.dat","rb")) == NULL){
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
		if (strcmp (categoria,carro.categoria) == 0 && strcmp ("disponivel",carro.cpfcliente) == 0){
			system("cls");
			printf ("--------------------------------\n");
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
		}
	} while(!feof(arquivo)); // repete enquanto nao chegar ao fim
	if(reg == 0)
		printf("Nao ha Veiculos Cadastrados. %d",reg);
	fclose(arquivo);
	getch();
}

void MENUCONSULTARVEICULO(){
	int opcao;
	int opcao2;
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
			 scanf("%d",&opcao2);
			 MOSTRAR_POR_CATEGORIA(opcao2);
			 break;
		case 3:
			 system("cls");
			 MOSTRARTODOS();
			 main();
			 break;
		default:
			system("cls");
			printf("Opcao Invalida.");
			return;
	}
}

void MENUCONSULTARCLIENTE(){
	int opcao;
	int opcao2;
	system("cls");
	printf("Informe a opcao desejada: \n\n\t1- TODOS\n\t2- POR CPF\n");
	scanf("%i",&opcao);
	switch(opcao){
		case 1:
			 system("cls");
			 EXIBIRCLIENTE(opcao);
			 main();
			 break;
		case 2:
			 system("cls");
			 EXIBIRCLIENTE(opcao);
			 break;
		default:
			system("cls");
			printf("Opcao Invalida.");
			return;
	}
}

void MENU(){
	int opcao;
	char placa[9];
	char cpf[15];
	system("cls");
	printf("Informe a opcao desejada: \n\n\t1- CADASTRAR VEICULO\n\t2- CADASTRAR CLIENTE \n\t3- LOCAR VEICULO \n\t4- DEVOLUCAO\n\t5- CONSULTAR VEICULO\n\t6- CONSULTAR CLIENTE\n");
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
			 LOCARVEICULO();
			 main();
			 break;
		case 4:
			 system("cls");
			 DEVOLUCAO();
			 main();
			 break;
		case 5:
			system("cls");
			MENUCONSULTARVEICULO();
			main();
		case 6:
			system("cls");
			MENUCONSULTARCLIENTE();
			main();
		default:
			system("cls");
			printf("Opcao Invalida.");
			return;
	}
}

void MOSTRARTODOS(){
	
	int reg;
	struct Veiculo carro;
	system("cls");
	
	if((arquivo = fopen("veiculo.dat","rb")) == NULL){
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
		printf ("--------------------------------\n");
		printf ("Registro numero: %d\n\n",reg);
		printf ("RENAVAN: %s",carro.renavan);
		printf ("MARCA: %s",carro.marca);
		printf ("MODELO: %s",carro.modelo);
		printf ("PLACA: %s",carro.placa);
		printf ("ANO: %d\n",carro.ano);
		printf ("COMBUSTIVEL: %s\n",carro.combustivel);		
		printf ("COR: %s",carro.cor);
		printf ("CATEGORIA: %s\n",carro.categoria);
		printf ("CLIENTE: %s\n",carro.cpfcliente);
		printf("INICIO: %d/%d/%d\n",carro.dt_ini.dia,carro.dt_ini.mes,carro.dt_ini.ano);
		printf("FIM: %d/%d/%d\n",carro.dt_fim.dia,carro.dt_fim.mes,carro.dt_fim.ano);
		printf ("--------------------------------\n");
		
		reg++;
	} while(!feof(arquivo)); // repete enquanto nao chegar ao fim
	if (reg == 0)
		printf("Nao ha veiculos cadastrados.\n");
	fclose(arquivo);
	getch();
}

void CONSULTARVEICULO(){
    struct Veiculo carro[100];
    int i = 0;
	if((arquivo = fopen("veiculo.dat","rb")) == NULL){
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

void CADASTRARVEICULO(){
   struct Veiculo carro;
	int opcao01,opc;
	
	if((arquivo = fopen("veiculo.dat","ab")) == NULL){
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
	fgets(carro.modelo, 30, stdin);
	
	printf("Informe o placa:\n");
	fflush(stdin); 
	fgets(carro.placa, 10, stdin);
	
	printf("Informe o ano:\n");
	fflush(stdin); 
	scanf("%d",&carro.ano);
	
	printf("Informe o combustivel:\n1-flex\n2-gasolina\n3-etanol: ");
	fflush(stdin); 
	scanf("%d",&opc);
	switch(opc){
		case 1:
			//fflush(stdin); 
			strcpy(carro.combustivel,"flex");
			break;
		case 2:
			//fflush(stdin); 
			strcpy(carro.combustivel,"gasolina");
			break;
		case 3:
			//fflush(stdin); 
			strcpy(carro.combustivel,"etanol");
			break;
		default:
			printf("Opcao Invalida.");
			break;
	}
	
	printf("Informe a categoria:\n1-economica\n2-intermediaria\n3-luxo: ");
	scanf("%d",&opcao01);
	switch(opcao01){
		case 1:
			strcpy(carro.categoria,"economica");
			break;
		case 2:
			strcpy(carro.categoria,"intermediaria");
			break; 
		case 3:
			strcpy(carro.categoria,"luxo");
			break;
		default:
			printf("Opcao Invalida.");
			break;
	}
	
	printf("Informe o cor:\n");
	fflush(stdin); 
	fgets(carro.cor, 15, stdin);
	
	strcpy(carro.cpfcliente,"disponivel");
	
	carro.dt_ini.dia = NULL;
	carro.dt_ini.mes = NULL;
	carro.dt_ini.ano = NULL;
	
	carro.dt_fim.dia = NULL;
	carro.dt_fim.mes = NULL;
	carro.dt_fim.ano = NULL;
	
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

void CADASTRARCLIENTE(){
	struct Cliente cliente;
	int dataok;
	
	if((arquivo = fopen("cliente.dat","ab")) == NULL){
		printf("ERRO AO ABRIR ARQUIVO");
		system("pause");
		exit(0);
	}

	system("cls");
	printf("Informe o Nome: ");
	fflush(stdin); 
	fgets(cliente.nome, 100, stdin);
	
	printf("\nInforme data Nascimento:\n");
	do{
		printf("DIA:");
		fflush(stdin); 
		scanf("%d",&cliente.nasc.dia);
		printf("\nMES:");
		fflush(stdin); 
		scanf("%d",&cliente.nasc.mes);
		printf("\nANO:");
		fflush(stdin); 
		scanf("%d",&cliente.nasc.ano);
		dataok = VALIDA_DATA(cliente.nasc.dia,cliente.nasc.mes,cliente.nasc.ano);
		if (dataok != 1){
			printf("Data Inválida, pressione enter para informar novamente.");
			system("pause");
		}
	}while(dataok != 1);
	
	printf("\nInforme o RG: ");
    fflush(stdin); 
	fgets(cliente.rg, 10, stdin);
	
	printf("\nInforme o CPF: ");
    fflush(stdin); 
	fgets(cliente.cpf, 15, stdin);
	
	printf("\nInforme a Nacionalidade: ");
	fflush(stdin); 
	fgets(cliente.nacionalidade, 20, stdin);
	
	printf("\nInforme o numero de registro da CNH: ");
	fflush(stdin); 
	fgets(cliente.cnh, 20, stdin);
	
	printf("\nInforme validade da CNH:\n");
	do{
		printf("DIA:");
		fflush(stdin); 
		scanf("%d",&cliente.validadecnh.dia);
		printf("\nMES:");
		fflush(stdin); 
		scanf("%d",&cliente.validadecnh.mes);
		printf("\nANO:");
		fflush(stdin); 
		scanf("%d",&cliente.validadecnh.ano);
		dataok = VALIDA_DATA(cliente.validadecnh.dia,cliente.validadecnh.mes,cliente.validadecnh.ano);
		if (dataok != 1){
			printf("Data Inválida, pressione enter para informar novamente.");
			system("pause");
		}
	}while(dataok != 1);
		
	if (fwrite(&cliente,sizeof(struct Cliente),1,arquivo) == 1){
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

/*############################# VALIDA DATA ############################# */  

int VALIDA_DATA(int dia, int mes, int ano)
    {
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1900 && ano <= 2100)) //verifica se os numeros sao validos
        {
            if ((dia == 29 && mes == 2) && ((ano % 4) == 0)) //verifica se o ano e bissexto
            {
                return 1;
            }
            if (dia <= 28 && mes == 2) //verifica o mes de feveireiro
            {
                return 1;
            }
            if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) //verifica os meses de 30 dias
            {
                return 1;
            }
            if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)) //verifica os meses de 31 dias
            {
                return 1;
            }
            else
            {
                return 0;
            }
      }
       else
           {
                return 0;
           }
}

int CALCULARDIAS(Data_2 dt_ini, Data_2 dt_fim) {
	Data_2 dia1, dia2;
	return dist_dias (dt_ini, dt_fim);
}

int BISSEXTO (int ano) {
	return (ano % 4 == 0) && ((ano % 100 != 0) || (ano % 400 == 0));
}

/*
 * Retorna a distancia entre inicio e fim em dias.
 * Assume que inicio nao vem depois de fim.
 */
unsigned long dist_dias (Data_2 inicio, Data_2 fim) {
	unsigned long idias, fdias;	/* guarda qtos dias tem da data */
					/* ate o comeco do ano */
	unsigned long def_anos = 0;	/* guarda diferenca entre anos das */
					/* datas inicio e fim medida em dias */
	register int i;
	int dbissexto;

	idias = inicio.dia;
	dbissexto = BISSEXTO (inicio.ano);
	for (i = inicio.mes - 1; i > 0; --i)
		idias += dias_mes[dbissexto][i];

	fdias = fim.dia;
	dbissexto = BISSEXTO (fim.ano);
	for (i = fim.mes - 1; i > 0; --i)
		fdias += dias_mes[dbissexto][i];

	while (inicio.ano < fim.ano)
		def_anos += 365 + BISSEXTO(inicio.ano++);

	return def_anos - idias + fdias;
}

