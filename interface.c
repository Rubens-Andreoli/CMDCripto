#include <stdio.h>      //printf, fflush, scanf, sprintf, getchar, putchar
#include <stdlib.h>     //system
#include <string.h>     //strlen
#include "interface.h"

void dashLine(int linesNum){
    int chars;
    while(linesNum--)
        for(chars=0; chars<UI_SIZE; chars++)
            putchar(DASH_CHAR);
}

void closedTextLine(const char uiText[], int align){
    int textSize=strlen(uiText), spaces, isOdd=0;
    switch(align){
        case -1:
            printf("%c  %s%*c", SIDE_CHAR, uiText, UI_SIZE-textSize-3, SIDE_CHAR);
            break;
        case 0:
            if(textSize%2!=0){
                textSize++;
                isOdd=1;
            }
            spaces=(UI_SIZE-textSize)/2;
            printf("%-*c%s%*c",spaces, SIDE_CHAR, uiText, spaces+isOdd, SIDE_CHAR);
            break;
        case 1:
            printf("%-*c%s  %c", UI_SIZE-textSize-3, SIDE_CHAR, uiText, SIDE_CHAR);
            break;
    }
}

void topBox(const char uiText[], int bottomLines){
    system("cls");
    dashLine(1);
    closedTextLine(uiText, TOP_ALIGN);
    dashLine(bottomLines);
}

void fillMenu(int numItens, int textSize, const char menuItems[numItens][textSize]){
    int i;
    char menuItem[textSize+10];
    for(i=0; i<numItens && i<MENU_MAX_ITEMS; i++){
        sprintf(menuItem, "%2d - %s", i+1, menuItems[i]);
        closedTextLine(menuItem, MENU_ALIGN);
    }
}

int chooseItem(const char uiText[], int itemMax){
    int choice, isInvalid = 1;
    while(isInvalid){
        printf(uiText);
        printf(" _\b");
        scanf("%d", &choice);
        clearBuffer();
        if(choice<1 || choice>itemMax || choice>MENU_MAX_ITEMS)
            printf("Escolha invalida!\n\n");
        else isInvalid = 0;
    }
    return choice;
}

void waitPress(void){
    printf("Pressione qualquer tecla para voltar.\a");
    getchar();
}

void setValidStr(const char uiText[], const char warning[], char str[], int (* validFunction)(char str[])){ //TODO: strLimit?
    int isInvalid = 1;
    while(isInvalid){
        printf(uiText);
        scanf("%s", str);
        clearBuffer();
        if(validFunction(str)) isInvalid = 0;
        else printf(warning);
    }
}

void splitTextLine(const char text[]){
    int start, end, textSize = strlen(text), i;
    for(start=0, end=UI_SIZE-2; start<textSize; start+=((end-start)+1), end+=UI_SIZE-2){
        if(end >= textSize){
            for(i=start; i<textSize; i++)
                putchar(text[i]);
        }else{
            while(end>start && text[end] != ' ') end--;
            for(i=start; i<=end; i++){
                if(text[i] == '\n'){
                    end = i;
                    break;
                }else putchar(text[i]);
            }
            putchar('\n');
        }
    }
    puts("\n");
}
