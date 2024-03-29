#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

//VARIÁVEIS GLOBAIS, variáveis essenciais chamadas várias vezes ao longo do programa.
int row=9, column=9; //variáveis que representam o tamanho do tabuleiro, valor inicial igual a 9 devido à dimensão mínima do tabuleiro.
int tipo[9] = {0,0,0,0,0,0,0,0,0}; //array que representa as peças, cada posição representa uma peça.
int tipo_copy[9] = {0,0,0,0,0,0,0,0,0}; //copia completa do array 'tipo', necessário visto da moda que implementamos certos modos.
// sequencia representa a ordem dos disparos; indicador_l e indicador_c apontam para a linha e coluna do tabuleiro no modo j2; incrementa ajuda na implementação da restrição no modo jogo 2 (disparo 2 e 3)
int sequencia = 0, indicador_l = 0, indicador_c = 0, incrementa = 0;
// peca indica o tipo peça (no vetor tipo); conta_pecas guarda o número de carácteres não nulos (' ' ou '-') de uma matriz.
int peca = 0, conta_pecas = 0;
char table[1][15][24] = {{{' '}}};
char pecas[43][3][3] = { //array que representa todas as posições possiveis das peças
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

void menu_ajuda();

/**
 *  Nome: printBoard
 *  Objetivo: representar no ecrã valores previamente carregados no tabuleiro dedicado ao correto modo de jogo
 */

void printBoard(int modo_pecas, int jogo) {
    int i1, i2, modo=0;
    char letters[] = "ABCDEFGHIJKLMNOQPRSTUVWX";

    //display da matriz na consola + column of numbers
    int num = row;

    printf("\n %ix%i", row, column);
    for(i1=1; i1<9; i1++) {
        printf(" %i", tipo[i1]);
    }

    printf("\n\n");

    // modo de jogo j0, j1 ou j2
    if(jogo == 1 || jogo == 2)
        modo=1;
    for (i1 = 0; i1 < row; i1++) {
        if(num<10)
            printf("  %i", num);
        else
            printf(" %i", num);

        for (i2 = 0; i2 < column; i2++) {
            printf(" %c", table[modo][i1][i2]);
        }
        num--;
        printf("\n");
    }

    // letras no final do tabuleiro
    printf("   ");
    for(i1=0; i1<column; i1++) {
        printf(" %c", letters[i1]);
    }
}

/**
 *  Nome: restricao_1
 *  Objetivo: implementar a restrição 1 relativamente á disposição das peças
 */

int restricao_1(int for1, int for2, int modo_pecas, int contador1) {

    int i1, flag = 0;
    char check1, check2, check3, check4;

    /* for1 - percorre matriz global de 3 em 3 linhas
       for2 - percorre matriz global de 3 em 3 colunas */

    // if - Verifica as primeiras 3 linhas e todas as colunas a partir da 3º
    if((for1==0) && (for2>0)) {
        for(i1=0; i1<3; i1++) {
            /* check1 - 1º coluna da matriz 3x3
               check2 - 3º coluna da matriz 3x3 anterior */
            check1 = table[0][i1][3*for2];
            check2 = table[0][i1][3*for2 - 1];

                // check3 - 3º coluna da matriz 3x3 anterior, linha superior
                if((i1-1) >= 0) {
                    check3 = table[0][i1 - 1][3*for2 - 1]; }
                else {
                    check3 = '-'; }

            // check4 - 3º coluna da matriz 3x3 anterior, linha inferior
            check4 = table[0][i1 + 1][3*for2 - 1];

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
            check1 = table[0][for1*3][i1];
            check2 = table[0][for1*3 - 1][i1];

            // check3 - linha superior, um bloco á esquerda
            if((i1-1) >= 0) {
                check3 = table[0][for1*3 - 1][i1-1]; }
            else {
                check3 = '-'; }

            // check4 - linha superior, uma bloco á direita
            check4 = table[0][for1*3 - 1][i1+1];

            // condições de peça inválida
            if(check1 != '-' && check2 != '-')
                flag = 1;
            if(check1 != '-' && check3 != '-')
                flag = 1;
            if(check1 != '-' && check1 != '-')
                flag = 1;
        }
    }

    // if - Verifica o resto do tabuleiro
    if((for1>0) && for2>0) {
        for(i1=0; i1<3; i1++) {
            /*  Verificação das 4 casas da coluna anterior
                check1 - 1º coluna da matriz 3x3
                check2 - 3º coluna da matriz 3x3 anterior */
            check1 = table[0][i1 + for1*3][for2*3];
            check2 = table[0][i1 + for1*3][for2*3 - 1];

            // check3 - 3º coluna da matriz 3x3 anterior, linha superior
            check3 = table[0][i1 + for1*3 - 1][for2*3 - 1];

            // check4 - 3º coluna da matriz 3x3 anterior, linha inferior
            if((for1*3 + i1) != (row - 1)) {
                check4 = table[0][i1 + for1*3 + 1][for2*3 - 1]; }
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
                check1 = table[0][for1*3][i1 + for2*3];
                check2 = table[0][for1*3 - 1][i1 + for2*3];

                //check3 - linha superior, um bloco á direita
                if((for2*3 + i1) != (column - 1)) {
                    check3 = table[0][for1*3 - 1][for2*3 + i1 + 1]; }
                else {
                    check3 = '-'; }

                //check4 - linha superior, um bloca á esquerda
                check4 = table[0][for1*3 - 1][for2*3 + i1 - 1];

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

    // caso a peça nao seja colocável, no modo de posicionamento 1, volta a subtrair o valor da peça no array
    if (flag == 1 && modo_pecas == 1)
        tipo[contador1]--;

    // caso a peça nao seja colocável, no modo de posicionamento 2, volta a adicionar o valor da peça no array
    if (flag == 1 && modo_pecas == 2)
        tipo_copy[peca]++;

    return flag;
}

/**
 *  Nome: rand_pecas
 *  Objetivo: randomização da variante de uma peça, utilizada no modo de posicionamento 2
 */

int rand_pecas() {
    int a = 0;
    switch(peca) {
        case 0:
            a = 42;
            break;
        case 1:
            a = rand() % 9;
            break;
        case 2:
            a = rand() % 12 + 9;
            break;
        case 3:
            a = rand() % 6 + 21;
            break;
        case 4:
            a = rand() % 4 + 27;
            break;
        case 5:
            a = rand() % 4 + 31;
            break;
        case 6:
            a = rand() % 4 + 35;
            break;
        case 7:
            a = rand() % 2 + 39;
            break;
        case 8:
            a = 41;
            break; }

    // ao subtrarir do array, conta como se a peça fosse colocada
    tipo_copy[peca]--;

    return a;
}

/**
 *  Nome: contador
 *  Objetivo: Realizar a Restrição 3
 */

int contador(int a) {
    if(a <= 8) {
        tipo[1]++;
        return 1;
    }
    else if (a > 8 && a <= 20) {
        tipo[2]++;
        return 2;
    }
    else if (a > 20 && a <= 26) {
        tipo[3]++;
        return 3;
    }
    else if (a > 26 && a <= 30 ) {
        tipo[4]++;
        return 4;
    }
    else if (a > 30 && a <= 34) {
        tipo[5]++;
        return 5;
    }
    else if (a > 34 && a <= 38) {
        tipo[6]++;
        return 6;
    }
    else if (a > 38 && a <= 40) {
        tipo[7]++;
        return 7;
    }
    else if (a == 41) {
        tipo[8]++;
        return 8;
    }
    return 0;
}

/**
 *  Nome: modo_pos
 *  Objetivo: construir o tabuleiro '0' de acordo com o modo de posicionamento escolhido
 */

int modo_pos(int modo_pecas, int jogo, int disparos, int repeticao) {

    /* for1 - percorre matriz global de 3 em 3 linhas.
       for2 - percorre matriz global de 3 em 3 colunas.
       for3 - percorre natriz específica 3x3 por linhas.
       for4 - percorre matriz específica 3x3 por colunas. */
    int for1, for2, for3, for4;
    int a=0, contador1=0, repeticao2=0;
    peca = 0;

    for (for1=0; for1<9; for1++) {
        tipo_copy[for1] = tipo[for1];
    }

    //Percorre a matriz em blocos 3x3
    for(for1=0; for1 < row/3; for1++) {
        for(for2=0; for2 < column/3; for2++) {
            repeticao2=0;

            //Matriz 3x3 específica (no caso de jogo 2 onde escolhemos o posicionamento, inicializamos a table 0 toda com '-')
            if (jogo == 2) {
                for(for3=0; for3<3; for3++) {
                    for(for4=0; for4<3; for4++) {
                        table[0][for3+for1*3][for4+for2*3] = '-';
                    }
                }
            }
            else {
                do {
                    repeticao2++;
                    // Modo p1
                    if (modo_pecas == 1) {
                        a = rand() % 43;
                        if (repeticao2 % 3 == 0)
                            a = 4; // se ao fim de 3 tentativas não conseguir colocar a peça gerada, cria uma peça 1 no meio da matriz 3x3
                        contador1 = contador(a);
                    }
                    // Modo p2
                    if(modo_pecas == 2) {
                        do {
                            peca = rand() % 9;
                        }while(tipo_copy[peca] == 0);
                        a = rand_pecas();
                    }
                    for(for3=0; for3<3; for3++) {
                        for(for4=0; for4<3; for4++) {
                            table[0][for3+for1*3][for4+for2*3] = pecas[a][for3][for4];
                        }
                    }
                    if (repeticao2 == 8) {
                        tipo_copy[peca]++;
                        return -1;
                    }
                }while(restricao_1(for1, for2, modo_pecas, contador1));
            }
        }
    }
    return 0;
}

/**
 *  Nome: d1_linha e d1_coluna
 *  Objetivo: implementar o modo de disparo 1 do computador (dispara em função das colunas e das linhas)
 */

int d1_linha() {
    int linha = rand() % (row+1);
    return linha;
}
char d1_coluna() {
    char coluna = (rand() % (column)) + 'A';
    return coluna;
}

/**
 *  Nome: disparo_j1
 *  Objetivo: verificar condição de vitória
 */

int disparo_j1(int disparo_linha, char disparo_coluna, int disparos, int jogo) {
    if (disparos == 1 || jogo == 1) {
        if (table[1][row - disparo_linha - 2][disparo_coluna - 17] != '-') {
            conta_pecas --;
            if (conta_pecas == 0)
                return 1;
        }
    }

    if (disparos == 2 || disparos == 3) {
        if (table[1][disparo_linha - 2][disparo_coluna - 17] != '-') {
            conta_pecas --;
            if (conta_pecas == 0)
                return 1;
        }
    }
    return 0;
}

 /**
 *  Nome: modo_j1
 *  Objetivo: implementar o modo de jogo 1 e 2 (todos os modos de disparo incluidos) com as suas devidas restrições
 */

int modo_j1(int disparos, int jogo) {
    //ordem dos disparos (centro, cima, baixo, esquerda, direita e cantos)
    int ordem[9][2][1] = {{{1}, {1}}, {{0}, {1}}, {{2}, {1}}, {{1}, {0}}, {{1}, {2}}, {{0}, {0}}, {{2}, {2}}, {{0}, {2}}, {{2}, {0}}};
    int disparo_linha = 0, vitoria=0, insurance=0;
    char disparo_coluna = '\0';
    time_t t;
    srand((unsigned) time(&t));

    if(jogo == 1) { //Modo de jogo 1
        scanf(" %c %i", &disparo_coluna, &disparo_linha);
        if (disparo_coluna < 'A' || disparo_coluna > ('A' + column)) {
            printf("*Coluna inválida");
            exit(-1);
        }
        if (disparo_linha < 1 || disparo_linha > row) {
            printf("*Linha inválida");
            exit(-1);
        }
        table[1][row - disparo_linha - 2][disparo_coluna - 17] = table[0][row - disparo_linha - 2][disparo_coluna - 17];
        printf("%c\n", table[1][row - disparo_linha - 2][disparo_coluna - 17]);
    }

    else if (jogo == 2) { //Modo de jogo 2
        if (disparos == 1) { //Modo d1
            do {
                disparo_linha = d1_linha();
                disparo_coluna = d1_coluna();
            }while(table[1][row - disparo_linha - 2][disparo_coluna - 17] != ' ');
            printf("%c%i\n", disparo_coluna, disparo_linha); // Display de onde vai acertar
            scanf(" %c", &table[1][row - disparo_linha - 2][disparo_coluna - 17]); // Scan da peça a colocar
            // Casos em que o carácter é valido
            if((table[1][row - disparo_linha - 2][disparo_coluna - 17] >= 49 && table[1][row - disparo_linha - 2][disparo_coluna - 17] <= 56) || (table[1][row - disparo_linha - 2][disparo_coluna - 17] == '-')) {
            }
            else {
                printf("\n*Caracter inválido.");
                exit(-1);
            }
        }
        else if (disparos == 2 || disparos == 3) { //Modo d2 e d3 (d3 é uma evolução do modo d2)
            if(sequencia >= 9) {
                sequencia = 0; // reset do ciclo
                if(indicador_c > (column/3 - 2)) {
                    indicador_c = 0; // volta para as primeiras 3 colunas
                    indicador_l ++; } // desce para as proximas 3 linhas
                else {
                    indicador_c ++; } // passa para as proximas 3 colunas
            }

            // conversão
            disparo_linha = ordem[sequencia][0][0] + (indicador_l*3);
            disparo_coluna = ordem[sequencia][1][0] + (indicador_c*3) + 'A';

            if ((disparos == 3) && (table[0][disparo_linha - 2][disparo_coluna - 17] == '-')) {
                    //printf(" %i %c", disparo_linha - 2, disparo_coluna - 17);
                //  PRIMEIRAS 3 LINHAS 3,5,8asas
                if((indicador_l==0) && (indicador_c>0)) {
                    switch(sequencia) {
                case 3: case 8:
                    if(table[0][disparo_linha - 2][disparo_coluna - 18] != '-') { // Atras
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 3][disparo_coluna - 18] != '-') { // Atras & Cima
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 1][disparo_coluna - 18] != '-') { // Atras & Baixo
                        sequencia++;
                        break; }
                    break;
                case 5:
                    if(table[0][disparo_linha - 2][disparo_coluna - 18] != '-') { // Atras
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 1][disparo_coluna - 18] != '-') { // Atras & Baixo
                        sequencia++;
                        break; }
                    break;
                default:
                    break;
                    }
                }
                // PRIMEIRAS 3 COLUNAS 1,5,7
                else if((indicador_l>0) && (indicador_c == 0)) {
                    switch(sequencia) {
                case 1: case 7:
                    if(table[0][disparo_linha - 3][disparo_coluna - 17] != '-') { // Cima
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 3][disparo_coluna - 16] != '-') { // Cima & Direita
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 3][disparo_coluna - 18] != '-') { // Cima & Esquerda
                        sequencia++;
                        break; }
                    break;
                case 5:
                    if(table[0][disparo_linha - 3][disparo_coluna - 17] != '-') { // Cima
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 3][disparo_coluna - 16] != '-') { // Cima & Direita
                        sequencia++;
                        break; }
                    break;
                default:
                    break;
                    }
                }
                // RESTO DO TABULEIRO 1,3,4,7,8
                else if((indicador_l>0) && indicador_c>0) {
                    switch(sequencia) {
                case 3:
                    if(table[0][disparo_linha - 2][disparo_coluna - 18] != '-') { // Atras
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 3][disparo_coluna - 18] != '-') { // Atras & Cima
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 1][disparo_coluna - 18] != '-') { // Atras & Baixo
                        sequencia++;
                        break; }
                    break;
                case 5:
                    if(table[0][disparo_linha - 2][disparo_coluna - 18] != '-') { // Atras
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 3][disparo_coluna - 18] != '-') { // Atras & Cima
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 1][disparo_coluna - 18] != '-') { // Atras & Baixo
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 3][disparo_coluna - 17] != '-') { // Cima
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 3][disparo_coluna - 16] != '-') { // Cima & Direita
                        sequencia++;
                        break; }
                    break;
                case 1:
                    if(table[0][disparo_linha - 3][disparo_coluna - 17] != '-') { // Cima
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 3][disparo_coluna - 16] != '-') { // Cima & Direita
                        sequencia++;
                        break; }
                    if(table[0][disparo_linha - 3][disparo_coluna - 18] != '-') { // Cima & Esquerda
                        sequencia++;
                        break; }
                    break;
                case 7:
                    if(table[0][disparo_linha - 3][disparo_coluna - 17] != '-') { // Cima
                        sequencia++;
                        break; } // CUIDADO
                    if(table[0][disparo_linha - 3][disparo_coluna - 18] != '-') // Cima & Esquerda
                        sequencia++;
                        break;
                case 8:
                    if(table[0][disparo_linha - 2][disparo_coluna - 18] != '-') { // Atras
                        sequencia++;
                        break;}
                    if(table[0][disparo_linha - 3][disparo_coluna - 18] != '-') { // Atras & Cima
                        sequencia++;
                        break; }
                    break;
                default:
                    break;
                    }
                }
            }

            if (sequencia == 9)
                insurance = 8;

            disparo_linha = ordem[sequencia-insurance][0][0] + (indicador_l*3);
            disparo_coluna = ordem[sequencia-insurance][1][0] + (indicador_c*3) + 'A';
            sequencia++; // passa para o proximo quadrado da sequencia pre-definida

            printf("%c%i\n", disparo_coluna, row-disparo_linha);
            scanf(" %c", &table[1][disparo_linha - 2][disparo_coluna - 17]);
            table[0][disparo_linha - 2][disparo_coluna - 17] = table[1][disparo_linha - 2][disparo_coluna - 17];
            // Casos em que o carácter é valido
            if((table[1][disparo_linha - 2][disparo_coluna - 17] >= 49 && table[1][disparo_linha - 2][disparo_coluna - 17] <= 56) || (table[1][disparo_linha - 2][disparo_coluna - 17] == '-')) {
            }
            else {
                printf("\n*Caracter inválido.");
                exit(-1);
            }

            if (table[1][disparo_linha - 2][disparo_coluna - 17] != '-') {
                char sinal = table[1][disparo_linha - 2][disparo_coluna - 17];
                incrementa++;
                if(incrementa == (sinal - '0')) {
                    incrementa = 0;
                    sequencia = 0;
                    if(indicador_c > (column/3 - 2)) {
                        indicador_c = 0; // volta para as primeiras 3 colunas
                        indicador_l ++; } // desce para as proximas 3 linhas
                    else {
                        indicador_c ++; } // passa para as proximas 3 colunas
                }
            }
        }
    }
    //condição de vitória
    vitoria = disparo_j1(disparo_linha, disparo_coluna, disparos, jogo);
    return vitoria;
}

