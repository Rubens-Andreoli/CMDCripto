#include <stdio.h>      //sprintf, printf, fprintf
#include <string.h>     //strcpy
#include "interface.h"
#include "textio.h"
#include "cripto.h"

int testText(int fileChoice, const char * const text);
int testRead(int readReturn);

int main()
{
    ////// VARIÁVEIS: INTERFACE //////
    char uiText[UI_TEXT_SIZE];

    /////// VARIÁVEIS: TEXTIO //////
    int fileNumTotal, fileChoice = -1, fileNumOver, isCreated;
    char files[FILES_MAX][FILES_NAME_MAX], fileName[FILES_NAME_MAX];
    char * text;
    initText(&text);

    ////// VARIÁVEIS: CRIPTO //////
    int isTextCripto, isFileCripto;
    char pass[PASS_MAX];

    int menuChoice = 0;
    while (menuChoice != MAIN_MENU_NUM_ITEMS){
        topBox("MENU", 1);
        MAIN_MENU;
        dashLine(2);
        sprintf(uiText, "Digite a opcao desejada de acordo com o menu (1-%d):", MAIN_MENU_NUM_ITEMS);
        menuChoice = chooseItem(uiText, MAIN_MENU_NUM_ITEMS);
        switch(menuChoice){
            case 1:
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 1);
                closedTextLine("!!NAO UTILIZE ACENTOS!!", 1);
                dashLine(2);
                sprintf(uiText, "Nome do arquivo [%d-%d caracteres] para salvar seu texto: ", FILES_NAME_MIN, FILES_NAME_MAX-EXT_LEN-1);
                setValidStr(uiText,"Nome invalido!\n\n",fileName,validFilename);
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 1);
                sprintf(uiText, "Para marcar o final do texto digite: %c", TEXT_STOP);
                closedTextLine(uiText, -1);
                closedTextLine("",-1);
                closedTextLine("!!NAO UTILIZE ACENTOS!!", 1);
                dashLine(2);
                isCreated = createText(fileName);
                if(isCreated==-2){
                    fprintf(stderr, "Arquivo [%s] pode ser criado na pasta [%s]!", fileName, FOLDER);
                }else if(isCreated>=0){
                    strcpy(files[0], fileName);
                    fileChoice = 0;
                    dashLine(1);
                    printf(uiText, "Arquivo [%s] foi criado com sucesso.\n", files[fileChoice]);
                    isTextCripto = isFileCripto = 0;
                    testRead(readFile(&text, files[fileChoice]));
                }
                waitPress();
                break;
            case 2:
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 1);
                fileNumTotal = readFolder(files);
                fileNumOver = (fileNumTotal<=MENU_MAX_ITEMS)? 0:fileNumTotal-MENU_MAX_ITEMS;
                if(fileNumTotal){
                    fillMenu(fileNumTotal-fileNumOver, FILES_NAME_MAX, files);
                    dashLine(fileNumOver? 1:2);
                    if(fileNumOver){
                      sprintf(uiText, "!!%d ARQUIVOS NAO EXIBIDOS!!", fileNumOver);
                      closedTextLine(uiText, 1);
                      dashLine(2);
                    }
                    sprintf(uiText, "Digite a opcao referente ao arquivo desejado (1-%d):", fileNumTotal-fileNumOver);
                    fileChoice = (chooseItem(uiText, fileNumTotal-fileNumOver))-1;
                    if(testRead(readFile(&text, files[fileChoice]))){
                        isTextCripto = isFileCripto = testCripto(text);
                        printf(uiText, "Arquivo [%s] selecionado\n", files[fileChoice]);
                    }
                }else{
                    dashLine(1);
                    puts("Nenhum arquivo foi encontrado!");
                }
                waitPress();
                break;
            case 3:
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 2);
                if(testText(fileChoice, text)){
                    putchar('\n');
                    if(!isTextCripto){
                        splitTextLine(text);
                        puts("\b ");
                    }else puts(text);
                    putchar('\n');
                    dashLine(2);
                    printf("O arquivo [%s]%s foi exibido.\n", files[fileChoice], isTextCripto?" criptografado":isFileCripto?" descriptografado":"");
                }
                waitPress();
                break;
            case 4:
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 2);
                if(testText(fileChoice, text)){
                    if(isTextCripto || isFileCripto){
                        printf("Arquivo ja esta criptografado. ");
                    }else{
                        sprintf(uiText, "Digite uma senha de %d-%d caracteres: ", PASS_MIN, PASS_MAX-1);
                        setValidStr(uiText, "Senha invalida!\n\n", pass, validPass);
                        encrypt(text, pass);
                        isTextCripto=1;
                        if(writeFile(text, files[fileChoice]) > 0){
                            isFileCripto=1;
                            printf("Arquivo criptografado com sucesso! ");
                        }else{
                            fprintf(stderr, "Texto criptografado não pode ser salvo! ");
                        }
                    }
                }
                waitPress();
                break;
            case 5:
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 2);
                if(testText(fileChoice, text)){
                    if(!isTextCripto){
                        printf("O texto ja esta descriptografado. ");
                    }else{
                        setValidStr("Digite a senha do arquivo: ", "Senha invalida!\n\n", pass, validPass);
                        decrypt(text, pass);
                        isTextCripto = 0;
                        puts("Texto descriptografado com sucesso! Acesse VISUALIZAR para ver o texto.");
                    }
                }
                waitPress();
                break;
            case 6:
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 2);
                if(testText(fileChoice, text)){
                    if(!isFileCripto && !isTextCripto){
                        printf("O arquivo ja esta descriptografado. ");
                    }else{
                        if(isTextCripto){
                            setValidStr("Digite a senha do arquivo: ", "Senha invalida!\n\n", pass, validPass);
                            decrypt(text, pass);
                        }
                        writeFile(text, files[fileChoice]);
                        isTextCripto = isFileCripto = 0;
                        printf("O arquivo foi restaurado com sucesso! ");
                    }
                }
                waitPress();
                break;
            case 7:
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 2);
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
                topBox(MAIN_MENU_ITEMS[menuChoice-1], 2);
                puts("SOFTWARE PROJETADO PARA A DISCIPLINA APS (ATIVIDADES PRATICAS"
                       " SUPERVISIONADAS).\nCURSO: CIENCIA DA COMPUTACAO --- TURMA:"
                       " CC2P18 / CC2Q18 --- UNIP CAMPUS VARGAS\n\nGUILHERME	C59386-9\n"
                        "GUSTAVO	        C64211-8\nMURILO		C42HIH-4\n"
                        "RUBENS		T49128-2\n\nESTE SOFTWARE FOI DESENVOLVIDO EM LINGUAGEM"
                        " DE PROGRAMACAO ESTRUTURADA (\"C\") E TEM COMO OBJETIVO UTILIZAR"
                        " TECNICAS DE CRIPTOGRAFIA PARA CRIPTOGRAFAR E DESCRIPTOGRAFAR O CONTEUDO"
                        " DE UM ARQUIVO DE TEXTO, CRIADO PREVIAMENTE OU COM O USO DESTE SOFTWARE,"
                        " UTILIZANDO PARA ISSO A CIFRA DE VIGENERE.");
                dashLine(2);
                waitPress();
                break;
        }
    }
    return 0;
}

int testText(int fileChoice, const char * const text){
    if(fileChoice == -1){
        puts("Nenhum arquivo foi selecionado ou criado!");
        return 0;
    }
    if(text == NULL){
        puts("Nao ha texto para ser processado!");
        return 0;
    }
    return 1;
}

int testRead(int readReturn){
    if(readReturn == -2){
        puts("Arquivo nao encontrado!");
        return 0;
    }
    if(readReturn == -1){
        fputs("Falha na alocação de memória!",stderr);
        return 0;
    }
    if(readReturn == 0){
        puts("Nenhum texto encontrado no arquivo!");
        return 0;
    }
    return 1;
}
