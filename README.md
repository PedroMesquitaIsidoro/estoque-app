# estoque-app

Um aplicativo de gerenciamento de estoque em C++ usando GTKmm.

## Descrição

O `estoque-app` é um software simples que permite gerenciar produtos em estoque, incluindo funcionalidades como adicionar, remover e atualizar produtos, bem como listar todos os itens disponíveis. Este projeto foi desenvolvido utilizando a biblioteca GTKmm para interface gráfica e é uma excelente introdução ao desenvolvimento de aplicativos com C++.

## Funcionalidades

- **Adicionar Produtos**: Permite ao usuário adicionar novos produtos ao estoque.
- **Remover Produtos**: Possibilita a remoção de produtos existentes.
- **Atualizar Produtos**: O usuário pode atualizar a quantidade e o preço dos produtos.
- **Listar Produtos**: Exibe todos os produtos cadastrados no estoque.

## Tecnologias

- **Linguagem**: C++
- **Biblioteca**: GTKmm

## Pré-requisitos

Antes de executar o aplicativo, você precisa ter o GTKmm instalado em seu sistema. 

### No Ubuntu, você pode instalar com:

```bash
sudo apt-get install libgtkmm-3.0-dev


git clone https://github.com/PedroMesquitaIsidoro/estoque-app.git
cd estoque-app

g++ -o estoque main.cpp Estoque.cpp Produto.cpp `pkg-config --cflags --libs gtkmm-3.0`

./estoque
