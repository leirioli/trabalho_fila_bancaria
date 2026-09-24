#include <iostream>
#include <string>
#include "FilaBanco.h"

using namespace std;

int main() {
    FilaBanco fila;
    int opcao = 0;

    do {
        cout << "\n========================================" << endl;
        cout << "          ATENDIMENTO BANCARIO" << endl;
        cout << "========================================" << endl;
        cout << "1. Gerar Senha" << endl;
        cout << "2. Chamar Proximo Cliente" << endl;
        cout << "3. Consultar Proximo Cliente" << endl;
        cout << "4. Buscar Cliente por Senha" << endl;
        cout << "5. Exibir Fila de Atendimento" << endl;
        cout << "6. Exibir Quantidade de Clientes Aguardando" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        // Trata entradas inválidas no cin
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nPor favor, digite um numero valido." << endl;
            continue;
        }

        cin.ignore(); // Limpa o buffer do teclado para leitura de strings

        switch (opcao) {
            case 1: {
                string nome, servico;
                cout << "Digite o nome do cliente: ";
                getline(cin, nome);
                cout << "Digite o tipo de serviço solicitado: ";
                getline(cin, servico);
                fila.enfileirar(nome, servico);
                break;
            }
            case 2:
                fila.atenderCliente();
                break;
            case 3:
                fila.consultarProximo();
                break;
            case 4: {
                int senha;
                cout << "Digite o numero da senha a buscar: ";
                cin >> senha;
                fila.buscarPorSenha(senha);
                break;
            }
            case 5:
                fila.exibirFila();
                break;
            case 6:
                fila.exibirQuantidade();
                break;
            case 0:
                cout << "\nEncerrando o programa..." << endl;
                break;
            default:
                cout << "\nOpção invalida! Tente novamente." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}
}