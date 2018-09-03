#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
//version 2.1

#define UI_SIZE 80           /*Tamanho m�ximo de caracteres de uma linha.*/
#define UI_TEXT_SIZE 64+1    /*N�mero m�ximo de caracteres em uma linha.*/ //[textio FILES_NAMEXT_MAX]
#define SIDE_CHAR 186        /*Caractere utilizado para linhas verticais.*/
#define DASH_CHAR 205        /*Caractere utilizado para linhas horizontais.*/
#define MENU_ALIGN -1        /*Alinhamento das linhas encapsuladas do menu.*/
#define TOP_ALIGN 0          /*Alinhamento da linha encapsulada do t�tulo. -1:esquerda/ 0:centralizado/ 1:direita*/
#define MENU_MAX_ITEMS 15    /*N�mero m�ximo de itens no menu.*/

/**Limita caracteres de uiText[] impresso ao valor de UI_TEXT_SIZE.*/
void limitPrint(const char uiText[]);

/**Exibe a quantidade linesNum de linhas horizontais com o caractere DASH_CHAR repetido UI_SIZE vezes.*/
void dashLine(int linesNum);

/**Exibe linha com texto uiText[] encapsulado pelo caractere SIDE_CHAR com alinhamento align (-1:esquerda/0:centralizado/1:direita).*/
void closedTextLine(const char uiText[], int align);

/**Limpa a tela, e cria t�tulo centralizado com uiText[] desejado, e n�mero de linhas horizontais, inferiores, indicado em bottomLines.*/
void topBox(const char uiText[], int bottomLines);

/**Exibe menu com o n�mero de itens indicado (ou no m�ximo MENU_MAX_ITEMS) com os itens de menuItems[][], e com op��o sair se indicado.*/
void fillMenu(const char menuItems[][UI_TEXT_SIZE], int numItens, int addExit);

/**Repete quest�o uiText[] at� que o valor da op��o do menu digitada seja v�lida (de 1 ao valor itemMax).
*Retorna: [valor escolhido pelo usu�rio].*/
int chooseItem(const char uiText[], int itemMax);

/**Exibe uma mensagem, emite um sinal sonoro, e espera que uma tecla seja pressionada para continuar a execu��o.*/
void waitPress(void);

#endif /* INTERFACE_H_INCLUDED */
