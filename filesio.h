#include <dirent.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define BAN_LETTERS "àáâãÀÁÂÃèéêÈÉÊìíîÌÍÎòóôõÒÓÔÕúùûüÙÚÛÜçÇ"
#define OK_LETTERS  "aaaaAAAAeeeEEEiiiIIIooooOOOOuuuuUUUUcC"
#define LETTERS_SIZE 38
#define FOLDER "./texts/"
#define FILENAM_MAX 50
#define FILENUM_MAX 20
#define CHAR_MAX 6001
#define LINE_MAX 60
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

/**Remove quebra de linha e acentuacao do texto.*/
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
    clearText(text, line);
    return line;
}

/**Mostra resultado da leitura do arquivo desejado.*/
void showText(char text[LINE_MAX][CHAR_MAX], int lineTotal){
    int line;
    if(lineTotal != -1){
        if(lineTotal == 0)
            printf("Nenhum texto encontrado no arquivo.\n");
        for(line=0;line < MIN(lineTotal,LINE_MAX);line++)
            printf("%s\n", text[line]);
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
    for(line=0;line < lineTotal;line++){
        fprintf(ptr_file, text[line]);
        if(line!=lineTotal-1)
            fprintf(ptr_file, "\n");
    }
    fclose(ptr_file);
    return 1;
}
