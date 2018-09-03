#ifndef TEXTIO_H_INCLUDED
#define TEXTIO_H_INCLUDED
//version 2.0

/* ---- Definições gerais ---- */
#define FOLDER "./texts/"       /*Caminho da pasta onde os aquivos são salvos.*/
#define FOLDER_LEN 8            /*Número de caracteres do caminho da pasta.*/
#define FILES_TYPE ".txt"       /*Tipo do arquivo salvo.*/
#define EXT_LEN 4               /*Número de caracteres da extensão do arquivo.*/
#define FILES_NAME_MIN 2        /*Número mínimo de caracteres do nome do arquivo.*/
#define FILES_NAME_MAX 60+4+1   /*Número máximo de caracteres do nome do arquivo + extensão + \0.*/
#define TEXT_STOP '|'           /*Caractere utilizado para simbolizar final da inserção de texto.*/
#define FILES_MAX 15            /*Número máximo de arquivos a serem lidos.*/

/*Constantes para conversão de caracteres não reconhecidos pelo console:*/
static const char BAN_CHAR_FILE[] = "àáâãÀÁÂÃèéêÈÉÊìíîÌÍÎòóôõÒÓÔÕúùûüÙÚÛÜçÇ";
static const char BAN_CHAR_CONSOLE[] = {
    -123,-96,-125,-58,-73,-75,-74,-57,      //a
    -118,-126,-120,-44,-112,-46,            //e
    -115,-95,-116,-34,-42,-41,              //i
    -107,-94,-109,-28,-29,-32,-30,-27,      //o
    -93,-105,-106,-127,-21,-23,-22,-102,    //u
    -121,-128};                             //c
static const char OK_CHAR[] = "aaaaAAAAeeeEEEiiiIIIooooOOOOuuuuUUUUcC";
static const int BAN_CHAR_SIZE = 38;

/* ---- Protótipo das funções ---- */
/**Inicializa "*text" para NULL.*/
void initText(char ** text);

/**Valida e acrescenta FILES_TYPE ao "fileName" se este não tiver caracteres especiais ou acentuados, e possui número de caracteres entre FILES_NAME_MIN e FILES_NAME_MAX-EXT_LEN.
*Retorn: 0[nome não válido]; 1[válido].*/
int validFilename(char fileName[]);

/**Preenche "fileName[]" com input do stdin até o limite do input buffer ou até o caractere TEXT_STOP, se algum texto for digitado além de TEXT_STOP.
*Retorna: -2[falha, arquivo não criado]; -1[falha, nenhum texto inserido]; 0[sucesso, porém limite foi atingido]; 1[sucesso].*/
int createText(const char fileName[]);

/**Preenche "files[][FILES_NAME_MAX]" com os arquivos de extensão FILES_TYPE,
até o limite FILES_MAX de arquivos, com FILES_NAME_MAX caracteres, encontrados na pasta determinada pelo programa.
*Retorna: -1[falha, ao acessar FOLDER]; 0+[número total de arquivos na pasta, sem restrições].*/
int readFolder(char files[][FILES_NAME_MAX]);

/**Libera memória alocada para "*text" e se arquivo "fileName[]" (deve conter extensão e ter tamanho máximo FILES_NAME_MAX) contém texto,
aloca espaço suficiente e copia o conteúdo para "(*text)[]".
*Retorna: -2[falha, arquivo não aberto]; -1[falha, memória não alocada]; 0[sucesso, porém arquivo vazio]; 1[sucesso].*/
int readFile(char ** text, const char fileName[]);

/**Escreve "(*text)[]" no arquivo "fileName[]" (deve conter extensão e ter tamanho máximo FILES_NAME_MAX).
*Retorna: -1[falha, arquivo não criado]; 0[falha, texto não inserido no arquivo]; 1[sucesso].*/
int writeFile(const char * const text, const char fileName[]);

/* ---- Main exemplo ---- */
/*int main()
{
    /////// VARIÁVEIS: TEXTIO //////
    int fileNumTotal, fileChoice = -1, fileNumOver, isCreated;
    char files[FILES_MAX][FILES_NAME_MAX], fileName[FILES_NAME_MAX];
    char * text;
    initText(&text);

    return 0;
}*/

#endif // TEXTIO_H_INCLUDED
