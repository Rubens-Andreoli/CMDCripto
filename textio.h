#ifndef TEXTIO_H_INCLUDED
#define TEXTIO_H_INCLUDED
//version 2.0

/* ---- Defini��es gerais ---- */
#define FOLDER "./texts/"       /*Caminho da pasta onde os aquivos s�o salvos.*/
#define FOLDER_LEN 8            /*N�mero de caracteres do caminho da pasta.*/
#define FILES_TYPE ".txt"       /*Tipo do arquivo salvo.*/
#define EXT_LEN 4               /*N�mero de caracteres da extens�o do arquivo.*/
#define FILES_NAME_MIN 2        /*N�mero m�nimo de caracteres do nome do arquivo.*/
#define FILES_NAME_MAX 60+4+1   /*N�mero m�ximo de caracteres do nome do arquivo + extens�o + \0.*/
#define TEXT_STOP '|'           /*Caractere utilizado para simbolizar final da inser��o de texto.*/
#define FILES_MAX 15            /*N�mero m�ximo de arquivos a serem lidos.*/

/*Constantes para convers�o de caracteres n�o reconhecidos pelo console:*/
static const char BAN_CHAR_FILE[] = "��������������������������������������";
static const char BAN_CHAR_CONSOLE[] = {
    -123,-96,-125,-58,-73,-75,-74,-57,      //a
    -118,-126,-120,-44,-112,-46,            //e
    -115,-95,-116,-34,-42,-41,              //i
    -107,-94,-109,-28,-29,-32,-30,-27,      //o
    -93,-105,-106,-127,-21,-23,-22,-102,    //u
    -121,-128};                             //c
static const char OK_CHAR[] = "aaaaAAAAeeeEEEiiiIIIooooOOOOuuuuUUUUcC";
static const int BAN_CHAR_SIZE = 38;

/* ---- Prot�tipo das fun��es ---- */
/**Inicializa "*text" para NULL.*/
void initText(char ** text);

/**Valida e acrescenta FILES_TYPE ao "fileName" se este n�o tiver caracteres especiais ou acentuados, e possui n�mero de caracteres entre FILES_NAME_MIN e FILES_NAME_MAX-EXT_LEN.
*Retorn: 0[nome n�o v�lido]; 1[v�lido].*/
int validFilename(char fileName[]);

/**Preenche "fileName[]" com input do stdin at� o limite do input buffer ou at� o caractere TEXT_STOP, se algum texto for digitado al�m de TEXT_STOP.
*Retorna: -2[falha, arquivo n�o criado]; -1[falha, nenhum texto inserido]; 0[sucesso, por�m limite foi atingido]; 1[sucesso].*/
int createText(const char fileName[]);

/**Preenche "files[][FILES_NAME_MAX]" com os arquivos de extens�o FILES_TYPE,
at� o limite FILES_MAX de arquivos, com FILES_NAME_MAX caracteres, encontrados na pasta determinada pelo programa.
*Retorna: -1[falha, ao acessar FOLDER]; 0+[n�mero total de arquivos na pasta, sem restri��es].*/
int readFolder(char files[][FILES_NAME_MAX]);

/**Libera mem�ria alocada para "*text" e se arquivo "fileName[]" (deve conter extens�o e ter tamanho m�ximo FILES_NAME_MAX) cont�m texto,
aloca espa�o suficiente e copia o conte�do para "(*text)[]".
*Retorna: -2[falha, arquivo n�o aberto]; -1[falha, mem�ria n�o alocada]; 0[sucesso, por�m arquivo vazio]; 1[sucesso].*/
int readFile(char ** text, const char fileName[]);

/**Escreve "(*text)[]" no arquivo "fileName[]" (deve conter extens�o e ter tamanho m�ximo FILES_NAME_MAX).
*Retorna: -1[falha, arquivo n�o criado]; 0[falha, texto n�o inserido no arquivo]; 1[sucesso].*/
int writeFile(const char * const text, const char fileName[]);

/* ---- Main exemplo ---- */
/*int main()
{
    /////// VARI�VEIS: TEXTIO //////
    int fileNumTotal, fileChoice = -1, fileNumOver, isCreated;
    char files[FILES_MAX][FILES_NAME_MAX], fileName[FILES_NAME_MAX];
    char * text;
    initText(&text);

    return 0;
}*/

#endif // TEXTIO_H_INCLUDED
