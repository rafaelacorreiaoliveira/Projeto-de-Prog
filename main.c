#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int row=9, column=9;
char table[15][24];
char pecas[43][3][3] = {
    {{'1','-','-'}, {'-','-','-'}, {'-','-','-'}},
    {{'-','1','-'}, {'-','-','-'}, {'-','-','-'}},
    {{'-','-','1'}, {'-','-','-'}, {'-','-','-'}},
    {{'-','-','-'}, {'1','-','-'}, {'-','-','-'}},
    {{'-','-','-'}, {'-','1','-'}, {'-','-','-'}},
    {{'-','-','-'}, {'-','-','1'}, {'-','-','-'}},
    {{'-','-','-'}, {'-','-','-'}, {'1','-','-'}},
    {{'-','-','-'}, {'-','-','-'}, {'-','1','-'}},
    {{'-','-','-'}, {'-','-','-'}, {'-','-','1'}},
    {{'2','2','-'}, {'-','-','-'}, {'-','-','-'}},
    {{'-','2','2'}, {'-','-','-'}, {'-','-','-'}},
    {{'-','-','-'}, {'2','2','-'}, {'-','-','-'}},
    {{'-','-','-'}, {'-','2','2'}, {'-','-','-'}},
    {{'-','-','-'}, {'-','-','-'}, {'2','2','-'}},
    {{'-','-','-'}, {'-','-','-'}, {'-','2','2'}},
    {{'2','-','-'}, {'2','-','-'}, {'-','-','-'}},
    {{'-','-','-'}, {'2','-','-'}, {'2','-','-'}},
    {{'-','2','-'}, {'-','2','-'}, {'-','-','-'}},
    {{'-','-','-'}, {'-','2','-'}, {'-','2','-'}},
    {{'-','-','2'}, {'-','-','2'}, {'-','-','-'}},
    {{'-','-','-'}, {'-','-','2'}, {'-','-','2'}},
    {{'3','3','3'}, {'-','-','-'}, {'-','-','-'}},
    {{'-','-','-'}, {'3','3','3'}, {'-','-','-'}},
    {{'-','-','-'}, {'-','-','-'}, {'3','3','3'}},
    {{'3','-','-'}, {'3','-','-'}, {'3','-','-'}},
    {{'-','3','-'}, {'-','3','-'}, {'-','3','-'}},
    {{'-','-','3'}, {'-','-','3'}, {'-','-','3'}},
    {{'4','4','-'}, {'4','4','-'}, {'-','-','-'}},
    {{'-','4','4'}, {'-','4','4'}, {'-','-','-'}},
    {{'-','-','-'}, {'4','4','-'}, {'4','4','-'}},
    {{'-','-','-'}, {'-','4','4'}, {'-','4','4'}},
    {{'5','5','5'}, {'-','5','-'}, {'-','5','-'}},
    {{'5','-','-'}, {'5','5','5'}, {'5','-','-'}},
    {{'-','5','-'}, {'-','5','-'}, {'5','5','5'}},
    {{'-','-','5'}, {'5','5','5'}, {'-','-','5'}},
    {{'-','6','-'}, {'6','-','6'}, {'6','6','6'}},
    {{'-','6','6'}, {'6','-','6'}, {'-','6','6'}},
    {{'6','6','6'}, {'6','-','6'}, {'-','6','-'}},
    {{'-','6','-'}, {'6','-','6'}, {'6','6','6'}},
    {{'7','-','7'}, {'7','7','7'}, {'7','-','7'}},
    {{'7','7','7'}, {'-','7','-'}, {'7','7','7'}},
    {{'8','8','8'}, {'8','-','8'}, {'8','8','8'}},
    {{'-','-','-'}, {'-','-','-'}, {'-','-','-'}},
};

