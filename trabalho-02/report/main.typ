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

- Por que foi escolhida essa estrutura e não outra?
- Como ela resolve o problema?
- Como foi a implementação?
- Quais as suas limitações?
- Quais as dificuldades encontradas ao longo da solução?

= Conclusão

- 

= Participações
== Vinicius Henrique P. Giroto
Responsável pela primeira implementação do TAD e resolução do problema.

== Caio Corrêa Chaves
Responsável pela reorganização do código (a fim de melhorar a modularização e legibilidade) e escrita do relatório.

