#include <stdio.h>
#include <string.h>

#define MAX 100
#define ARQUIVO_PACIENTES  "pacientes.dat"
#define ARQUIVO_MEDICOS    "medicos.dat"
#define ARQUIVO_CONSULTAS  "consultas.dat"

/* ================= STRUCTS ================= */

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

/* ================= ARRAYS GLOBAIS ================= */

Paciente pacientes[MAX];
Medico medicos[MAX];
Consulta consultas[MAX];

int totalPacientes = 0;
int totalMedicos = 0;
int totalConsultas = 0;

/* ================= PROTÓTIPOS ================= */

void cadastrarPaciente(void);
void cadastrarMedico(void);
void cadastrarConsulta(void);
void listarPacientes(void);
void listarMedicos(void);
void listarConsultas(void);

void salvarPacientes(void);
void salvarMedicos(void);
void salvarConsultas(void);

void carregarPacientes(void);
void carregarMedicos(void);
void carregarConsultas(void);

void excluirArquivos(void);

/* ================= CADASTRO ================= */

void cadastrarPaciente(void) {
    Paciente p;

    if (totalPacientes >= MAX) {
        printf("Limite de pacientes atingido!\n");
        return;
    }

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

void cadastrarMedico(void) {
    Medico m;

    if (totalMedicos >= MAX) {
        printf("Limite de medicos atingido!\n");
        return;
    }

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

void cadastrarConsulta(void) {
    Consulta c;

    if (totalConsultas >= MAX) {
        printf("Limite de consultas atingido!\n");
        return;
    }

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

/* ================= LISTAGEM ================= */

void listarPacientes(void) {
    int i;

    if (totalPacientes == 0) {
        printf("\nNenhum paciente cadastrado.\n");
        return;
    }

    printf("\n--- PACIENTES ---\n");
    for (i = 0; i < totalPacientes; i++) {
        printf("ID: %d\n", pacientes[i].id);
        printf("Nome: %s\n", pacientes[i].nome);
        printf("Telefone: %s\n", pacientes[i].telefone);
        printf("Nascimento: %s\n", pacientes[i].data_nascimento);
        printf("Endereco: %s\n", pacientes[i].endereco);
        printf("-------------------------\n");
    }
}

void listarMedicos(void) {
    int i;

    if (totalMedicos == 0) {
        printf("\nNenhum medico cadastrado.\n");
        return;
    }

    printf("\n--- MEDICOS ---\n");
    for (i = 0; i < totalMedicos; i++) {
        printf("ID: %d\n", medicos[i].id);
        printf("Nome: %s\n", medicos[i].nome);
        printf("CRM: %d\n", medicos[i].crm);
        printf("Especialidade: %s\n", medicos[i].especialidade);
        printf("-------------------------\n");
    }
}

void listarConsultas(void) {
    int i;

    if (totalConsultas == 0) {
        printf("\nNenhuma consulta cadastrada.\n");
        return;
    }

    printf("\n--- CONSULTAS ---\n");
    for (i = 0; i < totalConsultas; i++) {
        printf("ID Consulta: %d\n", consultas[i].id);
        printf("ID Paciente: %d\n", consultas[i].id_paciente);
        printf("ID Medico: %d\n", consultas[i].id_medico);
        printf("Data: %s\n", consultas[i].data);
        printf("Hora: %s\n", consultas[i].hora);
        printf("Motivo: %s\n", consultas[i].motivo);
        printf("-------------------------\n");
    }
}

/* ================= SALVAR EM ARQUIVO ================= */

/*
 * fopen(nome, "wb") — abre para escrita binaria. Cria o arquivo se nao existir,
 *                     ou sobrescreve se ja existir.
 * fwrite(&total, sizeof(int), 1, arq) — grava primeiro o total de registros.
 * fwrite(array,  sizeof(struct), total, arq) — grava todos os registros de uma vez.
 * fclose(arq) — fecha e descarrega o buffer para o disco.
 */

void salvarPacientes(void) {
    FILE *arq = fopen(ARQUIVO_PACIENTES, "wb");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo de pacientes para salvar!\n");
        return;
    }

    fwrite(&totalPacientes, sizeof(int), 1, arq);
    fwrite(pacientes, sizeof(Paciente), totalPacientes, arq);

    fclose(arq);
    printf("Pacientes salvos em '%s'.\n", ARQUIVO_PACIENTES);
}

void salvarMedicos(void) {
    FILE *arq = fopen(ARQUIVO_MEDICOS, "wb");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo de medicos para salvar!\n");
        return;
    }

    fwrite(&totalMedicos, sizeof(int), 1, arq);
    fwrite(medicos, sizeof(Medico), totalMedicos, arq);

    fclose(arq);
    printf("Medicos salvos em '%s'.\n", ARQUIVO_MEDICOS);
}

void salvarConsultas(void) {
    FILE *arq = fopen(ARQUIVO_CONSULTAS, "wb");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo de consultas para salvar!\n");
        return;
    }

    fwrite(&totalConsultas, sizeof(int), 1, arq);
    fwrite(consultas, sizeof(Consulta), totalConsultas, arq);

    fclose(arq);
    printf("Consultas salvas em '%s'.\n", ARQUIVO_CONSULTAS);
}

