# Minerva - Drone terréstre voltado ao pequeno agricultor 

## Resumo
O Minerva é um projeto dos alunos da EC3MA baseado na premissa de um drone terrestre voltado ao plantio de sementes e raízes , em especial a priprioca , uma raiz nativa da Amazônia e de cultivo prevalente na ilha de Cotijuba.
### Problema
Mesmo que simples, o plantio de tal raiz é feito de forma arcaica, repetitiva e exaustiva,  principalmente por donas de casa que se submetem a tal trabalho braçal em idades avançadas, podendo levar a lesões por esforço repetitivo e doenças osteo-musculares a longo prazo.

### Solução
Substituição desse trabalho braçal por um drone terrestre, operado por comandos simples selecionados pelo usuário utilizando seu telefone como controle remoto.

## Detalhes do projeto

 O drone em si se consiste em motores de passo controlados por um ESP-32, tal microcontrolador escolhido devido a sua fácil implementação de bluetooth e baixo custo.
### Código
O código em si é baseado nas bibliotecas voltadas ao controle do motor de passo e de conexão Bluetooth Low Energy. Em especial, vale destacar a base do código feita pelo canal [Wim der Kinderen](https://www.youtube.com/@wimderkinderen1952), voltado à conexão em aparelhos Apple por meio do app Bluefruit Connect, esse sendo um terminal de comunicação serial com uma interface de fácil aprendizado e implementação.
