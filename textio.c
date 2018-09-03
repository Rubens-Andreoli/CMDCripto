#include <stdio.h>      //getchar, fopen, fclose, getc, fputs
#include <stdlib.h>     //malloc, free
#include <dirent.h>     //opendir, readdir, closedir, struct dirent
#include <ctype.h>      //isalpha, isdigit
#include <string.h>     //strlen, strcat, strstr, strcpy
#include <assert.h>     //assert
#include "textio.h"

/**Valida caractere dependendo da origem do input (banChar = BAN_CHAR_CONSOLE/BAN_CHAR_FILE).
Retorna: char ASCII válido.*/
static char validChar(char invalidChar, const char banChar[]);

/**Libera memória alocada para "*text", e inicializa como NULL.*/
static void clearText(char ** text);

void initText(char ** text){
    *text = NULL;
}

int validFilename(char fileName[]){
    int pos, nameLen;
    nameLen = strlen(fileName);
    if(nameLen < FILES_NAME_MIN || nameLen > FILES_NAME_MAX-EXT_LEN)
        return 0;
    for(pos=0; pos<strlen(fileName); pos++){
        if(!isalpha(fileName[pos]) && !isdigit(fileName[pos]))
            return 0;
    }  //TODO: teste if file exists?!
    strcat(fileName, FILES_TYPE);
    return 1;
}

int createText(const char fileName[]){
    char ch = getchar();
    if(ch != '\n' && ch != TEXT_STOP){
        char filepath[FILES_NAME_MAX+FOLDER_LEN] = FOLDER;
        strcat(filepath, fileName);
        FILE * file;
        file = fopen(filepath, "w");
        if (file == NULL) return -2;
        int isLimit = 0; //[isLimit] registra se atingiu limite de buffer do arquivo
        do{
            if(ch<0) //caractere acentuado ou outro inválido
                ch = validChar(ch, BAN_CHAR_CONSOLE);
            if(putc(ch, file) == EOF)
                isLimit = 1;
        }while(!isLimit && (ch=getchar())!=TEXT_STOP);
        fclose(file);
        while (getchar() != '\n') continue;
        if(isLimit) return 0;
        else return 1;
    }else{
        getchar();
        return -1;
    }
}

static char validChar(char invalidChar, const char banChar[]){ //caracteres inválidos podem ter mesmo valor numérico dependendo do input
    int n;
    for(n=0; n<BAN_CHAR_SIZE; n++){
        if((int)invalidChar==banChar[n])
            return OK_CHAR[n];
    }
    return '*'; //se caractere for desconhecido para conversão
}

int readFolder(char files[][FILES_NAME_MAX]){
    DIR * folder;
    folder = opendir(FOLDER);
    if(folder == NULL) return -1;
    struct dirent * dir;
    int fileNum, fileTotal;
    for(fileNum=0, fileTotal=0; (dir=readdir(folder))!=NULL; fileTotal++){
        if(fileNum<FILES_MAX && strstr(dir->d_name, FILES_TYPE)!=NULL && strlen(dir->d_name)<FILES_NAME_MAX-4){
            strcpy(files[fileNum], dir->d_name);
            //*strchr(files[fileNum], '.') = '\0'; //remove extensão
            fileNum++;
        }
    }
    closedir(folder);
    return fileTotal-2; //Remove da contagem os arquivos: . e ..
}

static void clearText(char ** text){
    if(*text != NULL){
        free(*text);
        *text = NULL;
    }
}

int readFile(char ** text, const char fileName[]){
    clearText(text);
    assert(strlen(fileName) < FILES_NAME_MAX-1);
    assert(strchr(fileName, '.') != NULL);
    char filepath[FILES_NAME_MAX+FOLDER_LEN]=FOLDER;
    strcat(filepath, fileName);
    FILE * file;
    file = fopen(filepath,"r");
    if(file == NULL) return -2;
    long chNum;
    fseek(file, 0L, SEEK_END);
    chNum = ftell(file);
    fseek(file, 0L, SEEK_SET);
    if(chNum == 0){
        fclose(file);
        return 0;
    }
    *text = (char *)malloc((chNum+3)*sizeof(char)); //(chNum+3) para o \0 e buffer de segurança
    if(*text == NULL){
        fclose(file);
        return -1;
    }
    int i;
    for(i=0; ((*text)[i] = getc(file))!= EOF; i++){
        if((*text)[i]<0)
            (*text)[i] = validChar((*text)[i], BAN_CHAR_FILE);
    }
    (*text)[i]='\0';
    fclose(file);
    return 1;
}

int writeFile(const char * const text, const char fileName[]){
    assert(strlen(fileName) < FILES_NAME_MAX-1);
    assert(strchr(fileName, '.') != NULL);
    char filepath[FILES_NAME_MAX+FOLDER_LEN] = FOLDER;
    strcat(filepath, fileName);
    FILE * file;
    file = fopen(filepath, "w");
    if (file == NULL) return -1;
    int wTest = fputs(text, file);
    fclose(file);
    if(wTest == EOF) return 0;
    else return 1;
}
