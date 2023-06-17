#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 100
#define MAXM 100

int N, M;
char map_caverna[MAXN][MAXM];
bool visitados[MAXN][MAXM];

void busca_profundidade(int i, int j, int* count) {
    if (i < 0 || i >= N || j < 0 || j >= M || map_caverna[i][j] == 'x' || visitados[i][j]) {
        return;
    }

    visitados[i][j] = true;
    (*count)++;

    busca_profundidade(i - 1, j, count);
    busca_profundidade(i + 1, j, count);
    busca_profundidade(i, j - 1, count);
    busca_profundidade(i, j + 1, count);
}

void regioes() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            visitados[i][j] = false;
        }
    }

    int num_regioes = 0;
    int tam_max_regioes = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map_caverna[i][j] == '.' && !visitados[i][j]) {
                num_regioes++;
                int count = 0;
                busca_profundidade(i, j, &count);
                if (count > tam_max_regioes) {
                    tam_max_regioes = count;
                }
            }
        }
    }

    printf("%d regiao(s); a maior tem area %d\n", num_regioes, tam_max_regioes);
}

int dist[MAXN][MAXM];
int fila[MAXN * MAXM];
int inicio, fim;

void busca_largura(int i1, int j1, int i2, int j2) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dist[i][j] = -1;
        }
    }

    inicio = fim = 0;

    dist[i1][j1] = 0;
    fila[fim++] = i1 * M + j1;

    while (inicio != fim) {
        int vert_atual = fila[inicio++];
        int i_atual = vert_atual / M;
        int j_atual = vert_atual % M;

        if (i_atual > 0 && map_caverna[i_atual - 1][j_atual] == '.' && dist[i_atual - 1][j_atual] == -1) {
            dist[i_atual - 1][j_atual] = dist[i_atual][j_atual] + 1;
            fila[fim++] = (i_atual - 1) * M + j_atual;
        }
        if (i_atual < N - 1 && map_caverna[i_atual + 1][j_atual] == '.' && dist[i_atual + 1][j_atual] == -1) {
            dist[i_atual + 1][j_atual] = dist[i_atual][j_atual] + 1;
            fila[fim++] = (i_atual + 1) * M + j_atual;
        }
        if (j_atual > 0 && map_caverna[i_atual][j_atual - 1] == '.' && dist[i_atual][j_atual - 1] == -1) {
            dist[i_atual][j_atual - 1] = dist[i_atual][j_atual] + 1;
            fila[fim++] = i_atual * M + j_atual - 1;
        }
        if (j_atual < M - 1 && map_caverna[i_atual][j_atual + 1] == '.' && dist[i_atual][j_atual + 1] == -1) {
            dist[i_atual][j_atual + 1] = dist[i_atual][j_atual] + 1;
            fila[fim++] = i_atual * M + j_atual + 1;
        }
    }

    if (dist[i2][j2] == -1) {
        printf("Nao ha caminho de (%d,%d) para (%d,%d)\n", i1, j1, i2, j2);
    } else {
        printf("De (%d,%d) para (%d,%d) em %d passos\n", i1, j1, i2, j2, dist[i2][j2]);
    }
}

void cam() {
    int i1, j1, i2, j2;
    scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
    busca_largura(i1, j1, i2, j2);
}

void ponto() {
    int i, j;
    scanf("%d %d", &i, &j);
    map_caverna[i][j] = '.';
}

void printMap() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c", map_caverna[i][j]);
        }
        printf("\n");
    }
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%s", map_caverna[i]);
    }

    char comando[10];
    while (scanf("%s", comando) != EOF) {
        if (strcmp(comando, "regioes") == 0) {
            regioes();
        } else if (strcmp(comando, "cam") == 0) {
            cam();
        } else if (strcmp(comando, ".") == 0) {
            ponto();
            printMap();
        } else if (strcmp(comando, "F") == 0) {
            break;
        }
    }

    return 0;
}