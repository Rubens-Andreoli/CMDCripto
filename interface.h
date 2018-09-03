#include <string.h>

#define UI_SIZE 80
#define UI_TEXT_SIZE 30
#define SIDE_CHAR 186
#define LINE_CHAR 205
#define MENU_ALIGN -1
#define MENU_MAX_ITEMS 10
#define QUESTION_SIZE 60

/**Cria a quantidade desesaja de linhas horizontais.*/
void blankLine(int linesNum){
    int lines, chars;
    for(lines = 0;lines < linesNum; lines++){
        for(chars = 0; chars < UI_SIZE; chars++)
            printf("%c", LINE_CHAR);
    }
}

/**Cria linha com texto encapsulado com alinhamento desejado (-1:esquerda; 0:centralizado; 1:direita).*/
void textLine(char text[UI_TEXT_SIZE], int pos){
    int textSize = strlen(text);
    int i, spaces, isOdd = 0;
    switch(pos){
        case -1:
            printf("%c  ", SIDE_CHAR);
            printf("%s", text);
            spaces = UI_SIZE-textSize-4;
            for(i = 0; i < spaces; i++)
                printf(" ");
            printf("%c", SIDE_CHAR);
            break;
        case 0:
            if(textSize%2 != 0){
                textSize++;
                isOdd = 1;
            }
            spaces = (UI_SIZE - 2 - textSize) / 2;
            printf("%c", SIDE_CHAR);
            for(i = 0; i < spaces; i++)
                printf(" ");
            printf("%s", text);
            for(i = 0; i < spaces+isOdd; i++)
                printf(" ");
            printf("%c", SIDE_CHAR);
            break;
        case 1:
            printf("%c", SIDE_CHAR);
            spaces = UI_SIZE-textSize-4;
            for(i = 0; i < spaces; i++)
                printf(" ");
            printf("%s", text);
            printf("  %c", SIDE_CHAR);
            break;
    }
}

/**Cria t�tulo centralizado com o texto desejado.*/
void topBox(char text[UI_TEXT_SIZE], int bottomLines){
    system("cls");
    blankLine(1);
    textLine(text, 0);
    blankLine(bottomLines);
}

/**Cria menu principal com itens desejados.*/
void fillMenu(char menuItems[MENU_MAX_ITEMS][UI_TEXT_SIZE], int numItens){
    int i;
    char menuItem[UI_TEXT_SIZE+10];
    for(i=0;i<numItens;i++){
        sprintf(menuItem, "%d - %s", i+1, menuItems[i]);
        textLine(menuItem, MENU_ALIGN);
    }
    sprintf(menuItem, "%d - SAIR", i+1);
    textLine(menuItem, MENU_ALIGN);
    blankLine(2);
}

/**Repete uma quest�o at� que o valor da op��o digitada seja v�lida e retorna: [valor escolhido pelo usu�rio].*/
int chooseValue(char question[QUESTION_SIZE], int valueMax){
    int choice = 0;
    do{
        printf("%s", question);
        fflush(stdin);
        scanf("%d", &choice);
    }while(!(choice >= 1 && choice <= valueMax));
    return choice;
}

/**Espera que uma tecla seja pressionada para continuar a execu��o.*/
void waitPress(){
    printf("Pressione qualquer tecla para voltar.\n");
    fflush(stdin);
    getchar();
}
