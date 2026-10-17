#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>

class Personagem {
private:
    std::string nome;
    int limitePeso;

public:
    Personagem(const std::string& nome, int limitePeso);
    std::string getNome() const;
    int getLimitePeso() const;
};

#endif
