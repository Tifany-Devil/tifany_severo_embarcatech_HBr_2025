# ⏱️ Contador Decrescente com Interrupção de Botões  
Este projeto implementa um contador decrescente com interação por botões físicos e exibição das informações em um display OLED via I2C, utilizando a **Raspberry Pi Pico W** (ou outro microcontrolador compatível com SDK Pico C/C++).

## 🎯 Objetivo  
Demonstrar na prática a importância do uso de **debounce** ao notar que o botão B gera múltiplas interrupções para uma mesma pressão, evidenciando discrepâncias entre o número real de cliques e o valor contabilizado.

## 🔧 Componentes  
- Raspberry Pi Pico W  
- Display OLED 128x64 I2C (SSD1306)  
- 2 Botões (A e B)  
- Resistores de pull-up (caso não use os internos)

## ⚡ Pinagem  
| Componente        | Pino         |
|-------------------|--------------|
| Botão A           | GPIO5        |
| Botão B           | GPIO6        |
| Display OLED I2C  | SDA: GPIO14  |
|                   | SCL: GPIO15  |

## 🚀 Execução

1. Abra o projeto no VS Code com suporte ao SDK do Raspberry Pi Pico (CMake + compilador ARM);
2. Compile o projeto (Ctrl+Shift+B no VS Code ou via terminal com `cmake` e `make`);
3. Conecte a Pico via USB e coloque-a em modo de boot (pressione o botão **BOOTSEL** ao conectar);
4. Copie o arquivo `.uf2` gerado para a unidade de armazenamento que aparecer (`RPI-RP2`);
5. A Pico reiniciará automaticamente e iniciará o programa;
6. Pressione o botão **A** para iniciar a contagem regressiva de 9 a 0;
7. Pressione o botão **B** durante a contagem para registrar cliques — observe no terminal e no display que a quantidade pode ser maior que a esperada, evidenciando a ausência de debounce.

## 📋 Lógica do Programa

- Ao pressionar **A**, a contagem regressiva de 9 até 0 é iniciada;
- Enquanto a contagem ocorre, cada clique no botão **B** é registrado;
- O número de cliques e o valor do contador são exibidos no terminal serial e no display OLED;
- O projeto evidencia a importância de técnicas de debounce ao se observar que múltiplas interrupções podem ser geradas por um único clique físico.

## 📁 Arquivos

- `main.c`: Código principal do projeto;
- `inc/ssd1306.h`: Biblioteca de controle do display OLED.

## 🖼️ Imagens (opcional)

Caso deseje, adicione imagens demonstrando o projeto montado e o display em funcionamento.

## 📈 Resultados esperados  
O display mostrará uma quantidade de cliques do botão "B" maior que a quantidade real de cliques feitas pelo usuário.

---

## 📜 Licença  
MIT License
