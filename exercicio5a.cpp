/*
 * =====================================================================================
 *
 * Exercício 5 — Escalonamento
 * Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
 * a) Execute com schedule(static) e schedule(dynamic, 1000).
 *
 * =====================================================================================
 */

// --- Inclusão de Bibliotecas ---

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// --- Constantes ---

#define TAMANHO 1000000

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

    double tempo_inicio, tempo_fim;
    printf("Comparando politicas de escalonamento (schedule)...\n\n");


    // --- a) Execução com schedule(static) ---

    tempo_inicio = omp_get_wtime();

    // A cláusula `schedule(static)` define a estratégia de divisão de trabalho.
    //
    // - Como funciona: As 1.000.000 de iterações são divididas em blocos de
    //   tamanho igual (ou quase igual) e distribuídas para as threads ANTES do
    //   loop começar. É uma distribuição fixa e pré-determinada.
    // - Vantagem: Baixíssima sobrecarga (overhead), pois a decisão é tomada uma única vez.
    // - Ideal para: Loops onde cada iteração leva o mesmo tempo para executar,
    //   exatamente como o nosso caso.
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < TAMANHO; i++) {
        a[i] = (x[i] * x[i]) + (y[i] * y[i]) + (z[i] * z[i]);
    }

    tempo_fim = omp_get_wtime();
    printf("Tempo com schedule(static):   %f segundos\n", tempo_fim - tempo_inicio);


    // --- a) Execução com schedule(dynamic, 1000) ---

    tempo_inicio = omp_get_wtime();

    // A cláusula `schedule(dynamic, 1000)` define uma estratégia dinâmica.
    //
    // - Como funciona: As 1.000.000 de iterações são divididas em pequenos "pedaços"
    //   (chunks) de tamanho 1000. As threads ficam em uma fila; quando uma thread
    //   fica livre, ela pega o próximo "pedaço" de 1000 iterações disponível e o executa.
    //   Isso continua até que todos os pedaços tenham sido processados.
    // - Vantagem: Ótimo balanceamento de carga. Se algumas iterações forem mais lentas
    //   que outras, as threads mais rápidas podem simplesmente pegar mais trabalho.
    // - Desvantagem: Maior sobrecarga (overhead), pois existe uma coordenação contínua
    //   para distribuir os pedaços de trabalho.
    #pragma omp parallel for schedule(dynamic, 1000)
    for (int i = 0; i < TAMANHO; i++) {
        a[i] = (x[i] * x[i]) + (y[i] * y[i]) + (z[i] * z[i]);
    }

    tempo_fim = omp_get_wtime();
    printf("Tempo com schedule(dynamic, 1000): %f segundos\n", tempo_fim - tempo_inicio);


    // --- Liberação da Memória ---
    free(a); free(x); free(y); free(z);
    return 0;
}