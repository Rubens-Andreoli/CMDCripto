#include <dirent.h>
#include <ctype.h>

#define FOLDER "./texts/"
#define FOLDER_SIZE 8
#define FILES_TYPE ".txt"
#define FILES_MAX MENU_MAX_ITEMS
#define FILES_NAME_MAX UI_TEXT_SIZE
#define LINE_MAX 60
#define CHAR_MAX 6001
#define BAN_LETTERS "àáâãÀÁÂÃèéêÈÉÊìíîÌÍÎòóôõÒÓÔÕúùûüÙÚÛÜçÇ"
#define OK_LETTERS  "aaaaAAAAeeeEEEiiiIIIooooOOOOuuuuUUUUcC"
#define LETTERS_SIZE 38

/**Preenche uma matriz[número do arquivo][nome do arquivo] com os arquivos
encontrados na pasta determinada pelo programa.
Retorna: 0[nenhum arquivo encontrado]; 1+[total de arquivos].*/
int ReadFolder(char files[FILES_MAX][FILES_NAME_MAX]){
    DIR *ptr_folder;
    struct dirent *ptr_dir;
    ptr_folder=opendir(FOLDER);
    int fileCtr=0;
    while(((ptr_dir=readdir(ptr_folder))!=NULL)&&(fileCtr<FILES_MAX)){
        if(strstr(ptr_dir->d_name, FILES_TYPE)!=NULL){
            sprintf(files[fileCtr], "%s", ptr_dir->d_name);
            fileCtr++;
        }
    }
    closedir(ptr_folder);
    return fileCtr;
}

/**Remove quebra de linha e acentuação (geradas fora do programa) do texto.*/
void ClearText(char text[LINE_MAX][CHAR_MAX], int lineTotal){
    int line, pos, i, charsLine;
    for(line=0; line<lineTotal; line++){
        strtok(text[line], "\n");
        charsLine=strlen(text[line]);
        for(pos=0; pos<=charsLine-1; pos++){
            for(i=0; i<=LETTERS_SIZE; i++){
                if(text[line][pos]==BAN_LETTERS[i])
                    text[line][pos]=OK_LETTERS[i];
            }
        }
    }
}

/**Preenche uma matriz[linha][caracter] com o texto encontrado no arquivo desejado.
Retorna: -1[arquivo não encontrado]; 0[arquivo vazio]; 1+[total de linhas].*/
int ReadFile(char text[LINE_MAX][CHAR_MAX], char filename[FILES_NAME_MAX]){
    FILE *ptr_file;
    char filepath[FILES_NAME_MAX+FOLDER_SIZE]=FOLDER;
    strcat(filepath, filename);
    ptr_file=fopen(filepath,"r");
    int line=0;
    if(!ptr_file)
        return -1;
    while((fgets(text[line], CHAR_MAX, ptr_file)!=NULL)&&(line<LINE_MAX))
        line++;
    fclose(ptr_file);
    ClearText(text, line);
    return line;
}

/**Mostra resultado da leitura do arquivo desejado.*/
void ShowText(char text[LINE_MAX][CHAR_MAX], int lineTotal){
    int line;
    printf("\n");
    for(line=0; line<lineTotal; line++)
        printf("%s\n", text[line]);
    printf("\n");
}

/**Escreve matriz[linha][caracter] no arquivo desejado.
Retorna: 0[arquivo não criado]; 1[concluido].*/
int WriteFile(char text[LINE_MAX][CHAR_MAX], int lineTotal,
              char filename[FILES_NAME_MAX]){
    FILE *ptr_file;
    char filepath[FILES_NAME_MAX+FOLDER_SIZE] = FOLDER;
    strcat(filepath, filename);
    ptr_file=fopen(filepath, "w");
    if (!ptr_file)
        return 0;
    int line;
    for(line=0; line<lineTotal; line++){
        fprintf(ptr_file, text[line]);
        if(line!=lineTotal-1)
            fprintf(ptr_file, "\n");
    }
    fclose(ptr_file);
    return 1;
}

/**Repete questão ate receber nome do arquivo sem caracteres especiais
ou acentuados.*/
void CreateFilename(char fileName[FILES_NAME_MAX]){
   int pos=0, isInvalid;
   do{
        isInvalid=0;
        printf("Digite o nome do arquivo [%d-%d caracteres] para salvar seu texto: ",
                1, FILES_NAME_MAX);
        fflush(stdin);
        fgets(fileName, FILES_NAME_MAX, stdin);
        strtok(fileName, "\n");
        while((pos<strlen(fileName))&&(isInvalid==0)){
            if((!isalpha(fileName[pos]))&&(!isdigit(fileName[pos]))){
                printf("Nao utilize caracteres acentuados ou especiais.\n\n");
                isInvalid=1;
            }
            pos++;
        }
        strcat(fileName, FILES_TYPE);
    }while((strlen(fileName)<=1)||(isInvalid!=0));
}

/**Preenche uma matriz[linha][caracter] com o texto digitado pelo usuário.
Retorna: [total de linhas].*/
int GetText(char text[LINE_MAX][CHAR_MAX]){
    int line=0;
    do{
        printf("PARAGRAFO %d: ", line+1);
        fflush(stdin);
        fgets(text[line], CHAR_MAX, stdin);
        line++;
        }while((strlen(text[line-1])!=1)&&(line<LINE_MAX));
    line--;
    ClearText(text, line);
    return line;
}

/**Testa se arquivo pode ser utilizado nas operações do programa.
Retorna: 0[não]; 1[sim].*/
int TestFile(int fileChoice, int lineTotal){
    int isOk=1;
    if(fileChoice == 0){
        printf("Nenhum arquivo foi selecionado ou criado. ");
        isOk=0;
    }else if(lineTotal==-1){
        printf("Arquivo nao encontrado. ");
        isOk=0;
    }else if(lineTotal == 0){
        printf("Nenhum texto encontrado no arquivo. ");
        isOk=0;
    }
    return isOk;
}
