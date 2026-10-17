#include "Personagem.hpp"

Personagem::Personagem(const std::string& nome, int limitePeso)
    : nome(nome), limitePeso(limitePeso) {
}

std::string Personagem::getNome() const {
    return nome;
}

int Personagem::getLimitePeso() const {
    return limitePeso;
}
