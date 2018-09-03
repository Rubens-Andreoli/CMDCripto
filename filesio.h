#include <dirent.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define FOLDER "./texts/"
#define FILENAM_MAX 50
#define FILENUM_MAX 10
#define CHAR_MAX 6001
#define FILETYPE ".txt"

/**Preenche uma matriz[número do arquivo][nome do arquivo] com os arquivos encontrados na pasta determinada pelo programa e retorna: 0[nenhum arquivo encontrado]; 1+[total de arquivos].*/
int readFolder(char files[FILENUM_MAX][FILENAM_MAX]){
    DIR *ptr_folder;
    struct dirent *ptr_dir;
    ptr_folder = opendir(FOLDER);
    int fileNum = 0;
    char filenameShow[FILENAM_MAX+10];
    while(((ptr_dir = readdir(ptr_folder)) != NULL) && (fileNum <= FILENUM_MAX)){
        if(strstr(ptr_dir->d_name, FILETYPE) != NULL){
            if(fileNum < FILENUM_MAX){
                sprintf(files[fileNum], "%s", ptr_dir->d_name);
                sprintf(filenameShow, "%2d - [%s]", fileNum+1, files[fileNum]);
                textLine(filenameShow, MENU_ALIGN);
            }else{
                textLine("...", -1);
            }
            fileNum++;
        }
    }
    closedir(ptr_folder);
    return fileNum;
}

/**Preenche um array[caracter] com o texto encontrado no arquivo desejado e retorna: -1[arquivo não encontrado]; 0[arquivo vazio]; 1+[total de caracteres].*/
int readFile(char text[CHAR_MAX], char filename[FILENAM_MAX]){
    FILE *ptr_file;
    char filepath[FILENAM_MAX+10] = FOLDER;
    strcat(filepath, filename);
    ptr_file = fopen(filepath,"r");
    if(!ptr_file)
        return -1;
    fgets(text,CHAR_MAX, ptr_file);
    fclose(ptr_file);
    return strlen(text);
}

/**Mostra resultado da leitura do arquivo desejado.*/
void showText(char text[CHAR_MAX], int charTotal){
    if(charTotal != -1){
        if(charTotal == 0){
            printf("Nenhum texto encontrado no arquivo.\n");
        }else{
            printf("%s", text);
        }
    }else{
        printf("Arquivo nao encontrado.\n");
    }
}

/**Escreve matriz[linha][caracter] no arquivo desejado e retorna: 0[arquivo não encontrado]; 1[concluido].*/
int writeFile(char text[CHAR_MAX], char filename[FILENAM_MAX]){
    FILE *ptr_file;
    char filepath[FILENAM_MAX+10] = FOLDER;
    strcat(filepath, filename);
    ptr_file = fopen(filepath, "w");
    if (!ptr_file)
        return 0;
    fprintf(ptr_file, text);
    fclose(ptr_file);
    return 1;
}
