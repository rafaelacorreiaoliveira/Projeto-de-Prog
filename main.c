#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int row=9, column=9;
int tipo [9] = {0,0,0,0,0,0,0,0,0};
int peca, conta_pecas;
char table[1][15][24] = {{{' '}}};
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
 *  Nome: jogo_select
 *  Objetivo: obter a partir do utilizador o modo de jogo que o programa irá executar
 *
 *  Parametros de entrada: n/a
 *  Parametros de saida: jogo
 */

int jogo_select() {
    int jogo;

    do {
        printf("\n\n\t|Insira o modo de jogo desejado|\n\n\t0.Aleatório\n\t1.Disparo\n\t2.Computador \n\n\t--> ");
        if(scanf("%i", &jogo) != 1) {
            printf("\n\tInválido, tente novamente.");
            scanf("%*c");
        }
        system("clear");
    } while(jogo != 0 && jogo != 1 && jogo != 2);

    return jogo;
}

/**
 *  Nome: tamanho_jogo
 *  Objetivo: obter a partir do utilizador o tamanho do tabuleiro a ser utilizado
 *
 *  Parametros de entrada: n/a
 *  Parametros de saida: n/a
 */

void tamanho_jogo() {
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
 *  Nome: pos_select
 *  Objetivo: obter a partir do utilizador o tipo de posicionamento de peças
 *
 *  Parametros de entrada: n/a
 *  Parametros de saida: modo_pecas
 */

int pos_select() {

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
 *  Objetivo: representar no ecrã valores previamente carregados no tabuleiro dedicado ao correto modo de jogo
 *
 *  Parametros de entrada: n/a
 *  Parametros de saida: n/a
 */

void printBoard(modo_pecas, jogo) {

    system("clear");
    int i1, i2;
    char letters[] = "ABCDEFGHIJKLMNOQPRSTUVWX";

    //display da matriz na consola + column of numbers
    int num = row;

    // Tipos de peça no modo p1
    if (modo_pecas == 1 && jogo == 0) {
        printf("\n %ix%i", row, column);
        for(i1=1; i1<9; i1++) {
            printf(" - %i", tipo[i1]);
        }
        printf("\n\n");
    }

    // modo de jogo j0 ou j1 (dependendo da variável jogo)
    for (i1 = 0; i1 < row; i1++) {
        if(num<10)
            printf("  %i", num);
        else
            printf(" %i", num);

        for (i2 = 0; i2 < column; i2++) {
            printf(" %c", table[jogo][i1][i2]);
        }
        num--;
        printf("\n");
    }

    // letras no final do tabuleiro
    printf("   ");
    for(i1=0; i1<column; i1++) {
        printf(" %c", letters[i1]);
    }
    //if(jogo == 1)
    //    printf("\n\n O jogo demorou %i segundos.", tempo);
}

/**
 *  Nome: restricao_1
 *  Objetivo: implementar a restrição 1 relativamente á disposição das peças
 *
 *  Parametros de entrada: for1, for2, modo_pecas
 *  Paremetros de saida: n/a
 */

int restricao_1(for1, for2, modo_pecas, contador1) {

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
        controlo = 0;
        printf("\n - Insira o número de peças desejado por ordem de tamanho (1,2,3,4,5,6,7,8):\n\n");
        for(i1=1; i1<9; i1++) {
            printf("\tPeça %i - ", i1);
            if(scanf("%i", &tipo[i1]) != 1){
                printf("\n\tInválido, tente novamente (Entrada não reconhecida).");
                scanf("%*s");
                soma = 0;
                controlo = 1;
                break;
            }
            // Restrição 4
            if(soma > (row*column/18)) {
                printf("\n\tInválido, tente novamente (Reduza o número de peças).");
                soma = 0;
                controlo = 1;
                break;
            }
            soma += tipo[i1];
        }
        // Verifica se alguma peça de tipo superior têm mais repetições que a anterior
        for(i1=1; i1<8; i1++) {
            if(tipo[i1] < tipo[i1+1]) {
                printf("\n\tInválido, tente novamente (Ordem introduzida de peças incorreta).");
                soma = 0;
                controlo = 1;
            }

        }
        system("clear");

        // Espaços a preencher com matrizes vazias
        tipo[0] = (row*column)/9-tipo[1]-tipo[2]-tipo[3]-tipo[4]-tipo[5]-tipo[6]-tipo[7]-tipo[8];

    } while(controlo == 1);
}

/**
 *  Nome: rand_pecas
 *  Objetivo: randomização da variante de uma peça, utilizada no modo de posicionamento 2
 *
 *  Parametros de entrada: a, modo_pecas
 *  Paremetros de saida: n/a
 */

 void modo_d1() {


 }

int rand_pecas(a, modo_pecas) {

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
    tipo[peca]--;

    return a;
}

/**
 *  Nome: contador
 *  Objetivo: contar o tipo de peças geradas no modo p1
 *
 *  Parametros de entrada: a
 *  Paremetros de saida: n/a
 */

int contador(a) {

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
 *  Objetivo: correr o programa de acordo com o modo selecionado
 *
 *  Parametros de entrada: n/a
 *  Paremetros de saida: n/a
 */

int modo_pos() {

    /* for1 - percorre matriz global de 3 em 3 linhas.
       for2 - percorre matriz global de 3 em 3 colunas.
       for3 - percorre natriz específica 3x3 por linhas.
       for4 - percorre matriz específica 3x3 por colunas. */
    int for1, for2, for3, for4;
    int a, contador1;
    time_t t;
    srand((unsigned) time(&t));

    // Retira o modo de posicionamento de peças
    int modo_pecas = pos_select();

    // Modo p2
    if(modo_pecas == 2)
        escolha_pecas();

    //Percorre a matriz em blocos 3x3
    for(for1=0; for1 < row/3; for1++) {
        for(for2=0; for2 < column/3; for2++) {

            //Matriz 3x3 específica
            do {
                // Modo p1
                if (modo_pecas == 1) {
                    a = rand() % 43;
                    contador1 = contador(a);
                }
                // Modo p2
                if(modo_pecas == 2) {
                    do {
                        peca = rand()%9;
                    }while(tipo[peca] == 0);
                    a = rand_pecas(a, modo_pecas);
                }
                for(for3=0; for3<3; for3++) {
                    for(for4=0; for4<3; for4++) {
                        table[0][for3+for1*3][for4+for2*3] = pecas[a][for3][for4];
                    }
                }
            }while(restricao_1(for1, for2, modo_pecas, contador1));
        }
    }
    return modo_pecas;
}

/**
 *  Nome: disparo_j1
 *  Objetivo: verificar condição de vitória
 *
 *  Parametros de entrada: disparo_linha, disparo_coluna
 *  Paremetros de saida: vitoria
 */

int disparo_j1(disparo_linha, disparo_coluna) {
    if (table[1][row - disparo_linha - 2][disparo_coluna - 17] != '-') {
        conta_pecas --;
        if (conta_pecas == 0)
            return 1;
    }
    return 0;
}

 /**
 *  Nome: modo_j1
 *  Objetivo: implementar o modo de jogo 1
 *
 *  Parametros de entrada: n/a
 *  Paremetros de saida: n/a
 */

int modo_j1() {
    int disparo_linha;
    int vitoria;
    char disparo_coluna;

    printf("\n\n\t- Insira as coordenadas de disparo (coluna-linha): ");
    scanf(" %c %i", &disparo_coluna, &disparo_linha);
    printf("\n");

    //se o utilizador inserir uma coordenada já jogada, conta_pecas não é afetado com a próxima função
    if (table[1][row - disparo_linha - 2][disparo_coluna - 17] != ' ') {
        if(table[1][row - disparo_linha - 2][disparo_coluna - 17] != '-'){
            conta_pecas++;
        }
    }


    table[1][row - disparo_linha - 2][disparo_coluna - 17] = table[0][row - disparo_linha - 2][disparo_coluna - 17];

    //condição de vitória
    vitoria = disparo_j1(disparo_linha, disparo_coluna);
    return vitoria;
}

/**
 *  Nome: modo_jogo
 *  Objetivo: escolher modos de jogo???
 *
 *  Parametros de entrada: jogo
 *  Paremetros de saida:
 */

int modo_jogo(modo_pecas, jogo) {
    if(jogo == 1) {
        int i1, i2, vitoria;
        //Inicializar o tabuleiro de jogo j1 a ' '
        for(i1 = 0; i1 < row; i1++) {
            for (i2 = 0; i2 < column; i2++) {
                table[1][i1][i2] = ' ';
            }
        }
        // calcula número de células ocupadas por números na matriz
        for(i1=1; i1<=9; i1++) {
            conta_pecas += tipo[i1]*i1;
        }
        do {
            vitoria = modo_j1();
            if (vitoria == 0)
                printf("%i", conta_pecas);
                printBoard(modo_pecas, jogo);
        }while(vitoria == 0);
        system("clear");
    }
    return 0;
}

void utilizar(char *program){

    printf("Jogo da Batalha Naval.\n\n");
    printf("Opções de funcionamento: \n");
    printf("-h\t ajuda ao utilizador, mostra as instruções.\n");
    printf("-t\t dimensões do tabuleiro (linha x coluna).");
    printf("-j\t modos de jogo.");
    printf("-p\t modo de posicionamento de paças pelo computador (1 a 2)");
    printf("-d\t modos de disparo de peças pelo computador ( a 3)");
    printf("-1\t número de peças do tipo 1");
    printf("-2\t número de peças do tipo 2");
    printf("-3\t número de peças do tipo 3");
    printf("-4\t número de peças do tipo 3");
    printf("-4\t número de peças do tipo 4");
    printf("-5\t número de peças do tipo 5");
    printf("-6\t número de peças do tipo 6");
    printf("-7\t número de peças do tipo 7");
    printf("-8\t número de peças do tipo 8");
}

/**
 *  Nome: main
 *  Objetivo: chamar outras funções, completar o programa
 *
 *  Parametros de entrada: n/a
 *  Paremetros de saida: n/a
 */


/*int main() {
    tamanho_jogo();
    int modo_pecas = modo_pos();
    int jogo = jogo_select();
    modo_jogo(modo_pecas, jogo);
    printBoard(modo_pecas, jogo);
    return EXIT_SUCCESS;
} */
int main(int argc, char *argv[])
{
    int opt = 'h'; /* opção para getopt() */
    int opterr = 0;
    int optarg;
    while((opt=getopt(argc, argv, "tjpd12345678:")) != -1){

        switch (opt) {
            case 't': /* dimensão do tabuleiro */
                sscanf(optarg, " %d %d", &row, &column); /* se houver erro, fica o valor por omissão */
                break;
            case 'j': /* mínimo */
                sscanf(optarg, "%d", &jogo);
                break;
            case 'p':
                sscanf(optarg, "%d", &modo_pecas);
                break;
            case 'd':
                break;
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            case 'h':
                utilizacao(argv[0]);
                return EXIT_FAILURE;
                break;
        }
    }
}

