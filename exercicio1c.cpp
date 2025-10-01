/*
 * =====================================================================================
 *
 * Exercício 1 — “Hello World” Paralelo
 * c) Configure o programa para rodar com 4 threads.
 *
 * Este código é a solução completa para o Exercício 1, combinando os itens a, b e c.
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

// Inclui a biblioteca de Entrada e Saída Padrão (Standard Input/Output).
// Necessária para a função `printf`.
#include <stdio.h>

// Inclui a biblioteca principal do OpenMP.
// Essencial para o uso de diretivas (`#pragma omp`) e funções (`omp_...`).
#include <omp.h>

// --- Função Principal ---

int main() {

    // --- Configuração do Número de Threads ---

    // c) Configure o programa para rodar com 4 threads.
    // A função `omp_set_num_threads` define programaticamente o número de threads
    // que serão criadas e utilizadas na próxima região paralela.
    //
    // Parâmetros:
    //   - int num_threads: Um número inteiro que especifica a quantidade de threads.
    //
    // Ao chamar esta função com o valor 4, garantimos que o bloco de código
    // paralelo será executado por EXATAMENTE quatro threads.
    omp_set_num_threads(4);

    // --- Região Paralela ---

    // a) A diretiva `#pragma omp parallel` cria a equipe de 4 threads.
    // O bloco de código `{...}` a seguir será executado por cada uma delas.
    #pragma omp parallel
    {
        // Declaração de variáveis que serão privadas para cada thread.
        int id_da_thread;
        int total_de_threads;

        // b) Cada thread obtém seu número e o total de threads na equipe.

        // `omp_get_thread_num()` retorna o ID da thread atual (de 0 a 3).
        id_da_thread = omp_get_thread_num();

        // `omp_get_num_threads()` retorna o total de threads na equipe (que será 4).
        total_de_threads = omp_get_num_threads();

        // A mensagem final é impressa por cada uma das 4 threads.
        printf("Ola, sou a thread %d de um total de %d threads.\n", id_da_thread, total_de_threads);

    } // Fim da região paralela.

    return 0; // Indica que o programa terminou com sucesso.
}