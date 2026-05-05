#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQ_ALUNOS      "alunos.dat"
#define ARQ_PROFESSORES "professores.dat"
#define ARQ_MATRICULAS  "matriculas.dat"
#define ARQ_DISCIPLINAS "disciplinas.dat"

typedef struct {
    int  id;
    char nome[50];
    char cpf[15];
    char telefone[15];
    char endereco[80];
} Aluno;

typedef struct {
    int  id;
    char nome[50];
    char cpf[15];
    char telefone[15];
    char especialidade[50];
} Professor;

typedef struct {
    int  id;
    int  id_aluno;
    int  id_disciplina;
    char ano[5];
    char semestre[2];
} Matricula;

typedef struct {
    int  id;
    char nome[50];
    char codigo[10];
    int  carga_horaria;
} Disciplina;

/* ===== ID AUTOMATICO ===== */

int proximoId(const char *arquivo, size_t tamanho) {
    FILE *f = fopen(arquivo, "rb");
    if (!f) return 1;
    int maior = 0;
    char buf[256];
    while (fread(buf, tamanho, 1, f)) {
        int id;
        memcpy(&id, buf, sizeof(int));
        if (id > maior) maior = id;
    }
    fclose(f);
    return maior + 1;
}

/* ===== BUSCA POR ID ===== */

