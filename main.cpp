#include <iostream>
#include <string>

using namespace std;

// Estrutura para representar cada nó (Cliente) da Fila
struct Cliente {
    int senha;
    string nome;
    string servico;
    Cliente* proximo;

    Cliente(int s, string n, string sv) 
        : senha(s), nome(n), servico(sv), proximo(nullptr) {}
};

// Classe para gerenciar a Fila de Atendimento Bancário
class FilaBanco {
private:
    Cliente* inicio;
    Cliente* fim;
    int quantidade;
    int proximaSenha;

public:
    FilaBanco() {
        inicio = nullptr;
        fim = nullptr;
        quantidade = 0;
        proximaSenha = 1; // Senhas iniciam em 1
    }

    // Destrutor para liberar toda a memória alocada dinamicamente
    ~FilaBanco() {
        limparFila();
    }

    // 1. Cadastrar um cliente no final da fila e gerar sua senha
    void enfileirar(const string& nome, const string& servico) {
        Cliente* novoCliente = new Cliente(proximaSenha, nome, servico);

        if (estaVazia()) {
            inicio = novoCliente;
            fim = novoCliente;
        } else {
            fim->proximo = novoCliente;
            fim = novoCliente;
        }

        quantidade++;
        cout << "\nCliente cadastrado com sucesso!" << endl;
        cout << "Senha gerada: " << proximaSenha << endl;
        proximaSenha++;
    }

    // 2. Consultar o próximo cliente sem retirá-lo
    void consultarProximo() const {
        if (estaVazia()) {
            cout << "\nNao ha clientes na fila de espera." << endl;
            return;
        }

        cout << "\nPROXIMO CLIENTE A SER ATENDIDO" << endl;
        cout << "Senha:   " << inicio->senha << endl;
        cout << "Nome:    " << inicio->nome << endl;
        cout << "Servico: " << inicio->servico << endl;
    }

    // 3. Chamar e remover o cliente que está no início da fila
    void atenderCliente() {
        if (estaVazia()) {
            cout << "\nNao ha clientes para atender." << endl;
            return;
        }

        Cliente* temp = inicio;
        cout << "CHAMANDO CLIENTE PARA ATENDIMENTO" << endl;
        cout << "Senha:   " << temp->senha << endl;
        cout << "Nome:    " << temp->nome << endl;
        cout << "Servico: " << temp->servico << endl;

        inicio = inicio->proximo;
        delete temp; // Libera a memória do cliente atendido

        quantidade--;

        // Se a fila ficou vazia após o atendimento, reseta o ponteiro do fim
        if (inicio == nullptr) {
            fim = nullptr;
        }
    }

    // 4. Buscar um cliente pelo número da senha, sem alterar a fila
    void buscarPorSenha(int senhaBusca) const {
        if (estaVazia()) {
            cout << "\nA fila esta vazia." << endl;
            return;
        }

        Cliente* atual = inicio;
        int posicao = 1;

        while (atual != nullptr) {
            if (atual->senha == senhaBusca) {
                cout << "\nCLIENTE ENCONTRADO" << endl;
                cout << "Senha:             " << atual->senha << endl;
                cout << "Nome:              " << atual->nome << endl;
                cout << "Servico:           " << atual->servico << endl;
                cout << "Posicao na Fila:   " << posicao << ".o da fila" << endl;
                return;
            }
            atual = atual->proximo;
            posicao++;
        }

        cout << "\nSenha " << senhaBusca << " nao foi encontrada na fila." << endl;
    }

    // 5. Exibir todos os clientes na ordem de atendimento
    void exibirFila() const {
        if (estaVazia()) {
            cout << "\nA fila esta vazia." << endl;
            return;
        }

        cout << "\nFILA DE ESPERA (" << quantidade << " cliente(s))" << endl;
        Cliente* atual = inicio;
        int i = 1;
        while (atual != nullptr) {
            cout << i << ".o -> [Senha: " << atual->senha 
                 << " | Nome: " << atual->nome 
                 << " | Serviço: " << atual->servico << "]" << endl;
            atual = atual->proximo;
            i++;
        }
        cout << "==================================================" << endl;
    }

    // 6. Exibir a quantidade de clientes aguardando
    void exibirQuantidade() const {
        cout << "\nTotal de clientes aguardando na fila: " << quantidade << endl;
    }

    // 7. Informar se a fila está vazia
    bool estaVazia() const {
        return inicio == nullptr;
    }

    // Método para desalocar a memória de toda a fila
    void limparFila() {
        Cliente* atual = inicio;
        while (atual != nullptr) {
            Cliente* proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
        inicio = nullptr;
        fim = nullptr;
        quantidade = 0;
    }
};

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