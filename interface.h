#include <string.h>

#define UI_SIZE 80
#define UI_TEXT_SIZE 30
#define SIDE_CHAR '|'
#define LINE_CHAR '-'
#define QUESTION_SIZE 60
#define MENU_ALIGN -1

/**Cria a quantidade desesaja de linhas horizontais.*/
void blankLine(int linesNum){
    int lines, chars;
    for(lines = 0;lines < linesNum; lines++){
        for(chars = 0; chars < UI_SIZE; chars++)
            printf("%c", LINE_CHAR);
    }
}

/**Cria linha com texto encapsulado com alinhamento desejado [-1:esquerda; 0:centralizado; 1:direita].*/
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
            for(i = 0; i < spaces; i++){
                printf(" ");
            }
            printf("%s", text);
            for(i = 0; i < spaces+isOdd; i++){
                printf(" ");
            }
            printf("%c", SIDE_CHAR);
            break;
        case 1:
            printf("%c", SIDE_CHAR);
            spaces = UI_SIZE-textSize-4;
            for(i = 0; i < spaces; i++){
                printf(" ");
            }
            printf("%s", text);
            printf("  %c", SIDE_CHAR);
            break;
    }
}

/**Cria título centralizado com o texto desejado.*/
void topBox(char text[UI_TEXT_SIZE], int bottomLines){
    system("cls");
    blankLine(1);
    textLine(text, 0);
    blankLine(bottomLines);
}

/**Repete uma questão até que o valor da opção digitada seja válida.*/
int chooseValue(char text[QUESTION_SIZE], int valueMax){
    int choice = 0;
    do{
        printf("%s", text);
        fflush(stdin);
        scanf("%d", &choice);
    }while(!(choice >= 1 && choice <= valueMax));
    return choice;
}

/**Espera que uma tecla seja pressionada para continuar a execução.*/
void waitPress(){
    printf("Pressione qualquer tecla para voltar.\n");
    fflush(stdin);
    getchar();
}
