#ifndef TEXTIO_H_INCLUDED
#define TEXTIO_H_INCLUDED
//version 1.0

#define FOLDER "./texts/"      /*Caminho da pasta onde os aquivos são salvos.*/
#define FOLDER_LEN 8           /*Número de caracteres do caminho da pasta.*/
#define FILES_TYPE ".txt"      /*Tipo do arquivo salvo.*/
#define EXT_LEN 4              /*Número de caracteres da extensão do arquivo.*/
#define FILES_NAME_MIN 2       /*Número mínimo de caracteres do nome do arquivo.*/
#define FILES_NAME_MAX 60+4+1  /*Número máximo de caracteres do nome do arquivo + extensão + \0.*/ //[interface UI_TEXT_SIZE]
#define CHAR_MAX 6000+1+2      /*Número máximo de caracteres por linha a serem lidos + \0 + margem de segurança.*/
#define TEXT_STOP '|'

/*Constantes para conversão de caracteres não reconhecidos pelo console:*/
static const char BAN_CHAR_FILE[] = "àáâãÀÁÂÃèéêÈÉÊìíîÌÍÎòóôõÒÓÔÕúùûüÙÚÛÜçÇ";
static const int BAN_CHAR_CONSOLE[] = {
    -123,-96,-125,-58,-73,-75,-74,-57,      //a
    -118,-126,-120,-44,-112,-46,            //e
    -115,-95,-116,-34,-42,-41,              //i
    -107,-94,-109,-28,-29,-32,-30,-27,      //o
    -93,-105,-106,-127,-21,-23,-22,-102,    //u
    -121,-128};                             //c
static const char OK_CHAR[] = "aaaaAAAAeeeEEEiiiIIIooooOOOOuuuuUUUUcC";
static const int BAN_CHAR_SIZE = 38;

/**Preenche text[] com input do stdin até o limite de CHAR_MAX ou até o caractere TEXT_STOP.
*Retorna: [número de caracteres gravados].*/
unsigned int createText(char text[]);

/**Valida caractere dependendo da origem do input (cOrF = c: console/ f: file).
Retorna: [char ASCII válido].*/
char validChar(char invalidCharm, char cOrF);

/**Repete questão e preenche fileName[] até que o nome do arquivo seja validado pela função validFilename().*/
void setFilename(char fileName[]);

/**Remove quebra de linha e adiciona extensão FILES_TYPE ao nome do arquivo se este não tiver caracteres especiais
ou acentuados, e com número de caracteres entre FILES_NAME_MIN e FILES_NAME_MAX-4.
*Retorn: 0[nome não criado]; 1[concluído].*/
int validFilename(char fileName[]);

/**Escreve text[] no arquivo filename[] (deve conter extensão), e edita filename[] se passar do FILES_NAME_MAX.
*Retorna: 0[arquivo não criado]; 1[concluído].*/
int writeFile(const char text[], char filename[]);

/**Preenche files[][FILES_NAME_MAX] com os arquivos de extensão FILES_TYPE,
até o limite filesLimit de arquivos, e FILES_NAME_MAX caracteres, encontrados na pasta determinada pelo programa.
*Retorna: [número total de arquivos na pasta, sem restrições].*/
int readFolder(char files[][FILES_NAME_MAX], int filesLimit);

/**Preenche text[] com o texto encontrado no arquivo filename[] até o limite de CHAR_MAX.
*Retorna: -2[nome do arquivo muito grande]; -1[arquivo não encontrado]; 0[arquivo vazio]; 1+[total de linhas].*/
int readFile(char text[], const char filename[]);

#endif // TEXTIO_H_INCLUDED
