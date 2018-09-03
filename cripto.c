#include <stdio.h>      //printf, fflush, fgets
#include <ctype.h>      //isprint
#include <string.h>     //strlen, strtok
#include "cripto.h"

void setPass(char pass[]){
    int isInvalid = 1;
    while(isInvalid){
        printf("Digite uma senha de %d-%d caracteres: ", PASS_MIN, PASS_MAX-1);
        fflush(stdin);
        fgets(pass, PASS_MAX, stdin);
        strtok(pass, "\n");
        if(strlen(pass)<PASS_MIN){
            printf("Senha deve ter no minimo %d caracteres!\n\n", PASS_MIN);
        }else{
            isInvalid = 0;
        }
    }
}

int charToInt(char letter){
    int pos;
    for(pos=0; pos<ALPHABET_SIZE; pos++){
        if(letter==ALPHABET[pos])
            return pos;
    }
    return 0;
}

void encrypt(char text[], const char pass[]){
    int pos, passLenght=strlen(pass);
    for(pos=0; text[pos]!='\0'; pos++){
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
    if(text[strlen(text)-1]=='~')
        return 1;
    return 0;
}
