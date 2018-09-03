#ifndef CRIPTO_H_INCLUDED
#define CRIPTO_INCLUDED
//version 2.0

/* ---- Definições gerais ---- */
#define PASS_MIN 3          /*Número mínimo de caracteres da senha.*/
#define PASS_MAX 15+1       /*Número máximo de caracteres da senha + \0.*/

/*Alfabeto de caracteres válidos para utilização na criptografia e seu número de caracteres:*/
#define ALPHABET " !#$%&()*+,-./:;ABCDEFGHIJKLMNOPQRSTUVWXYZ<=>?@|^0123456789[]{}abcdefghijklmnopqrstuvwxyz"
#define ALPHABET_SIZE 89 //número primo para evitar conflito nos cálculos de módulo.

/* ---- Protótipos das funções ---- */
/**Valida se "pass[]" possui número de caracteres de PASS_MIN à PASS_MAX e se possui apenas caracteres do ALPHABET.
Retorna: 0[senha não válida]; 1[válida]*/
int validPass(const char pass[]);

/**Criptografa "text[]" com a senha "pass[]", utilizando a cifra de vigenere.*/
void encrypt(char text[], const char pass[]);

/**Descriptografa "text[]" com a senha "pass[]", utilizando a cifra de vigenere.*/
void decrypt(char text[], const char pass[]);

/**Testa se "text[]" está criptografado.
Retorna: 0[não é criptografado]; 1[é criptografado].*/
int testCripto(const char text[]);

/* ---- Main exemplo ---- */
/*int main()
{
    ////// VARIÁVEIS: CRIPTO //////
    int isTextCripto, isFileCripto;
    char pass[PASS_MAX];

    return 0;
}*/

#endif /* CRIPTO_H_INCLUDED */
