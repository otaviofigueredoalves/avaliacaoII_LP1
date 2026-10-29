# Gerenciador de memória

Programa interativo em C para alocar e liberar blocos de memória, consultar o estado dos blocos e visualizar o total de bytes atualmente alocados. Ao encerrar, libera os blocos restantes e os registros internos.

## Requisitos

- Compilador C com suporte a C11, como GCC ou Clang.
- GNU Make.
- Terminal em Linux, macOS ou WSL.

## Como executar

Abra um terminal na pasta do projeto e execute:

```sh
make
make run
```

O comando `make` compila o projeto e gera o executável `gerenciador_memoria`. O comando `make run` também compila automaticamente caso seja necessário. Depois de compilar, você pode executar diretamente:

```sh
./gerenciador_memoria
```

No menu, digite a opção desejada e pressione Enter:

| Opção | Ação |
| --- | --- |
| `1` | Alocar um bloco, informando o tamanho em bytes. |
| `2` | Liberar um bloco, informando o identificador exibido na alocação. |
| `3` | Exibir os registros e o estado de cada bloco. |
| `4` | Exibir a quantidade de blocos e os bytes atualmente alocados. |
| `0` | Liberar os recursos e encerrar. |

Por exemplo, escolha `1`, informe `64`, consulte o resumo com `4` e libere o bloco escolhendo `2` e informando o identificador recebido.

## Comandos de compilação

```sh
make                   # Compilar
make run               # Compilar e executar
make clean             # Remover objetos e executável
make CC=clang          # Compilar com Clang
```

Para trocar de compilador ou de opções após uma compilação, execute `make clean` antes. Exemplo com informações de depuração:

```sh
make clean
make CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -g -O0'
```

Se não tiver Make, compile diretamente:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -O2 main.c memoria.c -o gerenciador_memoria
./gerenciador_memoria
```

## Arquivos

- `main.c`: menu e validação das entradas.
- `memoria.c`: alocação, liberação e consultas de memória.
- `memoria.h`: estruturas e declarações das funções.
- `Makefile`: comandos de compilação, execução e limpeza.
