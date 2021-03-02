// Bibliotecas:
#include <stdio.h> // Biblioteca para o printf e scanf.
#include <stdlib.h> // Biblioteca para o rand() e system cls.
#include <time.h> // Biblioteca para o srand().
#include <locale.h> // Biblioteca para a regionalizacao.
#include <windows.h> // Biblioteca para o sleep.

//Tabuleiro:
#define N 4 // Largura do Tabuleiro (Linhas).
#define M 4 // Comprimento do Tabuleiro (Colunas).
#define P 8 // Quantidade de Cartas Diferentes (Metade do Total).
// Struct com as vari�veis que ser�o usadas nos usu�rios.
typedef struct {
	char usuario[100];
	int pontuacao;
}ranking;
ranking user, user2; //Declara��o dos dois usu�rios poss�veis.
// Variaveis Globais
struct {
	char GAB [N][M]; // Tabuleiro Gabarito.
	char TAB [N][M];// Tabuleiro
	char CAR [P];  // Tabuleiro Apresentado.
	int COL [M]; // Numero de Colunas.
	int ponto1, ponto2; // Pontuacao.
	int acao; // Acoes.
	int jogadores; // Numero de jogadores.
	int vez; // Para indicar qual jogador est� na vez.
}global;
//Fun��es utilizadas no c�digo.
void menu();
void esconder();
void inicializacao();
void embaralhar ();
void telajogo (int acao);
void atualizartela(int acao);
void umjogador();
void doisjogadores();
void jogar (int acao);
void ordem();
void usuario();
void instrucoes();
void creditos();
void rank();
void saida();
//func�o principal.
int main() {
	system("MODE con cols=80 lines=20 ");// Comando para alterar o tamanho da janela.
	char CAR[P] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	// Comando de Regionalizacao:
	setlocale(LC_ALL, "Portuguese");
	// Titulo do Programa:
	SetConsoleTitle("Jogo da Memoria");
	// Ordem de Execucao:
	ordem();
	return 0;
}
// Fun��o do menu
void menu(){
	do{
		system("color 0f");
		printf("\t****************************************************************\n"); 
		printf("\t****************************************************************\n");
	    printf("\t**                     Jogo da Mem�ria                        **\n");
		printf("\t****************************************************************\n"); 
		printf("\t****************************************************************\n");
		printf("\n\t\t\tSELECIONE UMA OP��O:\n");
		printf("\t\t\t1 - INICIAR\n");
		printf("\t\t\t2 - INSTRU��ES\n");
		printf("\t\t\t3 - CR�DITOS\n");
		printf("\t\t\t4 - RANKING\n");
		printf("\t\t\t5 - SAIR\n");
		printf("\t\t\tOp��o selecionada: ");
		scanf("%d", &global.acao);
		system("cls");
		switch(global.acao){
		case 1:
			break;	
		case 2:	
			instrucoes();
			break;
		case 3: 
			creditos();
			break;
		case 4:
			rank();
			break;
		case 5:
			saida();
			break;
		default:
			system("cls");
			printf("\n\n\n\n\n\n\n");
			printf("\tVOCE DIGITOU UMA OP��O INVALIDA, TENTE NOVAMENTE.\n\n");
			sleep(2);
			system("cls");
			break;
		}
	}while(global.acao != 1);
}
// Fun�ao para Esconder as Cartas:
void esconder() {
	int i, j;
	usuario();// Pergunta qual o usu�rio antes de esconder as cartas.
	global.vez = 1; // Indica qual jogador vai come�ar.
	// Loop para atrubuir o valor '*' na matriz do tabuleiro e esconder as cartas.
	for (i = 0; i < N; i++) 
		for (j  = 0; j < M; j++)
			global.TAB[i][j] = '*';
}
// Fun��o para Inicializar o Tabuleiro:
void inicializacao() {
	// Valores que est�o dispon�veis para criar os p�res a serem encontrados(Os valores ser�o usados duas vezes)
	char CAR[P] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	int i, j, k = 0;
	for (i = 0; i < N; i++)//Loop que cria os p�res
		for (j = 0; j < M; j++){
			global.GAB[i][j]=CAR[k];
			if (k < P-1)//Se k for menor que a quantidade de cartas(p),que vai de 0 a 7(p-1), ele incrementa o k.
				k++;
				else 
					k = 0;// Se k for maior que a quantidade de cartas(p), ele recebe 0 pra ser contado novamente e formar os pares.
		}
	esconder();// Chama a fun��o esconder para substituir os valores por '*'.
}
// Fun��o para Embaralhar Cartas:
void embaralhar () {
	int i, j, x, y;
	char aux;
	srand(time(NULL)); // Gerador de Numeros Aleatorios.
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++){
			x = rand()%N; // Gera Valores Aleatorios de 0 ate N(4).
			y = rand()%M; // Gera Valores Aleatorios de 0 ate M(4).
			aux = global.GAB[i][j];// Vari�vel auxiliar para receber os valores do gabarito.
			global.GAB[i][j] = global.GAB[x][y];// O gabarito das posi��es i e j recebem os valores das posi��es x e y que foram sorteadas.
			global.GAB[x][y] = aux;// O gabarito das posi��es x e y recebem o valor de aux(Gabarito de i e j)que ja teve seu valor escolhido.
		}	
}
// Fun��o para Mostrar Tela de Jogo
void telajogo (int acao) {
	int i, j, k = 0;
	
	if (global.acao == 1){// Se no menu for selecionado 1, ele ir� mostrar na tela do jogo o placar e as intru��es de sair.
		printf ("\n Para Sair, digite: 5 e 5 \n\n");
		printf("\t%s : %d pontos.\n\n ", user.usuario, global.ponto1);
		if(global.jogadores == 2){// Se estiver selecionado a opc�o multiplayer(2), ele ira mostrar o placar do segundo jogador.
		printf("\t%s : %d pontos. \n\n",  user2.usuario, global.ponto2);
		}
		printf ("\tVez de: ");
		if (global.vez == 1){// Mostra de quem � a vez.
			printf("%s\n\n\t",user.usuario);
		}
		else{
			printf("%s\n\n\t",user2.usuario);
		}
		
		for (i = 0; i < M; i++){//loop para imprimir os numeros das colunas na tela do jogo.
			global.COL[i] = i;
			printf (" %d\t", global.COL[i] + 1);
		}
		printf ("\n");
		for (i = 0; i < N; i++) {//loop para imprimir os numeros das linhas na tela do jogo. 
			printf ("\t%d", i + 1);
			for (j = 0; j < M; j++)// loop para imprimir as cartas escondidas ([*]) nas linhas.
				printf ("[%c]\t", global.TAB[i][j]);
			printf ("\n\n");
		}
	}
	k = 0;	
}
// Fun�ao para atualizar a tela.
void atualizartela(int acao) {
	Sleep (1000); // Para o Programa por 1 Segundo (1000ms).
	system ("cls");
	telajogo(global.acao);//Depois de apagar tudo na tela, mostra novamente a tela do jogo.
}
void umjogador(){//Caso escolhido a op��o um jogador, o codigo ir� salvar as pontua��es somente em um usu�rio.
	int i, j, x, y, virar = 0, checar = 1;
	global.vez = 1;// Nesta fun��o sempre ser� a vez do jogador um, para poder mostrar a sua vez na fun��o tela do jogo.
	while (global.ponto1 < 8 || global.acao == 1){ 
		if(global.ponto1 == 8){// O jogo termina quando faz 8 pontos.
			printf("\n\nParabens, voce ganhou.");
			sleep(2);
			break;
		}
		do {//loop para escolher a primeira carta.	
			printf ("\n> Informe as Coordenadas (Linha Coluna) da 1� Carta: ");
			scanf ("%d %d", &i, &j);
			if (i == 5 && j == 5){
				global.acao=-1;// Nescess�rio para sair do jogo e voltar para o menu (Vai ser usado mais abaixo).
				break;
			}
			// Diminui - 1 das coordenadas para poder ficar mais leg�vel na hora de escolher a carta(posi��o 1 1 no jogo equivale a 0 0 no codigo). 
			i--;
			j--; 
			if ((i >= N || j >= M ) || (i < 0 || j < 0)){// Informa que a op��o est� inv�lida.
				printf ("Coordenada Invalida!");
				checar = 0;//guarda 0 pra simular valor inv�lido.
				atualizartela(global.acao);// volta a mostrar a tela do jogo.
			}
			else 
				checar = 1;// guarda 1 para simular valor v�lido.
			if (global.TAB[i][j] == '*' && checar == 1){//Se selecionar uma coordenada v�lida e que seu valor na matriz seja '*', a coordenada recebe o gabarito.
				global.TAB[i][j] = global.GAB[i][j];
				system ("cls");
				telajogo(global.acao);
				virar++;
			}
			else if (checar == 1){//Caso a coordenada ja tenha receido o gabarito, o if anterior vai dar falso e esse if imprime carta escolhida.
					printf ("Esta carta j� foi escolhida!");
					atualizartela(global.acao);// Volta a mostrar a tela do jogo.
			}
		} while (virar < 1);//Quando a coordenada for v�lida, o loop vai fechar e entrar no loop da pr�xima carta.	
		if (global.acao < 0)// Caso seja digitado os valores "5  5" a ac�o recebe um valor negativo no if mais acima.
			break;
		do{//loop para escolher a segunda carta.
			printf ("\n> Informe as Coordenadas (Linha Coluna) da 2� Carta: ");
			scanf ("%d %d", &x, &y);	
			if ((x == 5 && y == 5) || global.ponto1 == 8){// O jogo termina quando faz 8 pontos ou "5 5" � digitado.
				global.acao = -1;// Nescess�rio para sair do jogo e voltar para o menu (Vai ser usado mais abaixo).
			}
			// Diminui - 1 das coordenadas para poder ficar mais leg�vel na hora de escolher a carta(posi��o 1 1 no jogo equivale a 0 0 no codigo). 
			x--;
			y--;
			if ((x >= N || y >= M ) || (x < 0 || y < 0)){// Informa que a op��o est� inv�lida.
				printf ("Coordenada Inv�lida!"); 
				checar = 0;//guarda 0 pra simular valor inv�lido.
				atualizartela(global.acao);//Volta a mostrar a tela do jogo.
			}
			else 
				checar = 1; //guarda 1 pra simular valor v�lido.
			if (global.TAB[x][y] == '*' && checar == 1){//Se selecionar uma coordenada v�lida e que seu valor na matriz seja '*', a coordenada recebe o gabarito.
				global.TAB[x][y] = global.GAB[x][y];
				system ("cls");
				telajogo(global.acao);
				virar++;
			}
			else 
				if (checar==1){//Caso a coordenada ja tenha receido o gabarito, o if anterior vai dar falso e esse if imprime carta escolhida.
					printf ("Esta carta j� foi escolhida!");
					atualizartela(global.acao);	
				}
	}while(virar < 2);//Quando a coordenada for v�lida, o loop vai fechar e retornar se acertou ou n�o.	
		if (global.acao < 0)// Caso seja digitado os valores "5  5" a ac�o recebe um valor negativo no if mais acima.
			break;
		if (global.TAB[i][j] == global.TAB[x][y]){//Compara os valores escolhidos, se iguais, o usu�rio achou um par de cartas.
			virar = 0;// Recebe valor 0 para retornar ao loop da primeira carta.
			global.ponto1++;//O jogador recebe mais um ponto.
			printf ("\n\t\t\t\t  ACERTOOOOOOU!");
			Sleep (500); // Para o Programa por Meio Segundo (500ms).
		}
			else { 
				global.TAB[i][j] = '*'; // Caso as cartas selecionadas n�o sejam par, os valores voltam a ser [*].
				global.TAB[x][y] = '*';	// Caso as cartas selecionadas n�o sejam par, os valores voltam a ser [*].
				virar=0; //Recebe valor - para retornar ao loop da primeira carta.
				printf ("\n\t\t\t\t  ERROOOOOOU!");
				Sleep (300); // Para o Programa por 0.3 Segundos (300ms).
			}
		atualizartela(global.acao);
	}
	if(global.ponto1 > 0){ //Entra neste c�digo apenas se tiver pontuado algo.
		FILE  * arquivo = NULL;
		char * usr, * svit; //Vari�veis ponteiros auxiliares para organizar a grava��o do ranking.
		int vit = 0;
		char texto[100];
		arquivo = fopen("ranking.bin", "ab");// Acessa o arquivo.
		user.pontuacao = global.ponto1;// O struct do ranking recebe os pontos conseguidos no jogo.
		fprintf(arquivo, "%s ,%d\n",user.usuario,user.pontuacao);//Grava no arquivo o usu�rio e a pontua��o.
		fflush(arquivo);//Limpa o buffer.
		fclose(arquivo);//Fecha o arquivo.
		system("cls");
	}
	//Essas vari�veis recebem 0 ao fim do jogo para poder iniciar um novo jogo.
	global.acao = 0;
	global.ponto1 = 0;
	system("cls");
	ordem();
}

