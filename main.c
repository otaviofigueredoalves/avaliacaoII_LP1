#include "memoria.h"
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Retorna 1 para sucesso, 0 para entrada invalida e -1 para fim da entrada. */
static int ler_numero(const char *mensagem, size_t *numero)
{
    char entrada[TAMANHO_ENTRADA];
    char *inicio;
    char *fim;
    printf("%s", mensagem);
    fflush(stdout);
    if (fgets(entrada, sizeof entrada, stdin) == NULL) {
        return -1;
    }
    if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
        int caractere;
        while ((caractere = getchar()) != '\n' && caractere != EOF) {
        }
        return 0;
    }
    inicio = entrada;
    while (isspace((unsigned char)*inicio)) {
        inicio++;
    }
    if (!isdigit((unsigned char)*inicio)) {
        return 0;
    }
    errno = 0;
    uintmax_t valor = strtoumax(inicio, &fim, 10);
    if (errno == ERANGE || valor > SIZE_MAX) {
        return 0;
    }
    while (isspace((unsigned char)*fim)) {
        fim++;
    }
    if (*fim != '\0') {
        return 0;
    }
    *numero = (size_t)valor;
    return 1;
}

int main(void)
{
    GerenciadorMemoria gerenciador;
    inicializar_memoria(&gerenciador);
    for (;;) {
        size_t opcao;
        size_t valor;
        puts("\n========== GERENCIADOR DE MEMORIA ==========\n"
             "1 - Alocar bloco de memoria\n2 - Liberar bloco de memoria\n"
             "3 - Exibir estado da memoria\n4 - Exibir resumo da memoria\n"
             "0 - Encerrar");
        int resultado = ler_numero("Escolha uma opcao: ", &opcao);
        if (resultado == -1) {
            break;
        }
        if (resultado == 0 || opcao > 4) {
            puts("Opcao invalida. Informe um numero de 0 a 4.");
            continue;
        }
        if (opcao == 0) {
            break;
        }
        if (opcao == 1 || opcao == 2) {
            resultado = ler_numero(opcao == 1
                ? "Informe o tamanho do bloco em bytes: "
                : "Informe o identificador do bloco: ", &valor);
            if (resultado == -1) {
                break;
            }
            if (resultado == 0 || valor == 0) {
                puts("Valor invalido. Informe um inteiro positivo.");
                continue;
            }
            if (opcao == 1) {
                alocar_bloco(&gerenciador, valor);
            } else {
                liberar_bloco(&gerenciador, valor);
            }
        } else if (opcao == 3) {
            exibir_estado(&gerenciador);
        } else {
            exibir_resumo(&gerenciador);
        }
    }
    puts("\nLiberando blocos restantes...");
    encerrar_memoria(&gerenciador);
    puts("Todos os recursos foram liberados.\nPrograma encerrado.");
    return EXIT_SUCCESS;
}
