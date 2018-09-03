#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
//version 3.0

/* ---- Defini��es gerais ---- */
#define UI_SIZE 80           /*Tamanho m�ximo de caracteres de uma linha.*/
#define UI_TEXT_SIZE 64+1    /*N�mero m�ximo de caracteres em uma linha + \0.*/
#define SIDE_CHAR 186        /*Caractere utilizado para linhas verticais.*/
#define DASH_CHAR 205        /*Caractere utilizado para linhas horizontais.*/
#define MENU_ALIGN -1        /*Alinhamento das linhas encapsuladas do menu.*/
#define TOP_ALIGN 0          /*Alinhamento da linha encapsulada do t�tulo. -1:esquerda/ 0:centralizado/ 1:direita*/
#define MENU_MAX_ITEMS 15    /*N�mero m�ximo de itens no menu.*/

/* ---- Defini��es espec�ficas ---- */
#define MAIN_MENU_NUM_ITEMS 9
const static char MAIN_MENU_ITEMS[MAIN_MENU_NUM_ITEMS][UI_TEXT_SIZE] = {"CRIAR ARQUIVO","SELECIONAR ARQUIVO","VISUALIZAR","CRIPTOGRAFAR","DESCRIPTOGRAFAR","RESTAURAR","AJUDA","SOBRE","SAIR"};

/* ---- Defini��es facilitadoras ---- */
#define MAIN_MENU fillMenu(MAIN_MENU_NUM_ITEMS, UI_TEXT_SIZE, MAIN_MENU_ITEMS) /*Exibe menu com os itens de MENU_ITEMS.*/

/* ---- Fun��es inline ---- */
inline static void clearBuffer(void){
    while (getchar() != '\n')
        continue;
}

/* ---- Prot�tipos das fun��es ---- */
/**Exibe a quantidade "linesNum" de linhas horizontais com o caractere DASH_CHAR repetido UI_SIZE vezes.*/
void dashLine(int linesNum);

/**Exibe linha com texto "uiText[]" encapsulado pelo caractere SIDE_CHAR com alinhamento align (-1:esquerda/0:centralizado/1:direita).*/
void closedTextLine(const char uiText[], int align);

/**Limpa a tela, e cria t�tulo centralizado com "uiText[]" desejado, e n�mero de linhas horizontais, inferiores, indicado em bottomLines.*/
void topBox(const char uiText[], int bottomLines);

/**Exibe menu com o n�mero de itens de "menuItems[][]" (ou no m�ximo MENU_MAX_ITEMS) e tamanho do texto "textSize".*/
void fillMenu(int numItens, int textSize, const char menuItems[numItens][textSize]);

/**Repete quest�o "uiText[]" at� que o valor da op��o do menu digitada seja v�lida (de 1 ao valor "itemMax").
*Retorna: [valor escolhido pelo usu�rio].*/
int chooseItem(const char uiText[], int itemMax);

/**Exibe uma mensagem, emite um sinal sonoro, e espera que uma tecla seja pressionada para continuar a execu��o.*/
void waitPress(void);

/**Repete quest�o "uiText[]" at� que "str[]" seja validado por "validFunction()", caso input seja inv�lido exibe "warning[]", sen�o preenche "str[]".*/
void setValidStr(const char uiText[], const char warning[], char str[], int (* validFunction)(char str[]));

/**Exibe "text[]" divido em no m�ximo UI_SIZE caracteres, sem cortar palavras.*/
void splitTextLine(const char text[]);

/* ---- Main exemplo ---- */
/*int main()
{
    ////// VARI�VEIS: INTERFACE //////
    char uiText[UI_TEXT_SIZE];

    int menuChoice = 0;
    while (menuChoice != MAIN_MENU_NUM_ITEMS){
        topBox("MENU", 1);
        MAIN_MENU;
        dashLine(2);
        sprintf(uiText, "Digite a opcao desejada de acordo com o menu (1-%d):", MAIN_MENU_NUM_ITEMS);
        menuChoice = chooseItem(uiText, MAIN_MENU_NUM_ITEMS);
        switch(menuChoice){
            case 1:
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 2);
                [...]
                waitPress();
                break;
            case 2:
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 1);
                [...]
                waitPress();
                break;
            [...]
        }
    }
    return 0;
}*/

#endif /* INTERFACE_H_INCLUDED */
