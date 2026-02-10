#ifndef RESERVAS_H
#define RESERVAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da Estrutura
typedef struct {
    int id;
    char laboratorio[50];
    char solicitante[50];
    char data[20];
} Reserva;

// Protótipos das Funções
// Note que algumas retornam "Reserva*" para atualizar a lista na main
Reserva* adicionarReserva(Reserva *lista, int *qtd, int *capacidade);
void listarReservas(Reserva *lista, int qtd);
void removerReserva(Reserva *lista, int *qtd);
void salvarArquivo(Reserva *lista, int qtd);
Reserva* carregarArquivo(int *qtd, int *capacidade);

// Função auxiliar para limpar teclado
void limparBuffer();

#endif