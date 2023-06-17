#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 100
#define MAXM 100

typedef struct {
    int N;
    int M;
    char map_caverna[MAXN][MAXM];
} Mapa;

typedef struct {
    int dist[MAXN][MAXM];
    int fila[MAXN * MAXM];
    int inicio;
    int fim;
} Distancias;

void busca_profundidade(Mapa* mapa, bool visitados[MAXN][MAXM], int i, int j, int* count) {
    if (i < 0 || i >= mapa->N || j < 0 || j >= mapa->M || mapa->map_caverna[i][j] == 'x' || visitados[i][j]) {
        return;
    }

    visitados[i][j] = true;
    (*count)++;

    busca_profundidade(mapa, visitados, i - 1, j, count);
    busca_profundidade(mapa, visitados, i + 1, j, count);
    busca_profundidade(mapa, visitados, i, j - 1, count);
    busca_profundidade(mapa, visitados, i, j + 1, count);
}

void regioes(Mapa* mapa) {
    bool visitados[MAXN][MAXM] = {false};

    int num_regioes = 0;
    int tam_max_regioes = 0;
    for (int i = 0; i < mapa->N; i++) {
        for (int j = 0; j < mapa->M; j++) {
            if (mapa->map_caverna[i][j] == '.' && !visitados[i][j]) {
                num_regioes++;
                int count = 0;
                busca_profundidade(mapa, visitados, i, j, &count);
                if (count > tam_max_regioes) {
                    tam_max_regioes = count;
                }
            }
        }
    }

    printf("%d regiao(s); a maior tem area %d\n", num_regioes, tam_max_regioes);
}

void busca_largura(Mapa* mapa, Distancias* dist, int i1, int j1, int i2, int j2) {
    for (int i = 0; i < mapa->N; i++) {
        for (int j = 0; j < mapa->M; j++) {
            dist->dist[i][j] = -1;
        }
    }

    dist->inicio = dist->fim = 0;

    dist->dist[i1][j1] = 0;
    dist->fila[dist->fim++] = i1 * mapa->M + j1;

    while (dist->inicio != dist->fim) {
        int vert_atual = dist->fila[dist->inicio++];
        int i_atual = vert_atual / mapa->M;
        int j_atual = vert_atual % mapa->M;

        if (i_atual > 0 && mapa->map_caverna[i_atual - 1][j_atual] == '.' && dist->dist[i_atual - 1][j_atual] == -1) {
            dist->dist[i_atual - 1][j_atual] = dist->dist[i_atual][j_atual] + 1;
            dist->fila[dist->fim++] = (i_atual - 1) * mapa->M + j_atual;
        }
        if (i_atual < mapa->N - 1 && mapa->map_caverna[i_atual + 1][j_atual] == '.' && dist->dist[i_atual + 1][j_atual] == -1) {
            dist->dist[i_atual + 1][j_atual] = dist->dist[i_atual][j_atual] + 1;
            dist->fila[dist->fim++] = (i_atual + 1) * mapa->M + j_atual;
        }
        if (j_atual > 0 && mapa->map_caverna[i_atual][j_atual - 1] == '.' && dist->dist[i_atual][j_atual - 1] == -1) {
            dist->dist[i_atual][j_atual - 1] = dist->dist[i_atual][j_atual] + 1;
            dist->fila[dist->fim++] = i_atual * mapa->M + j_atual - 1;
        }
        if (j_atual < mapa->M - 1 && mapa->map_caverna[i_atual][j_atual + 1] == '.' && dist->dist[i_atual][j_atual + 1] == -1) {
            dist->dist[i_atual][j_atual + 1] = dist->dist[i_atual][j_atual] + 1;
            dist->fila[dist->fim++] = i_atual * mapa->M + j_atual + 1;
        }
    }

    if (dist->dist[i2][j2] == -1) {
        printf("Nao ha caminho de (%d,%d) para (%d,%d)\n", i1, j1, i2, j2);
    } else {
        printf("De (%d,%d) para (%d,%d) em %d passos\n", i1, j1, i2, j2, dist->dist[i2][j2]);
    }
}

void ponto(Mapa* mapa, int i, int j) {
    mapa->map_caverna[i][j] = '.';
}

void estalactite(Mapa* mapa, int i, int j) {
    mapa->map_caverna[i][j] = 'x';
    printMap(mapa);
}


void printMap(Mapa* mapa) {
    for (int i = 0; i < mapa->N; i++) {
        for (int j = 0; j < mapa->M; j++) {
            printf("%c", mapa->map_caverna[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Mapa mapa;
    int i,j,i1, j1, i2, j2;
    scanf("%d %d", &mapa.N, &mapa.M);

    for (int i = 0; i < mapa.N; i++) {
        scanf("%s", mapa.map_caverna[i]);
    }

    char comando[10];
    while (scanf("%s", comando) != EOF) {
        if (strcmp(comando, "regioes") == 0) {
            regioes(&mapa);
        } else if (strcmp(comando, "cam") == 0) {
            scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
            Distancias dist;
            busca_largura(&mapa, &dist, i1, j1, i2, j2);
        } else if (strcmp(comando, ".") == 0) {
            scanf("%d %d", &i, &j);
            ponto(&mapa, i, j);
            printMap(&mapa);
        } else if (strcmp(comando, "F") == 0) {
            break;
        }else if (strcmp(comando, "x") == 0) {
            scanf("%d %d", &i, &j);
            estalactite(&mapa, i, j);
        }

    }

    return 0;
}
