# Simulador de cache

## Como executar

Num ambiente Linux, a partir da raíz do projeto, compile com:

```makefile
make
```

Executando:

```bash
./cache_simulator <nsets> <bsize> <assoc> <policy> <flag> <file>
```

Exemplo:

```bash
./cache_simulator 32 32 4 L 1 bin_1000.bin
```

Rodando todos os testes:

```makefile
make test
```

Somente testes unitários:

```makefile
make test-unit
```

Somente testes de integração

```makefile
make test-ci
