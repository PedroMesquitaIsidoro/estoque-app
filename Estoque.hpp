#ifndef ESTOQUE_HPP
#define ESTOQUE_HPP

#include "Produto.hpp"   
#include <vector>
#include <algorithm>
#include <iostream>

class Estoque {
private:
    std::vector<Produto> produtos;


public:

    bool produtoExiste(int id) const {
        for (const auto& produto : produtos) {
            if (produto.getId() == id) {
                return true;
            }
        }
        return false;
    }
    // Adiciona um novo produto ao estoque, caso o ID não exista
    void adicionarProduto(const Produto& produto) {
        if (produtoExiste(produto.getId())) {
            std::cout << "Erro: O produto com ID " << produto.getId() << " já existe no estoque.\n";
        } else {
            produtos.push_back(produto);
            std::cout << "Produto adicionado com sucesso!\n";
        }
    }

    void removerProduto(int id) {
        auto it = std::remove_if(produtos.begin(), produtos.end(),
                                 [id](const Produto& p) { return p.getId() == id; });
        if (it != produtos.end()) {
            produtos.erase(it, produtos.end());
            std::cout << "Produto removido com sucesso!\n";
        } else {
            std::cout << "Erro: Produto com ID " << id << " não encontrado no estoque.\n";
        }
    }

    void atualizarProduto(int id, int novaQuantidade, double novoPreco) {
        for (auto& produto : produtos) {
            if (produto.getId() == id) {
                produto.setQuantidade(novaQuantidade);
                produto.setPreco(novoPreco);
                std::cout << "Produto atualizado com sucesso!\n";
                return;
            }
        }
        std::cout << "Erro: Produto com ID " << id << " não encontrado no estoque.\n";
    }

    void exibirEstoque() const {
        if (produtos.empty()) {
            std::cout << "O estoque está vazio.\n";
        } else {
            for (const auto& produto : produtos) {
                produto.exibirProduto();
                std::cout << "-----------------------\n";
            }
        }
    }
};

#endif
