#include "Inventario.hpp"

Inventario::Inventario(const Personagem& dono) : dono(dono) {
}

bool Inventario::coletar(const std::string& nome, int peso, int quantidade) {
    std::map<std::string, Item>::iterator it = itens.find(nome);

    int pesoAdicionado;
    if (it != itens.end()) {
        pesoAdicionado = it->second.getPeso() * quantidade;
    } else {
        pesoAdicionado = peso * quantidade;
    }

    if (pesoTotal() + pesoAdicionado > dono.getLimitePeso()) {
        return false;
    }

    if (it != itens.end()) {
        it->second.somarQuantidade(quantidade);
    } else {
        itens[nome] = Item(nome, peso, quantidade);
    }

    return true;
}

bool Inventario::usar(const std::string& nome) {
    std::map<std::string, Item>::iterator it = itens.find(nome);
    if (it == itens.end()) {
        return false;
    }

    it->second.retirarQuantidade(1);
    if (it->second.getQuantidade() == 0) {
        itens.erase(it);
    }

    return true;
}

bool Inventario::descartar(const std::string& nome) {
    std::map<std::string, Item>::iterator it = itens.find(nome);
    if (it == itens.end()) {
        return false;
    }

    itens.erase(it);
    return true;
}

bool Inventario::buscar(const std::string& nome, Item& resultado) const {
    std::map<std::string, Item>::const_iterator it = itens.find(nome);
    if (it == itens.end()) {
        return false;
    }

    resultado = it->second;
    return true;
}

std::list<Item> Inventario::listar() const {
    std::list<Item> copia;
    std::map<std::string, Item>::const_iterator it;
    for (it = itens.begin(); it != itens.end(); ++it) {
        copia.push_back(it->second);
    }
    copia.sort();
    return copia;
}

int Inventario::pesoTotal() const {
    int total = 0;
    std::map<std::string, Item>::const_iterator it;
    for (it = itens.begin(); it != itens.end(); ++it) {
        total = total + it->second.pesoTotal();
    }
    return total;
}

bool Inventario::vazio() const {
    return itens.empty();
}
