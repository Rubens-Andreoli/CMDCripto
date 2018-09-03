#include <stdio.h>      //printf, fflush, scanf, sprintf, getchar, putchar
#include <stdlib.h>     //system
#include <string.h>     //strlen
#include "interface.h"

void dashLine(int linesNum){
    int chars;
    while(linesNum--){
        for(chars=0; chars<UI_SIZE; chars++)
            putchar(DASH_CHAR);
    }
}

void limitPrint(const char uiText[]){
    int i;
    for(i=0; uiText[i] != '\0' && i < UI_TEXT_SIZE; i++){
        putchar(uiText[i]);
    }
}

void closedTextLine(const char uiText[], int align){
    int i, textSize=strlen(uiText), spaces, isOdd=0;
    switch(align){
        case -1:
            printf("%c  ", SIDE_CHAR);
            limitPrint(uiText);
            spaces=UI_SIZE-textSize-4;
            while(spaces--)
                printf(" ");
            putchar(SIDE_CHAR);
            break;
        case 0:
            if(textSize%2!=0){
                textSize++;
                isOdd=1;
            }
            spaces=(UI_SIZE-2-textSize)/2;
            putchar(SIDE_CHAR);
            for(i=0; i<spaces; i++)
                printf(" ");
            limitPrint(uiText);
            for(i=0; i<spaces+isOdd; i++)
                printf(" ");
            putchar(SIDE_CHAR);
            break;
        case 1:
            putchar(SIDE_CHAR);
            spaces=UI_SIZE-textSize-4;
            while(spaces--)
                printf(" ");
            limitPrint(uiText);
            printf("  %c", SIDE_CHAR);
            break;
    }
}

void topBox(const char uiText[], int bottomLines){
    system("cls");
    dashLine(1);
    closedTextLine(uiText, TOP_ALIGN);
    dashLine(bottomLines);
}

void fillMenu(const char menuItems[][UI_TEXT_SIZE], int numItens, int addExit){
    int i;
    char menuItem[UI_TEXT_SIZE+10];
    for(i=0; i<numItens && i<MENU_MAX_ITEMS; i++){
        sprintf(menuItem, "%2d - %s", i+1, menuItems[i]);
        closedTextLine(menuItem, MENU_ALIGN);
    }
    if(addExit){
        sprintf(menuItem, "%2d - SAIR", i+1);
        closedTextLine(menuItem, MENU_ALIGN);
    }
}

int chooseItem(const char uiText[], int itemMax){
    int choice, isInvalid = 1;
    while(isInvalid){
        limitPrint(uiText);
        printf(" _\b");
        fflush(stdin);
        scanf("%d", &choice);
        if(choice<1 || choice>itemMax || choice>MENU_MAX_ITEMS){
            printf("Escolha invalida!\n\n");
        }else{
            isInvalid = 0;
        }
    }
    return choice;
}

void waitPress(void){
    printf("Pressione qualquer tecla para voltar.\a");
    fflush(stdin);
    getchar();
}
