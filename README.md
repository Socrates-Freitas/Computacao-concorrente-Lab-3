# Computacao-concorrente-Lab-3

Este é o terceiro Laboratório do curso de Computação Concorrente. Este projeto tem como objetivo a implementação e análise de um programa que resolve um problema de forma sequencial e concorrente, seus tempos de execução e vantagens da programação concorrente. 


## Sobre o programa:

O programa `Lab3.c` gera um vetor de números reais de tamanho *N* (fornecido na linha de comando), então o programa imprimirá o maior e menor valor deste vetor.

## Metodologia:

O programa `Lab3.c` foi executado 5 vezes com 3 tamanhos de vetores  diferentes e 3 diferentes quantidades de threads para completar a tarefa. Após as 5 execuções, o *menor tempo* foi utilizado. 

O cálculo do *Ganho de desempenho* é a divisão do tempo de execução linear(*de N elementos*) pelo tempo de execução concorrente(*N elementos em T threads*). 


<br/>

# Tempos de execução:


## 1 * 10⁵ elementos:

<br/>


| Nº de Threads |  Tempo de execução em Segundos  | Ganho de Desempenho|
|     :---:     |               :---:             |        :---:       |                           
|  *Sequencial* |               *0.000267*        |         *#*        |
| 1             |               0.000896          |    0.297991071     |
| 2             |               0.000627          |    0.425837321     |
| 4             |               0.000314          |    0.850318471     |

<br/>


## 1 * 10⁷ elementos:

<br/>


| Nº de Threads |  Tempo de execução em Segundos  | Ganho de Desempenho |
|     :---:     |               :---:             |        :---:        |                           
|  *Sequencial* |               *0.024328*        |         *#*         |
| 1             |               0.025391          |    0.958134772      |
| 2             |               0.013579          |    1.791589955      |
| 4             |               0.008427          |    2.886911119      |




<br/>

## 1 * 10⁸ elementos:

<br/>


| Nº de Threads |  Tempo de execução em Segundos  | Ganho de Desempenho |
|     :---:     |               :---:             |        :---:        |                           
|  *Sequencial* |               *0.243419*        |         *#*         |
| 1             |               0.251469          |    0.967988102      |
| 2             |               0.131473          |    1.851475208      |
| 4             |               0.070836          |    3.43637416       |


<br/>


## Especificações do computador utilizado para os testes acima:

<br/>

**Arquitetura:** x86_64

**Núcleos:** 4

**Memória RAM:** 4GB

**Modelo do processador:** Intel(R) Core(TM) i5-2500 CPU @ 3.30GHz


