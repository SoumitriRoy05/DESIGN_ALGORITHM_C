#include <stdio.h>
#include <limits.h>

// void printOptimalParenthesis(int s[][100], int i, int j) {
//     if (i == j) {
//         printf("A%d", i + 1);  
//     } else {
//         printf("(");
//         printOptimalParenthesis(s, i, s[i][j]);
//         printOptimalParenthesis(s, s[i][j] + 1, j);
//         printf(")");
//     }
// }
void printOptimalParenthesis(int s[][100], int i, int j) {
    if (i == j) {
        printf("A%d", i + 1);
        return;
    }
    
    printf("(");
    int splitPoint = s[i][j];
    printOptimalParenthesis(s, i, splitPoint);
    printOptimalParenthesis(s, splitPoint + 1, j);
    printf(")");
}

void matrixChainOrder(int p[], int n) {
    int m[100][100];  
    int s[100][100];  

    
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    
    for (int l = 2; l < n; l++) {
        for (int i = 1; i <= n - l; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;  // Set to a very large number initially
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
   }

    // Print the m matrix (minimum multiplication cost)
    printf("Matrix m (Minimum Multiplication Cost):\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i > j) {
                printf("    ");
            } else {
                printf("%4d", m[i][j]);
            }
        }
        printf("\n");
    }

    // Print the s matrix or k 
    printf("\nMatrix s :\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i >= j) {
                printf("    ");
            } else {
                printf("%4d", s[i][j]);
            }
        }
        printf("\n");
    }

    // Print the  parenthesization
    printf("\n Parenthesization: ");
    printOptimalParenthesis(s, 1, n - 1);
    printf("\n");

    // Print the minimum cost
    printf("Minimum cost of multiplication: %d\n", m[1][n - 1]);
}

int main() {
    int n;

    
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    
    int p[n + 1];
    printf("Enter dimensions of matrices:\n");
    for (int i = 0; i <= n; i++) {
        printf("p[%d] = ", i);
        scanf("%d", &p[i]);
    }


    matrixChainOrder(p, n + 1);

    return 0;
}