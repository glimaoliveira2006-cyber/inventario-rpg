# Plano do inventário de RPG

Este plano segue o `DESCRICAO.md` e as regras do `AGENTS.md`: C++11, só a
biblioteca padrão, sem `new`/`delete`, uma classe por par de arquivos, e a
lógica separada da interface (as classes não usam `cin` nem `cout`).

## 1. Visão geral

Três classes de lógica, mais a interface:

| Arquivo | Classe | Responsabilidade |
| --- | --- | --- |
| `include/Item.hpp` / `src/Item.cpp` | `Item` | Um item: nome, peso e quantidade. Sabe calcular seu peso total e comparar-se com outro item. |
| `include/Personagem.hpp` / `src/Personagem.cpp` | `Personagem` | O dono do inventário: nome e limite de peso. |
| `include/Inventario.hpp` / `src/Inventario.cpp` | `Inventario` | Guarda os itens e faz coletar, usar, descartar, listar e buscar. |
| `src/main.cpp` | interface | Lê do teclado e escreve na tela. Só ela conhece `cin`/`cout`. |

O `Inventario` guarda um `Personagem` (composição), porque é o dono que define
o limite de peso usado na regra de peso.

## 2. Classe `Item`

Guarda:

- `std::string nome` (uma única palavra, sem espaços)
- `int peso`
- `int quantidade`

Métodos:

- `Item()` (construtor padrão, peso e quantidade zerados; o `map` precisa
  dele para o `operator[]`)
- `Item(const std::string& nome, int peso, int quantidade)`
- `getNome()`, `getPeso()`, `getQuantidade()` (getters `const`)
- `int pesoTotal() const` → devolve `peso * quantidade`
- `void somarQuantidade(int q)` → soma `q` à quantidade
- `void retirarQuantidade(int q)` → subtrai `q` da quantidade
- `bool operator<(const Item& outro) const` → compara pelo **peso** (mais leve
  primeiro) e, se o peso for igual, pelo **nome**. É o que o `list::sort` usa
  para ordenar a listagem.

## 3. Classe `Personagem`

Guarda:

- `std::string nome` (uma única palavra, sem espaços)
- `int limitePeso`

Métodos: construtor e dois getters `const`. Nada mais, para manter simples.

## 4. Classe `Inventario`

Guarda:

- `Personagem dono`
- `std::map<std::string, Item> itens`

Métodos (sem `cin`/`cout`; devolvem `bool` ou dados):

- `Inventario(const Personagem& dono)`
- `bool coletar(const std::string& nome, int peso, int quantidade)`
  - Se o nome já existe, mantém o peso do primeiro cadastro e só soma a
    quantidade (regra do `DESCRICAO.md`).
  - Antes de aceitar, confere se o peso total não passa do limite. Se passar,
    devolve `false` sem alterar nada.
- `bool usar(const std::string& nome)` → tira 1 unidade. Se a quantidade
  chegar a zero, remove o item. Devolve `false` se o item não existe.
- `bool descartar(const std::string& nome)` → remove o item inteiro. `false`
  se não existe.
- `bool buscar(const std::string& nome, Item& resultado) const` → preenche
  `resultado` e devolve `true`, ou devolve `false` se não existe.
- `std::list<Item> listar() const` → copia os itens do `map` para uma `list` e
  ordena com `list::sort` (usa `Item::operator<`).
- `int pesoTotal() const` → soma de `pesoTotal()` de todos os itens.
- `bool vazio() const`

## 5. Containers da STL e por quê

| Onde | Container | O quê | Por quê |
| --- | --- | --- | --- |
| `Inventario` | `std::map<std::string, Item>` | os itens, com o nome como chave | nomes são únicos e a busca por nome fica O(log n). O `map` já existe justamente para isso, e ainda guarda o `Item` por valor. |
| `Inventario::listar` | `std::list<Item>` + `list::sort` | cópia ordenada dos itens | a cópia numa `list` deixa eu ordenar com `list::sort`, que usa `Item::operator<` (peso e, em empate, nome). |

Requisitos da atividade cobertos: `map` (armazenamento), `list`, e
`list::sort` aplicado a objetos de uma classe minha com `operator<` definido
nela.

