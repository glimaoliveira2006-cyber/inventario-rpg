#include <iostream>
#include <string>
#include <list>
#include "Item.hpp"
#include "Personagem.hpp"
#include "Inventario.hpp"

void mostrarMenu() {
    std::cout << "1 Coletar" << std::endl;
    std::cout << "2 Usar" << std::endl;
    std::cout << "3 Descartar" << std::endl;
    std::cout << "4 Listar" << std::endl;
    std::cout << "0 Sair" << std::endl;
}

void coletar(Inventario& inventario) {
    std::string nome;
    int peso;
    int quantidade;

    std::cout << "Nome: ";
    std::cin >> nome;
    std::cout << "Peso: ";
    std::cin >> peso;
    std::cout << "Quantidade: ";
    std::cin >> quantidade;

    if (inventario.coletar(nome, peso, quantidade)) {
        std::cout << "Item coletado." << std::endl;
    } else {
        std::cout << "Peso acima do limite." << std::endl;
    }
}

void usar(Inventario& inventario) {
    std::string nome;
    std::cout << "Nome: ";
    std::cin >> nome;

    if (inventario.usar(nome)) {
        std::cout << "Item usado." << std::endl;
    } else {
        std::cout << "Item nao encontrado." << std::endl;
    }
}

void descartar(Inventario& inventario) {
    std::string nome;
    std::cout << "Nome: ";
    std::cin >> nome;

    if (inventario.descartar(nome)) {
        std::cout << "Item descartado." << std::endl;
    } else {
        std::cout << "Item nao encontrado." << std::endl;
    }
}

void listar(const Inventario& inventario, int limite) {
    if (inventario.vazio()) {
        std::cout << "Inventario vazio." << std::endl;
        return;
    }

    std::list<Item> itens = inventario.listar();
    std::list<Item>::const_iterator it;
    for (it = itens.begin(); it != itens.end(); ++it) {
        std::cout << it->getNome() << " - peso " << it->getPeso()
                  << " - quantidade " << it->getQuantidade() << std::endl;
    }
    std::cout << "Peso total: " << inventario.pesoTotal() << " de "
              << limite << std::endl;
}

int main() {
    std::string nome;
    int limite;
    std::cout << "Nome do personagem: ";
    std::cin >> nome;
    std::cout << "Limite de peso: ";
    std::cin >> limite;

    Personagem personagem(nome, limite);
    Inventario inventario(personagem);

    int opcao = -1;
    while (opcao != 0) {
        mostrarMenu();
        std::cout << "Opcao: ";
        std::cin >> opcao;

        if (opcao == 1) {
            coletar(inventario);
        } else if (opcao == 2) {
            usar(inventario);
        } else if (opcao == 3) {
            descartar(inventario);
        } else if (opcao == 4) {
            listar(inventario, personagem.getLimitePeso());
        } else if (opcao == 0) {
            std::cout << "Sair" << std::endl;
        } else {
            std::cout << "Entrada invalida." << std::endl;
        }
    }

    return 0;
}