/**
 *  Nome: modo_jogo
 *  Objetivo: escolher modos de jogo
 */

int modo_jogo(int modo_pecas, int jogo, int disparos) {
    if(jogo == 0)
        printBoard(modo_pecas, jogo);
    if(jogo == 1 || jogo == 2) {
        int i1, i2, vitoria, jogadas = 0;
        // Inicializar o tabuleiro de jogo j1 a ' '
        for(i1 = 0; i1 < row; i1++) {
            for (i2 = 0; i2 < column; i2++) {
                table[1][i1][i2] = ' ';
            }
        }

        if(jogo == 1)
            printf(" * ================================\n* Modo de Jogo 1\n* Insira as Coordenadas de Disparo\n* ================================\n");

        if(jogo == 2)
            printf(" * ================================\n* Modo de Jogo 2\n* Crie um tabuleiro com as características indicadas\n* Responda aos disparos do programa\n* ================================\n");

        // Mostra numero de pecas e tamanho do tabuleiro para ambos os modos
        printf("%ix%i", row, column);
        for(i1=1; i1<9; i1++) {
                printf(" %i", tipo[i1]);
            }
        printf("\n");

        time_t comeco = time(NULL);
        do {
            vitoria = modo_j1(disparos, jogo);
            jogadas++;
            if (vitoria == 0)
                printf("\n");
        }while(vitoria == 0);

        printBoard(modo_pecas, jogo);

        time_t fim = time(NULL);
        int tempo_jogo = fim - comeco;

        printf("\n\n   %i jogadas em %i segundos. \n", jogadas, tempo_jogo);

    }
    return 0;
}

