#include <dirent.h>
#include <ctype.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define BAN_LETTERS "àáâãÀÁÂÃèéêÈÉÊìíîÌÍÎòóôõÒÓÔÕúùûüÙÚÛÜçÇ"
#define OK_LETTERS  "aaaaAAAAeeeEEEiiiIIIooooOOOOuuuuUUUUcC"
#define LETTERS_SIZE 38
#define FOLDER "./texts/"
#define CHAR_MAX 6001
#define LINE_MAX 60
#define FILETYPE ".txt"

/**Preenche uma matriz[número do arquivo][nome do arquivo] com os arquivos encontrados na pasta determinada pelo programa e retorna: 0[nenhum arquivo encontrado]; 1+[total de arquivos].*/
int readFolder(char files[MENU_MAX_ITEMS][UI_TEXT_SIZE]){
    DIR *ptr_folder;
    struct dirent *ptr_dir;
    ptr_folder = opendir(FOLDER);
    int fileNum = 0;
    char filenameShow[UI_TEXT_SIZE+10];
    while(((ptr_dir = readdir(ptr_folder)) != NULL) && (fileNum <= MENU_MAX_ITEMS)){
        if(strstr(ptr_dir->d_name, FILETYPE) != NULL){
            sprintf(files[fileNum], "%s", ptr_dir->d_name);
            fileNum++;
        }
    }
    closedir(ptr_folder);
    return fileNum;
}

/**Remove quebra de linha e acentuação do texto.*/
void clearText(char text[LINE_MAX][CHAR_MAX], int lineTotal){
    int line, pos, i,charsLine;
    for(line=0; line<=lineTotal;line++){
        strtok(text[line], "\n");
        charsLine = strlen(text[line]);
        for(pos=0;pos<=charsLine-1;pos++){
            for(i=0;i<=LETTERS_SIZE;i++){
                if(text[line][pos] == BAN_LETTERS[i])
                    text[line][pos] = OK_LETTERS[i];
            }
        }
    }
}

/**Preenche uma matriz[linha][caracter] com o texto encontrado no arquivo desejado e retorna: -1[arquivo não encontrado]; 0[arquivo vazio]; 1+[total de linhas].*/
int readFile(char text[LINE_MAX][CHAR_MAX], char filename[UI_TEXT_SIZE], int *isCripto){
    FILE *ptr_file;
    char filepath[UI_TEXT_SIZE+10] = FOLDER;
    strcat(filepath, filename);
    ptr_file = fopen(filepath,"r");
    int line = 0;
    if(!ptr_file)
        return -1;
    while((fgets(text[line],CHAR_MAX, ptr_file) != NULL) && (line < LINE_MAX))
        line++;
    fclose(ptr_file);
    clearText(text, line);
    *isCripto=0;
    if(text[line-1][strlen(text[line-1])-1]=='~')
        *isCripto=1;
    return line;
}

/**Mostra resultado da leitura do arquivo desejado.*/
void showText(char text[LINE_MAX][CHAR_MAX], int lineTotal, int isCripto){
    int line;
    if(lineTotal != -1){
        if(lineTotal == 0){
            printf("Nenhum texto encontrado no arquivo.\n");
        }else{
            if(isCripto==1)
                text[lineTotal-1][strlen(text[lineTotal-1])-1]=' ';
            for(line=0;line < MIN(lineTotal,LINE_MAX);line++)
                printf("%s\n", text[line]);
        }
    }else{
        printf("Arquivo nao encontrado.\n");
    }
}

/**Escreve matriz[linha][caracter] no arquivo desejado e retorna: 0[arquivo não encontrado]; 1[concluido].*/
int writeFile(char text[LINE_MAX][CHAR_MAX], int lineTotal, char filename[UI_TEXT_SIZE], int isCreate){
    FILE *ptr_file;
    char filepath[UI_TEXT_SIZE+10] = FOLDER;
    strcat(filepath, filename);
    ptr_file = fopen(filepath, "w");
    if (!ptr_file)
        return 0;
    int line;
    for(line=0;line < lineTotal;line++){
        fprintf(ptr_file, text[line]);
        if(line!=lineTotal-1)
            fprintf(ptr_file, "\n");
    }
    if(!isCreate)
      fprintf(ptr_file, "~");
    fclose(ptr_file);
    return 1;
}

/**Repete questão ate receber nome do arquivo sem caracteres especiais ou acentuados e com mais de 3 caracteres.*/
void createFilename(char fileName[UI_TEXT_SIZE]){
   int pos=0, isInvalid;
   do{
        isInvalid=0;
        printf("Digite o nome do arquivo [%d-%d caracteres] para salvar seu texto: ", 1, UI_TEXT_SIZE);
        fflush(stdin);
        fgets(fileName, UI_TEXT_SIZE, stdin);
        strtok(fileName, "\n");
        while(pos<strlen(fileName) && isInvalid==0){
            if(!isalpha(fileName[pos]) && !isdigit(fileName[pos])){
                printf("Nao utilize caracteres acentuados ou especiais.\n\n");
                isInvalid=1;
            }
            pos++;
        }
        strcat(fileName, FILETYPE);
    }while(strlen(fileName) <= 1 || isInvalid !=0);
}

/**Preenche uma matriz[linha][caracter] com o texto digitado pelo usuário e retorna: [total de linhas].*/
int getText(char text[LINE_MAX][CHAR_MAX]){
    int line=0;
    do{
        printf("PARAGRAFO %d: ", line+1);
        fflush(stdin);
        fgets(text[line],CHAR_MAX, stdin);
        line++;
        }while((strlen(text[line-1]) != 1) && (line < LINE_MAX));
    line--;
    clearText(text, line);
    return line;
}