void menu(void) {
    //escolher tamanho
    do {
        printf("\n\n\t|Enter the size of your desired playing field|\n\n --> Must be in multiples of three. Rows (9-15) x Columns (9-24): ");
        if(scanf("%i %i", &row, &column) != 2) {
            printf("\n\tINVALID INPUT - TRY AGAIN");
            scanf("%*s");
        }
        system("clear");
    } while((row < 9 || column < 9) || (row > 15 || column > 24) || ((row % 3) != 0) || ((column % 3) != 0));

}

void InicializacaoBoard() {

    int i, i2;
    char letters[] = "ABCDEFGHIJKLMNOQPRSTUVWX";

    //inicializar a matriz toda a '-'
    for(i=0; i<row; i++)
        for(i2=0; i2<column; i2++)
            table [i] [i2] = '-';

    //display da matriz na consola + column of numbers
    int num = row;
    for (i = 0; i < row; i++) {
        if(num<10)
            printf("  %i", num);
        else
            printf(" %i", num);

        for (i2 = 0; i2 < column; i2++) {
            printf(" %c", table [i][i2]);
        }
        num--;
    printf("\n");
    }

    //bottom row of letters
    printf("   ");
    for(i=0; i<column; i++) {
        printf(" %c ", letters[i]);
    }
    printf("\n");

}

void printBoard() {

    system("clear");
    int i, i2;
    char letters[] = "ABCDEFGHIJKLMNOQPRSTUVWX";

    //display da matriz na consola + column of numbers
    int num = row;
    for (i = 0; i < row; i++) {
        if(num<10)
            printf("  %i", num);
        else
            printf(" %i", num);

        for (i2 = 0; i2 < column; i2++) {
            printf(" %c", table [i][i2]);
        }
        num--;
    printf("\n");
    }

    //bottom row of letters
    printf("   ");
    for(i=0; i<column; i++) {
        printf(" %c", letters[i]);
    }
    printf("\n");
}

/* int rest_4() {
    while(((row*column)/9 ) {

    }
    int i1, i2, for3, for4, flag=0;
    time_t t;
    srand((unsigned) time(&t));

    do {
        i1 = rand() % row;
        i2 = rand() % column;
    }while((i1%3 != 0) || (i2%3 != 0));

    //Matriz 3x3 específica
    for(for3=0; for3<3; for3++) {
        for(for4=0; for4<3; for4++) {

            table[for3+i1*3][for4+i2*3] = '-';

        }
    }
    return flag;
} */

