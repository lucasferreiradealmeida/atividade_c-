/*
 * =====================================================================================
 *
 * Exercício 2 — Paralelizando um for simples
 * a) Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

// Inclui a biblioteca de Entrada e Saída Padrão (Standard Input/Output).
// Necessária para a função `printf`, que usaremos para verificar o conteúdo do vetor.
#include <stdio.h>

// --- Constantes ---

// Usar uma constante para o tamanho do vetor é uma boa prática de programação.
// Facilita a leitura do código e, se precisarmos mudar o tamanho depois,
// só alteramos em um lugar.
#define TAMANHO_VETOR 100

// --- Função Principal ---

int main() {

    // --- a) Criação e Inicialização do Vetor ---

    // Declara um vetor (array) de números inteiros chamado `v`.
    // Os colchetes `[]` indicam que é um vetor, e `TAMANHO_VETOR` define
    // que ele terá 100 posições (de 0 a 99).
    int v[TAMANHO_VETOR];

    // Este laço `for` é usado para percorrer o vetor e preencher seus valores.
    //
    // - `int i = 0;`: Inicia uma variável de controle `i` com o valor 0.
    // - `i < TAMANHO_VETOR;`: O laço continuará executando enquanto `i` for menor que 100.
    // - `i++`: Ao final de cada execução do laço, o valor de `i` é incrementado em 1.
    //
    // Assim, `i` assumirá os valores 0, 1, 2, ..., até 99, que são exatamente
    // os índices do nosso vetor.
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        // Para cada posição `i` do vetor `v`, atribuímos o valor inteiro 1.
        v[i] = 1;
    }

    // --- Verificação (Opcional, mas recomendado) ---
    // O código abaixo serve apenas para confirmar que o vetor foi preenchido corretamente.
    printf("Vetor inicializado. Exibindo os 10 primeiros elementos para verificacao:\n");
    for (int i = 0; i < 10; i++) {
        // Imprime o índice (posição) e o valor contido naquela posição.
        // `v[%d]` mostrará a posição e `= %d` mostrará o valor.
        printf("v[%d] = %d\n", i, v[i]);
    }

    return 0; // Indica que o programa terminou com sucesso.
}