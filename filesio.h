#include <dirent.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define FOLDER "./texts/"
#define FILENAM_MAX 50
#define FILENUM_MAX 10
#define CHAR_MAX 500
#define LINE_MAX 10

/**Preenche uma matriz[número do arquivo][nome do arquivo] com os arquivos encontrados na pasta determinada pelo programa e retorna: 0[nenhum arquivo encontrado]; 1+[total de arquivos].*/
int readFolder(char files[FILENUM_MAX][FILENAM_MAX]){
    DIR *ptr_folder;
    struct dirent *ptr_dir;
    ptr_folder = opendir(FOLDER);
    int fileNum = 0;
    char filenameShow[FILENAM_MAX+10];
    while(((ptr_dir = readdir(ptr_folder)) != NULL) && (fileNum <= FILENUM_MAX)){
        if(strstr(ptr_dir->d_name, ".txt") != NULL){
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

/**Preenche uma matriz[linha][caracter] com o texto encontrado no arquivo desejado e retorna: -1[arquivo não encontrado]; 0[arquivo vazio]; 1+[total de linhas].*/
int readFile(char text[LINE_MAX][CHAR_MAX], char filename[FILENAM_MAX]){
    FILE *ptr_file;
    char filepath[FILENAM_MAX+10] = FOLDER;
    strcat(filepath, filename);
    ptr_file = fopen(filepath,"r");
    int line = 0;
    if(!ptr_file)
        return -1;
    while((fgets(text[line],CHAR_MAX, ptr_file) != NULL) && (line < LINE_MAX))
        line++;
    fclose(ptr_file);
    return line;
}

/**Mostra resultado da leitura do arquivo desejado.*/
void showText(char text[LINE_MAX][CHAR_MAX], int lineTotal){
    int line;
    if(lineTotal != -1){
        if(lineTotal == 0)
            printf("Nenhum texto encontrado no arquivo.\n");
        for(line=0;line < MIN(lineTotal,LINE_MAX);line++)
            printf("%s", text[line]);
    }else{
        printf("Arquivo nao encontrado.\n");
    }
}

/**Escreve matriz[linha][caracter] no arquivo desejado e retorna: 0[arquivo não encontrado]; 1[concluido].*/
int writeFile(char text[LINE_MAX][CHAR_MAX], int lineTotal, char filename[FILENAM_MAX]){
    FILE *ptr_file;
    char filepath[FILENAM_MAX+10] = FOLDER;
    strcat(filepath, filename);
    ptr_file = fopen(filepath, "w");
    if (!ptr_file)
        return 0;
    int line;
    for(line=0;line < lineTotal;line++)
        fprintf(ptr_file, text[line]);
    fclose(ptr_file);
    return 1;
}
