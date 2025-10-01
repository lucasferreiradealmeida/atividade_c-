/*
 * =====================================================================================
 *
 * Exercício 2 — Paralelizando um for simples
 * c) Refaça o loop com #pragma omp parallel for reduction(+:soma).
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

#include <stdio.h> // Para a função `printf`.
#include <omp.h>   // Essencial para usar o OpenMP.

// --- Constantes ---

#define TAMANHO_VETOR 100

// --- Função Principal ---

int main() {

    // --- a) Inicialização do Vetor ---
    int v[TAMANHO_VETOR];
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        v[i] = 1;
    }

    // --- b) Soma Sequencial (para comparação) ---
    long soma_sequencial = 0;
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        soma_sequencial += v[i];
    }
    printf("Resultado da soma sequencial: %ld\n", soma_sequencial);


    // --- c) Loop Paralelo com Reduction ---

    // Declara uma nova variável para armazenar o resultado da soma paralela.
    long soma_paralela = 0;

    // Esta é a diretiva que instrui o OpenMP a paralelizar o loop `for` de forma segura.
    //
    // `#pragma omp parallel for`: É uma diretiva combinada que faz duas coisas:
    //   - `parallel`: Cria uma equipe de threads (ex: 4 threads).
    //   - `for`: Distribui as 100 iterações do laço `for` seguinte entre as threads.
    //     Por exemplo, a thread 0 pode pegar as iterações de 0 a 24, a thread 1 de 25 a 49, e assim por diante.
    //
    // `reduction(+:soma_paralela)`: Esta é a cláusula mais importante para operações como a soma.
    //   - O PROBLEMA: Se múltiplas threads tentassem modificar a mesma variável `soma_paralela`
    //     ao mesmo tempo, haveria uma "condição de corrida" (race condition). Uma thread poderia
    //     atrapalhar a outra, levando a um resultado final INCORRETO.
    //   - A SOLUÇÃO do `reduction`:
    //     1. O OpenMP cria uma cópia local (privada) da variável `soma_paralela` para CADA thread.
    //        Essa cópia é inicializada com 0 (o valor neutro para o operador de soma `+`).
    //     2. Cada thread trabalha em suas iterações e atualiza APENAS a sua cópia privada.
    //     3. Ao final do loop, o OpenMP, de forma segura e automática, "reduz" (combina)
    //        os valores de todas as cópias privadas, somando-os, e armazena o resultado
    //        final na variável original `soma_paralela`.
    #pragma omp parallel for reduction(+:soma_paralela)
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        // Cada thread está somando na sua cópia privada de `soma_paralela`.
        soma_paralela += v[i];
    }

    // --- Exibição do Resultado Paralelo ---
    printf("Resultado da soma paralela com reduction: %ld\n", soma_paralela);

    return 0; // Fim do programa.
}