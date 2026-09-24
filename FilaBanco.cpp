#include "FilaBanco.h"
#include <iostream>

using namespace std;

// Construtor
FilaBanco::FilaBanco() {
    inicio = nullptr;
    fim = nullptr;
    quantidade = 0;
    proximaSenha = 1; //Senhas iniciam em 1
}

// Destrutor
FilaBanco::~FilaBanco() {
    limparFila();
}

// 1. Cadastrar um cliente no final da fila e gerar sua senha
void FilaBanco::enfileirar(const string& nome, const string& servico) {
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
void FilaBanco::consultarProximo() const {
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
void FilaBanco::atenderCliente() {
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
void FilaBanco::buscarPorSenha(int senhaBusca) const {
    if (estaVazia()) {
        cout << "\nA fila esta vazia." << endl;
        return;
    }

    Cliente* atual = inicio;
    int posicao = 1;

    while (atual != nullptr) {
        if (atual->senha == senhaBusca) {
            cout << "\nCLIENTE ENCONTRADO" << endl;
            cout << "Senha:           " << atual->senha << endl;
            cout << "Nome:            " << atual->nome << endl;
            cout << "Servico:         " << atual->servico << endl;
            cout << "Posicao na Fila: " << posicao << ".o da fila" << endl;
            return;
        }
        atual = atual->proximo;
        posicao++;
    }

    cout << "\nSenha " << senhaBusca << " nao foi encontrada na fila." << endl;
}

// 5. Exibir todos os clientes na ordem de atendimento
void FilaBanco::exibirFila() const {
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
void FilaBanco::exibirQuantidade() const {
    cout << "\nTotal de clientes aguardando na fila: " << quantidade << endl;
}

// 7. Informar se a fila está vazia
bool FilaBanco::estaVazia() const {
    return inicio == nullptr;
}

// Método para desalocar a memória de toda a fila
void FilaBanco::limparFila() {
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