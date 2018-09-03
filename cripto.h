#define ALPHABET " ABCDEFGHIJKLMNOPQRSTUVWXYZ[]{}abcdefghijklmnopqrstuvwxyz0123456789!#$%&()*+,-./:;<=>?@|^"
#define ALPHABET_SIZE 89
#define MIN_PASS_SIZE 4
#define MAX_PASS_SIZE 9

/**Repete pedido de senha até que esta seja válida.*/
void getPass(char pass[MAX_PASS_SIZE+1]){
    do{
        printf("Digite uma senha de %d-%d digitos: ", MIN_PASS_SIZE, MAX_PASS_SIZE);
        fflush(stdin);
        fgets(pass, MAX_PASS_SIZE+1, stdin);
        strtok(pass, "\n");
    }while(strlen(pass)<MIN_PASS_SIZE);
}

/**Converte caractere retorna: [inteiro representativo do char].*/
int charToInt(char letter){
    int pos;
    for(pos=0;pos<=ALPHABET_SIZE-1;pos++){
        if(letter == ALPHABET[pos])
            return pos;
    }
    return 0;
}

/**Criptografa o texto utilizando a cifra de vigenere.*/
void encrypt(char text[LINE_MAX][CHAR_MAX], int lineTotal, char pass[MAX_PASS_SIZE+1]){
    int line, pos, charsLine, passLenght = strlen(pass);
    for(line=0;line<=lineTotal;line++){
        charsLine = strlen(text[line]);
        for(pos=0;pos<=charsLine-1;pos++)
            text[line][pos] = ALPHABET[(charToInt(text[line][pos])+charToInt(pass[pos%passLenght]))%ALPHABET_SIZE];
    }
}

/**Descriptografa o texto utilizando a cifra de vigenere.*/
void decrypt(char text[LINE_MAX][CHAR_MAX], int lineTotal, char pass[CHAR_MAX]){
    int line, pos, sum, charsLine, passLenght = strlen(pass);
    for(line=0;line<=lineTotal;line++){
        charsLine = strlen(text[line]);
        for(pos=0;pos<=charsLine-1;pos++){
            sum = charToInt(text[line][pos])-charToInt(pass[pos%passLenght]);
            if(sum<0){
                sum = charToInt(text[line][pos])+ALPHABET_SIZE;
                text[line][pos] = ALPHABET[sum-charToInt(pass[pos%passLenght])];
            }else{
                text[line][pos] = ALPHABET[(charToInt(text[line][pos])-charToInt(pass[pos%passLenght]))%ALPHABET_SIZE];
            }
        }
    }
}
