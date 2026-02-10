#include "reservas.h"

// Função para limpar o lixo do buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Reserva* adicionarReserva(Reserva *lista, int *qtd, int *capacidade) {
    // Lógica de Realloc: Se encheu, aumenta +10
    if (*qtd == *capacidade) {
        int novaCapacidade = (*capacidade == 0) ? 10 : *capacidade + 10;
        
        // Tenta aumentar a memória
        Reserva *temp = (Reserva*) realloc(lista, novaCapacidade * sizeof(Reserva));
        
        if (temp == NULL) {
            printf("Erro: Memoria cheia!\n");
            return lista; // Retorna a lista antiga sem mudar nada
        }
        
        lista = temp; // Atualiza o endereço
        *capacidade = novaCapacidade;
        printf("DEBUG: Capacidade aumentada para %d.\n", *capacidade);
    }

    // Adiciona na posição livre (no final)
    int i = *qtd; 
    lista[i].id = i + 1; // ID sequencial simples

    printf("\n--- Nova Reserva ---\n");
    
    printf("Informe o ID do laboratorio desejado: ");
    limparBuffer(); 
    scanf("%[^\n]", lista[i].laboratorio);

    printf("Solicitante: ");
    limparBuffer();
    scanf("%[^\n]", lista[i].solicitante);

    printf("Data: ");
    scanf("%s", lista[i].data);

    (*qtd)++; // Incrementa a quantidade
    printf("Sucesso! ID: %d\n", lista[i].id);

    return lista; // Retorna o novo endereço da lista
}

void listarReservas(Reserva *lista, int qtd) {
    if (qtd == 0) {
        printf("\nNenhuma reserva cadastrada.\n");
        return;
    }
    printf("\n--- Lista ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d | Lab: %s | Solicitante: %s | Data: %s\n", 
               lista[i].id, lista[i].laboratorio, lista[i].solicitante, lista[i].data);
    }
}

void removerReserva(Reserva *lista, int *qtd) {
    if (*qtd == 0){
        pritnf ("\n Nenhuma reserva para remover.\n");
        return;
    }
    printf ("\n Informe a reserva que deseja remover (ID): ");
    listarReservas(lista, *qtd);

    int id, encontrado = 0;
    scanf("%d", &id);

    if (id < encontrado || id > *qtd){
        printf ("\n ID nao encontrado.\n");
        return;
    }
   
}

void salvarArquivo(Reserva *lista, int qtd) {
    FILE *f = fopen("dados.txt", "w");
    if (f == NULL) {
        printf("Erro ao salvar!\n");
        return;
    }
    
    fprintf(f, "%d\n", qtd); // Salva a quantidade primeiro
    
    for (int i = 0; i < qtd; i++) {
        // Salva um dado por linha (mais fácil de ler)
        fprintf(f, "%d\n", lista[i].id);
        fprintf(f, "%s\n", lista[i].laboratorio);
        fprintf(f, "%s\n", lista[i].solicitante);
        fprintf(f, "%s\n", lista[i].data);
    }
    fclose(f);
    printf("Dados salvos.\n");
}

Reserva* carregarArquivo(int *qtd, int *capacidade) {
    FILE *f = fopen("dados.txt", "r");
    if (f == NULL) return NULL; // Se não existe arquivo, retorna NULL

    fscanf(f, "%d", qtd);
    *capacidade = *qtd + 10; // Já aloca com uma folga
    
    Reserva *lista = (Reserva*) malloc((*capacidade) * sizeof(Reserva));

    for (int i = 0; i < *qtd; i++) {
        fscanf(f, "%d", &lista[i].id);
        fgetc(f); // Tira o enter
        fscanf(f, "%[^\n]", lista[i].laboratorio);
        fgetc(f);
        fscanf(f, "%[^\n]", lista[i].solicitante);
        fscanf(f, "%s", lista[i].data);
    }
    fclose(f);
    printf("Carregados %d registros.\n", *qtd);
    return lista;
}