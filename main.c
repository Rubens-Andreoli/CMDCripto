#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "filesio.h"

int main()
{
    int menuChoice=0, fileNumTotal=0, fileChoice=0, lineTotal=0;
    char files[FILENUM_MAX][FILENAM_MAX], text[LINE_MAX][CHAR_MAX], question[QUESTION_SIZE];

    while (menuChoice != 7){
        topBox("MENU", 1);
        textLine("1 - SELECIONAR ARQUIVO", MENU_ALIGN);
        textLine("2 - VISUALIZAR", MENU_ALIGN);
        textLine("3 - CRIPTOGRAFAR", MENU_ALIGN);
        textLine("4 - DESCRIPTOGRAFAR", MENU_ALIGN);
        textLine("5 - AJUDA", MENU_ALIGN);
        textLine("6 - SOBRE", MENU_ALIGN);
        textLine("7 - SAIR", MENU_ALIGN);
        blankLine(2);
        menuChoice = chooseValue("Digite a opcao desejada de acordo com o menu (1-7): ", 7);

        switch(menuChoice){
            case 1:
                topBox("SELECIONAR ARQUIVO", 1);
                fileNumTotal = readFolder(files);
                blankLine(1);
                if(fileNumTotal != 0){
                    blankLine(1);
                    sprintf(question, "Digite a opcao referente ao arquivo desejado (1-%d): ", MIN(FILENUM_MAX, fileNumTotal));
                    fileChoice = chooseValue(question, MIN(FILENUM_MAX, fileNumTotal))-1;
                    printf("Arquivo [%s] selecionado. ", files[fileChoice]);
                    lineTotal = readFile(text, files[fileChoice]);
                }else{
                    printf("Nenhum arquivo foi encontrado. ");
                }
                waitPress();
                break;
            case 2:
                topBox("VISUALIZAR", 2);
                printf("\n");
                if (fileChoice != 0){
                    showText(text, lineTotal);
                    printf("\n");
                    blankLine(2);
                    printf("O arquivo [%s] foi exibido. ", files[fileChoice]);
                }else{
                    printf("Nenhum arquivo foi selecionado. ");
                }
                waitPress();
                break;
            case 3:
                topBox("CRIPTOGRAFAR", 2);
                //pedir senha; converter e testar senha; criptografar texto, salvar arquivo
                waitPress();
                break;
            case 4:
                topBox("DESCRIPTOGRAFAR", 2);
                //pedir senha; converter senha; descriptografar texto; salvar arquivo
                waitPress();
                break;
            case 5:
                topBox("AJUDA", 2);
                printf("***SELECIONAR ARQUIVO***\n"
                       "-LISTA TODOS OS ARQUIVOS DE TEXTO [.TXT] NA PASTA \"TEXTOS\", CONTIDA NA PASTA RAIZ DO PROGRAMA,"
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
                       "-ENCERRA O APLICATIVO.\n\n");
                blankLine(2);
                waitPress();
                break;
            case 6:
                topBox("SOBRE", 2);
                printf("SOFTWARE PROJETADO PARA A DISCIPLINA APS (ATIVIDADES PRATICAS SUPERVISIONADAS).\n"
                       "CURSO: CIENCIA DA COMPUTACAO --- TURMA: CC2P18 / CC2Q18 --- UNIP CAMPUS VARGAS\n\n"
                       "GUILHERME	RA\n"
                       "GUSTAVO		RA\n"
                       "MURILO		RA\n"
                       "RUBENS		RA\n"
                       "\nESTE SOFTWARE FOI DESENVOLVIDO EM LINGUAGEM DE PROGRAMACAO ESTRUTURADA (\"C\") E TEM COMO"
                       " OBJETIVO UTILIZAR TECNICAS DE CRIPTOGRAFIA PARA CRIPTOGRAFAR E DESCRIPTOGRAFAR UMA MENSAGEM"
                       " PREVIAMENTE INSERIDA EM UM ARQUIVO DE TEXTO UTILIZANDO PARA ISSO A CIFRA DE HILL.\n");
                blankLine(2);
                waitPress();
                break;
        }
    }
    return 0;
}