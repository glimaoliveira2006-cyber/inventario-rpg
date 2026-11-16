#ifndef PERSISTENCIA_HPP
#define PERSISTENCIA_HPP

#include <string>
#include <list>
#include "Item.hpp"

class Persistencia {
public:
    bool carregar(const std::string& caminho, std::string& nomePersonagem, int& limitePeso, std::list<Item>& itens) const;
    void salvar(const std::string& caminho, const std::string& nomePersonagem, int limitePeso, const std::list<Item>& itens) const;
};

#endif
