#include <stdio.h>
#include <string.h>
#define INF 9999 
#define RATE_PER_UNIT 5  // Ticket rate per unit distance
#define V 12  // Updated number of stations

// Function to create the Graphviz DOT file for the bus route system
void generateGraphvizFile(const char *stations[], int routes[V][V], int path[], int pathLength) {
    FILE *file = fopen("bus_route_system.dot", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write the header for the Graphviz DOT format
    fprintf(file, "digraph BusRouteSystem {\n");
    fprintf(file, "    graph [splines=polyline, nodesep=1, rankdir=LR];\n");
    fprintf(file, "    node [shape=circle, style=filled, color=lightblue, fontname=\"Arial\"];\n");
    fprintf(file, "    edge [fontname=\"Arial\", fontsize=10, color=gray];\n\n");

    // Define the nodes (stations)
    for (int i = 0; i < V; i++) {
        fprintf(file, "    %s [label=\"%s\"];\n", stations[i], stations[i]);
    }
    fprintf(file, "\n");

    // Write edges with distances as labels, highlighting the path from destination to Bhubaneswar
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (routes[i][j] != 0) {
                int isOnPath = 0;
                for (int k = 0; k < pathLength - 1; k++) {
                    if (path[k] == i && path[k + 1] == j) {
                        isOnPath = 1;
                        break;
                    }
                }
                if (isOnPath) {
                    fprintf(file, "    %s -> %s [label=\"%d km\", color=red, penwidth=2.0];\n", stations[i], stations[j], routes[i][j]);
                } else {
                    fprintf(file, "    %s -> %s [label=\"%d km\"];\n", stations[i], stations[j], routes[i][j]);
                }
            }
        }
    }

    // Close the DOT format
    fprintf(file, "}\n");
    fclose(file);

    printf("Graphviz DOT file 'bus_route_system.dot' created successfully.\n");
}

// Function to reverse the path array
void reversePath(int path[], int pathLength) {
    for (int i = 0; i < pathLength / 2; i++) {
        int temp = path[i];
        path[i] = path[pathLength - i - 1];
        path[pathLength - i - 1] = temp;
    }
}

int main() {
    int seq = 1;
    int Min, relax, visited;
    const char *stationNames[V] = {"Bhubaneswar", "Cuttack", "Kendrapara",
                                   "Jagatsinghpur", "Puri", "Khorda",
                                   "Berhampur", "Balasore", "Rourkela", "Sambalpur", "Angul", "Jharsuguda"};  

    int routes[V][V] = {
        {0, 26, 0, 56, 69, 27, 0, 0, 0, 0, 0, 0},   //Bhubaneswar
        {26, 0, 58, 0, 0, 0, 0, 90, 0, 0, 0, 0},    //Cuttack
        {0, 58, 0, 88, 0, 0, 0, 0, 0, 0, 0, 0},     //Kendrapara
        {56, 0, 88, 0, 73, 0, 0, 0, 0, 0, 0, 0},    //Jagatsinghpur
        {69, 0, 0, 73, 0, 62, 0, 0, 0, 0, 0, 0},    //Puri
        {27, 0, 0, 0, 62, 0, 83, 0, 0, 0, 0, 0},    //Khorda
        {0, 0, 0, 0, 0, 83, 0, 60, 92, 0, 0, 0},    //Berhampur
        {0, 90, 0, 0, 0, 0, 60, 0, 75, 0, 0, 0},    //Balasore
        {0, 0, 0, 0, 0, 0, 92, 75, 0, 85, 0, 0},    //Rourkela
        {0, 0, 0, 0, 0, 0, 0, 0, 85, 0, 50, 70},    //Sambalpur
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 0, 30},     //Angul
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 70, 30, 0}      //Jharsuguda
    };

    int shortestPaths[V][V];
    int visitOrder[V] = {0};
    char dest[20];
    int indexPosShortest, tracedStation;
    int path[V], pathLength = 0;

    for (int row = 0; row < V; row++) {
        for (int j = 0; j < V; j++) {
            shortestPaths[row][j] = (row == 0 && j == 0) ? 0 : INF;
        }
    }

    for (int l = 0; l < V; l++) {
        Min = INF;
        for (int j = 0; j < V; j++) {
            if (shortestPaths[l][j] < Min) {
                Min = shortestPaths[l][j];
                visited = j;
            }
        }

        visitOrder[visited] = seq++;
        for (int c = 0; c < V; c++) {
            if (routes[visited][c] != 0 && visitOrder[c] == 0) {
                relax = Min + routes[visited][c];
                if (relax < shortestPaths[l][c]) {
                    shortestPaths[l + 1][c] = relax;
                } else {
                    shortestPaths[l + 1][c] = shortestPaths[l][c];
                }
            } else if (visitOrder[c] == 0) {
                shortestPaths[l + 1][c] = shortestPaths[l][c];
            }
        }
    }

    printf("Shortest travel times/distances:\n");
    for (int b = 0; b < V; b++) {
        for (int m = 0; m < V; m++) {
            printf("%d\t", shortestPaths[b][m]);
        }
        printf("\n");
    }

    printf("\nVisiting sequence:\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t", visitOrder[i]);
    }
    printf("\n");

    printf("Enter destination station (e.g., Cuttack): ");
    scanf("%s", dest);

    int totalDistance = 0;
    for (int i = 0; i < V; i++) {
        if (strcmp(dest, stationNames[i]) == 0) {
            indexPosShortest = visitOrder[i] - 1;
            tracedStation = i;
            break;
        }
    }

    printf("Route to %s from Bhubaneswar: ", dest);
    printf("%s", dest);
    path[pathLength++] = tracedStation;

    for (; indexPosShortest > 0; indexPosShortest--) {
        if (shortestPaths[indexPosShortest][tracedStation] == shortestPaths[indexPosShortest - 1][tracedStation]);
        else {
            for (int i = 0; i < V; i++) {
                if (indexPosShortest == visitOrder[i]) {
                    printf(" <- %s", stationNames[i]);
                    totalDistance += routes[i][tracedStation];
                    path[pathLength++] = i;
                }
            }

            Min = INF;
            for (int j = 0; j < V; j++) {
                if (shortestPaths[indexPosShortest - 1][j] < Min) {
                    Min = shortestPaths[indexPosShortest - 1][j];
                    tracedStation = j;
                }
            }
        }
    }

    int ticketPrice = totalDistance * RATE_PER_UNIT;
    printf("\nTotal distance: %d Km\n", totalDistance);
    printf("Ticket Price: Rs. %d \n", ticketPrice);

    // Reverse the path to trace it in the opposite direction (from destination to Bhubaneswar)
    reversePath(path, pathLength);

    generateGraphvizFile(stationNames, routes, path, pathLength);

    return 0;
}