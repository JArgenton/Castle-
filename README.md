# Castle-: Jogo em C++ utilizando SFML
**TRABALHO PARA A DISCIPLINA DE TÉCNICAS DE PROGRAMAÇÃO DO CURSO DE ENGENHARIA DE COMPUTAÇÃO DA UTFPR**

## Descrição Geral

Este projeto é um jogo desenvolvido em C++ utilizando a biblioteca SFML para controle de eventos e gráficos. O código foi desenvolvido em um ambiente Linux e segue uma estrutura modular, onde diferentes componentes são organizados em namespaces específicos. A arquitetura do jogo é baseada em vários padrões de design, garantindo eficiência, flexibilidade e fácil manutenção.

## Compilação e Execução

O projeto inclui um `Makefile` para simplificar o processo de compilação no ambiente Linux. Aqui estão os passos essenciais:

 **Compilar o Projeto**:
   - No terminal, navegue até o diretório raiz do projeto e execute:
     ```sh
     make
     ```
   - O `Makefile` irá compilar automaticamente todos os arquivos `.cpp` encontrados no diretório `src` e gerar o executável `bin/program`.


## Autores

- **João Pedro de Andrade Argenton - 3º periodo Eng da Computação UTFPR**
- **Geovane Carlos Sabadin -  3º periodo Eng da Computação UTFPR**

## Disciplina

- **Técnicas de Programação – CSE20 / S1**


## Professor

- **Prof. Dr. Jean M. Simão**

## Estrutura do Código

### Namespaces Principais

- **Managers**: 
  - Contém os gerenciadores principais do jogo, incluindo:
    - **Gerenciador Gráfico**: Utiliza o padrão **Flyweight** para gerenciar `sf::Textures` de forma eficiente.
    - **Gerenciador de Colisões**: Implementa o padrão **Mediator** para mediar interações entre entidades.
    - **Gerenciadores de Eventos e Inputs**: Seguem o padrão **Observer** para monitorar e responder a eventos do jogo.

- **States** e **Menus**:
  - Controlam o fluxo do jogo e a interação com o jogador. Cada estado ou menu interpreta os dados gerenciados pelos componentes dos `Managers`.

- **GraphicElements**:
  - Organiza e manipula animações e elementos gráficos ou interativos do jogo. Este namespace facilita o controle de animações, que são integradas por outras classes.

- **Entities**:
  - Define os objetos presentes nas fases do jogo, categorizando-os em entidades móveis (ex. `Characters` e `Projectiles`) e estáticas (ex. `Obstacles`). 
  - `Characters` incluem tanto o jogador quanto os inimigos.

- **Factories**:
  - Implementa fábricas estáticas seguindo o padrão de design **Factory**. Estas fábricas abstraem a criação de entidades do jogo e são usadas para adicionar elementos de aleatoriedade às fases.

- **Lists**:
  - Contém listas template para gerenciar as entidades móveis e estáticas. Essas listas são compartilhadas com o gerenciador de colisões.

- **Math**:
  - Oferece ferramentas para manipulação vetorial e geometria analítica, contendo o namespace **Geometry** e a classe **Tuple**, que representa um vetor bidimensional.

### Classes Principais

- **Game**:
  - Controla o fluxo do jogo usando polimorfismo das classes que herdam de `State`. Gerencia eventos e cria fases dinâmicas com desafios específicos.

- **Level**:
  - Responsável pelo salvamento dos dados das fases e pela atualização e gerenciamento das entidades utilizando as listas do namespace `Lists`.

## Padrões de Design Utilizados

- **Flyweight**: Otimiza o uso de recursos gráficos, especialmente na distribuição de texturas (`sf::Textures`).
- **Mediator**: Facilita a interação e comunicação entre diferentes entidades do jogo.
- **Observer**: Monitora e responde a eventos e inputs do jogador.
- **Factory**: Abstrai e centraliza a criação das entidades do jogo, permitindo a geração de objetos e introduzindo aleatoriedade nas fases.


