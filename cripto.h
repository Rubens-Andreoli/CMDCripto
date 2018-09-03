#define ALPHABET " !#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]-{}"
#define TABLE_ORDER 3
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

/**Converte caracteres retornando inteiros de acordo com a tabela ASCII adaptada.*/
int charToInt(char letter){
    char letters[41]="_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.?,-";
    int pos;
    for(pos=0;pos<=40;pos++){
        if(toupper(letter) == letters[pos]){
            return pos;
        }
    }
    return -1;
    /*int letterValue = letter, isConverted=0;
    if(letterValue >= 32 && letterValue <= 59){ //0-27
       letterValue-=32;
       isConverted=1;
    }
    if(letterValue == 61){ //28
        letterValue-=33;
        isConverted=1;
    }
    if(letterValue >= 63 && letterValue <= 122){ //29-88
        letterValue-=34;
        isConverted=1;
    }
    return isConverted==1?letterValue:-1;*/
}

/**Converte inteiros retornando caracteres de acordo com a tabela ASCII adaptada.*/
char intToChar(int number){
    char letters[41]="_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.?,-";
    return letters[number];
    /*if(number>=0 && number<=27)
        return number+32;
    if(number==28)
        return number+33;
    if(number>=29 && number<=88)
        return number+34;*/
}

/**Converte password para matriz 3x3.*/
void passToTable(char pass[MAX_PASS_SIZE+1], int table[TABLE_ORDER][TABLE_ORDER]){
    int i;
    for(i=0;i<TABLE_ORDER;i++){
        table[0][i] = charToInt(pass[i]);
        table[1][i] = charToInt(pass[i+3]);
        table[2][i] = charToInt(pass[i+6]);
    }
    /*printf("PASS TO TABLE:\n");
    printf("%d-%d-%d\n", table[0][0], table[0][1], table[0][2]);
    printf("%d-%d-%d\n", table[1][0], table[1][1], table[1][2]);
    printf("%d-%d-%d\n", table[2][0], table[2][1], table[2][2]);*/
}

/**Calcula o determinante de uma matriz 3x3.*/
int determinant(int table[TABLE_ORDER][TABLE_ORDER]){
    double det=((table[0][0]*table[1][1]*table[2][2])
        +(table[0][1]*table[1][2]*table[2][0])
        +(table[0][2]*table[1][0]*table[2][1]))
        -((table[2][0]*table[1][1]*table[0][2])
        +(table[2][1]*table[1][2]*table[0][0])
        +(table[2][2]*table[1][0]*table[0][1]));
    return det;
}

/**Modifica matriz até esta se tornar inversível.*/
void makeInvertible(int table[TABLE_ORDER][TABLE_ORDER]){
    while(determinant(table)==0){
        table[2][2]+=1;
    }
}

/**Cria matriz inversa de uma matriz 3x3.*/
void invert(int table[TABLE_ORDER][TABLE_ORDER], double det, double tableInv[TABLE_ORDER][TABLE_ORDER]){
    int i, j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            tableInv[j][i] = ((table[(i+1)%3][(j+1)%3]*table[(i+2)%3][(j+2)%3]) -
            (table[(i+1)%3][(j+2)%3]*table[(i+2)%3][(j+1)%3]))/det;
        }
    }
    printf("TABLE INV:\n");
    printf("%f-%f-%f\n",tableInv[0][0],tableInv[0][1],tableInv[0][2]);
    printf("%f-%f-%f\n",tableInv[1][0],tableInv[1][1],tableInv[1][2]);
    printf("%f-%f-%f\n",tableInv[2][0],tableInv[2][1],tableInv[2][2]);
}

void matrixMult(int table[TABLE_ORDER][TABLE_ORDER], int x, int y, int z, int pos, int line, char text[LINE_MAX][CHAR_MAX]){
    int cripTable[3][3];
    cripTable[0][0] = ((table[0][0]*x)+(table[0][1]*y)+(table[0][2]*z))%89;
    cripTable[1][0] = ((table[1][0]*x)+(table[1][1]*y)+(table[1][2]*z))%89;
    cripTable[2][0] = ((table[2][0]*x)+(table[2][1]*y)+(table[2][2]*z))%89;
    text[line][pos] = intToChar(cripTable[0][0]);
    if(y!=0)
        text[line][pos+1] = intToChar(cripTable[1][0]);
    if(z!=0)
        text[line][pos+2] = intToChar(cripTable[2][0]);
}

void encrypt(char text[LINE_MAX][CHAR_MAX], int lineTotal, int table[TABLE_ORDER][TABLE_ORDER]){
    printf("TEXT TO MATRIX:\n");
    int line = 0;
    int i, charPos=0, charTotal = strlen(text[line]);
    for(i=1;i<=charTotal/3;i++){
        printf("%c-%c-%c\n",text[line][charPos],text[line][charPos+1],text[line][charPos+2]);
        printf("%d-%d-%d\n",charToInt(text[line][charPos]),charToInt(text[line][charPos+1]),charToInt(text[line][charPos+2]));
        matrixMult(table, charToInt(text[line][charPos]), charToInt(text[line][charPos+1]), charToInt(text[line][charPos+2]), charPos, line, text);
        charPos+=3;
    }
    if(charTotal%3 == 2){
        printf("%d-%d\n",charToInt(text[line][charTotal-2]),charToInt(text[line][charTotal-1]));
        matrixMult(table, charToInt(text[line][charTotal-2]), charToInt(text[line][charTotal-1]), 0, charPos, line, text);
    }
    if(charTotal%3 == 1){
        printf("%d\n",charToInt(text[line][charTotal-1]));
        matrixMult(table, charToInt(text[line][charTotal-1]), 0, 0, charPos, line, text);
    }
}

void invMatrixMult(double tableInv[TABLE_ORDER][TABLE_ORDER], int x, int y, int z, int pos, int line, char text[LINE_MAX][CHAR_MAX]){
    int cripTable[3][3];
    cripTable[0][0] = abs((tableInv[0][0]*x)+(tableInv[0][1]*y)+(tableInv[0][2]*z));
    cripTable[1][0] = abs((tableInv[1][0]*x)+(tableInv[1][1]*y)+(tableInv[1][2]*z));
    cripTable[2][0] = abs((tableInv[2][0]*x)+(tableInv[2][1]*y)+(tableInv[2][2]*z));
    text[line][pos] = intToChar(cripTable[0][0]);
    if(y!=0)
        text[line][pos+1] = intToChar(cripTable[1][0]);
    if(z!=0)
        text[line][pos+2] = intToChar(cripTable[2][0]);
}

void decrypt(char text[LINE_MAX][CHAR_MAX], int lineTotal, double tableInv[TABLE_ORDER][TABLE_ORDER]){
    int line;
    for(line=0;line<=lineTotal;line++){
        int i, charPos=0, charTotal = strlen(text[line]);
        for(i=1;i<=charTotal/3;i++){
            invMatrixMult(tableInv, charToInt(text[line][charPos]), charToInt(text[line][charPos+1]), charToInt(text[line][charPos+2]), charPos, line, text);
            charPos+=3;
        }
        if(charTotal%3 == 2)
            invMatrixMult(tableInv, charToInt(text[line][charTotal-2]), charToInt(text[line][charTotal-1]), 0, charPos, line, text);
        if(charTotal%3 == 1)
            invMatrixMult(tableInv, charToInt(text[line][charTotal-1]), 0, 0, charPos, line, text);
    }
}
