#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int row=9, column=9;
int tipo [9] = {0,0,0,0,0,0,0,0,0};
// DECLAREI PEÇA COMO GLOBAL PQ NAO SABIA COMO CONTORNAR O PROBLEMA DA RESTRIÇÃO 3, MUDAR SE POSSÍVEL
int peca;
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

/**
 *  Nome: menu
 *  Objetivo: obter a partir do utilizador o tamanho do tabuleiro a ser utilizado
 *
 *  Parametros de entrada: n/a
 *  Parametros de saida: n/a
 */

void menu() {
    do {
        printf("\n\n\t|Insira o tamanho do campo de jogo desejado|\n\n --> Input deverá ser múltiplo de 3. Linhas (9-15) x Colunas (9-24): ");
        if(scanf("%i %i", &row, &column) != 2) {
            printf("\n\tInválido, tente novamente.");
            scanf("%*c");
        }
        system("clear");
    } while((row < 9 || column < 9) || (row > 15 || column > 24) || ((row % 3) != 0) || ((column % 3) != 0));
}

/**
 *  Nome: pos
 *  Objetivo: obter a partir do utilizador o tipo de posicionamento de peças
 *
 *  Parametros de entrada: n/a
 *  Parametros de saida: modo_pecas
 */

int pos() {

    int modo_pecas=0;

    do {
        printf("\n\n\t|Modos de posicionamento de peças|\n\n\t1. Aleatório.\n\t2. Escolha \n\n\tEscolha: ");
        if(scanf("%i", &modo_pecas) != 1) {
            printf("\n\tInválido, tente novamente.");
            scanf("%*s");
        }
        system("clear");

    } while(modo_pecas < 1 || modo_pecas > 2);

    return modo_pecas;
}

/**
 *  Nome: printBoard
 *  Objetivo: representar no ecrã valores previamente carregados no tabuleiro
 *
 *  Parametros de entrada: n/a
 *  Parametros de saida: n/a
 */

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

/**
 *  Nome: restricao_1
 *  Objetivo: implementar a restrição 1 relativamente á disposição das peças
 *
 *  Parametros de entrada: for1, for2, modo_pecas
 *  Paremetros de saida: n/a
 */

int restricao_1(for1, for2, modo_pecas) {

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

    if (flag == 1 && modo_pecas == 2)
        tipo[peca]++;

    return flag;
}

/**
 *  Nome: escolha_pecas
 *  Objetivo: obter a partir do utilizador as peças a introduzir no tabuleiro
 *
 *  Parametros de entrada: n/a
 *  Paremetros de saida:
 */

void escolha_pecas() {

    int i1, controlo=0, soma=0;

    do {
        printf("\n - Insira o número de peças desejado por ordem de tamanho (1,2,3,4,5,6,7,8): \n\n --> ");
        for(i1=1; i1<9; i1++) {
            if(scanf("%i", &tipo[i1]) != 1){
                printf("\n\tInválido, tente novamente.");
                scanf("%*s");
                soma = 0;
                break;
            }
            soma += tipo[i1];
        }
        system("clear");

        // Verifica se alguma peça de tipo superior têm mais repetições que a anterior
        if(tipo[1] < tipo[2])
            controlo = 1;
        if(tipo[2] < tipo[3])
            controlo = 1;
        if(tipo[3] < tipo[4])
            controlo = 1;
        if(tipo[5] < tipo[6])
            controlo = 1;
        if(tipo[6] < tipo[7])
            controlo = 1;
        if(tipo[7] < tipo[8])
            controlo = 1;

        // Espaços a preencher com matrizes vazias
        tipo[0] = (row*column)/9-tipo[1]-tipo[2]-tipo[3]-tipo[4]-tipo[5]-tipo[6]-tipo[7]-tipo[8];

    } while((controlo != 0) && (soma < (row*column)/18));
}

/**
 *  Nome: restricao_3
 *  Objetivo: implementar a restrição 3 relativamente á disposição das peças
 *
 *  Parametros de entrada: a, modo_pecas
 *  Paremetros de saida: n/a
 */

int restricao_3(a, modo_pecas) {

    int peca;
    srand(time(NULL));

    peca = rand() % 9;

    if (peca == 0) {
        a = 42;
        tipo[peca]--;
    }
    else if (peca == 1) {
        a = rand() % 8;
        tipo[peca]--;
    }
    else if (peca == 2) {
        a = rand() % 12 + 8;
        tipo[peca]--;
    }
    else if (peca == 3) {
        a = rand() % 6 + 20;
        tipo[peca]--;
    }
    else if (peca == 4) {
        a = rand() % 4 + 26;
        tipo[peca]--;;
    }
    else if (peca == 5) {
        a = rand() % 4 + 30;
        tipo[peca]--;
    }
    else if (peca == 6) {
        a = rand() % 4 + 34;
        tipo[peca]--;
    }
    else if (peca == 7) {
        a = rand() % 2 + 38;
        tipo[peca]--;
    }
    else if (peca == 8) {
        a = 41;
        tipo[peca]--;
    }

    return a;
}


/**
 *  Nome: modo
 *  Objetivo: correr o programa de acordo com o modo selecionado
 *
 *  Parametros de entrada: n/a
 *  Paremetros de saida: n/a
 */

void modo() {

    /* for1 - percorre matriz global de 3 em 3 linhas.
       for2 - percorre matriz global de 3 em 3 colunas.
       for3 - percorre natriz específica 3x3 por linhas.
       for4 - percorre matriz específica 3x3 por colunas. */
    int for1, for2, for3, for4, a;
    char value;
    time_t t;
    srand((unsigned) time(&t));

    // Retira o modo de posicionamento de peças
    int modo_pecas = pos();

    //Percorre a matriz em blocos 3x3
    for(for1=0; for1 < row/3; for1++) {
        for(for2=0; for2 < column/3; for2++) {

            // Modo p2
            if(modo_pecas == 2)
                escolha_pecas();

            //Matriz 3x3 específica
            do {

                // Modo p1
                if (modo_pecas == 1)
                    a = rand() % 43;

                // Modo p2
                if(modo_pecas == 2)
                    a = restricao_3();

                for(for3=0; for3<3; for3++) {
                    for(for4=0; for4<3; for4++) {

                        value = pecas[a][for3][for4];
                        table[for3+for1*3][for4+for2*3] = value;

                    }
                }

                restricao_1(for1, for2);
            }while(restricao_1(for1,for2));
        }
    }
}

/**
 *  Nome: main
 *  Objetivo: chamar outras funções, completar o programa
 *
 *  Parametros de entrada: n/a
 *  Paremetros de saida: n/a
 */

int main() {

    menu();
    modo();
    printBoard();
    return EXIT_SUCCESS;
}