int buscarPorId(const char *arquivo, size_t tamanho, int id, void *resultado) {
    FILE *f = fopen(arquivo, "rb");
    if (!f) return 0;
    char buf[256];
    while (fread(buf, tamanho, 1, f)) {
        int rid;
        memcpy(&rid, buf, sizeof(int));
        if (rid == id) {
            memcpy(resultado, buf, tamanho);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

/* ===== BUSCA POR NOME ===== */

int buscarPorNome(const char *arquivo, size_t tamanho, const char *nome, void *resultado) {
    FILE *f = fopen(arquivo, "rb");
    if (!f) return 0;
    char buf[256];
    while (fread(buf, tamanho, 1, f)) {
        char *rnome = buf + sizeof(int);
        if (strcasecmp(rnome, nome) == 0) {
            memcpy(resultado, buf, tamanho);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

/* ===== ALUNOS ===== */

void cadastrarAluno() {
    FILE *f = fopen(ARQ_ALUNOS, "ab");
    if (!f) { perror("Erro ao abrir arquivo"); return; }
    Aluno a;
    a.id = proximoId(ARQ_ALUNOS, sizeof(Aluno));
    printf("\n--- CADASTRAR ALUNO (ID: %d) ---\n", a.id);
    printf("Nome: ");      scanf(" %[^\n]", a.nome);
    printf("CPF: ");       scanf(" %[^\n]", a.cpf);
    printf("Telefone: ");  scanf(" %[^\n]", a.telefone);
    printf("Endereco: ");  scanf(" %[^\n]", a.endereco);
    fwrite(&a, sizeof(Aluno), 1, f);
    fclose(f);
    printf("Aluno cadastrado com sucesso! ID: %d\n", a.id);
}

void listarAlunos() {
    FILE *f = fopen(ARQ_ALUNOS, "rb");
    if (!f) { printf("Nenhum aluno cadastrado.\n"); return; }
    Aluno a;
    printf("\n%-5s %-30s %-15s %-15s %-35s\n", "ID", "NOME", "CPF", "TELEFONE", "ENDERECO");
    printf("%-5s %-30s %-15s %-15s %-35s\n", "-----","------------------------------","---------------","---------------","-----------------------------------");
    while (fread(&a, sizeof(Aluno), 1, f))
        printf("%-5d %-30s %-15s %-15s %-35s\n", a.id, a.nome, a.cpf, a.telefone, a.endereco);
    fclose(f);
}

void buscarAluno() {
    int opcao;
    printf("\nBuscar por: 1-ID  2-Nome: ");
    scanf("%d", &opcao);
    Aluno a;
    if (opcao == 1) {
        int id; printf("ID: "); scanf("%d", &id);
        if (buscarPorId(ARQ_ALUNOS, sizeof(Aluno), id, &a))
            printf("Encontrado -> ID:%d | %s | %s | %s | %s\n", a.id, a.nome, a.cpf, a.telefone, a.endereco);
        else printf("Aluno nao encontrado.\n");
    } else {
        char nome[50]; printf("Nome: "); scanf(" %[^\n]", nome);
        if (buscarPorNome(ARQ_ALUNOS, sizeof(Aluno), nome, &a))
            printf("Encontrado -> ID:%d | %s | %s | %s | %s\n", a.id, a.nome, a.cpf, a.telefone, a.endereco);
        else printf("Aluno nao encontrado.\n");
    }
}

void excluirAluno() {
    int id; printf("\nID do aluno a excluir: "); scanf("%d", &id);
    FILE *f = fopen(ARQ_ALUNOS, "rb"), *tmp = fopen("_tmp.dat", "wb");
    if (!f) { printf("Nenhum aluno cadastrado.\n"); return; }
    Aluno a; int found = 0;
    while (fread(&a, sizeof(Aluno), 1, f))
        if (a.id != id) fwrite(&a, sizeof(Aluno), 1, tmp); else found = 1;
    fclose(f); fclose(tmp);
    remove(ARQ_ALUNOS); rename("_tmp.dat", ARQ_ALUNOS);
    printf(found ? "Aluno excluido!\n" : "ID nao encontrado.\n");
}

/* ===== PROFESSORES ===== */

void cadastrarProfessor() {
    FILE *f = fopen(ARQ_PROFESSORES, "ab");
    if (!f) { perror("Erro ao abrir arquivo"); return; }
    Professor p;
    p.id = proximoId(ARQ_PROFESSORES, sizeof(Professor));
    printf("\n--- CADASTRAR PROFESSOR (ID: %d) ---\n", p.id);
    printf("Nome: ");          scanf(" %[^\n]", p.nome);
    printf("CPF: ");           scanf(" %[^\n]", p.cpf);
    printf("Telefone: ");      scanf(" %[^\n]", p.telefone);
    printf("Especialidade: "); scanf(" %[^\n]", p.especialidade);
    fwrite(&p, sizeof(Professor), 1, f);
    fclose(f);
    printf("Professor cadastrado com sucesso! ID: %d\n", p.id);
}

void listarProfessores() {
    FILE *f = fopen(ARQ_PROFESSORES, "rb");
    if (!f) { printf("Nenhum professor cadastrado.\n"); return; }
    Professor p;
    printf("\n%-5s %-30s %-15s %-15s %-25s\n", "ID", "NOME", "CPF", "TELEFONE", "ESPECIALIDADE");
    printf("%-5s %-30s %-15s %-15s %-25s\n", "-----","------------------------------","---------------","---------------","-------------------------");
    while (fread(&p, sizeof(Professor), 1, f))
        printf("%-5d %-30s %-15s %-15s %-25s\n", p.id, p.nome, p.cpf, p.telefone, p.especialidade);
    fclose(f);
}

void buscarProfessor() {
    int opcao;
    printf("\nBuscar por: 1-ID  2-Nome: ");
    scanf("%d", &opcao);
    Professor p;
    if (opcao == 1) {
        int id; printf("ID: "); scanf("%d", &id);
        if (buscarPorId(ARQ_PROFESSORES, sizeof(Professor), id, &p))
            printf("Encontrado -> ID:%d | %s | %s | %s | %s\n", p.id, p.nome, p.cpf, p.telefone, p.especialidade);
        else printf("Professor nao encontrado.\n");
    } else {
        char nome[50]; printf("Nome: "); scanf(" %[^\n]", nome);
        if (buscarPorNome(ARQ_PROFESSORES, sizeof(Professor), nome, &p))
            printf("Encontrado -> ID:%d | %s | %s | %s | %s\n", p.id, p.nome, p.cpf, p.telefone, p.especialidade);
        else printf("Professor nao encontrado.\n");
    }
}

void excluirProfessor() {
    int id; printf("\nID do professor a excluir: "); scanf("%d", &id);
    FILE *f = fopen(ARQ_PROFESSORES, "rb"), *tmp = fopen("_tmp.dat", "wb");
    if (!f) { printf("Nenhum professor cadastrado.\n"); return; }
    Professor p; int found = 0;
    while (fread(&p, sizeof(Professor), 1, f))
        if (p.id != id) fwrite(&p, sizeof(Professor), 1, tmp); else found = 1;
    fclose(f); fclose(tmp);
    remove(ARQ_PROFESSORES); rename("_tmp.dat", ARQ_PROFESSORES);
    printf(found ? "Professor excluido!\n" : "ID nao encontrado.\n");
}

/* ===== DISCIPLINAS ===== */

void cadastrarDisciplina() {
    FILE *f = fopen(ARQ_DISCIPLINAS, "ab");
    if (!f) { perror("Erro ao abrir arquivo"); return; }
    Disciplina d;
    d.id = proximoId(ARQ_DISCIPLINAS, sizeof(Disciplina));
    printf("\n--- CADASTRAR DISCIPLINA (ID: %d) ---\n", d.id);
    printf("Nome: ");          scanf(" %[^\n]", d.nome);
    printf("Codigo: ");        scanf(" %[^\n]", d.codigo);
    printf("Carga horaria: "); scanf("%d", &d.carga_horaria);
    fwrite(&d, sizeof(Disciplina), 1, f);
    fclose(f);
    printf("Disciplina cadastrada com sucesso! ID: %d\n", d.id);
}

void listarDisciplinas() {
    FILE *f = fopen(ARQ_DISCIPLINAS, "rb");
    if (!f) { printf("Nenhuma disciplina cadastrada.\n"); return; }
    Disciplina d;
    printf("\n%-5s %-30s %-10s %-15s\n", "ID", "NOME", "CODIGO", "CARGA HORARIA");
    printf("%-5s %-30s %-10s %-15s\n", "-----","------------------------------","----------","---------------");
    while (fread(&d, sizeof(Disciplina), 1, f))
        printf("%-5d %-30s %-10s %-14dh\n", d.id, d.nome, d.codigo, d.carga_horaria);
    fclose(f);
}

void buscarDisciplina() {
    int opcao;
    printf("\nBuscar por: 1-ID  2-Nome: ");
    scanf("%d", &opcao);
    Disciplina d;
    if (opcao == 1) {
        int id; printf("ID: "); scanf("%d", &id);
        if (buscarPorId(ARQ_DISCIPLINAS, sizeof(Disciplina), id, &d))
            printf("Encontrado -> ID:%d | %s | %s | %dh\n", d.id, d.nome, d.codigo, d.carga_horaria);
        else printf("Disciplina nao encontrada.\n");
    } else {
        char nome[50]; printf("Nome: "); scanf(" %[^\n]", nome);
        if (buscarPorNome(ARQ_DISCIPLINAS, sizeof(Disciplina), nome, &d))
            printf("Encontrado -> ID:%d | %s | %s | %dh\n", d.id, d.nome, d.codigo, d.carga_horaria);
        else printf("Disciplina nao encontrada.\n");
    }
}

void excluirDisciplina() {
    int id; printf("\nID da disciplina a excluir: "); scanf("%d", &id);
    FILE *f = fopen(ARQ_DISCIPLINAS, "rb"), *tmp = fopen("_tmp.dat", "wb");
    if (!f) { printf("Nenhuma disciplina cadastrada.\n"); return; }
    Disciplina d; int found = 0;
    while (fread(&d, sizeof(Disciplina), 1, f))
        if (d.id != id) fwrite(&d, sizeof(Disciplina), 1, tmp); else found = 1;
    fclose(f); fclose(tmp);
    remove(ARQ_DISCIPLINAS); rename("_tmp.dat", ARQ_DISCIPLINAS);
    printf(found ? "Disciplina excluida!\n" : "ID nao encontrado.\n");
}

/* ===== MATRICULAS ===== */

void cadastrarMatricula() {
    FILE *f = fopen(ARQ_MATRICULAS, "ab");
    if (!f) { perror("Erro ao abrir arquivo"); return; }
    Matricula m;
    m.id = proximoId(ARQ_MATRICULAS, sizeof(Matricula));
    printf("\n--- CADASTRAR MATRICULA (ID: %d) ---\n", m.id);
    printf("ID do Aluno: ");       scanf("%d", &m.id_aluno);
    printf("ID da Disciplina: ");  scanf("%d", &m.id_disciplina);
    printf("Ano (ex: 2025): ");    scanf(" %[^\n]", m.ano);
    printf("Semestre (1 ou 2): "); scanf(" %[^\n]", m.semestre);
    fwrite(&m, sizeof(Matricula), 1, f);
    fclose(f);
    printf("Matricula realizada com sucesso! ID: %d\n", m.id);
}

void listarMatriculas() {
    FILE *f = fopen(ARQ_MATRICULAS, "rb");
    if (!f) { printf("Nenhuma matricula cadastrada.\n"); return; }
    Matricula m;
    printf("\n%-5s %-12s %-15s %-6s %-9s\n", "ID", "ID ALUNO", "ID DISCIPLINA", "ANO", "SEMESTRE");
    printf("%-5s %-12s %-15s %-6s %-9s\n", "-----","------------","---------------","------","---------");
    while (fread(&m, sizeof(Matricula), 1, f))
        printf("%-5d %-12d %-15d %-6s %-9s\n", m.id, m.id_aluno, m.id_disciplina, m.ano, m.semestre);
    fclose(f);
}

void excluirMatricula() {
    int id; printf("\nID da matricula a excluir: "); scanf("%d", &id);
    FILE *f = fopen(ARQ_MATRICULAS, "rb"), *tmp = fopen("_tmp.dat", "wb");
    if (!f) { printf("Nenhuma matricula cadastrada.\n"); return; }
    Matricula m; int found = 0;
    while (fread(&m, sizeof(Matricula), 1, f))
        if (m.id != id) fwrite(&m, sizeof(Matricula), 1, tmp); else found = 1;
    fclose(f); fclose(tmp);
    remove(ARQ_MATRICULAS); rename("_tmp.dat", ARQ_MATRICULAS);
    printf(found ? "Matricula excluida!\n" : "ID nao encontrado.\n");
}

/* ===== MENUS ===== */

void menuAlunos() {
    int op;
    do {
        printf("\n--- ALUNOS ---\n");
        printf("1. Cadastrar\n2. Listar\n3. Buscar\n4. Excluir\n0. Voltar\nOpcao: ");
        scanf("%d", &op);
        if      (op == 1) cadastrarAluno();
        else if (op == 2) listarAlunos();
        else if (op == 3) buscarAluno();
        else if (op == 4) excluirAluno();
    } while (op != 0);
}

void menuProfessores() {
    int op;
    do {
        printf("\n--- PROFESSORES ---\n");
        printf("1. Cadastrar\n2. Listar\n3. Buscar\n4. Excluir\n0. Voltar\nOpcao: ");
        scanf("%d", &op);
        if      (op == 1) cadastrarProfessor();
        else if (op == 2) listarProfessores();
        else if (op == 3) buscarProfessor();
        else if (op == 4) excluirProfessor();
    } while (op != 0);
}

void menuDisciplinas() {
    int op;
    do {
        printf("\n--- DISCIPLINAS ---\n");
        printf("1. Cadastrar\n2. Listar\n3. Buscar\n4. Excluir\n0. Voltar\nOpcao: ");
        scanf("%d", &op);
        if      (op == 1) cadastrarDisciplina();
        else if (op == 2) listarDisciplinas();
        else if (op == 3) buscarDisciplina();
        else if (op == 4) excluirDisciplina();
    } while (op != 0);
}

void menuMatriculas() {
    int op;
    do {
        printf("\n--- MATRICULAS ---\n");
        printf("1. Registrar\n2. Listar\n3. Excluir\n0. Voltar\nOpcao: ");
        scanf("%d", &op);
        if      (op == 1) cadastrarMatricula();
        else if (op == 2) listarMatriculas();
        else if (op == 3) excluirMatricula();
    } while (op != 0);
}

/* ===== MAIN ===== */

int main() {
    int op;
    do {
        printf("\n========================================\n");
        printf("   SISTEMA DE GESTAO ESCOLAR\n");
        printf("========================================\n");
        printf("1. Alunos\n");
        printf("2. Professores\n");
        printf("3. Disciplinas\n");
        printf("4. Matriculas\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if      (op == 1) menuAlunos();
        else if (op == 2) menuProfessores();
        else if (op == 3) menuDisciplinas();
        else if (op == 4) menuMatriculas();
    } while (op != 0);
    printf("Encerrando sistema...\n");
    return 0;
}
