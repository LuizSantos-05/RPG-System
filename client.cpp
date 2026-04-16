#include <iostream>
#include "sistema.h"
using namespace std;

int main()
{
    int op;

    do
    {
        cout << "\n|=================================|\n\n";
        cout << "1 -> Criar ficha\n";
        cout << "2 -> Listar fichas\n";
        cout << "3 -> Alterar ficha\n";
        cout << "0 -> Sair\n";
        cout << ">> ";
        cin >> op;

        switch (op)
        {
        case 1:
            adicionar_ficha();
            break;
        case 2:
            listar_fichas();
            break;
        case 3:
            alterar_ficha();
            break;
        }

    } while (op != 0);

    return 0;
}