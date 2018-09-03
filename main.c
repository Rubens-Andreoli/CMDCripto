#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "filesio.h"
#include "cripto.h"

int main()
{
    int menuChoice=0, fileNumTotal=0, fileChoice=0, lineTotal=0, isCripto=0;
    char files[MENU_MAX_ITEMS][UI_TEXT_SIZE], text[LINE_MAX][CHAR_MAX], question[UI_QSTN_SIZE];
    char pass[MAX_PASS_SIZE+1], fileName[UI_TEXT_SIZE];

    int MENU_NUM_ITEMS=7;
    char ITEMS[MENU_MAX_ITEMS][UI_TEXT_SIZE]={"CRIAR ARQUIVO","SELECIONAR ARQUIVO","VISUALIZAR",
        "CRIPTOGRAFAR","DESCRIPTOGRAFAR","AJUDA","SOBRE"};

    while (menuChoice!=MENU_NUM_ITEMS+1){
        TopBox("MENU", 1);
        FillMenu(ITEMS, MENU_NUM_ITEMS, 1);
        sprintf(question, "Digite a opcao desejada de acordo com o menu (1-%d): ",
                MENU_NUM_ITEMS+1);
        menuChoice=ChooseValue(question, MENU_NUM_ITEMS+1);
        switch(menuChoice){
            case 1:
                TopBox(ITEMS[0], 1);
                TextLine("!!NAO UTILIZE ACENTOS!!", 1);
                BlankLine(2);
                lineTotal=GetText(text);
                TopBox(ITEMS[0], 2);
                CreateFilename(fileName);
                if(WriteFile(text, lineTotal, fileName)==1){
                    sprintf(files[0], "%s", fileName);
                    fileChoice=1;
                    isCripto=0;
                    printf("Arquivo [%s] foi criado com sucesso.\n", files[fileChoice-1]);
                }else{
                    printf("Arquivo nao pode ser criado. Verifique se a pasta [%s] existe.\n",
                            FOLDER);
                }
                WaitPress();
                break;
            case 2:
                TopBox(ITEMS[1], 1);
                fileNumTotal=ReadFolder(files);
                if(fileNumTotal!=0){
                    FillMenu(files, fileNumTotal, 0);
                    sprintf(question, "Digite a opcao referente ao arquivo desejado (1-%d): ",
                        fileNumTotal);
                    fileChoice=ChooseValue(question, fileNumTotal);
                    lineTotal=ReadFile(text, files[fileChoice-1]);
                    if(lineTotal>0)
                        isCripto=TestCripto(text, lineTotal);
                    printf("Arquivo [%s] %s.\n", files[fileChoice-1],
                            lineTotal!=-1?"selecionado":"nao encontrado");
                }else{
                    BlankLine(1);
                    printf("Nenhum arquivo foi encontrado. ");
                }
                WaitPress();
                break;
            case 3:
                TopBox(ITEMS[2], 2);
                if(TestFile(fileChoice, lineTotal)){
                    ShowText(text, lineTotal);
                    BlankLine(2);
                    printf("O arquivo [%s]%s foi exibido.\n", files[fileChoice-1],
                            isCripto?" criptografado":"");
                }
                WaitPress();
                break;
            case 4:
                TopBox(ITEMS[3], 2);
                if(TestFile(fileChoice, lineTotal)){
                    if(isCripto == 1){
                        printf("Arquivo ja esta criptografado. ");
                    }else{
                        GetPass(pass);
                        Encrypt(text, lineTotal, pass);
                        isCripto=1;
                        if(WriteFile(text, lineTotal, files[fileChoice-1])==1){
                            printf("Arquivo criptografado com sucesso! ");
                        }else{
                            printf("Arquivo nao pode ser criptografado. ");
                        }
                    }
                }
                WaitPress();
                break;
            case 5:
                TopBox(ITEMS[4], 2);
                if(TestFile(fileChoice, lineTotal)){
                    if(isCripto == 0){
                        printf("Arquivo nao esta criptografado. ");
                    }else{
                        GetPass(pass);
                        Decrypt(text, lineTotal, pass);
                        isCripto=0;
                        printf("Texto descriptografado com sucesso!"
                               "Acesse VISUALIZAR para ver o texto.\n");
                    }
                }
                WaitPress();
                break;
            case 6:
                TopBox(ITEMS[5], 2);
                printf("***CRIAR ARQUIVO***\n"
                        "-CRIA ARQUIVO DESCRIPTOGRAFADO DE TEXTO [%s] NA PASTA \"%s\", CONTIDA"
                        " NA PASTA RAIZ DO PROGRAMA, COM TEXTO E NOME DIGITADO PELO USUARIO."
                        " PARA CONCLUIR A DIGITACAO DO TEXTO CRIE UM PARAGRAFO VAZIO.\n\n"
                        "***SELECIONAR ARQUIVO***\n"
                        "-LISTA TODOS OS ARQUIVOS DE TEXTO [%s] NA PASTA \"%s\", CONTIDA NA"
                        " PASTA RAIZ DO PROGRAMA, PERMITINDO AO USUARIO ESCOLHER QUAL SERA"
                        "LIDO PARA SER CRIPTOGRAFADO OU PARA VISUALIZA-LO DESCRIPTOGRAFADO.\n\n"
                        "***VISUALIZAR ARQUIVO***\n"
                        "-PERMITE AO USUARIO VISUALIZAR O TEXTO EXTRAIDO DO ARQUIVO SELECIONADO."
                        " ESTE PODERA SER EXIBIDO TANTO DESCRIPTOGRAFADO QUANTO CRIPTOGRAFADO.\n\n"
                        "***CRIPTOGRAFAR***\n"
                        "-ESSA OPCAO INICIA O PROCESSO DE CRIPTOGRAFIA SOBREPONDO O TEXTO NO"
                        " ARQUIVO ORIGINAL. ESTE PROCESSO E PERMANENTE, UMA VEZ CRIPTOGRAFADO"
                        " O ARQUIVO SO PODERA SER VISUALIZADO DESCRIPTOGRAFADO COM A AJUDA"
                        " DESTE PROGRAMA.\n\n"
                        "***DESCRIPTOGRAFAR***\n"
                        "-ESSA OPCAO INICIA O PROCESSO DE DESCRIPTOGRAFIA. O TEXTO"
                        " DESCRIPTOGRAFADO SO PODERA SER VISUALIZADO DENTRO DO APLICATIVO.\n\n"
                        "***SOBRE***\n"
                        "-INFORMACOES ACADEMICAS DO PROJETO.\n\n"
                        "***SAIR***\n"
                        "-ENCERRA O APLICATIVO.\n\n", FILES_TYPE, FOLDER, FILES_TYPE, FOLDER);
                BlankLine(2);
                WaitPress();
                break;
            case 7:
                TopBox(ITEMS[6], 2);
                printf("SOFTWARE PROJETADO PARA A DISCIPLINA APS (ATIVIDADES PRATICAS"
                       " SUPERVISIONADAS).\nCURSO: CIENCIA DA COMPUTACAO --- TURMA:"
                       " CC2P18 / CC2Q18 --- UNIP CAMPUS VARGAS\n\nGUILHERME	C59386-9\n"
                        "GUSTAVO	        C64211-8\nMURILO		C42HIH-4\n"
                        "RUBENS		T49128-2\n\nESTE SOFTWARE FOI DESENVOLVIDO EM LINGUAGEM"
                        " DE PROGRAMACAO ESTRUTURADA (\"C\") E TEM COMO OBJETIVO UTILIZAR"
                        " TECNICAS DE CRIPTOGRAFIA PARA CRIPTOGRAFAR E DESCRIPTOGRAFAR O CONTEUDO"
                        " DE UM ARQUIVO DE TEXTO, CRIADO PREVIAMENTE OU COM O USO DESTE SOFTWARE,"
                        " UTILIZANDO PARA ISSO A CIFRA DE VIGENERE.\n");
                BlankLine(2);
                WaitPress();
                break;
        }
    }
    return 0;
}
