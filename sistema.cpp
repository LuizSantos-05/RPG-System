#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <cctype>
#include "sistema.h"
using namespace std;

string nome_arquivo = "fichas.dat";

void to_lower_case(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

// Checa de o arquivo da ficha já existe
bool existe_arquivo(const char *nome)
{
    ifstream f(nome);
    return f.is_open();
}

void adicionar_ficha()
{
    Ficha f;

    // Entrada de nome no arquivo
    cout << "Nome: ";
    cin.ignore();
    cin.getline(f.nome, 100);

    // Evita o algoritmo ser case sensitive
    to_lower_case(f.nome);

    // Evita duplicatas
    if (busca_ficha(f.nome) != -1)
    {
        cout << "\033[31mFicha já existe!\033[0m\n";
        return;
    }

    // Entrada de HP no arquivo
    cout << "HP: ";
    cin >> f.hp;

    // Entrada de MP no arquivo
    cout << "MP: ";
    cin >> f.mp;

    // Entrada de CA no arquivo
    cout << "CA: ";
    cin >> f.ca;

    ofstream arq(nome_arquivo, ios::binary | ios::app);
    arq.write((char *)&f, sizeof(Ficha));
    arq.close();

    cout << "\033[34mFicha Salva!\033[0m\n";
}

void listar_fichas()
{
    ifstream arq(nome_arquivo, ios::binary);

    if (!arq)
    {
        cout << "\033[31mArquivo não encontrado!\n";
        return;
    }
    Ficha f;

    while (arq.read((char *)&f, sizeof(Ficha)))
    {
        cout << "\n|---------------------------------|\n";
        cout << "\033[36mNome: " << f.nome << "\033[0m\n"
             << " \033[31m|HP: " << f.hp << "\033[0m\n"
             << " \033[34m|MP: " << f.mp << "\033[0m\n"
             << " \033[33m|CA: " << f.ca << "\033[0m\n";
    }

    arq.close();
}

int busca_ficha(const char *nome)
{
    ifstream arq(nome_arquivo, ios::binary);

    Ficha f;

    to_lower_case(f.nome);

    int pos = 0;
    while (arq.read((char *)&f, sizeof(Ficha)))
    {
        if (strcmp(f.nome, nome) == 0)
        {
            arq.close();
            return pos;
        }
        pos++;
    }

    arq.close();
    return -1; // Não encontrou
}

// Multiplica o dano pelo multiplicador
int critico(int dano, int mult)
{
    return dano * mult;
}

int calcular_dano(int dano, int ca)
{
    string condicao;
    cout << "Dano foi crítico?\n>> ";
    cin >> condicao;
    if (condicao == "Sim")
    {
        int mult;
        cout << "Qual multiplicador?\n>> ";
        cin >> mult;
        dano = critico(dano, mult);
    }

    int danoFinal = dano - ca;

    if (danoFinal < 0)
        danoFinal = 0;

    return danoFinal;
}

void aplicar_dano(Ficha &f, int danoBase)
{
    int danoFinal = calcular_dano(danoBase, f.ca);

    f.hp -= danoFinal;

    if (f.hp < 0)
        f.hp = 0;

    cout << "Dano recebido: " << danoFinal << "\n";
    cout << "HP restante: " << f.hp << "\n";
}

void alterar_ficha()
{
    int dano;
    char nome[100];
    cout << "Digite o nome da ficha: ";
    cin.ignore();
    cin.getline(nome, 100);

    to_lower_case(nome);

    int pos = busca_ficha(nome);

    if (pos == -1)
    {
        cout << "\033[31mFicha não encontrada!\033[0m\n";
        return;
    }

    fstream arq(nome_arquivo, ios::binary | ios::in | ios::out);

    Ficha f;

    to_lower_case(f.nome);

    // Vai direto na posição da ficha
    arq.seekg(pos * sizeof(Ficha));
    arq.read((char *)&f, sizeof(Ficha));

    int decisao;
    cout << "\n|---------------------------------|\n";
    cout << "O que gostaria de alterar?\n"
         << "0 -> Sair\n"
         << "1 -> Alterar o HP atual\n"
         << "2 -> Alterar o MP atual\n"
         << "3 -> Causar dano\n";
    cin >> decisao;

    switch (decisao)
    {
    case 0:
        return;
        break;
    case 1:
        cout << "\n\nHP atual: " << f.hp << endl;
        cout << "Novo HP: ";
        cin >> f.hp;
        break;
    case 2:
        cout << "\n\nMP atual: " << f.mp << endl;
        cout << "Novo MP: ";
        cin >> f.mp;
        break;
    case 3:
        cout << "\n\nDano causado: ";
        cin >> dano;

        aplicar_dano(f, dano);

        if (f.hp < 20)
        {
            cout << "\n\n\033[31mHP CRÍTICO: " << f.hp << "\033[0m\n";
        }
        else
        {
            cout << "\n\n\033[32mHP: " << f.hp << "\033[0m\n";
        }
        break;
    }
    arq.seekp(pos * sizeof(Ficha));
    arq.write((char *)&f, sizeof(Ficha));
}