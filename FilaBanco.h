#ifndef FILABANCO_H
#define FILABANCO_H

#include <string>

// Estrutura para representar cada nó (Cliente) da Fila
struct Cliente {
    int senha;
    std::string nome;
    std::string servico;
    Cliente* proximo;

    Cliente(int s, std::string n, std::string sv) 
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
    FilaBanco();
    ~FilaBanco();

    void enfileirar(const std::string& nome, const std::string& servico);
    void consultarProximo() const;
    void atenderCliente();
    void buscarPorSenha(int senhaBusca) const;
    void exibirFila() const;
    void exibirQuantidade() const;
    bool estaVazia() const;
    void limparFila();
};

#endif // FILABANCO_H