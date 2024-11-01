#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>
#include <iostream>

class Produto {
private:
    int id;
    std::string nome;
    int quantidade;
    double preco;

public:
    // Construtor
    Produto(int id, const std::string& nome, int quantidade, double preco)
        : id(id), nome(nome), quantidade(quantidade), preco(preco) {}

    // Métodos para acessar os atributos
    int getId() const { return id; }
    std::string getNome() const { return nome; }
    int getQuantidade() const { return quantidade; }
    double getPreco() const { return preco; }

    // Métodos para modificar os atributos
    void setQuantidade(int novaQuantidade) { quantidade = novaQuantidade; }
    void setPreco(double novoPreco) { preco = novoPreco; }

    // Exibe as informações do produto
    void exibirProduto() const {
        std::cout << "ID: " << id << "\n";
        std::cout << "Nome: " << nome << "\n";
        std::cout << "Quantidade: " << quantidade << "\n";
        std::cout << "Preço: " << preco << "\n";
    }
};

#endif