/* ================= CARREGAR DE ARQUIVO ================= */

/*
 * fopen(nome, "rb") — abre para leitura binaria. Retorna NULL se nao existir.
 * fread(&total, sizeof(int), 1, arq) — le o total de registros gravado antes.
 * fread(array,  sizeof(struct), total, arq) — le todos os registros de uma vez.
 */

void carregarPacientes(void) {
    FILE *arq = fopen(ARQUIVO_PACIENTES, "rb");

    if (arq == NULL) {
        /* Arquivo ainda nao existe — normal na primeira execucao */
        return;
    }

    fread(&totalPacientes, sizeof(int), 1, arq);
    fread(pacientes, sizeof(Paciente), totalPacientes, arq);

    fclose(arq);
    printf("Pacientes carregados de '%s'.\n", ARQUIVO_PACIENTES);
}

void carregarMedicos(void) {
    FILE *arq = fopen(ARQUIVO_MEDICOS, "rb");

    if (arq == NULL) {
        return;
    }

    fread(&totalMedicos, sizeof(int), 1, arq);
    fread(medicos, sizeof(Medico), totalMedicos, arq);

    fclose(arq);
    printf("Medicos carregados de '%s'.\n", ARQUIVO_MEDICOS);
}

void carregarConsultas(void) {
    FILE *arq = fopen(ARQUIVO_CONSULTAS, "rb");

    if (arq == NULL) {
        return;
    }

    fread(&totalConsultas, sizeof(int), 1, arq);
    fread(consultas, sizeof(Consulta), totalConsultas, arq);

    fclose(arq);
    printf("Consultas carregadas de '%s'.\n", ARQUIVO_CONSULTAS);
}

/* ================= EXCLUIR ARQUIVOS ================= */

/*
 * remove(nome) — funcao da stdlib que deleta um arquivo do disco.
 * Retorna 0 em sucesso, diferente de 0 em erro.
 */

void excluirArquivos(void) {
    int confirmacao;

    printf("\nTem certeza? Isso apagara TODOS os dados salvos em disco!\n");
    printf("1 - Sim, apagar\n");
    printf("0 - Cancelar\n");
    printf("Escolha: ");
    scanf("%d", &confirmacao);

    if (confirmacao != 1) {
        printf("Operacao cancelada.\n");
        return;
    }

    if (remove(ARQUIVO_PACIENTES) == 0)
        printf("Arquivo '%s' excluido.\n", ARQUIVO_PACIENTES);
    else
        printf("Nao foi possivel excluir '%s' (pode nao existir).\n", ARQUIVO_PACIENTES);

    if (remove(ARQUIVO_MEDICOS) == 0)
        printf("Arquivo '%s' excluido.\n", ARQUIVO_MEDICOS);
    else
        printf("Nao foi possivel excluir '%s' (pode nao existir).\n", ARQUIVO_MEDICOS);

    if (remove(ARQUIVO_CONSULTAS) == 0)
        printf("Arquivo '%s' excluido.\n", ARQUIVO_CONSULTAS);
    else
        printf("Nao foi possivel excluir '%s' (pode nao existir).\n", ARQUIVO_CONSULTAS);

    /* Limpa os arrays em memoria tambem */
    totalPacientes = 0;
    totalMedicos   = 0;
    totalConsultas = 0;

    printf("Dados em memoria limpos.\n");
}

/* ================= MENU ================= */

int main(void) {
    int opcao;

    /* Carrega dados salvos ao iniciar o programa */
    carregarPacientes();
    carregarMedicos();
    carregarConsultas();

    do {
        printf("\n===== SISTEMA CLINICA =====\n");
        printf("1 - Cadastrar Paciente\n");
        printf("2 - Cadastrar Medico\n");
        printf("3 - Marcar Consulta\n");
        printf("4 - Listar Pacientes\n");
        printf("5 - Listar Medicos\n");
        printf("6 - Listar Consultas\n");
        printf("7 - Salvar todos os dados\n");
        printf("8 - Excluir arquivos de dados\n");
        printf("0 - Salvar e Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarPaciente(); break;
            case 2: cadastrarMedico();   break;
            case 3: cadastrarConsulta(); break;
            case 4: listarPacientes();   break;
            case 5: listarMedicos();     break;
            case 6: listarConsultas();   break;
            case 7:
                salvarPacientes();
                salvarMedicos();
                salvarConsultas();
                break;
            case 8: excluirArquivos(); break;
            case 0:
                salvarPacientes();
                salvarMedicos();
                salvarConsultas();
                printf("Saindo...\n");
                break;
            default: printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
