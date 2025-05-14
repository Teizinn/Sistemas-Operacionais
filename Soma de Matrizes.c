#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int **matrizA, **matrizB, **matrizResultado;
    int linha_inicio, linha_fim, colunas;
} ArgumentosSoma;

void *somar_matrizes(void *argumento) {
    ArgumentosSoma *args = (ArgumentosSoma *)argumento;
    for (int i = args->linha_inicio; i < args->linha_fim; ++i)
        for (int j = 0; j < args->colunas; ++j)
            args->matrizResultado[i][j] = args->matrizA[i][j] + args->matrizB[i][j];
    pthread_exit(NULL);
}

int **alocar_matriz(int linhas, int colunas) {
    int **matriz = malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; ++i)
        matriz[i] = malloc(colunas * sizeof(int));
    return matriz;
}

void preencher_matriz(int **matriz, int linhas, int colunas, const char *nome) {
    printf("Preenchendo a matriz %s:\n", nome);
    for (int i = 0; i < linhas; ++i)
        for (int j = 0; j < colunas; ++j) {
            printf("%s[%d][%d] = ", nome, i, j);
            scanf("%d", &matriz[i][j]);
        }
}

void imprimir_matriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

int main() {
    int linhas, colunas, total_threads;

    printf("Digite o número de linhas e colunas da matriz (N M): ");
    scanf("%d %d", &linhas, &colunas);
    printf("Digite o número de threads: ");
    scanf("%d", &total_threads);

    int **matrizA = alocar_matriz(linhas, colunas);
    int **matrizB = alocar_matriz(linhas, colunas);
    int **matrizResultado = alocar_matriz(linhas, colunas);

    preencher_matriz(matrizA, linhas, colunas, "A");
    preencher_matriz(matrizB, linhas, colunas, "B");

    pthread_t threads[total_threads];
    ArgumentosSoma argumentos[total_threads];
    int linhas_por_thread = linhas / total_threads;

    for (int i = 0; i < total_threads; ++i) {
        argumentos[i] = (ArgumentosSoma){
            matrizA, matrizB, matrizResultado,
            i * linhas_por_thread,
            (i == total_threads - 1) ? linhas : (i + 1) * linhas_por_thread,
            colunas
        };
        pthread_create(&threads[i], NULL, somar_matrizes, &argumentos[i]);
    }

    for (int i = 0; i < total_threads; ++i)
        pthread_join(threads[i], NULL);

    printf("Resultado da soma das matrizes:\n");
    imprimir_matriz(matrizResultado, linhas, colunas);

    return 0;
}
