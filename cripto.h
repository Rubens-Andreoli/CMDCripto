#define ALPHABET " !#$%&()*+,-./:;ABCDEFGHIJKLMNOPQRSTUVWXYZ<=>?@|^0123456789[]{}abcdefghijklmnopqrstuvwxyz"
#define ALPHABET_SIZE 89
#define MIN_PASS_SIZE 4
#define MAX_PASS_SIZE 9

/**Repete pedido de senha até que esta seja válida.*/
void GetPass(char pass[MAX_PASS_SIZE+1]){
    do{
        printf("Digite uma senha de %d-%d digitos: ", MIN_PASS_SIZE, MAX_PASS_SIZE);
        fflush(stdin);
        fgets(pass, MAX_PASS_SIZE+1, stdin);
        strtok(pass, "\n");
    }while(strlen(pass)<MIN_PASS_SIZE);
}

/**Converte caractere em inteiro.
Retorna: [inteiro representativo do char].*/
int CharToInt(char letter){
    int pos;
    for(pos=0; pos<=ALPHABET_SIZE-1; pos++){
        if(letter==ALPHABET[pos])
            return pos;
    }
    return 0;
}

/**Criptografa o texto utilizando a cifra de vigenere.*/
void Encrypt(char text[LINE_MAX][CHAR_MAX], int lineTotal, char pass[MAX_PASS_SIZE+1]){
    int line, pos, charsLine, passLenght=strlen(pass);
    for(line=0; line<lineTotal; line++){
        charsLine=strlen(text[line]);
        for(pos=0; pos<charsLine; pos++)
            text[line][pos]=ALPHABET[(CharToInt(text[line][pos])+CharToInt(pass[pos%passLenght]))%ALPHABET_SIZE];
        if(line==lineTotal-1)
            text[line][charsLine]='~';
    }
}

/**Descriptografa o texto utilizando a cifra de vigenere.*/
void Decrypt(char text[LINE_MAX][CHAR_MAX], int lineTotal, char pass[CHAR_MAX]){
    int line, pos, charsLine, passLenght=strlen(pass);
    for(line=0;line<lineTotal; line++){
        charsLine=strlen(text[line]);
        for(pos=0; pos<charsLine; pos++)
            text[line][pos]=ALPHABET[((CharToInt(text[line][pos])-CharToInt(pass[pos%passLenght]))+ALPHABET_SIZE)%ALPHABET_SIZE];
        if(line==lineTotal-1)
            text[line][charsLine-1]=' ';
    }
}

/**Testa se texto está criptografado.
Retorna: 0[não é criptografado]; 1[é criptografado].*/
int TestCripto(char text[LINE_MAX][CHAR_MAX], int lineTotal){
    if(text[lineTotal-1][strlen(text[lineTotal-1])-1]=='~')
        return 1;
    return 0;
}
