#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "pacientes.dat"

typedef struct {
    int id;
    char nome[50];
    char telefone[15];
    char endereco[80];
    char cpf[15];
} Paciente;

int proximoId() {
    FILE *f = fopen(ARQUIVO, "rb");
    int id = 1;
    Paciente p;
    if (!f) return id;
    while (fread(&p, sizeof(Paciente), 1, f)) id = p.id + 1;
    fclose(f);
    return id;
}

void cadastrar() {
    FILE *f = fopen(ARQUIVO, "ab");
    Paciente p;
    p.id = proximoId();
    printf("\n--- CADASTRAR PACIENTE (ID: %d) ---\n", p.id);
    printf("Nome: ");      scanf(" %[^\n]", p.nome);
    printf("Telefone: ");  scanf(" %[^\n]", p.telefone);
    printf("Endereco: ");  scanf(" %[^\n]", p.endereco);
    printf("CPF: ");       scanf(" %[^\n]", p.cpf);
    fwrite(&p, sizeof(Paciente), 1, f);
    fclose(f);
    printf("Paciente cadastrado com sucesso!\n");
}

void listar() {
    FILE *f = fopen(ARQUIVO, "rb");
    Paciente p;
    if (!f) { printf("Nenhum paciente cadastrado.\n"); return; }
    printf("\n%-5s %-25s %-15s %-30s %-15s\n", "ID", "NOME", "TELEFONE", "ENDERECO", "CPF");
    printf("%-5s %-25s %-15s %-30s %-15s\n", "-----", "-------------------------", "---------------", "------------------------------", "---------------");
    while (fread(&p, sizeof(Paciente), 1, f))
        printf("%-5d %-25s %-15s %-30s %-15s\n", p.id, p.nome, p.telefone, p.endereco, p.cpf);
    fclose(f);
}

void excluir() {
    int id; Paciente p;
    printf("\nID do paciente a excluir: "); scanf("%d", &id);
    FILE *f = fopen(ARQUIVO, "rb"), *tmp = fopen("temp.dat", "wb");
    int found = 0;
    if (!f) { printf("Nenhum paciente cadastrado.\n"); return; }
    while (fread(&p, sizeof(Paciente), 1, f))
        if (p.id != id) fwrite(&p, sizeof(Paciente), 1, tmp); else found = 1;
    fclose(f); fclose(tmp);
    remove(ARQUIVO); rename("temp.dat", ARQUIVO);
    printf(found ? "Paciente excluido!\n" : "ID nao encontrado.\n");
}

int main() {
    int op;
    do {
        printf("\n=== HOSPITAL - GESTAO DE PACIENTES ===\n");
        printf("1. Cadastrar paciente\n2. Listar pacientes\n3. Excluir paciente\n0. Sair\nOpcao: ");
        scanf("%d", &op);
        if (op == 1) cadastrar();
        else if (op == 2) listar();
        else if (op == 3) excluir();
    } while (op != 0);
    return 0;
}
