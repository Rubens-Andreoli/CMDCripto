//#define ALPHABET " !#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]{}"
#define ALPHABET "_abcdefghijklmnopqrstuvwxyz0123456789.?,-"
                //1234567890123456789012345678901234567890123456789012345678901
//#define ALPHABET_SIZE 61
#define ALPHABET_SIZE 41
#define MATRX_ORDER 3
#define MIN_PASS_SIZE 4
#define MAX_PASS_SIZE 9

/**Cria password espelhando este se for menor do que o tanto de digitos necessários.*/
void createPass(char pass[MAX_PASS_SIZE+1]){
    int pos, dec=1, lenght=0;
    do{
        printf("Digite uma senha, [4-9] digitos, para criptografar/descriptografar o texto: ");
        fflush(stdin);
        fgets(pass,MAX_PASS_SIZE+1,stdin);
        strtok(pass, "\n");
        lenght=strlen(pass);
    }while(lenght<MIN_PASS_SIZE || lenght>MAX_PASS_SIZE);
    if (lenght<=MAX_PASS_SIZE && lenght>=MIN_PASS_SIZE){
        for(pos=lenght;MAX_PASS_SIZE-pos>0;pos++){
            pass[pos]=pass[lenght-dec];
            dec++;
        }
    }
    printf("PASS:%s",pass);
}

/**Converte caractere retornando inteiro.*/
int charToInt(char letter){
    int pos;
    for(pos=0;pos<=ALPHABET_SIZE-1;pos++){
        if(letter == ALPHABET[pos]){
            return pos;
        }
    }
    return 0;
}

/**Converte password para matriz 3x3.*/
void passToTable(char pass[MAX_PASS_SIZE+1], int matrix[MATRX_ORDER][MATRX_ORDER]){
    int i, j, x=0;
    for(i=0;i<MATRX_ORDER;i++){
        for(j=0;j<MATRX_ORDER;j++){
            matrix[i][j] = charToInt(pass[x]);
            x++;
        }
    }
    printf("\nMATRIX:\n");
    printf("%d-%d-%d\n",matrix[0][0],matrix[0][1],matrix[0][2]);
    printf("%d-%d-%d\n",matrix[1][0],matrix[1][1],matrix[1][2]);
    printf("%d-%d-%d\n",matrix[2][0],matrix[2][1],matrix[2][2]);

}

/**Calcula o determinante de uma matriz 3x3.*/
int determinant(int matrix[MATRX_ORDER][MATRX_ORDER]){
    int det=((matrix[0][0]*matrix[1][1]*matrix[2][2])
        +(matrix[0][1]*matrix[1][2]*matrix[2][0])
        +(matrix[0][2]*matrix[1][0]*matrix[2][1]))
        -((matrix[2][0]*matrix[1][1]*matrix[0][2])
        +(matrix[2][1]*matrix[1][2]*matrix[0][0])
        +(matrix[2][2]*matrix[1][0]*matrix[0][1]));;
    printf("DET:%d\n",det);
    return det;
}

/**Modifica matriz até esta se tornar inversível.*/
void makeInvertible(int matrix[MATRX_ORDER][MATRX_ORDER]){
    int d = determinant(matrix)%ALPHABET_SIZE;
    while(d==0){
        matrix[0][0]+=10;
    }
}

unsigned int modinv(unsigned int u, unsigned int v){
    unsigned int inv, u1, u3, v1, v3, t1, t3, q;
    int iter;
    /* Step X1. Initialise */
    u1 = 1;
    u3 = u;
    v1 = 0;
    v3 = v;
    /* Remember odd/even iterations */
    iter = 1;
    /* Step X2. Loop while v3 != 0 */
    while (v3 != 0)
    {
        /* Step X3. Divide and "Subtract" */
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        /* Swap */
        u1 = v1; v1 = t1; u3 = v3; v3 = t3;
        iter = -iter;
    }
    /* Make sure u3 = gcd(u,v) == 1 */
    if (u3 != 1)
        return 0;   /* Error: No inverse exists */
    /* Ensure a positive result */
    if (iter < 0)
        inv = v - u1;
    else
        inv = u1;
    return inv;
}

int gcdExtended(int a, int b, int *x, int *y){
    // Base Case
    if (a == 0){
        *x = 0, *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

int modInverse(int a, int m){
    int x, y, res;
    int g = gcdExtended(a, m, &x, &y);
    if (g != 1){
        //"Inverse doesn't exist";
    }else{
        // m is added to handle negative x
        res = (x%m + m) % m;
        //"Modular multiplicative inverse is " << res;
    }
    return res;

}
/**Cria matriz inversa de uma matriz 3x3.*/
void invert(int matrix[MATRX_ORDER][MATRX_ORDER], int det, int matrixInv[MATRX_ORDER][MATRX_ORDER]){
    printf("MODINV:%d\n",modInverse(det, ALPHABET_SIZE));
    int i, j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            matrixInv[j][i] = (((matrix[(i+1)%3][(j+1)%3]*matrix[(i+2)%3][(j+2)%3]) -
            (matrix[(i+1)%3][(j+2)%3]*matrix[(i+2)%3][(j+1)%3]))*modInverse(det,ALPHABET_SIZE))%ALPHABET_SIZE;
        }
    }
    printf("MATRIX INV:\n");
    printf("%d-%d-%d\n",matrixInv[0][0],matrixInv[0][1],matrixInv[0][2]);
    printf("%d-%d-%d\n",matrixInv[1][0],matrixInv[1][1],matrixInv[1][2]);
    printf("%d-%d-%d\n",matrixInv[2][0],matrixInv[2][1],matrixInv[2][2]);
}

void matrixMult(int matrix[MATRX_ORDER][MATRX_ORDER], int x, int y, int z, int pos, char text[CHAR_MAX]){
    int matrixProd[MATRX_ORDER][1];
    matrixProd[0][0] = ((matrix[0][0]*x)+(matrix[0][1]*y)+(matrix[0][2]*z));
    matrixProd[1][0] = ((matrix[1][0]*x)+(matrix[1][1]*y)+(matrix[1][2]*z));
    matrixProd[2][0] = ((matrix[2][0]*x)+(matrix[2][1]*y)+(matrix[2][2]*z));
    text[pos] = ALPHABET[matrixProd[0][0]%ALPHABET_SIZE];
    text[pos+1] = ALPHABET[matrixProd[1][0]%ALPHABET_SIZE];
    text[pos+2] = ALPHABET[matrixProd[2][0]%ALPHABET_SIZE];
}

void crypt(char text[CHAR_MAX], int charTotal, int matrix[MATRX_ORDER][MATRX_ORDER]){
    int i, charPos=0;
    for(i=1;i<=charTotal/3;i++){
        matrixMult(matrix, charToInt(text[charPos]), charToInt(text[charPos+1]), charToInt(text[charPos+2]), charPos, text);
        charPos+=3;
    }
    if(charTotal%3 == 2)
        matrixMult(matrix, charToInt(text[charTotal-2]), charToInt(text[charTotal-1]), 0, charTotal-2, text);
    if(charTotal%3 == 1)
        matrixMult(matrix, charToInt(text[charTotal-1]), 0, 0, charTotal-1, text);
}
