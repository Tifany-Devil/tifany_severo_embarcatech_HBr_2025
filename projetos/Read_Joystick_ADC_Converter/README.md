# 🕹️ Joystick ADC Reader  
Este projeto lê os valores analógicos do joystick da BitDogLab usando os canais ADC do RP2040, exibindo os dados em tempo real no terminal ou em um display OLED.

## 🎯 Objetivo  
Demonstrar como converter sinais analógicos de um joystick para valores digitais e exibi-los graficamente, incluindo a leitura do botão (digital).

## 🔧 Componentes  
- Raspberry Pi Pico / BitDogLab (RP2040)  
- Joystick KY-023  
- Display OLED I2C (SSD1306)  

## ⚡ Pinagem  
| Componente           | Pino         |
|----------------------|--------------|
| Joystick eixo X (vRx) | GPIO26 (ADC0) |
| Joystick eixo Y (vRy) | GPIO27 (ADC1) |
| Botão do Joystick    | GPIO22       |
| Display OLED I2C     | SDA: GPIO14 / SCL: GPIO15 |

## 🧠 Execução

1. Abra o projeto no VS Code configurado com o SDK do Raspberry Pi Pico (CMake + compilador ARM);
2. Compile o código (`Ctrl+Shift+B` ou via terminal com `cmake` + `make`);
3. Conecte a Pico via USB e entre em modo de boot (pressione BOOTSEL e conecte);
4. Copie o arquivo `.uf2` gerado para o disco `RPI-RP2`;
5. A execução exibirá os valores X, Y e o estado do botão no terminal e no display OLED.

## 🧮 Lógica

- O joystick possui dois eixos analógicos (X e Y), lidos via ADC;
- A leitura do botão é digital (nível lógico baixo quando pressionado);
- O display OLED mostra os valores centralizados na tela, atualizados em tempo real;
- O terminal também exibe os valores para depuração.

## 📁 Arquivos

- `src/main.c`: Código principal do projeto.

## 🖼️ Visualização


## 📈 Resultados esperados  
- O terminal exibe os valores dos eixos e do botão continuamente;
- O display OLED mostra os mesmos dados centralizados com atualização suave.
- Exemplo de leitura exibida no OLED/terminal:
    - X: 512, Y: 403
    - Button: Pressionado

---

## 📜 Licença  
MIT License  
 
