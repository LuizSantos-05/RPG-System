#ifndef SISTEMA_H
#define SISTEMA_H

typedef struct ficha
{
    char nome[100];
    int hp;
    int mp;
    int ca;
} Ficha;

void to_lower_case(char *str);

bool existe_arquivo(const char *nome);

void adicionar_ficha();

void listar_fichas();

int busca_ficha(const char *nome);

int critico(int dano, int mult);

int calcular_dano(int dano, int ca);

void aplicar_dano(Ficha &f, int danoBase);

void alterar_ficha();

#endif