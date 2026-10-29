#include "memoria.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void inicializar_memoria(GerenciadorMemoria *gerenciador)
{
    *gerenciador = (GerenciadorMemoria){0};
}

int alocar_bloco(GerenciadorMemoria *gerenciador, size_t tamanho)
{
    if (tamanho == 0 || tamanho > SIZE_MAX - gerenciador->bytes_alocados) {
        puts("Tamanho invalido ou total de bytes excedido.");
        return 0;
    }

    if (gerenciador->quantidade == gerenciador->capacidade) {
        size_t limite = SIZE_MAX / sizeof(BlocoMemoria);
        size_t capacidade;
        if (gerenciador->capacidade >= limite) {
            puts("Limite de registros atingido.");
            return 0;
        }
        if (gerenciador->capacidade == 0) {
            capacidade = CAPACIDADE_INICIAL;
        } else {
            capacidade = gerenciador->capacidade > limite / 2
                ? limite : gerenciador->capacidade * 2;
        }
        BlocoMemoria *novo = realloc(gerenciador->blocos,
                                    capacidade * sizeof(BlocoMemoria));
        if (novo == NULL) {
            puts("Falha ao ampliar o vetor de registros.");
            return 0;
        }
        gerenciador->blocos = novo;
        gerenciador->capacidade = capacidade;
    }

    void *endereco = malloc(tamanho);
    if (endereco == NULL) {
        puts("Falha ao alocar o bloco de memoria.");
        return 0;
    }

    size_t id = gerenciador->quantidade + 1;
    gerenciador->blocos[gerenciador->quantidade++] =
        (BlocoMemoria){id, endereco, tamanho, 1};
    gerenciador->bytes_alocados += tamanho;
    printf("Bloco alocado com sucesso!\nIdentificador: %zu\n"
           "Endereco: %p\nTamanho: %zu bytes\nEstado: OCUPADO\n",
           id, endereco, tamanho);
    return 1;
}

int liberar_bloco(GerenciadorMemoria *gerenciador, size_t id)
{
    if (id == 0 || id > gerenciador->quantidade) {
        puts("Identificador inexistente.");
        return 0;
    }
    BlocoMemoria *bloco = &gerenciador->blocos[id - 1];
    if (!bloco->ocupado) {
        puts("O bloco ja esta livre. Liberacao duplicada rejeitada.");
        return 0;
    }
    free(bloco->endereco);
    bloco->endereco = NULL;
    bloco->ocupado = 0;
    gerenciador->bytes_alocados -= bloco->tamanho;
    printf("Bloco %zu liberado com sucesso.\n", id);
    return 1;
}

void exibir_estado(const GerenciadorMemoria *gerenciador)
{
    puts("ID\tENDERECO\tTAMANHO\tESTADO");
    if (gerenciador->quantidade == 0) {
        puts("Nenhum bloco registrado.");
    }
    for (size_t i = 0; i < gerenciador->quantidade; i++) {
        const BlocoMemoria *bloco = &gerenciador->blocos[i];
        printf("%zu\t", bloco->id);
        if (bloco->ocupado) {
            printf("%p", bloco->endereco);
        } else {
            printf("(liberado)");
        }
        printf("\t%zu bytes\t%s\n", bloco->tamanho,
               bloco->ocupado ? "OCUPADO" : "LIVRE");
    }
}

void exibir_resumo(const GerenciadorMemoria *gerenciador)
{
    size_t ocupados = 0;
    for (size_t i = 0; i < gerenciador->quantidade; i++) {
        if (gerenciador->blocos[i].ocupado) {
            ocupados++;
        }
    }
    printf("Total de registros: %zu\nBlocos ocupados: %zu\n"
           "Blocos livres: %zu\nBytes atualmente alocados: %zu\n",
           gerenciador->quantidade, ocupados,
           gerenciador->quantidade - ocupados, gerenciador->bytes_alocados);
}

void encerrar_memoria(GerenciadorMemoria *gerenciador)
{
    for (size_t i = 0; i < gerenciador->quantidade; i++) {
        if (gerenciador->blocos[i].ocupado) {
            free(gerenciador->blocos[i].endereco);
        }
    }
    free(gerenciador->blocos);
    inicializar_memoria(gerenciador);
}
