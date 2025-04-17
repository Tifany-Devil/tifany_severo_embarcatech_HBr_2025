# 🌡️ Internal Temperature Reader - RP2040

Este projeto realiza a leitura da temperatura interna do microcontrolador RP2040 utilizando seu sensor embutido. A temperatura é exibida tanto no terminal quanto em um display OLED I2C.

## 🎯 Objetivo

Demonstrar como utilizar o sensor de temperatura interno do RP2040 com conversão do valor ADC para graus Celsius, exibindo os dados em tempo real.

## 🔧 Componentes

- Raspberry Pi Pico / BitDogLab (RP2040)  
- Display OLED I2C (SSD1306)

## ⚡ Pinagem

| Componente       | Pino         |
|------------------|--------------|
| Display OLED I2C |SDA: GPIO14 / SCL: GPIO15  |
|                  |   |

## 🧠 Execução

1. Configure o ambiente de desenvolvimento (VS Code + SDK do RP2040);
2. Compile o projeto (com `Ctrl+Shift+B` ou via `cmake` + `make`);
3. Copie o arquivo `.uf2` gerado para a Raspberry Pi Pico em modo de boot;
4. Observe a leitura da temperatura no terminal e no display OLED.

## 🧮 Conversão de Temperatura

A leitura do sensor interno é feita pelo canal ADC4. A conversão do valor lido (em voltagem) para temperatura é feita com a fórmula oficial do datasheet:

```c
voltage = raw * (3.3f / 4096);
temperature_celsius = 27.0f - (voltage - 0.706f) / 0.001721f;
```

## 💻 Terminal

A cada segundo, o terminal exibirá:

```
Internal Temperature: 28.45 °C  
Internal Temperature: 83.21 °F
```

## 🖥️ Display OLED

O display OLED exibirá:

```
     Temperatura     
      28.45 °C       
```

## 📁 Arquivos

- `main.c`: Código-fonte principal contendo toda a lógica de leitura e exibição.

## 🖼️ Visualização



## 🧪 Resultados Esperados

- Atualização da temperatura a cada 1 segundo;
- Exibição dos valores tanto em °C quanto em °F no terminal;
- Exibição da temperatura em °C no centro do display OLED.

---

## 📜 Licença

MIT License