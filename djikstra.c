#include<stdio.h>
#include<stdlib.h>
#define Inf 9999

int main() {
    int i, j, k;
    int visit_vertex;
    int min;
    int Graph[6][6] = {{0, 3, 2, 5, 0, 0}, {3, 0, 0, 2, 4, 0}, {2, 0, 0, 2, 0, 1}, {2, 2, 2, 0, 3, 0}, {0, 4, 0, 3, 0, 2}, {0, 0, 1, 0, 2, 0}};
    char vertex[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int visited[6] = {0, 0, 0, 0, 0, 0};
    int DijComp[6][6];
    char path[6];
    char source;
    
    printf("Enter the Source:\n");
    scanf(" %c", &source);
    int row;
    for (i = 0; i < 6; i++) {
        if (vertex[i] == source) {
            row = i;
            break;
        }
    }

    printf("\n");
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            if (i == 0 && j == row)
                DijComp[i][j] = 0;
            else
                DijComp[i][j] = Inf;
        }
    }

    printf("GRAPH MATRIX:\n");
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            printf("%d\t", Graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (i = 0; i < 6 - 1; i++) {
        min = Inf;
        for (j = 0; j < 6; j++) {
            if (visited[j] != 1 && DijComp[i][j] < min) {
                min = DijComp[i][j];
                visit_vertex = j;
            }
        }
        visited[visit_vertex] = 1;
        for (k = 0; k < 6; k++) {
            if (visited[k] != 1) {
                if (Graph[visit_vertex][k] != 0) {
                    int relax = Graph[visit_vertex][k] + min;
                    if (relax < DijComp[i][k]) {
                        DijComp[i + 1][k] = relax;
                    } else {
                        DijComp[i + 1][k] = DijComp[i][k];
                    }
                }
                if (Graph[visit_vertex][k] == 0 && DijComp[i][k] != Inf) {
                    DijComp[i + 1][k] = DijComp[i][k];
                }
            }
        }
    }

    printf("Dij Comp Matrix:\n");
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            if (DijComp[i][j] == Inf) {
                printf("inf\t ");
            } else {
                printf("%d\t ", DijComp[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    char destination;
    printf("Enter the destination\n");
    scanf(" %c", &destination);

   
    int destinationIndex;
    for (i = 0; i < 6; i++) {
        if (destination == vertex[i]) 
            destinationIndex = i;
           
        
    }

   
    path[0] = destination;
    int p = 1;
    int currentVertex = destinationIndex;

    for (i = 6-1; i > 0; i--) {  
        if (DijComp[i][currentVertex] != DijComp[i - 1][currentVertex] && DijComp[i][currentVertex]!=Inf) {
            
            int minDist = Inf;
            
            for (j = 0; j < 6; j++) {
               
                if(DijComp[i-1][j]<minDist){
                    minDist = DijComp[i - 1][j];
                    destinationIndex= j;
                }
            }
            path[p]=vertex[destinationIndex];
            p++;

        }
    }
    printf("THE PATH:\n");
    for (i = p - 1; i >= 0; i--) {
        if (i == 0)
            printf("%c", path[i]);
        else
            printf("%c -> ", path[i]);
    }
    return 0;                                                        
}



