/*
 * =====================================================================================
 *
 * Exercício 2 — Paralelizando um for simples
 * b) Escreva um loop sequencial que soma todos os elementos.
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

// Inclui a biblioteca de Entrada e Saída Padrão (Standard Input/Output).
// Necessária para a função `printf`.
#include <stdio.h>

// --- Constantes ---

// Define o tamanho do vetor para facilitar a manutenção do código.
#define TAMANHO_VETOR 100

// --- Função Principal ---

int main() {

    // --- a) Criação e Inicialização do Vetor (Pré-requisito) ---

    // Declara um vetor de inteiros com 100 posições.
    int v[TAMANHO_VETOR];

    // Este primeiro loop preenche o vetor, garantindo que cada posição contenha o valor 1.
    // Este passo é o que fizemos no item 'a'.
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        v[i] = 1;
    }
    printf("Vetor de %d posicoes inicializado com o valor 1.\n", TAMANHO_VETOR);


    // --- b) Loop Sequencial para Somar os Elementos ---

    // Declara uma variável para armazenar o resultado da soma.
    // É crucial inicializá-la com 0, que é o elemento neutro da operação de adição.
    // Usamos o tipo `long` por segurança, para garantir que a variável possa
    // armazenar a soma total mesmo que o vetor fosse muito maior.
    long soma = 0;

    // Este é o laço de soma sequencial. "Sequencial" significa que ele é
    // executado em uma única thread (a thread principal do programa), uma
    // iteração de cada vez, em ordem.
    //
    // - `int i = 0;`: Inicia o contador `i` em 0 (primeira posição do vetor).
    // - `i < TAMANHO_VETOR;`: A condição de parada é `i` ser menor que 100.
    // - `i++`: Incrementa `i` ao final de cada iteração.
    for (int i = 0; i < TAMANHO_VETOR; i++) {

        // Em cada iteração do laço, o valor do elemento atual do vetor (v[i])
        // é adicionado ao valor acumulado na variável `soma`.
        // A expressão `soma += v[i]` é um atalho para a escrita `soma = soma + v[i]`.
        soma += v[i];
    }

    // --- Exibição do Resultado ---

    // Ao final do loop, a variável `soma` contém o total de todos os elementos.
    // Usamos a função `printf` para exibir o resultado final no console.
    // O especificador de formato `%ld` é usado para imprimir uma variável do tipo `long`.
    printf("O resultado da soma sequencial e: %ld\n", soma);

    return 0; // Indica que o programa terminou com sucesso.
}