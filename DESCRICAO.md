# Descrição do sistema

Escreva este arquivo sem IA, antes de qualquer código. Apague as instruções
em itálico quando preencher.

## Nome e ideia

inventário de RPG é um sistema em modo texto para jogadores controlarem os itens do personagem de forma prática, no lugar do papel. Ele serve para qualquer tipo de RPG e guarda itens de qualquer natureza, como armas, poções e materiais. O jogador pode coletar, usar e descartar itens, respeitando o limite de peso do personagem.

## O que o sistema guarda


O sistema guarda itens e um personagem. Cada item tem nome, peso e quantidade, e itens iguais ficam numa única entrada. O personagem tem nome e um limite de peso.

## O que dá para fazer

1. Coletar item: pede nome, peso e quantidade e adiciona ao inventário.
2. Usar item: pede o nome e gasta uma unidade.
3. Descartar item: pede o nome e remove o item.
4. Listar itens: mostra todos os itens e o peso total.
5. Buscar item: pede o nome e mostra o item.
0. Sair: encerra o programa.

## Regras

O peso total dos itens não pode passar do limite do personagem.
Itens com o mesmo nome ficam numa única entrada, e a quantidade soma.
O peso e a quantidade de um item devem ser maiores que zero.
Não dá para descartar ou usar um item que não existe no inventário.
Quando a quantidade de um item chega a zero, ele sai do inventário.

## regras

- O peso total dos itens não pode passar do limite do personagem.
- Itens com o mesmo nome ficam numa única entrada, e a quantidade soma.
- O peso e a quantidade de um item devem ser maiores que zero.
- Não dá para descartar ou usar um item que não existe no inventário.
- Quando a quantidade de um item chega a zero, ele sai do inventário.
- Nomes de itens são comparados exatamente: Pocao e pocao são itens diferentes.   ← nova
- Se o item já existe, o peso do primeiro cadastro é mantido e só a quantidade é somada.   ← nova
...


## Quando algo dá errado

Item não existe: o sistema mostra "Item não encontrado" e volta ao menu.
Item já existe: a quantidade é somada à entrada que já existe, sem criar outra.
Inventário vazio: o sistema mostra "Inventário vazio" e volta ao menu.
Peso acima do limite: o item não é adicionado e o sistema avisa.
Entrada inválida: se o usuário digitar texto onde se espera número, ou um número menor ou igual a zero, o sistema mostra "Entrada inválida" e pede de novo.

## quando algo dá errado
- Buscar com inventário vazio: mostra "Inventario vazio."
- Nome de item vazio: mostra "Entrada invalida."
- Mensagens padrão: "Item coletado.", "Item usado.", "Item descartado.", "Item nao encontrado.", "Inventario vazio.", "Entrada invalida.", "Peso acima do limite."


## Classes que eu imagino

Item: guarda nome, peso e quantidade de um item.
Personagem: guarda o nome e o limite de peso.
Inventario: guarda os itens do personagem e faz coletar, usar, descartar, listar e buscar.

## Exemplo de uso

Personagem: Aragorn, limite de peso 10.

Menu: 1 Coletar, 2 Usar, 3 Descartar, 4 Listar, 5 Buscar, 0 Sair

Opcao: Coletar item
Nome: Pocao
Peso: 1
Quantidade: 3
Item coletado.

Opcao: Listar itens
Pocao - peso 1 - quantidade 3
Peso total: 3 de 10

Opcao: Buscar item
Nome: Arco
Item nao encontrado.

Opcao: Sair
