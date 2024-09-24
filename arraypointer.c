#include<stdio.h>

int main()
{
    int n, m; 
    printf("Enter the number of rows (n): ");
    scanf("%d", &n);
    printf("Enter the number of columns (m): ");
    scanf("%d", &m);

    int arr[n][m];
    int *p = &arr[0][0]; 
    int i, j;

    printf("Enter the values of diagonal elements:\n");

    
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (i == j && i < m) {  
                scanf("%d", p + i * m + j);
            } else {   
                *(p + i * m + j) = 0;
            }
        }
    }

   
    for (int k = 1; k < m; k++) {  
        for (i = 0; i < n - k; i++) {
            j = i + k;
            if (j < m) {
                *(p + i * m + j) = *(p + i * m + (j - 1)) + *(p + (i + 1) * m + j);
            }
        }
    }

   
    printf("Display the matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d\t", *(p + i * m + j));
        }
        printf("\n");
    }

    return 0;
}