#import "@preview/ilm:1.4.1": *
#import "@preview/lilaq:0.4.0" as lq

#set text(lang: "pt")

#show: ilm.with(
  title: [Trabalho I],
  author: "Caio Corrêa Chaves\nVinicius Henrique P. Giroto",
  date: datetime.today(),
  abstract: [
    Relatório de desempenho de algoritmos de busca e ordenação em C.
  ],
  bibliography: bibliography("refs.bib"),
  figure-index: (enabled: true),
  table-index: (enabled: true),
  listing-index: (enabled: true),
)

#let results = csv("benchmark.csv", row-type: dictionary)
#let counts = (10, 100, 1000, 5000)
#let plot-performance = (method) => {
  let groups = results.filter(it => it.method == method).fold((:), (acc, it) => {
    let (key, value) = (it.elements, float(it.time))
    let elements = acc.at(key, default: ())
    elements.push(value)
    acc.insert(key, elements)
    acc
  })

  let plots = groups.pairs().map(((key, values)) => {
    if values.len() == 0 {
      return
    }

    let x = counts.position(it => it == int(key))
    lq.boxplot(values, x: x + 1)
  })

  lq.diagram(
    ..plots,
    // lq.boxplot(..data),
    xaxis: (
      ticks: range(1, 5),
      format-ticks: ((x, ..) => x.map(it => $#(counts.at(int(it - 1)))$
     )),
    ),
    xlabel: "Número de elementos",
    ylabel: "Tempo (ms)",
  )
}

= Introdução

= Resultados


== Inversão
#figure(
  plot-performance("inverse")
)

== Busca sequencial
#figure(
  plot-performance("sequential-search")
)

== Busca binária iterativa
#figure(
  plot-performance("binary-search-iterative")
)

== Busca binária recursiva
#figure(
  plot-performance("binary-search-recursive")
)

= Conclusão

= Participações
== Caio Corrêa Chaves

== Vinicius Henrique P. Giroto
