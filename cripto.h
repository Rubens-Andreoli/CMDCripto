#ifndef CRIPTO_H_INCLUDED
#define CRIPTO_INCLUDED
//version 1.0

#define PASS_MIN 4          /*Número mínimo de caracteres da senha.*/
#define PASS_MAX 9+1        /*Número máximo de caracteres da senha + \0.*/

/*Alfabeto de caracteres válidos para utilização na criptografia e seu número de caracteres:*/
#define ALPHABET " !#$%&()*+,-./:;ABCDEFGHIJKLMNOPQRSTUVWXYZ<=>?@|^0123456789[]{}abcdefghijklmnopqrstuvwxyz"
#define ALPHABET_SIZE 89 //número primo para evitar conflito nos cálculos de módulo.

/**Repete questão e preenche pass[] com senha válida, maior que PASS_MIN e menor que PASS_MAX.*/
void setPass(char pass[]);

/**Converte caractere em inteiro de acordo com a posição no ALPHABET.
Retorna: [inteiro representativo do char].*/
int charToInt(char letter);

/**Criptografa text[] utilizando a cifra de vigenere.*/
void encrypt(char text[], const char pass[]);

/**Descriptografa text[] utilizando a cifra de vigenere.*/
void decrypt(char text[], const char pass[]);

/**Testa se text[] está criptografado.
Retorna: 0[não é criptografado]; 1[é criptografado].*/
int testCripto(const char text[]);

#endif /* CRIPTO_H_INCLUDED */
