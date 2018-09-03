#ifndef CRIPTO_H_INCLUDED
#define CRIPTO_INCLUDED
//version 1.0

#define PASS_MIN 4          /*N�mero m�nimo de caracteres da senha.*/
#define PASS_MAX 9+1        /*N�mero m�ximo de caracteres da senha + \0.*/

/*Alfabeto de caracteres v�lidos para utiliza��o na criptografia e seu n�mero de caracteres:*/
#define ALPHABET " !#$%&()*+,-./:;ABCDEFGHIJKLMNOPQRSTUVWXYZ<=>?@|^0123456789[]{}abcdefghijklmnopqrstuvwxyz"
#define ALPHABET_SIZE 89 //n�mero primo para evitar conflito nos c�lculos de m�dulo.

/**Repete quest�o e preenche pass[] com senha v�lida, maior que PASS_MIN e menor que PASS_MAX.*/
void setPass(char pass[]);

/**Converte caractere em inteiro de acordo com a posi��o no ALPHABET.
Retorna: [inteiro representativo do char].*/
int charToInt(char letter);

/**Criptografa text[] utilizando a cifra de vigenere.*/
void encrypt(char text[], const char pass[]);

/**Descriptografa text[] utilizando a cifra de vigenere.*/
void decrypt(char text[], const char pass[]);

/**Testa se text[] est� criptografado.
Retorna: 0[n�o � criptografado]; 1[� criptografado].*/
int testCripto(const char text[]);

#endif /* CRIPTO_H_INCLUDED */
