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

<p align="justify">
    A placa de desenvolvimento DE1-SoC é uma plataforma baseada no chip Altera Cyclone V SoC, que integra um processador ARM Cortex-A9 dual-core com uma FPGA da família Cyclone V. A DE1-SoC possui uma ampla variedade de periféricos e interfaces, incluindo:
</p>

- Interfaces de entrada/saída;
- Conexões de áudio de vídeo;
- Interface USB;
- Conexões Ethernet;
- LEDS, chaves e botões, entre outros.

<p align="center">
    <img src="https://github.com/vitoriatanan/Processador-Grafico/blob/main/Imagens/placa.jpg" alt="Placa DE1-SoC" width="500">
    <br>
    Figura 1. Placa de desenvolvimento DE1-SoC.
</p>



### Linguagem C
<p align="justify">
A linguagem C é uma linguagem de programação de alto nível que foi criada nos anos 70 com o propósito inicial de desenvolver sistemas operacionais. Nos dias atuais, ela permanece bastante popular, sendo amplamente utilizada em sistemas embarcados, no Kernel do Linux, aleḿ de também ter servido de influência para criação de outras linguagens como C#, C++ e Java. No projeto, essa linguagem foi utilizada para desenvolver o código fonte em conjunto com o compilador GCC para execução do programa.
</p>

### Compilador GCC
<p align="justify"> 
    GCC é sigla para GNU Compiler Collection, trata-se de um conjunto de compiladores para linguagem de programação C, C++, Objective-C, Fortran, Ada, Go, entre outras. Lançado em 1987, é o compilador padrão na maior parte das distribuições Linux além de estar disponível para muitos sistemas embarcados, incluindo chips baseados em ARM e Power ISA. No projeto, foi utilizado para compilar o código fonte escrito em linguagem C.
</p>

### Padrão VGA
<p align="justify"> 
    A placa DE1-SoC possui um conector D-SUB de 15 pinos para saída VGA, com sinais de sicronização gerados pelo FPGA Cyclone V Soc. Um DAC de vídeo triplo ADV7123 converte sinais digitais para analógicos, representando as cores vermelho, verde e azul, suportando até a resolução SXGA (1280x1024) a 100 MHz.
    </p>
    <p align="justify"> 
    A sicronização VGA envolve pulsos de sicronização horizontal (hsync) e vertical (vsync), com períodos específicos denominados back porch, front porch e intervalo de exibição para controlar os dados RGB. Após o pulso hsync, os sinais RGB são desligados (back porch), seguidos pelo intervalo de exibição onde os dados RGB ativam cada pixel, e depois desligados novamente (front porch) antes do próximo pulso hsync.
</p>
<p align="center">
    <img src="https://github.com/vitoriatanan/Processador-Grafico/blob/main/Imagens/vga.png" alt="VGA" width="600">
    <br>
    Figura 2. Conexões entre o FPGA e o VGA
</p>

## Arquitetura do Processador Gráfico
<p align="justify"> 
    O Processador Gráfico 
</p>

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
