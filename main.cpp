#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdexcept>

class Produto {
public:
    Produto(int id, const std::string& nome, int quantidade, double preco)
        : id(id), nome(nome), quantidade(quantidade), preco(preco) {}

    int getId() const { return id; }
    std::string getNome() const { return nome; }
    int getQuantidade() const { return quantidade; }
    double getPreco() const { return preco; }

    void setQuantidade(int novaQuantidade) { quantidade = novaQuantidade; }
    void setPreco(double novoPreco) { preco = novoPreco; }

    std::string toString() const {
        std::ostringstream oss;
        oss << id << "," << nome << "," << quantidade << "," << preco;
        return oss.str();
    }

private:
    int id;
    std::string nome;
    int quantidade;
    double preco;
};

class Estoque {
public:
    void adicionarProduto(const Produto& produto) {
        for (const auto& p : produtos) {
            if (p.getId() == produto.getId()) {
                throw std::runtime_error("Erro: ID já existe!");
            }
        }
        produtos.push_back(produto);
    }

    void removerProduto(int id) {
        for (auto it = produtos.begin(); it != produtos.end(); ++it) {
            if (it->getId() == id) {
                produtos.erase(it);
                return;
            }
        }
        throw std::runtime_error("Erro: Produto não encontrado!");
    }

    void atualizarProduto(int id, int novaQuantidade, double novoPreco) {
        for (auto& produto : produtos) {
            if (produto.getId() == id) {
                produto.setQuantidade(novaQuantidade);
                produto.setPreco(novoPreco);
                return;
            }
        }
        throw std::runtime_error("Erro: Produto não encontrado!");
    }

    const std::vector<Produto>& getProdutos() const { return produtos; }

    void carregarProdutos(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return; // Arquivo não existe, nada a carregar
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int id, quantidade;
            double preco;
            std::string nome;

            if (std::getline(iss, line, ',') && (std::istringstream(line) >> id) &&
                std::getline(iss, nome, ',') &&
                std::getline(iss, line, ',') && (std::istringstream(line) >> quantidade) &&
                std::getline(iss, line) && (std::istringstream(line) >> preco)) {
                adicionarProduto(Produto(id, nome, quantidade, preco));
            }
        }
    }

    void salvarProdutos(const std::string& filename) const {
        std::ofstream file(filename);
        for (const auto& produto : produtos) {
            file << produto.toString() << "\n";
        }
    }

private:
    std::vector<Produto> produtos;
};

class MyApp : public Gtk::Window {
public:
    MyApp() {
    set_title("Gerenciamento de Estoque");
    set_default_size(600, 600); // Tamanho padrão da janela

    vbox.set_spacing(5);
    add(vbox);

    // Criar uma box horizontal para os botões
    Gtk::Box* button_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
    button_box->set_spacing(5);

    id_entry.set_placeholder_text("ID");
    nome_entry.set_placeholder_text("Nome");
    quantidade_entry.set_placeholder_text("Quantidade");
    preco_entry.set_placeholder_text("Preço");
    
    vbox.pack_start(id_entry);
    vbox.pack_start(nome_entry);
    vbox.pack_start(quantidade_entry);
    vbox.pack_start(preco_entry);

    button_add.set_label("Adicionar Produto");
    button_add.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::on_button_add_clicked));
    button_box->pack_start(button_add, true, true);

    button_remove.set_label("Remover Produto");
    button_remove.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::on_button_remove_clicked));
    button_box->pack_start(button_remove, true, true);

    button_update.set_label("Atualizar Produto");
    button_update.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::on_button_update_clicked));
    button_box->pack_start(button_update, true, true);

    button_list.set_label("Listar Produtos");
    button_list.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::on_button_list_clicked));
    button_box->pack_start(button_list, true, true);

    button_exit.set_label("Sair");
    button_exit.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::on_button_exit_clicked));
    button_box->pack_start(button_exit, true, true);

    vbox.pack_start(*button_box, false, false); // Não expande para preencher

    // Adicionando ScrolledWindow
    Gtk::ScrolledWindow* scrolled_window = new Gtk::ScrolledWindow();
    scrolled_window->set_vexpand(true);
    scrolled_window->set_hexpand(true);
    text_output.set_wrap_mode(Gtk::WRAP_WORD);
    scrolled_window->add(text_output);
    vbox.pack_start(*scrolled_window, true, true); // Expansão configurada

    estoque.carregarProdutos("estoque.txt");

    show_all_children();
}



private:
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL};
    Gtk::Entry id_entry, nome_entry, quantidade_entry, preco_entry;
    Gtk::Button button_add, button_remove, button_update, button_list, button_exit;
    Gtk::TextView text_output;
    Estoque estoque;

    void on_button_add_clicked() {
        try {
            int id = std::stoi(id_entry.get_text());
            std::string nome = nome_entry.get_text();
            int quantidade = std::stoi(quantidade_entry.get_text());
            double preco = std::stod(preco_entry.get_text());

            Produto novoProduto(id, nome, quantidade, preco);
            estoque.adicionarProduto(novoProduto);
            text_output.get_buffer()->set_text("Produto adicionado: " + nome);
        } catch (const std::invalid_argument& e) {
            text_output.get_buffer()->set_text("Erro: Entrada inválida!");
        } catch (const std::out_of_range& e) {
            text_output.get_buffer()->set_text("Erro: Valor fora do intervalo!");
        } catch (const std::runtime_error& e) {
            text_output.get_buffer()->set_text(e.what());
        }
    }

    void on_button_remove_clicked() {
        try {
            int id = std::stoi(id_entry.get_text());
            estoque.removerProduto(id);
            text_output.get_buffer()->set_text("Produto removido com sucesso!");
        } catch (const std::invalid_argument& e) {
            text_output.get_buffer()->set_text("Erro: Entrada inválida!");
        } catch (const std::out_of_range& e) {
            text_output.get_buffer()->set_text("Erro: Valor fora do intervalo!");
        } catch (const std::runtime_error& e) {
            text_output.get_buffer()->set_text(e.what());
        }
    }

    void on_button_update_clicked() {
        try {
            int id = std::stoi(id_entry.get_text());
            int novaQuantidade = std::stoi(quantidade_entry.get_text());
            double novoPreco = std::stod(preco_entry.get_text());

            estoque.atualizarProduto(id, novaQuantidade, novoPreco);
            text_output.get_buffer()->set_text("Produto atualizado com sucesso!");
        } catch (const std::invalid_argument& e) {
            text_output.get_buffer()->set_text("Erro: Entrada inválida!");
        } catch (const std::out_of_range& e) {
            text_output.get_buffer()->set_text("Erro: Valor fora do intervalo!");
        } catch (const std::runtime_error& e) {
            text_output.get_buffer()->set_text(e.what());
        }
    }

    void on_button_list_clicked() {
        std::ostringstream oss;
        const auto& produtos = estoque.getProdutos();
        for (const auto& produto : produtos) {
            oss << produto.getId() << ": " << produto.getNome() << " - "
                << produto.getQuantidade() << " - R$ " << produto.getPreco() << "\n";
        }

        if (oss.str().empty()) {
            oss << "Nenhum produto cadastrado.";
        }
        
        text_output.get_buffer()->set_text(oss.str());
    }

    void on_button_exit_clicked() {
        estoque.salvarProdutos("estoque.txt");
        hide(); // Fecha a janela
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "com.example.gtkmm");
    MyApp window;
    return app->run(window);
}
