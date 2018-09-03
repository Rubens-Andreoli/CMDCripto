//#define ALPHABET " !#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]{}"
#define ALPHABET "_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.?,-"
                //1234567890123456789012345678901234567890123456789012345678901
#define ALPHABET_SIZE 61
#define MATRX_ORDER 3
#define MIN_PASS_SIZE 5
#define MAX_PASS_SIZE 9

/**Cria password espelhando este se for menor do que o tanto de digitos necessários.*/
void createPass(char pass[MAX_PASS_SIZE+1]){
    int pos, dec=1, lenght=0;
    do{
        printf("Digite uma senha, [4-9] digitos, para criptografar/descriptografar o texto: ");
        fflush(stdin);
        fgets(pass,MAX_PASS_SIZE,stdin);
        strtok(pass, "\n");
        lenght=strlen(pass);
    }while(lenght<MIN_PASS_SIZE || lenght>MAX_PASS_SIZE);
    if (lenght<=MAX_PASS_SIZE && lenght>=MIN_PASS_SIZE){
        for(pos=lenght;MAX_PASS_SIZE-pos>0;pos++){
            pass[pos]=pass[lenght-dec];
            dec++;
        }
    }
}

/**Converte caractere retornando inteiro.*/
int charToInt(char letter){
    int pos;
    for(pos=0;pos<=ALPHABET_SIZE-1;pos++){
        if(toupper(letter) == ALPHABET[pos]){
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
    printf("MATRIX:\n");
    printf("%d-%d-%d\n",matrix[0][0],matrix[0][1],matrix[0][2]);
    printf("%d-%d-%d\n",matrix[1][0],matrix[1][1],matrix[1][2]);
    printf("%d-%d-%d\n",matrix[2][0],matrix[2][1],matrix[2][2]);
    //printf("DETPASS:%d\n",determinant(matrix));

}

/**Calcula o determinante de uma matriz 3x3.*/
int determinant(int matrix[MATRX_ORDER][MATRX_ORDER]){
    int det=((matrix[0][0]*matrix[1][1]*matrix[2][2])
        +(matrix[0][1]*matrix[1][2]*matrix[2][0])
        +(matrix[0][2]*matrix[1][0]*matrix[2][1]))
        -((matrix[2][0]*matrix[1][1]*matrix[0][2])
        +(matrix[2][1]*matrix[1][2]*matrix[0][0])
        +(matrix[2][2]*matrix[1][0]*matrix[0][1]));
    //printf("DET:%d\n",det);
    return det;
}

/**Modifica matriz até esta se tornar inversível.*/
void makeInvertible(int matrix[MATRX_ORDER][MATRX_ORDER]){
    while(determinant(matrix)==0){
        matrix[2][2]+=1;
    }
}

int modInverse(int det, int m) {
    int x;
    det %= m;
    for(x = 1; x < m; x++) {
        if((det*x) % m == 1) return x;
    }
}

/**Cria matriz inversa de uma matriz 3x3.*/
void invert(int matrix[MATRX_ORDER][MATRX_ORDER], int det, int matrixInv[MATRX_ORDER][MATRX_ORDER]){
    printf("DET:%d\n",det);
    printf("MODINV:%d\n",modInverse(abs(det), 41));
    int i, j;
    for(i=0;i<MATRX_ORDER;i++){
        for(j=0;j<MATRX_ORDER;j++){
            matrixInv[j][i] = (matrix[j][i]*modInverse(abs(det), 41));
            if(i+j == MATRX_ORDER-1){
                matrixInv[j][i]*=-1;
            }
            while(matrixInv[j][i] > 41){
                matrixInv[j][i]-=41;
            }
            while(matrixInv[j][i] < 0){
                matrixInv[j][i]+=41;
            }
        }
    }


    /*int i, j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            matrixInv[j][i] = (((matrix[(i+1)%3][(j+1)%3]*matrix[(i+2)%3][(j+2)%3]) -
            (matrix[(i+1)%3][(j+2)%3]*matrix[(i+2)%3][(j+1)%3]))*modInverse(det,41));
        }
    }*/
    printf("TABLE INV:\n");
    printf("%d-%d-%d\n",matrixInv[0][0],matrixInv[0][1],matrixInv[0][2]);
    printf("%d-%d-%d\n",matrixInv[1][0],matrixInv[1][1],matrixInv[1][2]);
    printf("%d-%d-%d\n",matrixInv[2][0],matrixInv[2][1],matrixInv[2][2]);
}

void matrixMult(int matrix[MATRX_ORDER][MATRX_ORDER], int x, int y, int z, int pos, int line, char text[LINE_MAX][CHAR_MAX]){
    int matrixProd[3][1];
    matrixProd[0][0] = ((matrix[0][0]*x)+(matrix[0][1]*y)+(matrix[0][2]*z))%41;
    matrixProd[1][0] = ((matrix[1][0]*x)+(matrix[1][1]*y)+(matrix[1][2]*z))%41;
    matrixProd[2][0] = ((matrix[2][0]*x)+(matrix[2][1]*y)+(matrix[2][2]*z))%41;
    text[line][pos] = ALPHABET[matrixProd[0][0]];
    text[line][pos+1] = ALPHABET[matrixProd[1][0]];
    text[line][pos+2] = ALPHABET[matrixProd[2][0]];
}

void crypt(char text[LINE_MAX][CHAR_MAX], int lineTotal, int matrix[MATRX_ORDER][MATRX_ORDER]){
    int line;
    for(line=0;line<=lineTotal;line++){
        int i, charPos=0, charTotal = strlen(text[line]);
        for(i=1;i<=charTotal/3;i++){
            matrixMult(matrix, charToInt(text[line][charPos]), charToInt(text[line][charPos+1]), charToInt(text[line][charPos+2]), charPos, line, text);
            charPos+=3;
        }
        if(charTotal%3 == 2)
            matrixMult(matrix, charToInt(text[line][charTotal-2]), charToInt(text[line][charTotal-1]), 0, charPos, line, text);
        if(charTotal%3 == 1)
            matrixMult(matrix, charToInt(text[line][charTotal-1]), 0, 0, charPos, line, text);
    }
}
