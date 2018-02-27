# Smart Seedling
Smart Seedling é um projeto de código aberto que provê algumas funções básicas para um sistema de irrigação automatizado para mudas de plantas, você só precisa criar as regras para o seu tipo de horta, sem precisar se preocupar com coisas mais técnicas.

## Começando

Este projeto é derivado de um anterior, o Smart Garden, embora seja mais simples ele tem algo diferente do anterior. Nesse novo sistema foi desenvolvido a implementação com um multiplexador, para a leitura de mais sensores. Abaixo mostro como funciona a conexão de com o arduino.

Imagem do projeto sem o Multiplexador:

![alt tag](http://4.bp.blogspot.com/-tkFyCMCa3-Y/WpWjsGy0QBI/AAAAAAAADxc/1qtnzrjQsd0Qhvhyi48994QdLeGokusqwCK4BGAYYCw/s1600/unnamed.png)

### Conectar o multiplexador 4051 no arduino

![alt tag](http://2.bp.blogspot.com/-Rb70EwOABZE/WpWafmWI_uI/AAAAAAAADxM/ikiXlRldTVcLsLL08iFRx71StUxHOLI5ACK4BGAYYCw/s1600/4051.jpg)

Desenvolvi uma biblioteca onde substituimos o objeto "Sensor" pelo "MULT4051", que é responsável pela mesma tarefa do Sensor, só que agora funciona por meio de multiplexação.

Para adicionar ao projeto é só incluir a "MULT4051.cpp" e substituir Sensor por MULT4051.

```
#include "MULT4051.cpp"
```

### Sobre a MULT4051.cpp

Ela possui os mesmos métodos da Sensor, só que você terá que inserir alguns parãmetros. Ex:

```
sensores_solo.ler(false, false, true);
```

Esses parâmetros são responsáveis por setar qual sensor será lido, variando de (false, false, false) até (true, true, true).

## Testes

Antes de utilizar tudo em conjunto faça testes unitários.

## Final

Projeto final utilizando o 4051

![alt tag](http://4.bp.blogspot.com/-cREMc7kr-dM/WpWnBCYQ60I/AAAAAAAADxo/tUZWbt2R8rYuTLNWnAZ84nP-NyZN5N_wQCK4BGAYYCw/s1600/index.jpg)
