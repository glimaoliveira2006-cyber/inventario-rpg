#include <iostream>
#include <string>
#include <list>
#include <stdexcept>
#include "Item.hpp"
#include "Personagem.hpp"
#include "Inventario.hpp"
#include "Persistencia.hpp"

void mostrarMenu() {
    std::cout << "1 Coletar" << std::endl;
    std::cout << "2 Usar" << std::endl;
    std::cout << "3 Descartar" << std::endl;
    std::cout << "4 Listar" << std::endl;
    std::cout << "5 Buscar" << std::endl;
    std::cout << "0 Sair" << std::endl;
}

std::string lerNome(const std::string& rotulo) {
    std::string nome;
    while (true) {
        std::cout << rotulo;
        std::getline(std::cin, nome);
        if (!nome.empty()) {
            return nome;
        }
        std::cout << "Entrada invalida." << std::endl;
    }
}

int lerInteiroPositivo(const std::string& rotulo) {
    int valor;
    while (true) {
        std::cout << rotulo;
        if (std::cin >> valor) {
            std::cin.ignore(1000, '\n');
            if (valor > 0) {
                return valor;
            }
        } else {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        std::cout << "Entrada invalida." << std::endl;
    }
}

int lerOpcao() {
    int opcao;
    while (true) {
        std::cout << "Opcao: ";
        if (std::cin >> opcao) {
            std::cin.ignore(1000, '\n');
            return opcao;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Entrada invalida." << std::endl;
    }
}

void coletar(Inventario& inventario) {
    std::string nome = lerNome("Nome: ");
    int peso = lerInteiroPositivo("Peso: ");
    int quantidade = lerInteiroPositivo("Quantidade: ");

    try {
        if (inventario.coletar(nome, peso, quantidade)) {
            std::cout << "Item coletado." << std::endl;
        } else {
            std::cout << "Peso acima do limite." << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

void usar(Inventario& inventario) {
    std::string nome = lerNome("Nome: ");

    if (inventario.usar(nome)) {
        std::cout << "Item usado." << std::endl;
    } else {
        std::cout << "Item nao encontrado." << std::endl;
    }
}

void descartar(Inventario& inventario) {
    std::string nome = lerNome("Nome: ");

    if (inventario.descartar(nome)) {
        std::cout << "Item descartado." << std::endl;
    } else {
        std::cout << "Item nao encontrado." << std::endl;
    }
}

void buscar(const Inventario& inventario) {
    if (inventario.vazio()) {
        std::cout << "Inventario vazio." << std::endl;
        return;
    }

    std::string nome = lerNome("Nome: ");
    Item item;
    if (inventario.buscar(nome, item)) {
        std::cout << item.getNome() << " - peso " << item.getPeso()
                  << " - quantidade " << item.getQuantidade() << std::endl;
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
    const std::string arquivoDados = "dados.txt";
    Persistencia persistencia;
    std::string nome;
    int limite = 0;
    std::list<Item> itensCarregados;
    bool carregado = false;

    try {
        carregado = persistencia.carregar(arquivoDados, nome, limite, itensCarregados);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    if (!carregado) {
        bool personagemValido = false;
        while (!personagemValido) {
            try {
                nome = lerNome("Nome do personagem: ");
                limite = lerInteiroPositivo("Limite de peso: ");
                Personagem personagem(nome, limite);
                personagemValido = true;
            } catch (const std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    try {
        Personagem personagem(nome, limite);
        Inventario inventario(personagem);

        if (carregado) {
            std::list<Item>::const_iterator it;
            for (it = itensCarregados.begin(); it != itensCarregados.end(); ++it) {
                inventario.definirItem(it->getNome(), it->getPeso(), it->getQuantidade());
            }
        }

        int opcao = -1;
        while (opcao != 0) {
            mostrarMenu();
            opcao = lerOpcao();

            if (opcao == 1) {
                coletar(inventario);
            } else if (opcao == 2) {
                usar(inventario);
            } else if (opcao == 3) {
                descartar(inventario);
            } else if (opcao == 4) {
                listar(inventario, personagem.getLimitePeso());
            } else if (opcao == 5) {
                buscar(inventario);
            } else if (opcao == 0) {
                try {
                    persistencia.salvar(arquivoDados, inventario.getDono().getNome(),
                                        inventario.getDono().getLimitePeso(), inventario.listar());
                    std::cout << "Sair" << std::endl;
                } catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            } else {
                std::cout << "Entrada invalida." << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