/**
 *  Nome: menu_ajuda
 *  Objetivo: ajuda ao utilizador, diz ao utilizador os argumentos que deve utilizar para conseguir correr o programa
*/

void menu_ajuda() {
    printf("Jogo da Batalha Naval.\n\n");
    printf("Opções de funcionamento: \n");
    printf("-h\t ajuda ao utilizador, mostra as instruções.\n");
    printf("-t\t dimensões do tabuleiro (linha x coluna).\n");
    printf("-j\t modos de jogo.\n");
    printf("-p\t modo de posicionamento de paças pelo computador (1 a 2)\n");
    printf("-d\t modos de disparo de peças pelo computador (1 a 3)\n");
    printf("-1\t número de peças do tipo 1\n");
    printf("-2\t número de peças do tipo 2\n");
    printf("-3\t número de peças do tipo 3\n");
    printf("-4\t número de peças do tipo 3\n");
    printf("-4\t número de peças do tipo 4\n");
    printf("-5\t número de peças do tipo 5\n");
    printf("-6\t número de peças do tipo 6\n");
    printf("-7\t número de peças do tipo 7\n");
    printf("-8\t número de peças do tipo 8\n");
    printf("Exemplos de programas que podem ser efetuados:\n");
    printf("-j 1 -p 1\n");
    printf("-j 2 -p 1 -d 3\n");
}

