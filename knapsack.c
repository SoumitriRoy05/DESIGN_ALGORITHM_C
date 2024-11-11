
// #include <stdio.h>

// // Function to perform Bubble Sort on ratios and corresponding indices
// void bubbleSort(float ratio[], int index[], int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (ratio[j] < ratio[j + 1]) {
//                 // Swap ratios
//                 float tempRatio = ratio[j];
//                 ratio[j] = ratio[j + 1];
//                 ratio[j + 1] = tempRatio;
                
//                 // Swap indices to keep track of original items
//                 int tempIndex = index[j];
//                 index[j] = index[j + 1];
//                 index[j + 1] = tempIndex;
//             }
//         }
//     }
// }

// int main() {
//     int n, capacity;
    
//     // Input number of items
//     printf("Enter number of items: ");
//     scanf("%d", &n);
    
//     int weight[n], value[n];
//     float ratio[n]; // Value-to-weight ratio array
    
//     // Input weights and values
//     printf("Enter the weights and values of the items:\n");
//     for (int i = 0; i < n; i++) {
//         printf("Item %d Weight: ", i + 1);
//         scanf("%d", &weight[i]);
//         printf("Item %d Value: ", i + 1);
//         scanf("%d", &value[i]);
//         ratio[i] = (float)value[i] / weight[i]; // Calculate ratio
//     }
    
//     // Input the maximum capacity of the knapsack
//     printf("Enter the max capacity of the knapsack: ");
//     scanf("%d", &capacity);
    
//     // Create an array of indices to sort the ratios
//     int index[n];
//     for (int i = 0; i < n; i++) {
//         index[i] = i;
//     }
    
//     // Sort the items by value-to-weight ratio using Bubble Sort
//     bubbleSort(ratio, index, n);
    
//     // Compute the maximum profit
//     float totalProfit = 0.0;
//     printf("Items included in the knapsack:\n");
//     for (int i = 0; i < n && capacity > 0; i++) {
//         int idx = index[i];
//         int takeWeight = weight[idx] <= capacity ? weight[idx] : capacity;
//         float takeValue = value[idx] * (float)takeWeight / weight[idx];
        
//         // Update the total profit and remaining capacity
//         totalProfit += takeValue;
//         capacity -= takeWeight;
        
//         // Print the fraction of the item included
//         printf("Item %d: %.2f%%\n", idx + 1, (float)takeWeight / weight[idx] * 100);
//     }
    
//     // Output the maximum profit
//     printf("Maximum profit in the knapsack: %.2f\n", totalProfit);
    
//     return 0;
// }

#include <stdio.h>
#include<stdlib.h>
// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem using dynamic programming
int knapsack(int W, int wt[], int val[], int n) {
    int i, j;
    int K[n + 1][W + 1];

    // Build the table K[][] in bottom-up manner
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= W; j++) {
            if (i == 0 || j == 0)
                K[i][j] = 0;
            else if (wt[i - 1] <= j)
                K[i][j] = max(val[i - 1] + K[i - 1][j - wt[i - 1]], K[i - 1][j]);
            else{
                K[i][j] = K[i - 1][j];
            }
        }
    }

    // The maximum value that can be put in a knapsack of capacity W
    

printf("\nDP Table:\n");
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= W; j++) {
            printf("%d\t", K[i][j]);
        }
        printf("\n");
    }

    // Maximum value that can be carried
    printf("\nMaximum value in Knapsack = %d\n", K[n][W]);

    // Find out which items to select
    printf("Items selected:\n");
    int res = K[n][W];
    j= W;
    for (i = n; i > 0 && res > 0; i--) {
        if (res == K[i - 1][j])
            continue; // Item not included
        else {
            // Item included
            printf("Item %d (Value: %d, Weight: %d)\n", i, val[i - 1], wt[i - 1]);
            res = res - val[i - 1];
            j = j - wt[i - 1];
        }
    }
}


int main() {
    int W,n,i;
    printf("ENTER THE KNAPSACK CAPACITY:");
    scanf("%d/n",&W);
    printf("ENTER THE NUMBER OF ELEMENTS REQUIRED:");
    scanf("%d",&n);
    int val[n], wt[n];
    printf("ENTER THE VALUES OF ELEMENTS:");
    for(i=0;i<n;i++){
    scanf("%d",&val[i]);
    }
    printf("ENTER THE WEIGHT OF THE ITEMS:");
    for(i=0;i<n;i++){
        scanf("%d",&wt[i]);
    }
   
knapsack(W, wt, val, n);

    return 0;
}