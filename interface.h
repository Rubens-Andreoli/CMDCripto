#include <string.h>

#define UI_SIZE 80
#define UI_TEXT_SIZE 30
#define UI_QSTN_SIZE 60
#define SIDE_CHAR 186
#define LINE_CHAR 205
#define MENU_MAX_ITEMS 20
#define MENU_ALIGN -1

/**Cria a quantidade desejada de linhas horizontais.*/
void BlankLine(int linesNum){
    int lines, chars;
    for(lines=0; lines<linesNum; lines++){
        for(chars=0; chars<UI_SIZE; chars++)
            printf("%c", LINE_CHAR);
    }
}

/**Cria linha com texto encapsulado com alinhamento desejado
* (1:esquerda; 0:centralizado; 1:direita).*/
void TextLine(char text[UI_TEXT_SIZE], int pos){
    int i, spaces, isOdd=0, textSize=strlen(text);
    switch(pos){
        case -1:
            printf("%c  ", SIDE_CHAR);
            printf("%s", text);
            spaces=UI_SIZE-textSize-4;
            for(i=0; i<spaces; i++)
                printf(" ");
            printf("%c", SIDE_CHAR);
            break;
        case 0:
            if(textSize%2!=0){
                textSize++;
                isOdd=1;
            }
            spaces=(UI_SIZE-2-textSize)/2;
            printf("%c", SIDE_CHAR);
            for(i=0; i<spaces; i++)
                printf(" ");
            printf("%s", text);
            for(i=0; i<spaces+isOdd; i++)
                printf(" ");
            printf("%c", SIDE_CHAR);
            break;
        case 1:
            printf("%c", SIDE_CHAR);
            spaces=UI_SIZE-textSize-4;
            for(i=0; i<spaces; i++)
                printf(" ");
            printf("%s", text);
            printf("  %c", SIDE_CHAR);
            break;
    }
}

/**Cria título centralizado com o texto desejado.*/
void TopBox(char text[UI_TEXT_SIZE], int bottomLines){
    system("cls");
    BlankLine(1);
    TextLine(text, 0);
    BlankLine(bottomLines);
}

/**Cria menu com itens desejados.*/
void FillMenu(char menuItems[MENU_MAX_ITEMS][UI_TEXT_SIZE],
              int numItens, int isExit){
    int i;
    char menuItem[UI_TEXT_SIZE+10];
    for(i=0;i<numItens;i++){
        sprintf(menuItem, "%2d - %s", i+1, menuItems[i]);
        TextLine(menuItem, MENU_ALIGN);
    }
    if(isExit==1){
        sprintf(menuItem, "%2d - SAIR", i+1);
        TextLine(menuItem, MENU_ALIGN);
    }
    BlankLine(2);
}

/**Repete uma questão até que o valor da opção digitada seja válida.
Retorna: [valor escolhido pelo usuário].*/
int ChooseValue(char question[UI_QSTN_SIZE], int valueMax){
    int choice=0;
    do{
        printf("%s", question);
        fflush(stdin);
        scanf("%d", &choice);
    }while((choice<1) || (choice>valueMax));
    return choice;
}

/**Espera que uma tecla seja pressionada para continuar a execução.*/
void WaitPress(void){
    printf("Pressione qualquer tecla para voltar.\n");
    fflush(stdin);
    getchar();
}