int restricao_1(for1, for2) {

    int i1, flag = 0;
    char check1, check2, check3, check4;

    /* for1 - percorre matriz global de 3 em 3 linhas
       for2 - percorre matriz global de 3 em 3 colunas */

    // if - Verifica as primeiras 3 linhas e todas as colunas a partir da 3º
    if((for1==0) && (for2>0)) {
        for(i1=0; i1<3; i1++) {
            /* check1 - 1º coluna da matriz 3x3
               check2 - 3º coluna da matriz 3x3 anterior */
            check1 = table[i1][3*for2];
            check2 = table[i1][3*for2 - 1];

                // check3 - 3º coluna da matriz 3x3 anterior, linha superior
                if((i1-1) >= 0) {
                    check3 = table[i1 - 1][3*for2 - 1]; }
                else {
                    check3 = '-'; }

            // check4 - 3º coluna da matriz 3x3 anterior, linha inferior
            check4 = table[i1 + 1][3*for2 - 1];

            // condições de peça inválida
            if(check1 != '-' && check2 != '-')
                flag = 1;
            if(check1 != '-' && check3 != '-')
                flag = 1;
            if(check1 != '-' && check4 != '-')
                flag = 1;
        }
    }

    // if - Verifica primeiras 3 colunas depois das primeiras 3 linhas
    if((for1>0) && (for2 == 0)) {
        for(i1=0; i1<3; i1++) {
            /* check1 - 1º linha da matriz 3x3
               check2 - 3º linha da matriz 3x3 anterior */
            check1 = table[for1*3][i1];
            check2 = table[for1*3 - 1][i1];

            // check3 - linha superior, um bloco á esquerda
            if((i1-1) >= 0) {
                check3 = table[for1*3 - 1][i1-1]; }
            else {
                check3 = '-'; }

            // check4 - linha superior, uma bloco á direita
            check4 = table[for1*3 - 1][i1+1];

            // condições de peça inválida
            if(check1 != '-' && check2 != '-')
                flag = 1;
            if(check1 != '-' && check3 != '-')
                flag = 1;
            if(check1 != '-' && check1 != '-')
                flag = 1;
        }
    }

    // if - Verifica o resto do tabuleiro.
    if((for1>0) && for2>0) {
        for(i1=0; i1<3; i1++) {
            /*  Verificação das 4 casas da coluna anterior
                check1 - 1º coluna da matriz 3x3
                check2 - 3º coluna da matriz 3x3 anterior */
            check1 = table[i1 + for1*3][for2*3];
            check2 = table[i1 + for1*3][for2*3 - 1];

            // check3 - 3º coluna da matriz 3x3 anterior, linha superior
            check3 = table[i1 + for1*3 - 1][for2*3 - 1];

            // check4 - 3º coluna da matriz 3x3 anterior, linha inferior
            if((for1*3 + i1) != (row + 2)) {
                check4 = table[i1 + for1*3 + 1][for2*3 - 1]; }
            else {
                check4 = '-'; }

            // condições de peça inválida
            if(check1 != '-' && check2 != '-')
                flag = 1;
            if(check1 != '-' && check3 != '-')
                flag = 1;
            if(check1 != '-' && check4 != '-')
                flag = 1;
        }
        if(flag==0) {
            for(i1=0; i1<3; i1++) {
                /*  Verificação das 5 casas da linha superior
                    check1 - 1º linha da matriz 3x3
                    check2 - 3º linha da matriz 3x3 anterior */
                check1 = table[for1*3][i1 + for2*3];
                check2 = table[for1*3 - 1][i1 + for2*3];

                //check3 - linha superior, um bloco á direita
                if((for2*3 + i1) != (column + 2)) {
                    check3 = table[for1*3 - 1][for2*3 + i1 + 1]; }
                else {
                    check3 = '-'; }

                //check4 - linha superior, um bloca á esquerda
                check4 = table[for1*3 - 1][for2*3 + i1 - 1];

            // condições de peça inválida
            if(check1 != '-' && check2 != '-')
                flag = 1;
            if(check1 != '-' && check3 != '-')
                flag = 1;
            if(check1 != '-' && check4 != '-')
                flag = 1;
            }
        }
    }

    return flag;
}


void pecas_() {

    /* for1 - percorre matriz global de 3 em 3 linhas.
       for2 - percorre matriz global de 3 em 3 colunas.
       for3 - percorre natriz específica 3x3 por linhas.
       for4 - percorre matriz específica 3x3 por colunas. */
    int for1, for2, for3, for4;
    char value;
    time_t t;
    srand((unsigned) time(&t));

    //Percorre a matriz em blocos 3x3
    for(for1=0; for1 < row/3; for1++) {
        for(for2=0; for2 < column/3; for2++) {


            //Matriz 3x3 específica
            do {
                // Randomização da peça
                int i1 = rand() % 43;

                for(for3=0; for3<3; for3++) {
                    for(for4=0; for4<3; for4++) {

                        value = pecas[i1][for3][for4];
                        table[for3+for1*3][for4+for2*3] = value;

                    }
                }

                restricao_1(for1, for2);
            }while(restricao_1(for1,for2));
        }
    }

    /*do {
        rest_4(for1, for2);
    }while(rest_4(for1, for2)); */

}


int main() {
    menu();
    InicializacaoBoard();
    pecas_();
    printBoard();
    return EXIT_SUCCESS;
}
