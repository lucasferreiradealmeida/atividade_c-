/*
 * =====================================================================================
 *
 * Exercício 5 — Escalonamento
 * Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
 * b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// --- Constantes ---

#define TAMANHO 1000000

// --- Função Principal ---

int main() {
    // --- Alocação e Inicialização ---
    double *a, *x, *y, *z;
    a = (double *) malloc(TAMANHO * sizeof(double));
    x = (double *) malloc(TAMANHO * sizeof(double));
    y = (double *) malloc(TAMANHO * sizeof(double));
    z = (double *) malloc(TAMANHO * sizeof(double));

    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;
        y[i] = i * 0.2;
        z[i] = i * 0.3;
    }

    double tempo_inicio, tempo_fim;

    // b) Array que define as diferentes quantidades de threads que vamos usar para a comparação.
    int threads_para_testar[] = {2, 4, 8};
    // Calcula quantos testes faremos com base no tamanho do array acima.
    int num_testes = sizeof(threads_para_testar) / sizeof(threads_para_testar[0]);

    printf("Iniciando bateria de testes de escalonamento...\n");

    // Loop principal que itera sobre as quantidades de threads (2, 4, 8).
    for (int i = 0; i < num_testes; i++) {
        int n_threads = threads_para_testar[i];

        printf("\n--- Testando com %d threads ---\n", n_threads);

        // Esta é a função chave para este exercício. Antes de cada par de testes,
        // nós a usamos para forçar o OpenMP a criar uma equipe com um número
        // específico de threads (`n_threads`).
        omp_set_num_threads(n_threads);

        // --- Teste com schedule(static) ---
        tempo_inicio = omp_get_wtime();
        #pragma omp parallel for schedule(static)
        for (int j = 0; j < TAMANHO; j++) {
            a[j] = (x[j] * x[j]) + (y[j] * y[j]) + (z[j] * z[j]);
        }
        tempo_fim = omp_get_wtime();
        printf("  - Tempo com schedule(static):   %f segundos\n", tempo_fim - tempo_inicio);

        // --- Teste com schedule(dynamic, 1000) ---
        tempo_inicio = omp_get_wtime();
        #pragma omp parallel for schedule(dynamic, 1000)
        for (int j = 0; j < TAMANHO; j++) {
            a[j] = (x[j] * x[j]) + (y[j] * y[j]) + (z[j] * z[j]);
        }
        tempo_fim = omp_get_wtime();
        printf("  - Tempo com schedule(dynamic): %f segundos\n", tempo_fim - tempo_inicio);
    }

    // --- Liberação da Memória ---
    free(a); free(x); free(y); free(z);
    return 0;
}