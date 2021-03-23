#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int row=9, column=9;
char table[15][24];

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
    for(i=0; i<row; i++) {
        for(i2=0; i2<column; i2++) {
            table [i] [i2] = '-';
        }
    }

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

void p1() {
    time_t t;
    srand((unsigned) time(&t));

    int i1 = rand() % 3;
    int i2 = rand() % 3;
    table[i1][i2] = '1';
}

int main()
{
    menu();
    InicializacaoBoard();
    p1();
    return EXIT_SUCCESS;
}
