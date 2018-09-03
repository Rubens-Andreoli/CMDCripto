#include <stdio.h>      //sprintf, printf, fprintf
#include <stdlib.h>
#include <string.h>     //strcpy
#include "interface.h"
#include "textio.h"
#include "cripto.h"

/**Testa se há arquivo selecionado e se o texto é válido para ser processado exibindo mensagem apropriada.
Retorna: 0[não há texto]; 1[texto válido].*/
int testText(int fileChoice, int chNum);

int main()
{
    /*VARIÁVEIS: INTERFACE*/
    const char MENU_ITEMS[MENU_MAX_ITEMS][UI_TEXT_SIZE] = {"CRIAR ARQUIVO","SELECIONAR ARQUIVO","VISUALIZAR","CRIPTOGRAFAR","DESCRIPTOGRAFAR","RESTAURAR","AJUDA","SOBRE"};
    const int MENU_NUM_ITEMS = 8;
    char uiText[UI_TEXT_SIZE];

    /*VARIÁVEIS: TEXTIO*/
    int fileNumTotal, fileChoice = -1, fileNumOver, chNum;
    char text[CHAR_MAX], fileName[FILES_NAME_MAX], files[MENU_MAX_ITEMS][FILES_NAME_MAX];

    /*VARIÁVEIS: CRIPTO*/
    int isTextCripto, isFileCripto;
    char pass[PASS_MAX];


    int menuChoice = 0;
    while (menuChoice != MENU_NUM_ITEMS+1){
        topBox("MENU", 1);
        fillMenu(MENU_ITEMS, MENU_NUM_ITEMS, 1);
        dashLine(2);
        sprintf(uiText, "Digite a opcao desejada de acordo com o menu (1-%d):", MENU_NUM_ITEMS+1);
        menuChoice = chooseItem(uiText, MENU_NUM_ITEMS+1);
        switch(menuChoice){
            case 1:
                topBox(MENU_ITEMS[0], 1);
                sprintf(uiText, "Para marcar o final do texto digite: %c", TEXT_STOP);
                closedTextLine(uiText, -1);
                closedTextLine("",-1);
                closedTextLine("!!NAO UTILIZE ACENTOS!!", 1);
                dashLine(2);
                if((chNum = createText(text))){
                    topBox(MENU_ITEMS[0], 1);
                    closedTextLine("!!NAO UTILIZE ACENTOS!!", 1);
                    dashLine(2);
                    setFilename(fileName);
                    if(writeFile(text, fileName)){
                        strcpy(files[0], fileName);
                        fileChoice = 0;
                        printf("Arquivo [%s] foi criado com sucesso.\n", files[fileChoice]);
                        isTextCripto = isFileCripto = 0;
                    }else{
                        fprintf(stderr, "Arquivo nao pode ser criado na pasta [%s]!\n", FOLDER);
                        limitPrint(uiText);
                    }
                }
                waitPress();
                break;
            case 2:
                topBox(MENU_ITEMS[1], 1);
                fileNumTotal = readFolder(files, MENU_MAX_ITEMS);
                fileNumOver = (fileNumTotal<=MENU_MAX_ITEMS)? 0:fileNumTotal-MENU_MAX_ITEMS;
                if(fileNumTotal){
                    fillMenu(files, fileNumTotal, 0);
                    dashLine(fileNumOver? 1:2);
                    if(fileNumOver){
                      sprintf(uiText, "!!%d ARQUIVOS NAO EXIBIDOS!!", fileNumOver);
                      closedTextLine(uiText, 1);
                      dashLine(2);
                    }
                    sprintf(uiText, "Digite a opcao referente ao arquivo desejado (1-%d):", fileNumTotal-fileNumOver);
                    fileChoice = (chooseItem(uiText, fileNumTotal))-1;
                    chNum = readFile(text, files[fileChoice]);
                    if(chNum>0)
                        isTextCripto = isFileCripto = testCripto(text);
                    printf("Arquivo [%s] %s\n", files[fileChoice], chNum==-1?"nao encontrado!":"selecionado.");
                }else{
                    dashLine(1);
                    printf("Nenhum arquivo foi encontrado!\n");
                }
                waitPress();
                break;
            case 3:
                topBox(MENU_ITEMS[2], 2);
                if(testText(fileChoice, chNum)){
                    isTextCripto? printf("%s\b \n", text):printf("%s\n", text);
                    dashLine(2);
                    printf("O arquivo [%s]%s foi exibido.\n", files[fileChoice], isTextCripto?" criptografado":isFileCripto?" descriptografado":"");
                }
                waitPress();
                break;
            case 4:
                topBox(MENU_ITEMS[3], 2);
                if(testText(fileChoice, chNum)){
                    if(isTextCripto || isFileCripto){
                        printf("Arquivo ja esta criptografado. ");
                    }else{
                        setPass(pass);
                        encrypt(text, pass);
                        isTextCripto=1;
                        if(writeFile(text, files[fileChoice])){
                            printf("Arquivo criptografado com sucesso! ");
                        }else{
                            fprintf(stderr, "Texto criptografado não pode ser salvo! ");
                        }
                    }
                }
                waitPress();
                break;
            case 5:
                topBox(MENU_ITEMS[4], 2);
                if(testText(fileChoice, chNum)){
                    if(!isTextCripto){
                        printf("O texto ja esta descriptografado. ");
                    }else{
                        setPass(pass);
                        decrypt(text, pass);
                        isTextCripto = 0;
                        printf("Texto descriptografado com sucesso! Acesse VISUALIZAR para ver o texto.\n");
                    }
                }
                waitPress();
                break;
            case 6:
                topBox(MENU_ITEMS[5], 2);
                if(testText(fileChoice, chNum)){
                    if(!isFileCripto && !isTextCripto){
                        printf("O arquivo ja esta descriptografado. ");
                    }else{
                        if(isTextCripto){
                            setPass(pass);
                            decrypt(text, pass);
                            writeFile(text, files[fileChoice]);
                            isTextCripto = isFileCripto = 0;
                        }else if(isFileCripto && !isTextCripto){
                            writeFile(text, files[fileChoice]);
                            isTextCripto = isFileCripto = 0;
                        }
                        printf("O arquivo foi restaurado com sucesso! ");
                    }
                }
                waitPress();
                break;
            case 7:
                topBox(MENU_ITEMS[6], 2);
                printf("***CRIAR ARQUIVO***\n"
                        "-CRIA ARQUIVO DESCRIPTOGRAFADO DE TEXTO [%s] NA PASTA \"%s\", CONTIDA"
                        " NA PASTA RAIZ DO PROGRAMA, COM TEXTO E NOME DIGITADO PELO USUARIO."
                        " PARA CONCLUIR A DIGITACAO DO TEXTO DIGITE O CARACTERE |.\n\n"
                        "***SELECIONAR ARQUIVO***\n"
                        "-LISTA %d ARQUIVOS DE TEXTO [%s] NA PASTA \"%s\", CONTIDA NA"
                        " PASTA RAIZ DO PROGRAMA, PERMITINDO AO USUARIO ESCOLHER QUAL SERA"
                        " LIDO PARA SER CRIPTOGRAFADO OU PARA VISUALIZA-LO DESCRIPTOGRAFADO.\n\n"
                        "***VISUALIZAR ARQUIVO***\n"
                        "-PERMITE AO USUARIO VISUALIZAR O TEXTO EXTRAIDO DO ARQUIVO SELECIONADO."
                        " ESTE PODERA SER EXIBIDO TANTO DESCRIPTOGRAFADO QUANTO CRIPTOGRAFADO.\n\n"
                        "***CRIPTOGRAFAR***\n"
                        "-ESSA OPCAO INICIA O PROCESSO DE CRIPTOGRAFIA SOBREPONDO O TEXTO NO"
                        " ARQUIVO ORIGINAL.\n\n"
                        "***DESCRIPTOGRAFAR***\n"
                        "-ESSA OPCAO INICIA O PROCESSO DE DESCRIPTOGRAFIA.\n\n"
                        "***RESTAURAR***\n"
                        "-INICIA O PROCESSO DE DESCRIPTOGRAFIA CASO NECESSARIO E"
                        " SOBREPOE O TEXTO CRIPTOGRAFADO NO ARQUIVO.\n\n"
                        "***SOBRE***\n"
                        "-INFORMACOES ACADEMICAS DO PROJETO.\n\n"
                        "***SAIR***\n"
                        "-ENCERRA O APLICATIVO.\n\n", FILES_TYPE, FOLDER, MENU_MAX_ITEMS, FILES_TYPE, FOLDER);
                dashLine(2);
                waitPress();
                break;
            case 8:
                topBox(MENU_ITEMS[7], 2);
                printf("SOFTWARE PROJETADO PARA A DISCIPLINA APS (ATIVIDADES PRATICAS"
                       " SUPERVISIONADAS).\nCURSO: CIENCIA DA COMPUTACAO --- TURMA:"
                       " CC2P18 / CC2Q18 --- UNIP CAMPUS VARGAS\n\nGUILHERME	C59386-9\n"
                        "GUSTAVO	        C64211-8\nMURILO		C42HIH-4\n"
                        "RUBENS		T49128-2\n\nESTE SOFTWARE FOI DESENVOLVIDO EM LINGUAGEM"
                        " DE PROGRAMACAO ESTRUTURADA (\"C\") E TEM COMO OBJETIVO UTILIZAR"
                        " TECNICAS DE CRIPTOGRAFIA PARA CRIPTOGRAFAR E DESCRIPTOGRAFAR O CONTEUDO"
                        " DE UM ARQUIVO DE TEXTO, CRIADO PREVIAMENTE OU COM O USO DESTE SOFTWARE,"
                        " UTILIZANDO PARA ISSO A CIFRA DE VIGENERE.\n");
                dashLine(2);
                waitPress();
                break;
        }
    }
    return 0;
}

int testText(int fileChoice, int chNum){
    if(fileChoice != -1){
        if(chNum == -1){
            printf("Arquivo nao encontrado!\n");
            return 0;
        }else if(chNum == 0){
            printf("Nenhum texto encontrado no arquivo!\n");
            return 0;
        }else{
            return 1;
        }
    }else{
        printf("Nenhum arquivo foi selecionado ou criado!\n");
        return 0;
    }
}
