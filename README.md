# Nome do sistema

Atividade da Unidade 2 de Linguagem de Programação I. Leia `ENUNCIADO.md`
antes de começar.

Uma frase dizendo o que o sistema faz. A descrição completa está em
`DESCRICAO.md`.

## Arquivos

```text
.
├── AGENTS.md       regras que a IA lê antes de cada pedido
├── DESCRICAO.md    a descrição do sistema, escrita por você
├── ENUNCIADO.md    a atividade
├── PLANO.md        o plano feito com a IA (criado na etapa 3)
├── README.md       este arquivo
├── exemplos/       arquivos de entrada para testar
├── include/        um .hpp por classe
└── src/            um .cpp por classe, mais a interface
```

## Compilar e executar

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

Se o comando mudar, atualize esta seção. Na correção eu vou usar o que
estiver escrito aqui.

## Onde uso a STL

- **`map<string, Item>`** (classe `Inventario`): guarda os itens do inventário, com o nome do item como chave. Usei `map` porque cada nome aparece uma única vez e a busca pelo nome é rápida, o que ajuda em coletar, usar, descartar e buscar. Quando o item já existe, só a quantidade é somada na mesma entrada. A classe `Item` tem construtor padrão porque o `map` precisa dele para criar uma entrada nova.
- **`list<Item>`** (método `Inventario::listar()`): devolve uma cópia dos itens numa lista. Usei `list` porque ela tem o seu próprio `sort()` e porque aqui só preciso percorrer os itens do início ao fim, sem acessar por posição.
- **`list::sort` com `Item::operator<`** (classes `Inventario` e `Item`): o `listar()` ordena a lista com `sort()`, que usa o `operator<` definido na classe `Item`. Esse operador compara pelo peso, do mais leve ao mais pesado, e, se o peso for igual, pelo nome. Como o `map` já guarda os itens em ordem de nome, o `sort` muda a ordem da listagem.

## Como usei a IA

Usei o OpenCode com o modelo Big Pickle. Trabalhei em etapas: escrevi o `DESCRICAO.md` e fiz um commit só com ele, pedi à IA que apontasse o que estava ambíguo, respondi e atualizei a descrição, e depois pedi o plano em `PLANO.md`. Li o plano e pedi correções antes de programar. Implementei uma etapa por vez, cada uma numa conversa nova (`/new`) e com um commit.

Depois de cada etapa conferi o resultado: compilei com `-Wall -Wextra`, rodei todos os cenários de `exemplos/`, olhei o `git status` e procurei `cin` e `cout` nas classes para garantir que a lógica está separada da interface.

Corrigi três coisas no caminho: troquei `double` por `int` no peso, porque a descrição diz que o peso é inteiro; pedi para simplificar o armazenamento, trocando um `map` com iteradores da `list` por `map<string, Item>`, que é mais fácil de explicar e usa só o que vimos em aula; e fiz o `operator<` comparar pelo peso, para o `sort` ter efeito sobre a ordem que o `map` já dá.

