#include <stdio.h>      //fflush, getchar, printf, fgets, fopen, fprintf, fclose, getc
#include <dirent.h>     //opendir, readdir, closedir, struct dirent
#include <ctype.h>      //isalpha, isdigit
#include <string.h>     //strlen, strtok, strcat, strstr, strcpy
#include "textio.h"

unsigned int createText(char text[]){
    unsigned int chNum=0;
    fflush(stdin);
    for(chNum=0; chNum<CHAR_MAX-3 && (text[chNum]=getchar())!=TEXT_STOP; chNum++){
        if((int)text[chNum]<0){ //caractere acentuado ou outro inválido
            text[chNum] = validChar(text[chNum],'c');
        }
    }
    text[chNum]='\0';
    return chNum;
}

char validChar(char invalidChar, char cOrF){
    int n;
    for(n=0; n<BAN_CHAR_SIZE; n++){
        if(cOrF=='c'){ //caracteres inválidos podem ter mesmo valor numérico dependendo do input
            if((int)invalidChar==BAN_CHAR_CONSOLE[n])
                return OK_CHAR[n];
        }
        if(cOrF=='f'){
            if(invalidChar==BAN_CHAR_FILE[n])
            return OK_CHAR[n];
        }
    }
    return '*'; //se caractere for desconhecido para conversão
}

void setFilename(char fileName[]){
    int isInvalid = 1;
    while(isInvalid){
        printf("Digite o nome do arquivo [%d-%d caracteres] para salvar seu texto: ", FILES_NAME_MIN, FILES_NAME_MAX-EXT_LEN-1);
        fflush(stdin);
        fgets(fileName, FILES_NAME_MAX-EXT_LEN, stdin);
        if(!validFilename(fileName)){
            printf("Nome invalido!\n\n");
        }else{
            isInvalid = 0;
        }
    }
}

int validFilename(char fileName[]){
    int pos, nameLen;
    nameLen = strlen(fileName);
    if(nameLen < FILES_NAME_MIN || nameLen > FILES_NAME_MAX-EXT_LEN)
        return 0;
    strtok(fileName, "\n");
    for(pos=0; pos<strlen(fileName); pos++){
        if(!isalpha(fileName[pos]) && !isdigit(fileName[pos])){
            return 0;
        }
    }
    strcat(fileName, FILES_TYPE);
    return 1;
}

int writeFile(const char text[], char filename[]){
    if(strlen(filename)>FILES_NAME_MAX-1){
        filename[FILES_NAME_MAX-1] = '\0'; //reduz filename caso não tenha sido criado com createFilename()
    }
    char filepath[FILES_NAME_MAX+FOLDER_LEN] = FOLDER;
    strcat(filepath, filename);
    FILE * file;
    file = fopen(filepath, "w");
    if (file == NULL)
        return 0;
    fprintf(file, text);
    fclose(file);
    return 1;
}

int readFolder(char files[][FILES_NAME_MAX], int filesLimit){
    DIR * folder;
    folder = opendir(FOLDER);
    struct dirent * dir;
    int fileNum, fileTotal;
    for(fileNum=0, fileTotal=0; (dir=readdir(folder))!=NULL; fileTotal++){
        if(fileNum<filesLimit && strstr(dir->d_name, FILES_TYPE)!=NULL && strlen(dir->d_name)<FILES_NAME_MAX-4){
            strcpy(files[fileNum], dir->d_name);
            //*strchr(files[fileNum], '.') = '\0'; //remove extensão
            fileNum++;
        }
    }
    closedir(folder);
    return fileTotal-2; //Remove os arquivos: . e ..
}

int readFile(char text[], const char filename[]){
    if(strlen(filename)>FILES_NAME_MAX-1){
        return -2; //filename muito grande para adicionar a pasta no filepath
    }
    char filepath[FILES_NAME_MAX+FOLDER_LEN]=FOLDER;
    strcat(filepath, filename);
    FILE * file;
    file = fopen(filepath,"r");
    if(file == NULL)
        return -1;
    int chNum;
    for(chNum=0; chNum<CHAR_MAX-2 && (text[chNum] = getc(file))!= EOF; chNum++){
        if((int)text[chNum]<0){
            text[chNum] = validChar(text[chNum],'f');
        }
    }
    text[chNum]='\0';
    fclose(file);
    return chNum;
}
