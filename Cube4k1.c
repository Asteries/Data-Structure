#include <stdio.h>
#include <stdlib.h>

void judge(int c[][130], int n) {
    int sum, i, j;
    for (i = 1; i <= n; i++) {
        sum = 0;
        for (j = 1; j <= n; j++)
            sum += c[i][j];
        printf("%d ", sum);
    }
    printf("\n");
    for (i = 1; i <= n; i++) {
        sum = 0;
        for (j = 1; j <= n; j++)
            sum += c[j][i];
        printf("%d ", sum);
    }
}

int main(void) {
    int cube[130][130], i, j, temp = 1;
    int n = 12;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            cube[i][j] = temp++;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) {
            if ((i <= n / 2 && j <= n / 2 && (i + j) % 2 == 0) ||
                (i <= n / 2 && j > n / 2 && (i + j) % 2 == 1)) {
                temp = cube[i][j];
                cube[i][j] = cube[n - i + 1][n - j + 1];
                cube[n - i + 1][n - j + 1] = temp;
            }
        }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            printf("%*d", 5, cube[i][j]);
        printf("\n");
    }
    printf("\n");
    judge(cube, n);
}
