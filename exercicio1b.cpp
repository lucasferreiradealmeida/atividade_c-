/*
 * =====================================================================================
 *
 * Exercício 1 — “Hello World” Paralelo
 * b) Cada thread deve imprimir uma mensagem indicando seu número (omp_get_thread_num())
 * e o total de threads (omp_get_num_threads()).
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

// Inclui a biblioteca de Entrada e Saída Padrão (Standard Input/Output).
// Necessária para a função `printf`, usada para imprimir texto no console.
#include <stdio.h>

// Inclui a biblioteca principal do OpenMP.
// Essencial para o uso de diretivas (`#pragma omp`) e funções (`omp_...`).
#include <omp.h>

// --- Função Principal ---

// Ponto de entrada do programa.
int main() {

    // --- Região Paralela ---

    // A diretiva `#pragma omp parallel` cria uma equipe de threads.
    // O bloco de código `{...}` a seguir será executado por cada uma delas.
    #pragma omp parallel
    {
        // --- Variáveis Privadas ---
        // Estas variáveis são declaradas dentro da região paralela, então cada thread
        // terá sua própria cópia independente.
        int id_da_thread;
        int total_de_threads;

        // --- Coleta de Informações da Thread ---

        // b) Obter o número da thread (ID)
        // A função `omp_get_thread_num` retorna o identificador único da thread
        // que está executando esta linha. Os IDs começam em 0.
        // - Parâmetros: Nenhum.
        // - Retorno: (int) O ID da thread atual.
        id_da_thread = omp_get_thread_num();

        // b) Obter o total de threads na equipe
        // A função `omp_get_num_threads` retorna o número total de threads que
        // estão ativas nesta região paralela.
        // - Parâmetros: Nenhum.
        // - Retorno: (int) A quantidade total de threads.
        total_de_threads = omp_get_num_threads();

        // --- Impressão da Mensagem ---

        // A função `printf` imprime a mensagem final no console.
        // - O primeiro `%d` será substituído pelo valor de `id_da_thread`.
        // - O segundo `%d` será substituído pelo valor de `total_de_threads`.
        // - `\n` cria uma nova linha para manter a saída organizada.
        printf("Ola, sou a thread %d de um total de %d threads.\n", id_da_thread, total_de_threads);

    } // Fim da região paralela.

    return 0; // Indica que o programa terminou com sucesso.
}