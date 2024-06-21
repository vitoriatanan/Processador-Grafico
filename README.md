<h1 align="center"> Comunicação com Processador Gráfico </h1>


## Sobre

<p align="justify"> 
O projeto consistiu em desenvolver um módulo de Kernel Linux e uma biblioteca em linguagem C com o intuito de criar uma ponte de comunicação entre o processador gráfico que se encontra na FPGA contida na placa DE1-SoC e um programa a nível de usuário 

</p>
<p align="justify"> 
...

</p>
<p align="justify"> 
...

</p>


## Sumário
- [Softwares e Periféricos Utilizados](#softwares-e-periféricos-utilizados)
    - [Kit de desenvolvimento DE1 SoC](#kit-de-desenvolvimento-de1-soc)
    - [Linguagem C](#linguagem-c)
    - [Compilador GCC](#compilador-gcc)
    - [Monitor VGA](#monitor-vga)
- [Arquitetura do Processador Gráfico](#arquitetura-do-processador-gragico)
- [Detalhamento da Lógica de Comunicação](#detalhamento-da-lógica-de-comunicação)
- [Preparação do Ambiente e Execução do Projeto](#preparação-do-ambiente-e-execução-do-projeto)
- [Cenários de Testes](#cenários-de-testes)
- [Conclusão](#conclusão)
- [Referências](#referências)

## Equipe
- Jeferson Almeida da Silva Ribeiro
- Letícia Teixeira Ribeiro dos Santos
- Vitória Tanan dos Santos

## Softwares e Periféricos Utilizados
### Kit de desenvolvimento DE1-SoC
### Linguagem C
### Compilador GCC
### Monitor VGA

## Arquitetura do Processador Gráfico

## Detalhamento da Lógica de Comunicação
### Mapeamento de Memória
<p align="justify"> 
Para que haja comunicação entre hardware e software no ambiente Linux, é necessário aplicar a técnica de mapeamento de memória. Devido ao Linux utilizar um sistema de memória virtual, os endereços físicos do hardware não ficam disponíveis para acesso direto em programas em execução. O Kernel disponibiliza a função mmap que pode ser usada em conjunto com o arquivo /dev/mem e assim mapear os endereços físicos para endereços virtuais, permitindo o acesso ao hardware.
</p>
<p align="justify"> 
No contexto do projeto, essa técnica foi usada para ter acesso aos barramentos Data A e Data B do Processador Gráfico, que se encontra na FPGA. O processador ARM (HPS) possui as pontes de acesso HPS-to-FPGA e LightWeight-to-FPGA, que são mapeadas para regiões no espaço de memória do HPS, ao utilizar uma delas é possível acessar os barramentos através da soma da ponte + offset, que representa o endereço base.
</p>


mapeamento de memoria, ... driver de caractere

## Preparação do Ambiente e Execução do Projeto
