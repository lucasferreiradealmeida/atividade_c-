/*
 * =====================================================================================
 *
 * Exercício 4 — Medindo tempo por thread
 * Adapte o código do exercício anterior para:
 * b) Medir e exibir o tempo gasto por cada thread.
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// --- Constantes ---

#define TAMANHO 1000000
// Define um número máximo de threads que o programa suportará,
// para podermos criar um array para armazenar os tempos.
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

    // Variável para o tempo total (item a)
    double tempo_inicio_total, tempo_fim_total;

    // b) Array para armazenar o tempo gasto por cada thread individualmente.
    // Cada posição do array corresponderá a uma thread (ex: tempos_threads[0] para a thread 0).
    // É inicializado com 0.0.
    double tempos_threads[MAX_THREADS] = {0.0};
    int num_threads_usadas; // Para guardar o número de threads que foram usadas.


    // --- Medição de Tempo Total e por Thread ---

    tempo_inicio_total = omp_get_wtime();

    // A diretiva `#pragma omp parallel` inicia a região paralela.
    // O código dentro do bloco `{...}` será executado por cada thread.
    // Note que removemos o `for` daqui para ter mais controle dentro do bloco.
    #pragma omp parallel
    {
        // --- Variáveis Privadas para cada Thread ---
        int id_thread = omp_get_thread_num();
        double inicio_thread, fim_thread;

        // A diretiva `#pragma omp master` garante que o código dentro do seu bloco
        // seja executado APENAS pela thread mestre (ID 0).
        // Usamos isso para obter o número total de threads de forma segura,
        // evitando que todas as threads tentem escrever na mesma variável ao mesmo tempo.
        #pragma omp master
        {
            num_threads_usadas = omp_get_num_threads();
        }

        // Cada thread registra seu próprio tempo de início.
        inicio_thread = omp_get_wtime();

        // A diretiva `#pragma omp for` agora está DENTRO da região paralela.
        // Ela distribui as iterações do loop entre as threads que já foram criadas.
        #pragma omp for schedule(static)
        for (int i = 0; i < TAMANHO; i++) {
            a[i] = (x[i] * x[i]) + (y[i] * y[i]) + (z[i] * z[i]);
        }

        // Ao final do loop `for`, existe uma barreira implícita. Todas as threads
        // esperam aqui até que todas as outras tenham terminado suas iterações.

        // Agora, cada thread registra seu próprio tempo de término.
        fim_thread = omp_get_wtime();

        // A duração é calculada e armazenada na posição do array correspondente
        // ao ID desta thread. Como cada thread escreve em uma posição diferente
        // do array (ex: thread 0 escreve em tempos_threads[0], thread 1 em tempos_threads[1]),
        // esta operação é segura e não causa condição de corrida.
        tempos_threads[id_thread] = fim_thread - inicio_thread;

    } // Fim da região paralela

    tempo_fim_total = omp_get_wtime();

    // --- Exibição dos Resultados ---
    printf("a) Tempo total de execucao: %f segundos\n", tempo_fim_total - tempo_inicio_total);
    printf("\nb) Tempo gasto por cada thread:\n");

    // Loop para imprimir o tempo de cada thread que foi utilizada.
    for (int i = 0; i < num_threads_usadas; i++) {
        printf("   - Thread %d: %f segundos\n", i, tempos_threads[i]);
    }


    // --- Liberação da Memória ---
    free(a); free(x); free(y); free(z);
    return 0;
}