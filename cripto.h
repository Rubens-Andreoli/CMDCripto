#ifndef CRIPTO_H_INCLUDED
#define CRIPTO_INCLUDED
//version 2.0

/* ---- Defini��es gerais ---- */
#define PASS_MIN 3          /*N�mero m�nimo de caracteres da senha.*/
#define PASS_MAX 15+1       /*N�mero m�ximo de caracteres da senha + \0.*/

/*Alfabeto de caracteres v�lidos para utiliza��o na criptografia e seu n�mero de caracteres:*/
#define ALPHABET " !#$%&()*+,-./:;ABCDEFGHIJKLMNOPQRSTUVWXYZ<=>?@|^0123456789[]{}abcdefghijklmnopqrstuvwxyz"
#define ALPHABET_SIZE 89 //n�mero primo para evitar conflito nos c�lculos de m�dulo.

/* ---- Prot�tipos das fun��es ---- */
/**Valida se "pass[]" possui n�mero de caracteres de PASS_MIN � PASS_MAX e se possui apenas caracteres do ALPHABET.
Retorna: 0[senha n�o v�lida]; 1[v�lida]*/
int validPass(const char pass[]);

/**Criptografa "text[]" com a senha "pass[]", utilizando a cifra de vigenere.*/
void encrypt(char text[], const char pass[]);

/**Descriptografa "text[]" com a senha "pass[]", utilizando a cifra de vigenere.*/
void decrypt(char text[], const char pass[]);

/**Testa se "text[]" est� criptografado.
Retorna: 0[n�o � criptografado]; 1[� criptografado].*/
int testCripto(const char text[]);

/* ---- Main exemplo ---- */
/*int main()
{
    ////// VARI�VEIS: CRIPTO //////
    int isTextCripto, isFileCripto;
    char pass[PASS_MAX];

    return 0;
}*/

#endif /* CRIPTO_H_INCLUDED */
