#include <iostream>
#include <string>
#include "Item.hpp"
#include "Personagem.hpp"

int main() {
    std::string nome;
    int limite;
    std::cout << "Nome do personagem: ";
    std::cin >> nome;
    std::cout << "Limite de peso: ";
    std::cin >> limite;

    Personagem personagem(nome, limite);
    std::cout << "Personagem: " << personagem.getNome()
              << ", limite de peso " << personagem.getLimitePeso() << std::endl;

    Item item("Espada", 3, 2);
    std::cout << "Item: " << item.getNome()
              << " - peso " << item.getPeso()
              << " - quantidade " << item.getQuantidade() << std::endl;
    std::cout << "Peso total do item: " << item.pesoTotal() << std::endl;

    return 0;
}
