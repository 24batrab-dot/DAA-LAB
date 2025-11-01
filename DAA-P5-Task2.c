#include <stdio.h>
#include <string.h>

#define MAX 100

void longestRepeatingSubsequence(char* str) {
    int n = strlen(str);
    int dp[MAX][MAX];
    
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i-1] == str[j-1] && i != j)
                dp[i][j] = 1 + dp[i-1][j-1];
            else if (dp[i-1][j] > dp[i][j-1])
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = dp[i][j-1];
        }
    }

    int i = n, j = n;
    char lrs[MAX];
    int index = 0;

    while (i > 0 && j > 0) {
        if (str[i-1] == str[j-1] && i != j && dp[i][j] == dp[i-1][j-1]+1) {
            lrs[index++] = str[i-1];
            i--; j--;
        } else if (dp[i-1][j] >= dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }

    lrs[index] = '\0';

    for (int k = 0; k < index/2; k++) {
        char temp = lrs[k];
        lrs[k] = lrs[index-1-k];
        lrs[index-1-k] = temp;
    }

    printf("Longest Repeating Subsequence: %s\n", lrs);
}

int main() {
    char str[MAX];
    printf("Enter the string: ");
    scanf("%s", str);
    longestRepeatingSubsequence(str);
    return 0;
}