void doisjogadores(){
	int i, j, x, y, virar = 0, checar = 1;
	global.vez = 1; // Vari�vel para indicar de quem � a vez, iniciando pelo jogador 1.
		
	while (global.ponto1 < 8 || global.acao == 1){ 
		if(global.ponto1 == 8 || global.ponto2 == 8){ //Se um dos jogadores chegar a 8 pontos o jogo acaba.
			printf("\n\nParabens, voce ganhou.");
			sleep(2);
			break;
		}
		do {   			
			printf ("\n> Informe as Coordenadas (Linha Coluna) da 1� Carta: ");
			scanf ("%d %d", &i, &j);
			if (i == 5 && j == 5){ // Nescess�rio para sair do jogo e voltar para o menu (Vai ser usado mais abaixo).
				global.acao = -1;
				break;
			}
			// Diminui - 1 das coordenadas para poder ficar mais leg�vel na hora de escolher a carta(posi��o 1 1 no jogo equivale a 0 0 no codigo). 
			i--;
			j--; 
			if ((i >= N || j >= M ) || (i < 0 || j < 0)){ // Informa que a op��o est� inv�lida.
				printf ("Coordenada Invalida!");
				checar=0; //Guarda 0 para simular valor inv�lido.
				atualizartela(global.acao); //Volta a mostrar a tela do jogo.
			}
				else 
					checar=1; //Guarda 0 para simular valor v�lido.	
			if (global.TAB[i][j] =='*' && checar == 1){ //Se selecionar uma coordenada v�lida e que seu valor na matriz seja '*', a coordenada recebe o gabarito. 
				global.TAB[i][j] = global.GAB[i][j];
				system ("cls");
				telajogo(global.acao);
				virar++;
			}
				else if (checar==1){ //Caso a coordenada ja tenha receido o gabarito, o if anterior vai dar falso e esse if imprime carta escolhida.
						printf ("Esta carta j� foi escolhida!");
						atualizartela(global.acao);
				}
		} 
		while (virar < 1); //Quando a coordenada for v�lida, o loop vai fechar e entrar no loop da pr�xima carta.
		if (global.acao<0) // Caso seja digitado os valores "5  5" a ac�o recebe um valor negativo no if mais acima.
			break;
		do{
			printf ("\n> Informe as Coordenadas (Linha Coluna) da 2� Carta: ");
			scanf ("%d %d", &x, &y);	

			if ((x == 5 && y == 5) || global.ponto1 == 8){ // Nescess�rio para sair do jogo e voltar para o menu (Vai ser usado mais abaixo).
				global.acao=-1;
		
			}
			// Diminui - 1 das coordenadas para poder ficar mais leg�vel na hora de escolher a carta(posi��o 1 1 no jogo equivale a 0 0 no codigo).
			x--;
			y--;
			if ((x >= N || y >= M ) || (x < 0 || y < 0)){
				printf ("Coordenada Inv�lida!"); // Informa que a op��o est� inv�lida.
				checar = 0; //Guarda 0 para simular valor inv�lido.
				atualizartela(global.acao); //Volta a mostrar a tela do jogo.
			}
			else 
				checar=1;
			if (global.TAB[x][y] == '*' && checar==1){ //Se selecionar uma coordenada v�lida e que seu valor na matriz seja '*', a coordenada recebe o gabarito. 
				global.TAB[x][y] = global.GAB[x][y];
				system ("cls");
				telajogo(global.acao);
				virar++;
			}
			else 
				if (checar==1){ //Caso a coordenada ja tenha receido o gabarito, o if anterior vai dar falso e esse if imprime carta escolhida.
					printf ("Esta carta j� foi escolhida!");
					atualizartela(global.acao);	
				}
	}while(virar<2); //Quando a coordenada for v�lida, o loop vai fechar e retornar se acertou ou n�o.

	
		if (global.acao<0) // Caso seja digitado os valores "5  5" a ac�o recebe um valor negativo no if mais acima.
			break;
		if (global.TAB[i][j] == global.TAB[x][y]){ //Compara os valores escolhidos, se iguais, o usu�rio achou um par de cartas.
			virar = 0; //Recebe valor 0 para voltar ao loop da primeira carta
			if (global.vez == 1){ //Pontua��o para caso seja a vez do primeiro usu�rio.
					global.ponto1 = global.ponto1 + 2; //No modo multiplayer(2) a pontua��o recebe um valor dobrado, devido a serem dois jogadores.
			printf ("\n\t\t\t\t%s  ACERTOOOOOOU!", user.usuario);
			Sleep (500); // Para o Programa por Meio Segundo (500ms).
			}
			else if (global.vez == 2){//Pontua��o para caso seja a vez do segundo usu�rio.
					global.ponto2 = global.ponto2 + 2;//No modo multiplayer(2) a pontua��o recebe um valor dobrado, devido a serem dois jogadores.
			printf ("\n\t\t\t\t%s  ACERTOOOOOOU!", user2.usuario);
			Sleep (500); // Para o Programa por Meio Segundo (500ms).
			}
		}
			else { 
				global.TAB[i][j] = '*';// Caso as cartas selecionadas n�o sejam par, o valores voltam a ser [*].
				global.TAB[x][y] = '*';// Caso as cartas selecionadas n�o sejam par, o valores voltam a ser [*].
				virar=0; // Recebe valor 0 para voltar ao loop da primeira carta.
				printf ("\n\t\t\t\t  ERROOOOOOU!");
				if (global.vez == 2){ // Caso o segundo jogador n�o encontre um par de cartas, ir� retornar a tentativa ao primeiro jogador.
					global.vez = 1;
				}
				else{
					global.vez++; // Caso o primeiro jogador n�o encontre um par de cartas, ir� passar a tentativa ao segundo jogador. 
				}
				Sleep (300); // Para o Programa por 0.3 Segundos (300ms).
			}
		atualizartela(global.acao);
		
	}

	if(global.ponto1 > 0 || global.ponto2 > 0){ //Entra neste c�digo apenas se tiver pontuado algo. 
		FILE  * arquivo = NULL; 
		char * usr, * svit; // Vari�veis ponteiros auxiliares para organizar a grava��o do ranking.
		int vit = 0;
		char texto[100];
		arquivo = fopen("ranking.bin", "ab");// Acessar o arquivo.
		user.pontuacao = global.ponto1; // O struct do ranking do usu�rio um recebe os pontos conseguidos no jogo.
		user2.pontuacao = global.ponto2; // O struct do ranking do usu�rio dois recebe os pontos conseguidos no jogo.
		fprintf(arquivo, "%s ,%d\n",user.usuario,user.pontuacao); //Grava no arquivo o primeiro usu�rio e a sua pontua��o.
		fflush(arquivo); // limpar o buffer.
		fprintf(arquivo, "%s ,%d\n",user2.usuario,user2.pontuacao); //Grava no arquivo o segundo usu�rio e a sua pontua��o.
		fflush(arquivo); // limpar o buffer.
		fclose(arquivo); // Fechar arquivo
		system("cls");
	}
	//Essas vari�veis recebem 0 ao fim do jogo para poder iniciar um novo jogo.
	global.acao = 0;
	global.ponto1 = 0;
	global.ponto2 = 0;
	system("cls");
	ordem();
}
// Funcao para execu��o do Jogo.
void jogar (int acao) { 

	if(global.jogadores == 1){ // Caso o usu�rio selecione a op��o singleplayer(1), ir� retornar a fun��o umjogador.
		umjogador();
	}
	if(global.jogadores == 2){ // Caso o usu�rio selecione a op��o multiplayer(2), ir� retornar a fun��o doisjogareos.
		doisjogadores();
	}
}
		

