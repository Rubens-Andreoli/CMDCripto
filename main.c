#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "filesio.h"
#include "cripto.h"

#define MENU_NUM_ITEMS 7
char ITEMS[MENU_MAX_ITEMS][UI_TEXT_SIZE]={"CRIAR ARQUIVO","SELECIONAR ARQUIVO","VISUALIZAR","CRIPTOGRAFAR","DESCRIPTOGRAFAR","AJUDA","SOBRE"};

int main()
{
    int menuChoice=0, fileNumTotal=0, fileChoice=0, lineTotal=0, isCripto=0;
    char files[FILENUM_MAX][FILENAM_MAX], text[LINE_MAX][CHAR_MAX], question[QUESTION_SIZE], pass[MAX_PASS_SIZE+1], fileName[FILENAM_MAX];

    while (menuChoice!=MENU_NUM_ITEMS+1){
        topBox("MENU", 1);
        fillMenu(ITEMS, MENU_NUM_ITEMS);
        sprintf(question, "Digite a opcao desejada de acordo com o menu (1-%d): ", MENU_NUM_ITEMS+1);
        menuChoice = chooseValue(question, MENU_NUM_ITEMS+1);
        switch(menuChoice){
            case 1:
                topBox(ITEMS[0], 1);
                textLine("!!NAO UTILIZE ACENTOS!!", 1);
                blankLine(2);
                lineTotal=getText(text);
                topBox(ITEMS[0], 2);
                createFilename(fileName);
                writeFile(text,lineTotal,fileName,1);
                sprintf(files[0], "%s", fileName);
                fileChoice=1;
                isCripto=0;
                printf("Arquivo [%s] foi criado com sucesso.\n", fileName);
                waitPress();
                break;
            case 2:
                topBox(ITEMS[1], 1);
                fileNumTotal = readFolder(files);
                blankLine(1);
                if(fileNumTotal != 0){
                    blankLine(1);
                    sprintf(question, "Digite a opcao referente ao arquivo desejado (1-%d): ", MIN(FILENUM_MAX, fileNumTotal));
                    fileChoice = chooseValue(question, MIN(FILENUM_MAX, fileNumTotal));
                    printf("Arquivo [%s] selecionado.\n", files[fileChoice-1]);
                    lineTotal = readFile(text, files[fileChoice-1],&isCripto);
                }else{
                    printf("Nenhum arquivo foi encontrado. ");
                }
                waitPress();
                break;
            case 3:
                topBox(ITEMS[2], 2);
                if (fileChoice!=0){
                    printf("\n");
                    showText(text, lineTotal, isCripto);
                    printf("\n");
                    blankLine(2);
                    printf("O arquivo [%s]%s foi exibido.\n", files[fileChoice-1], isCripto?" criptografado":"");
                }else{
                    printf("Nenhum arquivo foi selecionado. ");
                }
                waitPress();
                break;
            case 4:
                topBox(ITEMS[3], 2);
                if(fileChoice == 0){
                    printf("Nenhum arquivo foi selecionado ou criado. ");
                }else if(lineTotal == 0){
                    printf("Nenhum texto encontrado no arquivo. ");
                }else if(isCripto == 1){
                    printf("Arquivo ja esta criptografado. ");
                }else{
                    getPass(pass);
                    encrypt(text, lineTotal, pass);
                    isCripto=1;
                    if(writeFile(text, lineTotal, files[fileChoice-1],0)==1){
                        printf("Arquivo criptografado com sucesso! ");
                    }else{
                        printf("Arquivo nao pode ser criptografado. ");
                    }
                }
                waitPress();
                break;
            case 5:
                topBox(ITEMS[4], 2);
                if(fileChoice == 0){
                    printf("Nenhum arquivo foi selecionado. ");
                }else if(lineTotal == 0){
                    printf("Nenhum texto encontrado no arquivo. ");
                }else if(isCripto == 0){
                    printf("Arquivo nao esta criptografado. ");
                }else{
                    getPass(pass);
                    decrypt(text, lineTotal, pass);
                    printf("Texto descriptografado com sucesso! Acesse VISUALIZAR para ver o texto.\n");
                }
                waitPress();
                break;
            case 6:
                topBox(ITEMS[5], 2);
                printf("***CRIAR ARQUIVO***\n"
                        "-CRIA ARQUIVO DE TEXTO [%s] NA PASTA \"%s\", CONTIDA NA PASTA RAIZ DO PROGRAMA,"
                        " COM TEXTO E NOME DIGITADO PELO USUARIO.\n\n"
                        "***SELECIONAR ARQUIVO***\n"
                        "-LISTA TODOS OS ARQUIVOS DE TEXTO [%s] NA PASTA \"%s\", CONTIDA NA PASTA RAIZ DO PROGRAMA,"
                        " PERMITINDO AO USUARIO ESCOLHER QUAL SERA LIDO PARA SER CRIPTOGRAFADO OU PARA"
                        " VISUALIZADO DESCRIPTOGRAFADO.\n\n"
                        "***VISUALIZAR ARQUIVO***\n"
                        "-PERMITE AO USUARIO VISUALIZAR O TEXTO EXTRAIDO DO ARQUIVO SELECIONADO."
                        " ESTE PODERA SER EXIBIDO TANTO DESCRIPTOGRAFADO QUANTO CRIPTOGRAFADO.\n\n"
                        "***CRIPTOGRAFAR***\n"
                        "-ESSA OPCAO INICIA O PROCESSO DE CRIPTOGRAFIA SOBREPONDO O TEXTO NO ARQUIVO ORIGINAL.\n\n"
                        "***DESCRIPTOGRAFAR***\n"
                        "-ESSA OPCAO INICIA O PROCESSO DE DESCRIPTOGRAFIA. O TEXTO DESCRIPTOGRAFADO SÓ"
                        "-PODERA SER VISUALIZADO DENTRO DO APLICATIVO.\n\n"
                        "***SOBRE***\n"
                        "-INFORMACOES ACADEMICAS DO PROJETO.\n\n"
                        "***SAIR***\n"
                        "-ENCERRA O APLICATIVO.\n\n", FILETYPE, FOLDER, FILETYPE, FOLDER);
                blankLine(2);
                waitPress();
                break;
            case 7:
                topBox(ITEMS[6], 2);
                printf("SOFTWARE PROJETADO PARA A DISCIPLINA APS (ATIVIDADES PRATICAS SUPERVISIONADAS).\n"
                        "CURSO: CIENCIA DA COMPUTACAO --- TURMA: CC2P18 / CC2Q18 --- UNIP CAMPUS VARGAS\n\n"
                        "GUILHERME	C59386-9\n"
                        "GUSTAVO	C64211-8\n"
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
