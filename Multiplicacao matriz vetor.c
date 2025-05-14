#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int **matriz;
    int *vetor;
    int *resultado;
    int linha_inicio, linha_fim, tamanho;
} ArgumentosMultiplicacao;

void *multiplicar_matriz_vetor(void *argumento) {
    ArgumentosMultiplicacao *args = (ArgumentosMultiplicacao *)argumento;
    for (int i = args->linha_inicio; i < args->linha_fim; ++i) {
        args->resultado[i] = 0;
        for (int j = 0; j < args->tamanho; ++j)
            args->resultado[i] += args->matriz[i][j] * args->vetor[j];
    }
    pthread_exit(NULL);
}

int main() {
    int tamanho, total_threads;

    printf("Digite a ordem da matriz quadrada (N): ");
    scanf("%d", &tamanho);
    printf("Digite o número de threads: ");
    scanf("%d", &total_threads);

    int **matriz = malloc(tamanho * sizeof(int *));
    int *vetor = malloc(tamanho * sizeof(int));
    int *resultado = malloc(tamanho * sizeof(int));

    for (int i = 0; i < tamanho; ++i)
        matriz[i] = malloc(tamanho * sizeof(int));

    printf("Preenchendo a matriz:\n");
    for (int i = 0; i < tamanho; ++i)
        for (int j = 0; j < tamanho; ++j) {
            printf("matriz[%d][%d] = ", i, j);
            scanf("%d", &matriz[i][j]);
        }

    printf("Preenchendo o vetor:\n");
    for (int i = 0; i < tamanho; ++i) {
        printf("vetor[%d] = ", i);
        scanf("%d", &vetor[i]);
    }

    pthread_t threads[total_threads];
    ArgumentosMultiplicacao argumentos[total_threads];
    int linhas_por_thread = tamanho / total_threads;

    for (int i = 0; i < total_threads; ++i) {
        argumentos[i] = (ArgumentosMultiplicacao){
            matriz, vetor, resultado,
            i * linhas_por_thread,
            (i == total_threads - 1) ? tamanho : (i + 1) * linhas_por_thread,
            tamanho
        };
        pthread_create(&threads[i], NULL, multiplicar_matriz_vetor, &argumentos[i]);
    }

    for (int i = 0; i < total_threads; ++i)
        pthread_join(threads[i], NULL);

    printf("Resultado da multiplicação da matriz pelo vetor:\n");
    for (int i = 0; i < tamanho; ++i)
        printf("%d\n", resultado[i]);

    return 0;
}