Detalhe de memória: não uso `new`/`delete`. Os `Item` ficam por valor dentro
do `map`, e a `list` do `listar` é só uma cópia temporária, sem ponteiros.

## 6. Interface (`src/main.cpp`)

1. No início, pergunta o nome do personagem (uma única palavra, sem espaços)
   e o limite de peso, cria `Personagem` e `Inventario`.
2. Mostra o menu: `1 Coletar, 2 Usar, 3 Descartar, 4 Listar, 5 Buscar, 0 Sair`.
3. Traduz cada resultado em mensagem (as classes só devolvem `bool`/dados):
   - sucesso: `Item coletado.`, `Item usado.`, `Item descartado.`
   - erro: `Item nao encontrado.`, `Inventario vazio.`,
     `Peso acima do limite.`, `Entrada invalida.`
4. Valida a leitura: texto onde se espera número, ou número `<= 0`, mostra
   `Entrada invalida.` e pede de novo. Nome vazio também é `Entrada invalida.`
5. A listagem (opção 4) mostra os itens ordenados por peso (mais leve
   primeiro) e, em empate, por nome.

## 7. Etapas de implementação

Cada etapa termina compilando com o comando do `README.md`
(`g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema`) e com um
cenário em `exemplos/` para rodar.

### Etapa 1 — `Item`, `Personagem` e o primeiro `main`
- Crio `include/Item.hpp`, `src/Item.cpp`, `include/Personagem.hpp`,
  `src/Personagem.cpp`.
- O `Item` já sai com o construtor padrão e o `operator<` (peso e, em
  empate, nome).
- `src/main.cpp` (temporário): lê nome e limite do personagem, imprime na
  tela, e cria um `Item` de teste mostrando os getters.
- Teste: compilar e rodar. Ainda não há menu.

### Etapa 2 — `Inventario`: coletar e listar
- Crio `include/Inventario.hpp` e `src/Inventario.cpp` com `coletar`,
  `listar`, `pesoTotal`, `vazio`. Os itens ficam num `std::map<std::string,
  Item>`, e `listar` devolve uma `std::list<Item>` ordenada com `list::sort`.
- O `main` vira o menu com as opções `1`, `4` e `0`.
- Crio `exemplos/cenario1.txt`: coletar 3 poções e listar.
- Teste: `./sistema < exemplos/cenario1.txt`. Deve aparecer `Item coletado.`,
  a linha da poção e `Peso total: 3 de 10`.

### Etapa 3 — usar e descartar
- Acrescento `usar` e `descartar` ao `Inventario` e as opções `2` e `3` ao
  menu. Regra: quantidade zero remove o item.
- Crio `exemplos/cenario2.txt`: coletar, usar até zerar, tentar usar de novo
  (não encontrado), descartar.
- Teste: rodar o cenário e conferir as mensagens.

### Etapa 4 — buscar e validação de entrada
- Acrescento `buscar` e a opção `5`. Coloco o laço que rejeita entrada
  inválida com `Entrada invalida.` e o aviso `Inventario vazio.`
- Crio `exemplos/cenario3.txt` com texto no lugar de número, número `<= 0`,
  nome vazio e item inexistente.
- Teste: rodar e conferir que o programa não trava e repete a pergunta.

### Etapa 5 — peso acima do limite e fechamento
- Confiro a regra do limite em `coletar` (inclusive quando o item já existe) e
  a mensagem `Peso acima do limite.`
- Crio `exemplos/cenario4.txt` com todos os casos: item repetido (soma),
  estouro de peso, inventário vazio, sair.
- Rodo todos os cenários de uma vez. Se algum arquivo novo entrou, confiro se
  o comando do `README.md` ainda cobre tudo (ele usa `src/*.cpp`, então já
  cobre).

## 8. Pontos para você confirmar antes de codificar

1. **Criação do personagem:** o programa deve perguntar nome e limite de peso
   no início? (assumi que sim, para os exemplos ficarem determinísticos).
2. **Nome de item e de personagem:** são uma única palavra, sem espaços.
3. **Peso e limite de peso:** são números inteiros e aparecem como `1`, `2`
   etc.
4. **Coletar item que já existe e estourar o limite:** recusar a coleta
   inteira e avisar. (assumi que sim).
