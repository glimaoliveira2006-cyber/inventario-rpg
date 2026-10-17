#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include <map>
#include <list>
#include <string>
#include "Item.hpp"
#include "Personagem.hpp"

class Inventario {
private:
    Personagem dono;
    std::map<std::string, Item> itens;

public:
    Inventario(const Personagem& dono);
    bool coletar(const std::string& nome, int peso, int quantidade);
    std::list<Item> listar() const;
    int pesoTotal() const;
    bool vazio() const;
};

#endif
