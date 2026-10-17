#include "Item.hpp"

Item::Item() : nome(""), peso(0), quantidade(0) {
}

Item::Item(const std::string& nome, int peso, int quantidade)
    : nome(nome), peso(peso), quantidade(quantidade) {
}

std::string Item::getNome() const {
    return nome;
}

int Item::getPeso() const {
    return peso;
}

int Item::getQuantidade() const {
    return quantidade;
}

int Item::pesoTotal() const {
    return peso * quantidade;
}

void Item::somarQuantidade(int q) {
    quantidade = quantidade + q;
}

void Item::retirarQuantidade(int q) {
    quantidade = quantidade - q;
}

bool Item::operator<(const Item& outro) const {
    if (peso != outro.peso) {
        return peso < outro.peso;
    }
    return nome < outro.nome;
}
