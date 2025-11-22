#import "@preview/ilm:1.4.1": *

#set text(lang: "pt")

#show: ilm.with(
  title: [Trabalho I],
  author: "Caio Corrêa Chaves - 15444406\nVinicius Henrique P. Giroto - 11319656",
  date: datetime.today(),
  date-format: "21 de setembro de 2025",
  abstract: [
    Representação de grandes números através de listas encadeadas.
  ],
)

#let plot-performance = (method) => {
  image("./figures/"+method+".png")
}

= Introdução
O projeto tem como objetivo propor uma solução para o problema de operar matematicamente grandes números, levando em conta que os tipos primitivos da linguagem C não são suficientes para alguns casos de usos da vida real (como cálculos astronômicos ou navais, por exemplo).

Para tal, foi implementado um TAD baseado em listas encadeadas, onde cada nó armazena uma dada quantidade de dígitos do grande número representado.

O projeto foi escrito em C, e compilado utilizando o compilador Clang, e executado em uma máquina Linux. Os gráficos foram gerados utilizando Python e Matplotlib.

== Especificações
=== Clang
```
> clang --version
clang version 20.1.8 (Fedora 20.1.8-4.fc42)
Target: x86_64-redhat-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
Configuration file: /etc/clang/x86_64-redhat-linux-gnu-clang.cfg
```

=== Flags
```makefile
CFLAGS := -std=c2x -Wall -Wextra -pedantic -O3
```

=== Sistema Operacional
```
> uname -a
Linux toolbx 6.16.7-200.fc42.x86_64 #1 SMP PREEMPT_DYNAMIC Thu Sep 11 17:46:54 UTC 2025 x86_64 GNU/Linux
```

=== Processador
```
AMD Ryzen™ 5 5600G with Radeon™ Graphics × 12 @ 3.90 GHz
```

= Metodologia

Para resolução do problema das representações de grandes números, foi implementado, conforme orientado pelo enunciado, um TAD baseado na estrutura de lista encadeada. Dessa forma, podemos representar números de qualquer tamanho, uma vez que a única limitação para o tamanho da lista encadeada é a própria memória do computador.

Outra limitação do TAD implementado, entretanto, é a inacessibilidade direta à algarismos específicos do número representado, uma vez que a lista encadeada exige que todos os elementos anteriores sejam processados.

Os desafios da implementação se deram principalmente em relação à elaboração da lógica de adição e subtração dos grandes números. Em especial no caso da subtração, onde é essencial um conhecimento prévio a respeito de qual dos operandos é maior, exigindo assim um maior processamento prévio à operação.

= Conclusão

O TAD, apesar das dificuldades de implementação, se mostrou uma solução eficiente para a representação e operação de números de alta ordem, uma vez que contorna a limitação dos tipos primitivos e ainda permite que operações complexas sejam realizadas.

= Participações
== Vinicius Henrique P. Giroto
Responsável pela primeira implementação do TAD e resolução do problema.

== Caio Corrêa Chaves
Responsável pela reorganização do código (a fim de melhorar a modularização e legibilidade) e escrita do relatório.

