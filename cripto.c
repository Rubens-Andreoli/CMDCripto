#include <ctype.h>      //isprint
#include <string.h>     //strlen
#include "cripto.h"

/**Converte caractere em inteiro de acordo com a posição no ALPHABET.
Retorna: [inteiro representativo do char].*/
static int charToInt(char letter);

int validPass(const char pass[]){
    int passLen = strlen(pass);
    if(passLen<PASS_MIN || passLen>PASS_MAX) return 0;
    int i, isInvalid = 0, pos;
    for(i=0; i<passLen && isInvalid == 0; i++){
        isInvalid = 1;
        for(pos=0; pos<ALPHABET_SIZE; pos++){
            if(pass[i]==ALPHABET[pos])
                isInvalid = 0;
        }
    }
    if(isInvalid) return 0;
    else return 1;
}

static int charToInt(char letter){
    int pos;
    for(pos=0; pos<ALPHABET_SIZE; pos++){
        if(letter==ALPHABET[pos])
            return pos;
    }
    return 0;
}

void encrypt(char text[], const char pass[]){
    int pos, passLenght=strlen(pass);
    for(pos=0; text[pos]!='\0'; pos++){ // ou [pos<strlen(text)]
        if(isprint(text[pos]))
            text[pos]=ALPHABET[(charToInt(text[pos])+charToInt(pass[pos%passLenght]))%ALPHABET_SIZE];
            //ALPHABET[(posição do char do texto no alfabeto + posição relativa do char da senha no alfabeto)%tamanho do alfabeto]
    }
    text[pos] = '~';
    text[pos+1] = '\0';
}

void decrypt(char text[], const char pass[]){
    int pos, passLenght=strlen(pass);
    for(pos=0; text[pos]!='\0'; pos++){
        if(isprint(text[pos]))
            text[pos]=ALPHABET[((charToInt(text[pos])-charToInt(pass[pos%passLenght]))+ALPHABET_SIZE)%ALPHABET_SIZE];
            //ALPHABET[((posição do char do texto no alfabeto - posição relativa do char da senha no alfabeto)+tamanho do alfabeto para recuperar % da criptografia)%tamanho do alfabeto]
    }
    text[pos-1] = ' ';
    text[pos] = '\0';
}

int testCripto(const char text[]){
    if(text[strlen(text)-1]=='~') return 1;
    else return 0;
}
