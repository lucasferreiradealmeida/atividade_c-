/*
 * =====================================================================================
 *
 * Exercício 1 — “Hello World” Paralelo
 * a) Crie uma região paralela com #pragma omp parallel.
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

// Inclui a biblioteca de Entrada e Saída Padrão (Standard Input/Output).
// É necessária para usarmos a função `printf`, que serve para imprimir
// texto formatado no console (terminal).
#include <stdio.h>

// Inclui a biblioteca principal do OpenMP.
// É obrigatória para que o compilador reconheça as diretivas (`#pragma omp ...`)
// e as funções do OpenMP.
#include <omp.h>

// --- Função Principal ---

// A função `main` é o ponto de entrada de qualquer programa em C/C++.
// O `int` no início indica que a função retornará um número inteiro ao sistema
// operacional, onde 0 (zero) significa que o programa terminou com sucesso.
int main() {

    // --- Região Paralela ---

    // a) Crie uma região paralela com #pragma omp parallel.
    // A linha abaixo é uma "diretiva" para o compilador. Ela instrui o OpenMP
    // a criar uma equipe de threads (o número padrão geralmente é o de núcleos
    // do seu processador) e fazer com que cada uma delas execute o bloco de código
    // delimitado pelas chaves `{...}` de forma simultânea.
    #pragma omp parallel
    {
        // O código escrito DENTRO deste bloco será executado por CADA thread.

        // Para demonstrar que múltiplas threads estão ativas, vamos fazê-las
        // se identificarem.

        // A função `omp_get_thread_num()` retorna o ID (identificador único) da
        // thread que está executando esta linha. Os IDs começam em 0.
        // - Parâmetros: Nenhum.
        // - Retorno: (int) O ID da thread.
        int id_da_thread = omp_get_thread_num();

        // A função `printf` imprime a mensagem formatada no console.
        // O `%d` é um marcador que será substituído pelo valor da variável `id_da_thread`.
        // O `\n` no final cria uma nova linha.
        printf("Ola da thread %d!\n", id_da_thread);

    } // Fim da região paralela. Aqui, o programa espera todas as threads terminarem
      // antes de continuar para a próxima linha.

    // Esta linha será executada apenas uma vez, pela thread principal, após
    // o fim da região paralela.
    printf("A execucao paralela terminou.\n");

    return 0; // Retorna 0, indicando sucesso.
}