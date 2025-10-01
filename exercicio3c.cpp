/*
 * =====================================================================================
 *
 * Exercício 3 — Expressão Vetorial
 * Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
 * c) Mostre o tempo total de execução em cada versão.
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

#include <stdio.h>   // Para a função `printf`.
#include <stdlib.h>  // Para `malloc` e `free`.
#include <omp.h>     // Essencial para OpenMP, incluindo a função de tempo `omp_get_wtime()`.

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

    // Variáveis para armazenar os tempos de início e fim.
    double tempo_inicio, tempo_fim;

    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;
        y[i] = i * 0.2;
        z[i] = i * 0.3;
    }

    // --- c) Medindo e Mostrando o Tempo da Versão Sequencial ---

    // A função `omp_get_wtime()` (wall time) da biblioteca OpenMP retorna o tempo
    // de relógio (tempo real) decorrido em segundos, com alta precisão.
    // - Parâmetros: Nenhum.
    // - Retorno: (double) O tempo atual em segundos.
    // Guardamos o tempo exato antes de iniciar o cálculo.
    tempo_inicio = omp_get_wtime();

    // Loop sequencial (item a)
    for (int i = 0; i < TAMANHO; i++) {
        a[i] = (x[i] * x[i]) + (y[i] * y[i]) + (z[i] * z[i]);
    }

    // Capturamos o tempo exato após o término do cálculo.
    tempo_fim = omp_get_wtime();

    // A diferença `tempo_fim - tempo_inicio` nos dá a duração total do loop.
    // Imprimimos este valor, que é a resposta para o item 'c' para a versão sequencial.
    printf("Tempo total de execucao (Sequencial): %f segundos\n", tempo_fim - tempo_inicio);


    // --- c) Medindo e Mostrando o Tempo da Versão Paralela ---

    // Repetimos o processo para a versão paralela.
    tempo_inicio = omp_get_wtime();

    // Loop paralelo (item b)
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < TAMANHO; i++) {
        a[i] = (x[i] * x[i]) + (y[i] * y[i]) + (z[i] * z[i]);
    }

    tempo_fim = omp_get_wtime();

    // Imprimimos a duração do loop paralelo, que é a resposta para o item 'c'
    // para a versão paralela.
    printf("Tempo total de execucao (Paralelo):   %f segundos\n", tempo_fim - tempo_inicio);


    // --- Liberação da Memória ---
    free(a);
    free(x);
    free(y);
    free(z);

    return 0;
}