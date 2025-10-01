/*
 * =====================================================================================
 *
 * Exercício 3 — Expressão Vetorial
 * Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
 * b) Paralelize com #pragma omp parallel for schedule(static).
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

    // --- Alocação Dinâmica dos Vetores ---
    double *a, *x, *y, *z;
    a = (double *) malloc(TAMANHO * sizeof(double));
    x = (double *) malloc(TAMANHO * sizeof(double));
    y = (double *) malloc(TAMANHO * sizeof(double));
    z = (double *) malloc(TAMANHO * sizeof(double));

    // Variáveis para medir o tempo de execução.
    double tempo_inicio, tempo_fim;

    // --- Inicialização dos Vetores de Entrada ---
    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;
        y[i] = i * 0.2;
        z[i] = i * 0.3;
    }

    // --- a) Execução e Medição da Versão Sequencial (para comparação) ---

    printf("Iniciando calculo sequencial...\n");

    // A função `omp_get_wtime()` retorna o tempo atual em segundos com alta precisão.
    // Guardamos o tempo exato de início do cálculo.
    tempo_inicio = omp_get_wtime();

    for (int i = 0; i < TAMANHO; i++) {
        a[i] = (x[i] * x[i]) + (y[i] * y[i]) + (z[i] * z[i]);
    }

    // Guardamos o tempo exato de término.
    tempo_fim = omp_get_wtime();
    printf("Tempo de execucao sequencial: %f segundos\n", tempo_fim - tempo_inicio);


    // --- b) Execução e Medição da Versão Paralela ---

    printf("\nIniciando calculo paralelo com schedule(static)...\n");

    tempo_inicio = omp_get_wtime();

    // Esta é a diretiva de paralelização para o loop `for`.
    //
    // `#pragma omp parallel for`: Diretiva combinada que cria uma equipe de threads
    // e divide as iterações do loop seguinte entre elas.
    //
    // `schedule(static)`: Esta cláusula define a ESTRATÉGIA de divisão do trabalho.
    //   - Como funciona: O OpenMP divide as 1.000.000 de iterações em blocos de
    //     tamanho aproximadamente igual (chunks) e entrega um bloco para cada thread
    //     ANTES do loop começar. Por exemplo, com 4 threads, a thread 0 ficaria
    //     com as iterações 0-249999, a thread 1 com 250000-499999, e assim por diante.
    //   - Vantagem: É a estratégia com menor sobrecarga (overhead), pois a divisão
    //     é feita apenas uma vez. É ideal para loops como este, onde cada iteração
    //     leva praticamente o mesmo tempo para ser executada.
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < TAMANHO; i++) {
        a[i] = (x[i] * x[i]) + (y[i] * y[i]) + (z[i] * z[i]);
    }

    tempo_fim = omp_get_wtime();
    printf("Tempo de execucao paralela: %f segundos\n", tempo_fim - tempo_inicio);


    // --- Liberação da Memória Alocada ---
    free(a);
    free(x);
    free(y);
    free(z);

    return 0; // Fim do programa.
}