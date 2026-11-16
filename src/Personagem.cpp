#include "Personagem.hpp"
#include <stdexcept>

Personagem::Personagem(const std::string& nome, int limitePeso)
    : nome(nome), limitePeso(limitePeso) {
    if (nome.find(';') != std::string::npos) {
        throw std::invalid_argument("Nome invalido.");
    }
}

std::string Personagem::getNome() const {
    return nome;
}

int Personagem::getLimitePeso() const {
    return limitePeso;
}