//Funcao para ordenar o programa.
void ordem(){
	
	menu();	
    inicializacao();
	embaralhar();
	telajogo(global.acao);
	jogar(global.acao);	
}
//Funcao p/ salvar o nome dos jogadores
void usuario(){
	system("color 0f");
	printf("Selecione o modo de jogo:\n");
	printf("1- Singleplayer(1 Jogador) \n2- Multiplayer(2 Jogadores).\n");
	printf("> "); // Pede ao usu�rio para selecionar o modo que ele deseja jogar.
	scanf("%d",&global.jogadores);
	fflush(stdin);//limpar o buffer.
	system("cls");
	if(global.jogadores == 1){ // Caso ele selecione a op��o singleplayer.
	
	printf("Digite o nome do Jogador 1: "); // Recebe o nome de apenas um usu�rio.
	fflush(stdin);
	gets(user.usuario);
	fflush(stdin);
	system("cls");
	}
	else if(global.jogadores == 2){ // Caso ele selecione a op��o multiplayer.
	
	printf("Digite o nome do Jogador 1: "); // Recebe o nome de dois usu�rios.
	fflush(stdin);
	gets(user.usuario);
	fflush(stdin);
	printf("Digite o nome do Jogador 2: ");
	fflush(stdin);
	gets(user2.usuario);
	fflush(stdin);
	system("cls");
	}
	else{ // Caso selecione algo que fuja do esperado(op��o 1 ou op��o 2), imprime que op��o selecionada � inv�lida.
		printf("\tOp��o inv�lida.\n");
		sleep(2);
		system("cls");
		esconder();//retorna a fun��o esconder.
		
	}
}
//Funcao que mostra as instrucoes.
void instrucoes(){	
	system("cls");
	system("MODE con cols=90 lines=20 ");

	printf("\n\n");
	printf("\t****************************************************************************\n");
	printf("\t**                          O QUE � O JOGO?                               **\n");
	printf("\t**          O jogo da memoria e constituido por uma matriz 4x4            **\n");
	printf("\t**                    Dividido em 8 letras de A-H                         **\n");
	printf("\t****************************************************************************\n");
	printf("\t**                      O OBEJTIVO DO JOGO?                               **\n");
	printf("\t**      Decorar onde est�o as letras e achar seus pares                   **\n");
	printf("\t**                Quantos mais acertos, mais pontos!                      **\n");
	printf("\t****************************************************************************\n");
	printf("\t**                      COMO ENTRAR NO RANKING?                           **\n");
	printf("\t**             Sua pontua��o no jogo deve ser maior que 0.                **\n");
	printf("\t**             A pontua��o m�xima poss�vel � de 8 pontos.                 **\n");
	printf("\t****************************************************************************\n");
	sleep(2);
	printf("\n\n");
	system("pause");
	system("cls");
}
//Funcao para mostrar os creditos.
void creditos() {
	system("MODE con cols=100 lines=20 ");
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t****************************************************************************\n");
	printf("\t**	Desenvolvido por: Victor, Allison e Daniel.                       **\n");
	printf("\t****************************************************************************\n");
	printf("\t**	Jogo da memoria com fins totalmente educativos.                   **\n");
	printf("\t****************************************************************************\n");
	sleep(2);
	printf("\n\n");
	system("pause");
	system("cls");	
}
//Funcao para mostrar o sistema de ranking
void rank() {
	system("cls");
	FILE  * arquivo = NULL;
	char * user, * spontos;
	int pontos = 0;
	char texto[100];
	arquivo = fopen("ranking.bin","rb");// Abre o arquivo.
	if(!arquivo){ // Se o arquivo n�o estiver dispon�vel, ele imprime uma mensagem diferente.
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n");
		printf("\t*********************************************************\n");
		printf("\t**  N�o h� ningu�m no ranking ainda, jogue e entre!    **\n");
		printf("\t*********************************************************\n");
		printf("\n\n");
		sleep(2);
		system("pause");
		system("cls");
	}
	else{
	fflush(arquivo);
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t*****************************************************\n");
	printf("\t**                   Ranking:                      **\n");
	printf("\t*****************************************************\n");
	while(fgets(texto,100,arquivo) != NULL) {
		user = strtok(texto, ","); // Guarda todo conte�do antes da v�rgula na vari�vel user.
		spontos = strtok(NULL, ",");// Guarda todo conte�o depois da v�rgula na vari�vel spontos.
		pontos = atoi(spontos);// atoi transforma o conte�do de string para int.
		printf("\tUsu�rio: %s, Pontos: %d\n",user, pontos);
	}
	fclose(arquivo);// Fecha o arquivo.
	sleep(2);
	printf("\n\n");
	system("pause");
	system("cls");
	}
}
//Funcao para saida do programa.
void saida() {
	system ("cls");
	if ( global.ponto1 == 0){ // Caso saia sem realizar nenhum ponto, imprimir apenas.
	printf("\n\n");
	printf("\t*****************************************************\n");
	printf("\t**             Jogo encerrado!                     **\n");
	printf("\t*****************************************************\n");	
	exit(0);
	}
}

