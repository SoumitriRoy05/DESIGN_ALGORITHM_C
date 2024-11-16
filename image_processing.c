#include <stdio.h>

int main() {
    int i, j, n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);
    int arr[n][n];
    printf("Enter elements for the diagonal of the 2D array:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                printf("Enter element [%d][%d]: ", i, j);
                scanf("%d", &arr[i][j]);
            } else {
                arr[i][j] = 0; 
            }
        }
    }
    for (i = n - 1; i >= 0; i--) 
    { 
        for (j = i + 1; j < n; j++)
         { 
            arr[i][j] = arr[i][j - 1] + arr[i + 1][j];
        }
    }
    printf("\nGenerated Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
