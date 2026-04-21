#include <stdio.h>
#include <string.h>

#define MAX 100

// ================= STRUCTS =================

typedef struct {
    int id;
    char nome[50];
    char telefone[20];
    char data_nascimento[15];
    char endereco[100];
} Paciente;

typedef struct {
    int id;
    char nome[50];
    int crm;
    char especialidade[50];
} Medico;

typedef struct {
    int id;
    int id_paciente;
    int id_medico;
    char data[15];
    char hora[10];
    char motivo[100];
} Consulta;

// ================= ARRAYS GLOBAIS =================

Paciente pacientes[MAX];
Medico medicos[MAX];
Consulta consultas[MAX];

int totalPacientes = 0;
int totalMedicos = 0;
int totalConsultas = 0;

// ================= FUNÇÕES =================

void cadastrarPaciente() {
    if (totalPacientes >= MAX) {
        printf("Limite de pacientes atingido!\n");
        return;
    }

    Paciente p;

    printf("\nID: ");
    scanf("%d", &p.id);
    printf("Nome: ");
    scanf(" %[^\n]", p.nome);
    printf("Telefone: ");
    scanf(" %[^\n]", p.telefone);
    printf("Data nascimento (DD/MM/AAAA): ");
    scanf(" %[^\n]", p.data_nascimento);
    printf("Endereco: ");
    scanf(" %[^\n]", p.endereco);

    pacientes[totalPacientes] = p;
    totalPacientes++;

    printf("Paciente cadastrado!\n");
}

void cadastrarMedico() {
    if (totalMedicos >= MAX) {
        printf("Limite de medicos atingido!\n");
        return;
    }

    Medico m;

    printf("\nID: ");
    scanf("%d", &m.id);
    printf("Nome: ");
    scanf(" %[^\n]", m.nome);
    printf("CRM: ");
    scanf("%d", &m.crm);
    printf("Especialidade: ");
    scanf(" %[^\n]", m.especialidade);

    medicos[totalMedicos] = m;
    totalMedicos++;

    printf("Medico cadastrado!\n");
}

void cadastrarConsulta() {
    if (totalConsultas >= MAX) {
        printf("Limite de consultas atingido!\n");
        return;
    }

    Consulta c;

    printf("\nID Consulta: ");
    scanf("%d", &c.id);
    printf("ID Paciente: ");
    scanf("%d", &c.id_paciente);
    printf("ID Medico: ");
    scanf("%d", &c.id_medico);
    printf("Data (DD/MM/AAAA): ");
    scanf(" %[^\n]", c.data);
    printf("Hora (HH:MM): ");
    scanf(" %[^\n]", c.hora);
    printf("Motivo: ");
    scanf(" %[^\n]", c.motivo);

    consultas[totalConsultas] = c;
    totalConsultas++;

    printf("Consulta cadastrada!\n");
}

void listarPacientes() {
    if (totalPacientes == 0) {
        printf("\nNenhum paciente cadastrado.\n");
        return;
    }

    printf("\n--- PACIENTES ---\n");
    for (int i = 0; i < totalPacientes; i++) {
        printf("ID: %d\n", pacientes[i].id);
        printf("Nome: %s\n", pacientes[i].nome);
        printf("Telefone: %s\n", pacientes[i].telefone);
        printf("Nascimento: %s\n", pacientes[i].data_nascimento);
        printf("Endereco: %s\n", pacientes[i].endereco);
        printf("-------------------------\n");
    }
}

void listarMedicos() {
    if (totalMedicos == 0) {
        printf("\nNenhum medico cadastrado.\n");
        return;
    }

    printf("\n--- MEDICOS ---\n");
    for (int i = 0; i < totalMedicos; i++) {
        printf("ID: %d\n", medicos[i].id);
        printf("Nome: %s\n", medicos[i].nome);
        printf("CRM: %d\n", medicos[i].crm);
        printf("Especialidade: %s\n", medicos[i].especialidade);
        printf("-------------------------\n");
    }
}

void listarConsultas() {
    if (totalConsultas == 0) {
        printf("\nNenhuma consulta cadastrada.\n");
        return;
    }

    printf("\n--- CONSULTAS ---\n");
    for (int i = 0; i < totalConsultas; i++) {
        printf("ID Consulta: %d\n", consultas[i].id);
        printf("ID Paciente: %d\n", consultas[i].id_paciente);
        printf("ID Medico: %d\n", consultas[i].id_medico);
        printf("Data: %s\n", consultas[i].data);
        printf("Hora: %s\n", consultas[i].hora);
        printf("Motivo: %s\n", consultas[i].motivo);
        printf("-------------------------\n");
    }
}

// ================= MENU =================

int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA CLINICA =====\n");
        printf("1 - Cadastrar Paciente\n");
        printf("2 - Cadastrar Medico\n");
        printf("3 - Marcar Consulta\n");
        printf("4 - Listar Pacientes\n");
        printf("5 - Listar Medicos\n");
        printf("6 - Listar Consultas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarPaciente(); break;
            case 2: cadastrarMedico(); break;
            case 3: cadastrarConsulta(); break;
            case 4: listarPacientes(); break;
            case 5: listarMedicos(); break;
            case 6: listarConsultas(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