/**
 *  Nome: main
 *  Objetivo: chamar outras funções, completar o programa
 */

int main(int argc, char *argv[]) {
    int modo_pecas,jogo,disparos,i1;
    int opt = 'h', soma = 0, flag = 0, repeticao = 0;
    opterr = 0;
    time_t t;
    srand((unsigned) time(&t));
    while((opt=getopt(argc, argv, "t:j:p:d:1:2:3:4:5:6:7:8:h")) != -1){

        switch (opt) {
            case 't': /* dimensão do tabuleiro */
                sscanf(optarg, " %dx%d", &row, &column);
                break;
            case 'j':
                sscanf(optarg, "%d", &jogo);
                if (jogo == 2) {
                    modo_pecas = 2;
                }
                if (jogo == 1) {
                    disparos = 0;
                }
                break;
            case 'p':
                sscanf(optarg, "%d", &modo_pecas);
                if(jogo == 2 && modo_pecas == 1) {
                    exit(-1);
                }
                break;
            case 'd':
                sscanf(optarg, "%d", &disparos);
                if (disparos == 1 || disparos == 2 || disparos == 3)
                    jogo = 2;
                break;
            case '1':
                sscanf(optarg, "%d", &tipo[1]);
                break;
            case '2':
                sscanf(optarg, "%d", &tipo[2]);
                break;
            case '3':
                sscanf(optarg, "%d", &tipo[3]);
                break;
            case '4':
                sscanf(optarg, "%d", &tipo[4]);
                break;
            case '5':
                sscanf(optarg, "%d", &tipo[5]);
                break;
            case '6':
                sscanf(optarg, "%d", &tipo[6]);
                break;
            case '7':
                sscanf(optarg, "%d", &tipo[7]);
                break;
            case '8':
                sscanf(optarg, "%d", &tipo[8]);
                break;
            case 'h':
                menu_ajuda(argv[0]);
                return EXIT_FAILURE;
                break;
        }
    }
    if (modo_pecas == 2) {
        for(i1=1; i1<=9; i1++) {
            conta_pecas += tipo[i1]*i1; // conta o número de carácteres números
            if (i1 != 9) { // caso seja 9, não corre o código abaixo pois sairia dos paramentros do array
                if(tipo[i1] < tipo[i1+1]) { // restrição de peças do modo posicionamento 2
                    printf("*Número de peças inválido.\n");
                    menu_ajuda();
                    exit(-1);
                }
            }

            if(soma > (row*column/18)) { // restrição 4 do modo posicionamento 2
                soma = 0;
                printf("*Número de peças inválido.\n");
                menu_ajuda();
                exit(-1);
            }
            soma += tipo[i1];
        }
    }

    if((row < 9 || column < 9) || (row > 15 || column > 24) || ((row % 3) != 0) || ((column % 3) != 0)) { //restrição dos tamanhos do tabuleiro
        printf("*Tabuleiro Inválido.\n");
        menu_ajuda();
        exit(-1);
    }
    tipo[0] = (row*column)/9-tipo[1]-tipo[2]-tipo[3]-tipo[4]-tipo[5]-tipo[6]-tipo[7]-tipo[8]; // conta quantas peças do tipo nulo estão presentes no tabuleiro
    do {
        repeticao++;
        flag = modo_pos(modo_pecas, jogo, disparos, repeticao);
        if (repeticao == 1000) {
            printf("*Não foi possível criar o tabuleiro.\n");
            exit(-1);
        }
    } while(flag == -1);

    modo_jogo(modo_pecas, jogo, disparos);
    return EXIT_SUCCESS;
}
