#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
private:
    std::string nome;
    int peso;
    int quantidade;

public:
    Item();
    Item(const std::string& nome, int peso, int quantidade);
    std::string getNome() const;
    int getPeso() const;
    int getQuantidade() const;
    int pesoTotal() const;
    void somarQuantidade(int q);
    void retirarQuantidade(int q);
    bool operator<(const Item& outro) const;
};

#endif
