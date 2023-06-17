#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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