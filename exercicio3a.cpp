/*
 * =====================================================================================
 *
 * Exercício 3 — Expressão Vetorial
 * Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
 * a) Faça a versão sequencial.
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

#include <stdio.h>   // Para a função `printf`.
#include <stdlib.h>  // Para as funções de alocação de memória `malloc` e `free`.

// --- Constantes ---

// Define o tamanho dos vetores para 1 milhão, facilitando a leitura e manutenção.
#define TAMANHO 1000000

// --- Função Principal ---

int main() {

    // --- Alocação Dinâmica dos Vetores ---

    // Declaração de ponteiros. Cada variável irá apontar para o início de um
    // grande bloco de memória que funcionará como nosso vetor.
    // Usamos `double` para armazenar números com casas decimais e com maior precisão.
    double *a, *x, *y, *z;

    // A função `malloc` (memory allocation) aloca um bloco de memória no "heap".
    // É a forma correta de trabalhar com vetores muito grandes.
    //
    // Parâmetro:
    //   - (size_t size): O número total de bytes a serem alocados.
    //
    // `TAMANHO * sizeof(double)` calcula a quantidade exata de bytes necessários
    // para armazenar 1 milhão de números do tipo `double`.
    // O `(double *)` no início é um "cast" (conversão) que ajusta o tipo do ponteiro
    // retornado por `malloc` para o tipo que precisamos (`ponteiro para double`).
    a = (double *) malloc(TAMANHO * sizeof(double));
    x = (double *) malloc(TAMANHO * sizeof(double));
    y = (double *) malloc(TAMANHO * sizeof(double));
    z = (double *) malloc(TAMANHO * sizeof(double));


    // --- Inicialização dos Vetores de Entrada (x, y, z) ---

    // Antes de realizar o cálculo, precisamos preencher os vetores de entrada `x`, `y` e `z`
    // com alguns valores de exemplo. Este loop `for` percorre todos os 1 milhão de
    // elementos para inicializá-los.
    printf("Inicializando vetores de entrada...\n");
    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;
        y[i] = i * 0.2;
        z[i] = i * 0.3;
    }


    // --- a) Implementação do Cálculo Sequencial ---

    printf("Calculando a expressao vetorial (versao sequencial)...\n");

    // Este é o loop sequencial que executa a operação matemática principal.
    // "Sequencial" significa que ele é processado por uma única thread,
    // calculando o resultado para `i=0`, depois `i=1`, `i=2`, e assim por diante, em ordem.
    for (int i = 0; i < TAMANHO; i++) {
        // A expressão `x[i] * x[i]` calcula o quadrado de `x[i]`. É, em geral,
        // mais eficiente do que chamar a função `pow(x[i], 2)` da biblioteca de matemática.
        // O resultado da soma dos três quadrados é armazenado na posição `i`
        // do vetor de resultado `a`.
        a[i] = (x[i] * x[i]) + (y[i] * y[i]) + (z[i] * z[i]);
    }

    printf("Calculo sequencial concluido.\n");

    // --- Verificação (Opcional) ---
    // Imprime o valor calculado para o último elemento para confirmar que o loop rodou até o fim.
    printf("Verificao: a[999999] = %f\n", a[TAMANHO - 1]);


    // --- Liberação da Memória Alocada ---

    // A função `free` libera a memória que foi previamente alocada com `malloc`.
    // É uma prática essencial para evitar "vazamentos de memória" (memory leaks),
    // devolvendo a memória que não será mais usada para o sistema operacional.
    // Devemos chamar `free` para cada `malloc` que fizemos.
    free(a);
    free(x);
    free(y);
    free(z);

    return 0; // Fim do programa.
}