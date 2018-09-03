#define ALPHABET " !#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]{}abcdefghijklmnopqrstuvwxyz|^"
#define ALPHABET_SIZE 89
#define MIN_PASS_SIZE 4
#define MAX_PASS_SIZE 9

/**Repete pedido de senha até que esta seja válida.*/
void getPass(char pass[MAX_PASS_SIZE+1]){
    int lenght;
    do{
        printf("Digite uma senha de %d-%d digitos: ", MIN_PASS_SIZE, MAX_PASS_SIZE);
        fflush(stdin);
        fgets(pass, MAX_PASS_SIZE+1, stdin);
        strtok(pass, "\n");
        lenght=strlen(pass);
    }while(lenght<MIN_PASS_SIZE);
}

/**Converte caractere retornando inteiro.*/
int charToInt(char letter){
    int pos;
    for(pos=0;pos<=ALPHABET_SIZE-1;pos++){
        if(letter == ALPHABET[pos])
            return pos;
    }
    return 0;
}

/**Cria password estendido com número de caracteres igual ao texto a ser criptografado/descriptografado. */
void extendPass(char pass[MAX_PASS_SIZE+1], int charTotal, char extPass[CHAR_MAX]){
    int lenght=strlen(pass), pos, oldPos=0;
    for(pos=0;pos<=charTotal-1;pos++){
        extPass[pos] = pass[oldPos];
        oldPos++;
        if(oldPos>lenght-1)
            oldPos=0;
    }
}

/**Criptografa o texto utilizando a cifra de vigenere.*/
void encrypt(char text[LINE_MAX][CHAR_MAX], int lineTotal, char pass[MAX_PASS_SIZE+1]){
    int line, pos, charsLine;
    char extPass[CHAR_MAX];
    for(line=0;line<=lineTotal;line++){
        charsLine = strlen(text[line]);
        extendPass(pass, strlen(text[line]), extPass);
        for(pos=0;pos<=charsLine-1;pos++)
            text[line][pos] = ALPHABET[(charToInt(text[line][pos])+charToInt(extPass[pos]))%ALPHABET_SIZE];
    }
}

/**Descriptografa o texto utilizando a cifra de vigenere.*/
void decrypt(char text[LINE_MAX][CHAR_MAX], int lineTotal, char pass[CHAR_MAX]){
    int line, pos, sum, charsLine;
    char extPass[CHAR_MAX];
    for(line=0;line<=lineTotal;line++){
        charsLine = strlen(text[line]);
        extendPass(pass, strlen(text[line]), extPass);
        for(pos=0;pos<=charsLine-1;pos++){
            sum = charToInt(text[line][pos])-charToInt(extPass[pos]);
            if(sum<0){
                sum = charToInt(text[line][pos])+ALPHABET_SIZE;
                text[line][pos] = ALPHABET[sum-charToInt(extPass[pos])];
            }else{
                text[line][pos] = ALPHABET[(charToInt(text[line][pos])-charToInt(extPass[pos]))%ALPHABET_SIZE];
            }
        }
    }
}
