/*
 * =====================================================================================
 *
 * Exercício 4 — Medindo tempo por thread
 * Adapte o código do exercício anterior para:
 * a) Medir e exibir o tempo total de execução.
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

#include <stdio.h>   // Para a função `printf`.
#include <stdlib.h>  // Para `malloc` e `free`.
#include <omp.h>     // Essencial para OpenMP e para a função de tempo `omp_get_wtime()`.

// --- Constantes ---

#define TAMANHO 1000000

// --- Função Principal ---

int main() {
    // --- Alocação e Inicialização dos Vetores ---
    double *a, *x, *y, *z;
    a = (double *) malloc(TAMANHO * sizeof(double));
    x = (double *) malloc(TAMANHO * sizeof(double));
    y = (double *) malloc(TAMANHO * sizeof(double));
    z = (double *) malloc(TAMANHO * sizeof(double));

    // Variáveis para medir o tempo de execução total.
    double tempo_inicio_total, tempo_fim_total;

    // Inicializa os vetores de entrada com valores de exemplo.
    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;
        y[i] = i * 0.2;
        z[i] = i * 0.3;
    }

    // --- a) Medindo o Tempo Total de Execução da Região Paralela ---

    // A função `omp_get_wtime()` (wall time) retorna o tempo de relógio (tempo real)
    // decorrido, em segundos e com alta precisão.
    // Capturamos o tempo EXATAMENTE ANTES de iniciar a computação paralela.
    tempo_inicio_total = omp_get_wtime();

    // Início da região paralela. O OpenMP cria a equipe de threads aqui.
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < TAMANHO; i++) {
        // As iterações deste loop são divididas entre as threads.
        a[i] = (x[i] * x[i]) + (y[i] * y[i]) + (z[i] * z[i]);
    }
    // Fim da região paralela. O programa espera aqui até que TODAS as threads
    // tenham concluído suas tarefas.

    // Capturamos o tempo EXATAMENTE DEPOIS que a computação paralela terminou.
    tempo_fim_total = omp_get_wtime();

    // A diferença entre o tempo final e o inicial nos dá a duração total que
    // a seção paralela levou para ser executada do ponto de vista do usuário.
    // Esta é a resposta para o item 'a'.
    printf("a) Tempo total de execucao: %f segundos\n", tempo_fim_total - tempo_inicio_total);


    // --- Liberação da Memória ---
    free(a);
    free(x);
    free(y);
    free(z);

    return 0; // Fim do programa.
}