#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int length;
    char sequence[MAX];
} Cell;

char* findLCS(const char* X, const char* Y) {
    static char result[MAX];
    int m = strlen(X);
    int n = strlen(Y);
    Cell sub[MAX][MAX];

    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++) {
            sub[i][j].length = 0;
            sub[i][j].sequence[0] = '\0';
        }

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                sub[i][j].length = sub[i - 1][j - 1].length + 1;
                strcpy(sub[i][j].sequence, sub[i - 1][j - 1].sequence);
                int len = strlen(sub[i][j].sequence);
                sub[i][j].sequence[len] = X[i - 1];
                sub[i][j].sequence[len + 1] = '\0';
            } else if (sub[i - 1][j].length >= sub[i][j - 1].length) {
                sub[i][j].length = sub[i - 1][j].length;
                strcpy(sub[i][j].sequence, sub[i - 1][j].sequence);
            } else {
                sub[i][j].length = sub[i][j - 1].length;
                strcpy(sub[i][j].sequence, sub[i][j - 1].sequence);
            }
        }

    strcpy(result, sub[m][n].sequence);
    printf("LCS Sequence: %s\n", result);
    printf("Length of LCS: %d\n", sub[m][n].length);
    return result;
}

int main() {
    char X[] = "AGCCCTAAGGGCTACCTAGCTT";
    char Y[] = "GACAGCCTACAAGCGTTAGCTTG";
    findLCS(X, Y);
    return 0;
}
