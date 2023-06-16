#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 100
#define MAXM 100

int N, M;
char caveMap[MAXN][MAXM];
bool visited[MAXN][MAXM];

void DFS(int i, int j, int* count) {
    if (i < 0 || i >= N || j < 0 || j >= M || caveMap[i][j] == 'x' || visited[i][j]) {
        return;
    }

    visited[i][j] = true;
    (*count)++;

    DFS(i - 1, j, count);
    DFS(i + 1, j, count);
    DFS(i, j - 1, count);
    DFS(i, j + 1, count);
}

void processRegioesCommand() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            visited[i][j] = false;
        }
    }

    int numRegions = 0;
    int maxRegionSize = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (caveMap[i][j] == '.' && !visited[i][j]) {
                numRegions++;
                int count = 0;
                DFS(i, j, &count);
                if (count > maxRegionSize) {
                    maxRegionSize = count;
                }
            }
        }
    }

    printf("%d regioes; a maior tem area %d\n", numRegions, maxRegionSize);
}

int distance[MAXN][MAXM];
int queue[MAXN * MAXM];
int front, rear;

void BFS(int i1, int j1, int i2, int j2) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            distance[i][j] = -1;
        }
    }

    front = rear = 0;

    distance[i1][j1] = 0;
    queue[rear++] = i1 * M + j1;

    while (front != rear) {
        int currentVertex = queue[front++];
        int currentI = currentVertex / M;
        int currentJ = currentVertex % M;

        if (currentI > 0 && caveMap[currentI - 1][currentJ] == '.' && distance[currentI - 1][currentJ] == -1) {
            distance[currentI - 1][currentJ] = distance[currentI][currentJ] + 1;
            queue[rear++] = (currentI - 1) * M + currentJ;
        }
        if (currentI < N - 1 && caveMap[currentI + 1][currentJ] == '.' && distance[currentI + 1][currentJ] == -1) {
            distance[currentI + 1][currentJ] = distance[currentI][currentJ] + 1;
            queue[rear++] = (currentI + 1) * M + currentJ;
        }
        if (currentJ > 0 && caveMap[currentI][currentJ - 1] == '.' && distance[currentI][currentJ - 1] == -1) {
            distance[currentI][currentJ - 1] = distance[currentI][currentJ] + 1;
            queue[rear++] = currentI * M + currentJ - 1;
        }
        if (currentJ < M - 1 && caveMap[currentI][currentJ + 1] == '.' && distance[currentI][currentJ + 1] == -1) {
            distance[currentI][currentJ + 1] = distance[currentI][currentJ] + 1;
            queue[rear++] = currentI * M + currentJ + 1;
        }
    }

    if (distance[i2][j2] == -1) {
        printf("Nao ha caminho de (%d,%d) para (%d,%d)\n", i1, j1, i2, j2);
    } else {
        printf("De (%d,%d) para (%d,%d) em %d passos\n", i1, j1, i2, j2, distance[i2][j2]);
    }
}

void processCamCommand() {
    int i1, j1, i2, j2;
    scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
    BFS(i1, j1, i2, j2);
}

void processDotCommand() {
    int i, j;
    scanf("%d %d", &i, &j);
    caveMap[i][j] = '.';
}

void printMap() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c", caveMap[i][j]);
        }
        printf("\n");
    }
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%s", caveMap[i]);
    }

    char command[10];
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "regioes") == 0) {
            processRegioesCommand();
        } else if (strcmp(command, "cam") == 0) {
            processCamCommand();
        } else if (strcmp(command, ".") == 0) {
            processDotCommand();
            printMap();
        } else if (strcmp(command, "F") == 0) {
            break;
        }
    }

    return 0;
}