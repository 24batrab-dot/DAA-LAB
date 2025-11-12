#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAX 100

void optimalBST(int keys[], float p[], float q[], int n) {
    float e[MAX][MAX], w[MAX][MAX];
    int root[MAX][MAX];

    // Initialize cost and weight for empty subtrees
    for (int i = 0; i <= n; i++) {
        e[i][i] = q[i];
        w[i][i] = q[i];
    }

    // l = length of the subtree
    for (int l = 1; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l;
            e[i][j] = FLT_MAX;
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

            // Try all possible roots 'r'
            for (int r = i + 1; r <= j; r++) {
                float t = e[i][r - 1] + e[r][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum expected search cost: %.2f\n", e[0][n]);
}

int main() {
    int n;
    printf("Enter number of book IDs: ");
    scanf("%d", &n);

    int keys[MAX];
    float p[MAX], q[MAX + 1];

    printf("Enter the %d sorted book IDs:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &keys[i]);
    }

    printf("Enter the %d probabilities of successful searches (p[i]):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%f", &p[i]);
    }

    printf("Enter the %d probabilities of unsuccessful searches (q[i]):\n", n + 1);
    for (int i = 0; i <= n; i++) {
        scanf("%f", &q[i]);
    }

    optimalBST(keys, p, q, n);

    return 0;
}

