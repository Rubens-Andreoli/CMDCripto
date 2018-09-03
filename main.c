#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "filesio.h"
#include "cripto.h"

#define MENU_NUM_ITEMS 6
const char ITEMS[MENU_MAX_ITEMS][UI_TEXT_SIZE]={"SELECIONAR ARQUIVO","VISUALIZAR","CRIPTOGRAFAR","DESCRIPTOGRAFAR","AJUDA","SOBRE"};

int main()
{
    int menuChoice=0, fileNumTotal=0, fileChoice=0, lineTotal=0;
    char files[FILENUM_MAX][FILENAM_MAX], text[LINE_MAX][CHAR_MAX], question[QUESTION_SIZE], pass[MAX_PASS_SIZE+1], fileName[FILENAM_MAX];

    while (menuChoice != MENU_NUM_ITEMS+1){
        topBox("MENU", 1);
        fillMenu(ITEMS, MENU_NUM_ITEMS);
        sprintf(question, "Digite a opcao desejada de acordo com o menu (1-%d): ", MENU_NUM_ITEMS+1);
        menuChoice = chooseValue(question, MENU_NUM_ITEMS+1);
        switch(menuChoice){
            case 1:
                topBox(ITEMS[0], 1);
                fileNumTotal = readFolder(files);
                blankLine(1);
                if(fileNumTotal != 0){
                    blankLine(1);
                    sprintf(question, "Digite a opcao referente ao arquivo desejado (1-%d): ", MIN(FILENUM_MAX, fileNumTotal));
                    fileChoice = chooseValue(question, MIN(FILENUM_MAX, fileNumTotal));
                    printf("Arquivo [%s] selecionado.\n", files[fileChoice-1]);
                    lineTotal = readFile(text, files[fileChoice-1]);
                }else{
                    printf("Nenhum arquivo foi encontrado. ");
                }
                waitPress();
                break;
            case 2:
                topBox(ITEMS[1], 2);
                if (fileChoice!=0){
                    printf("\n");
                    showText(text, lineTotal);
                    printf("\n");
                    blankLine(2);
                    printf("O arquivo [%s] foi exibido.\n", files[fileChoice-1]);
                }else{
                    printf("Nenhum arquivo foi selecionado. ");
                }
                waitPress();
                break;
            case 3:
                topBox(ITEMS[2], 2);
                if(fileChoice == 0){
                    printf("Nenhum arquivo foi selecionado ou criado. ");
                }else if(lineTotal == 0){
                    printf("Nenhum texto encontrado no arquivo. ");
                }else{
                    getPass(pass);
                    encrypt(text, lineTotal, pass);
                    if(writeFile(text, lineTotal, files[fileChoice-1])==1){
                        printf("Arquivo criptografado com sucesso! ");
                    }else{
                        printf("Arquivo nao pode ser criptografado. ");
                    }
                }
                waitPress();
                break;
            case 4:
                topBox(ITEMS[3], 2);
                if(fileChoice == 0){
                    printf("Nenhum arquivo foi selecionado. ");
                }else if(lineTotal == 0){
                    printf("Nenhum texto encontrado no arquivo. ");
                }else{
                    getPass(pass);
                    decrypt(text, lineTotal, pass);
                    if(writeFile(text, lineTotal, files[fileChoice-1])==1){
                        printf("Arquivo descriptografado com sucesso! ");
                    }else{
                        printf("Arquivo nao pode ser descriptografado. ");
                    }
                }
                waitPress();
                break;
            case 5:
                topBox(ITEMS[4], 2);
                printf("***SELECIONAR ARQUIVO***\n"
                        "-LISTA TODOS OS ARQUIVOS DE TEXTO [%s] NA PASTA \"%s\", CONTIDA NA PASTA RAIZ DO PROGRAMA,"
                        " PERMITINDO AO USUARIO ESCOLHER QUAL SERA LIDO PARA SER CRIPTOGRAFADO OU DESCRIPTOGRAFADO.\n\n"
                        "***VISUALIZAR ARQUIVO***\n"
                        "-PERMITE AO USUARIO VISUALIZAR O TEXTO EXTRAIDO DO ARQUIVO SELECIONADO."
                        " ESTE PODERA SER EXIBIDO TANTO DESCRIPTOGRAFADO QUANTO CRIPTOGRAFADO.\n\n"
                        "***CRIPTOGRAFAR***\n"
                        "-ESSA OPCAO INICIA O PROCESSO DE CRIPTOGRAFIA SOBREPONDO O TEXTO NO ARQUIVO ORIGINAL.\n\n"
                        "***DESCRIPTOGRAFAR***\n"
                        "-ESSA OPCAO INICIA O PROCESSO DE DESCRIPTOGRAFIA SOBREPONDO O TEXTO NO ARQUIVO CRIPTOGRAFADO.\n\n"
                        "***SOBRE***\n"
                        "-INFORMACOES ACADEMICAS DO PROJETO.\n\n"
                        "***SAIR***\n"
                        "-ENCERRA O APLICATIVO.\n\n", FILETYPE, FOLDER);
                blankLine(2);
                waitPress();
                break;
            case 6:
                topBox(ITEMS[5], 2);
                printf("SOFTWARE PROJETADO PARA A DISCIPLINA APS (ATIVIDADES PRATICAS SUPERVISIONADAS).\n"
                        "CURSO: CIENCIA DA COMPUTACAO --- TURMA: CC2P18 / CC2Q18 --- UNIP CAMPUS VARGAS\n\n"
                        "GUILHERME	C59386-9\n"
                        "GUSTAVO		C64211-8\n"
                        "MURILO		C42HIH-4\n"
                        "RUBENS		T49128-2\n"
                        "\nESTE SOFTWARE FOI DESENVOLVIDO EM LINGUAGEM DE PROGRAMACAO ESTRUTURADA (\"C\") E TEM COMO"
                        " OBJETIVO UTILIZAR TECNICAS DE CRIPTOGRAFIA PARA CRIPTOGRAFAR E DESCRIPTOGRAFAR UMA MENSAGEM"
                        " PREVIAMENTE INSERIDA EM UM ARQUIVO DE TEXTO UTILIZANDO PARA ISSO A CIFRA DE VIGENERE.\n");
                blankLine(2);
                waitPress();
                break;
        }
    }
    return 0;
}
