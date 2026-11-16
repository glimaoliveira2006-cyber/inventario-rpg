#include "Persistencia.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdio>

bool Persistencia::carregar(const std::string& caminho, std::string& nomePersonagem, int& limitePeso, std::list<Item>& itens) const {
    std::ifstream arquivo(caminho.c_str());
    if (!arquivo.is_open()) {
        std::ifstream teste(caminho.c_str());
        if (!teste.good() && !teste.is_open()) {
            // verifica se arquivo nao existe
            FILE* f = std::fopen(caminho.c_str(), "r");
            if (f == 0) {
                return false;
            }
            std::fclose(f);
        }
        throw std::runtime_error("Nao foi possivel abrir o arquivo.");
    }

    std::string linha;
    if (!std::getline(arquivo, linha)) {
        throw std::runtime_error("Arquivo invalido.");
    }

    std::size_t pos = linha.find(';');
    if (pos == std::string::npos) {
        throw std::runtime_error("Arquivo invalido.");
    }
    if (linha.find(';', pos + 1) != std::string::npos) {
        throw std::runtime_error("Arquivo invalido.");
    }

    nomePersonagem = linha.substr(0, pos);
    std::string limiteStr = linha.substr(pos + 1);
    if (nomePersonagem.empty() || limiteStr.empty()) {
        throw std::runtime_error("Arquivo invalido.");
    }
    if (nomePersonagem.find(';') != std::string::npos) {
        throw std::runtime_error("Arquivo invalido.");
    }

    std::istringstream issLimite(limiteStr);
    if (!(issLimite >> limitePeso)) {
        throw std::runtime_error("Arquivo invalido.");
    }
    std::string resto;
    if (issLimite >> resto) {
        throw std::runtime_error("Arquivo invalido.");
    }
    if (limitePeso <= 0) {
        throw std::runtime_error("Arquivo invalido.");
    }

    itens.clear();
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) {
            throw std::runtime_error("Arquivo invalido.");
        }
        std::size_t p1 = linha.find(';');
        if (p1 == std::string::npos) {
            throw std::runtime_error("Arquivo invalido.");
        }
        std::size_t p2 = linha.find(';', p1 + 1);
        if (p2 == std::string::npos) {
            throw std::runtime_error("Arquivo invalido.");
        }
        if (linha.find(';', p2 + 1) != std::string::npos) {
            throw std::runtime_error("Arquivo invalido.");
        }

        std::string nomeItem = linha.substr(0, p1);
        std::string pesoStr = linha.substr(p1 + 1, p2 - p1 - 1);
        std::string qtdStr = linha.substr(p2 + 1);
        if (nomeItem.empty() || pesoStr.empty() || qtdStr.empty()) {
            throw std::runtime_error("Arquivo invalido.");
        }

        int peso = 0;
        int quantidade = 0;
        std::istringstream issPeso(pesoStr);
        std::istringstream issQtd(qtdStr);
        if (!(issPeso >> peso) || !(issQtd >> quantidade)) {
            throw std::runtime_error("Arquivo invalido.");
        }
        std::string r1, r2;
        if ((issPeso >> r1) || (issQtd >> r2)) {
            throw std::runtime_error("Arquivo invalido.");
        }
        if (peso <= 0 || quantidade <= 0) {
            throw std::runtime_error("Arquivo invalido.");
        }

        itens.push_back(Item(nomeItem, peso, quantidade));
    }

    return true;
}

void Persistencia::salvar(const std::string& caminho, const std::string& nomePersonagem, int limitePeso, const std::list<Item>& itens) const {
    std::ofstream arquivo(caminho.c_str());
    if (!arquivo.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo.");
    }

    arquivo << nomePersonagem << ";" << limitePeso << std::endl;
    std::list<Item>::const_iterator it;
    for (it = itens.begin(); it != itens.end(); ++it) {
        arquivo << it->getNome() << ";" << it->getPeso() << ";" << it->getQuantidade() << std::endl;
    }

    if (!arquivo.good()) {
        throw std::runtime_error("Erro ao salvar o arquivo.");
    }
}
