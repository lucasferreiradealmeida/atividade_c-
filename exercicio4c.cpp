/*
 * =====================================================================================
 *
 * Exercício 4 — Medindo tempo por thread
 * Adapte o código do exercício anterior para:
 * c) Mostrar quantas threads foram utilizadas no cálculo.
 *
 * Este código é a solução final para o Exercício 4 (itens a, b, c).
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// --- Constantes ---

#define TAMANHO 1000000
#define MAX_THREADS 16

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

    double tempo_inicio_total, tempo_fim_total;
    double tempos_threads[MAX_THREADS] = {0.0};
    int num_threads_usadas;


    // --- Medição de Tempo Total e por Thread ---

    tempo_inicio_total = omp_get_wtime();

    #pragma omp parallel
    {
        int id_thread = omp_get_thread_num();
        double inicio_thread, fim_thread;

        // A diretiva `#pragma omp master` garante que este bloco de código
        // seja executado apenas pela thread mestre (thread de ID 0).
        #pragma omp master
        {
            // c) Capturando o número de threads utilizadas.
            // A função `omp_get_num_threads()` retorna o número total de threads
            // que estão ativas na equipe paralela.
            // Colocamos essa atribuição dentro do bloco 'master' para garantir que
            // a variável `num_threads_usadas` seja escrita apenas uma vez,
            // de forma segura.
            num_threads_usadas = omp_get_num_threads();
        }

        inicio_thread = omp_get_wtime();

        // O trabalho do loop `for` é dividido entre as threads da equipe.
        #pragma omp for schedule(static)
        for (int i = 0; i < TAMANHO; i++) {
            a[i] = (x[i] * x[i]) + (y[i] * y[i]) + (z[i] * z[i]);
        }

        fim_thread = omp_get_wtime();

        // Cada thread armazena seu tempo gasto na sua respectiva posição no array.
        tempos_threads[id_thread] = fim_thread - inicio_thread;

    } // Fim da região paralela

    tempo_fim_total = omp_get_wtime();

    // --- Exibição dos Resultados (Itens a, b, c) ---

    // a) Exibe o tempo total de execução.
    printf("a) Tempo total de execucao: %f segundos\n", tempo_fim_total - tempo_inicio_total);

    // c) Exibe o número de threads que foram utilizadas no cálculo.
    printf("c) Threads utilizadas no calculo: %d\n", num_threads_usadas);

    // b) Exibe o tempo gasto individualmente por cada thread.
    printf("\nb) Tempo gasto por cada thread:\n");
    for (int i = 0; i < num_threads_usadas; i++) {
        printf("   - Thread %d: %f segundos\n", i, tempos_threads[i]);
    }


    // --- Liberação da Memória ---
    free(a); free(x); free(y); free(z);
    return 0;
}