#ifndef MEMORIA_H
#define MEMORIA_H

#include <stddef.h>

#define CAPACIDADE_INICIAL 8
#define TAMANHO_ENTRADA 128

typedef struct {
    size_t id;
    void *endereco;
    size_t tamanho;
    int ocupado;
} BlocoMemoria;

typedef struct {
    BlocoMemoria *blocos;
    size_t quantidade;
    size_t capacidade;
    size_t bytes_alocados;
} GerenciadorMemoria;

void inicializar_memoria(GerenciadorMemoria *gerenciador);
int alocar_bloco(GerenciadorMemoria *gerenciador, size_t tamanho);
int liberar_bloco(GerenciadorMemoria *gerenciador, size_t id);
void exibir_estado(const GerenciadorMemoria *gerenciador);
void exibir_resumo(const GerenciadorMemoria *gerenciador);
void encerrar_memoria(GerenciadorMemoria *gerenciador);

#endif
