# 💡 Arquitetura Modular para Controle de LED  
Este projeto implementa uma arquitetura modular para controle do LED embutido utilizando a *Raspberry Pi Pico W* (ou outro microcontrolador compatível com SDK Pico C/C++).

## 🎯 Objetivo  
Demonstrar a estruturação de um projeto embarcado utilizando separação em camadas (*drivers*, *HAL* e *app*) para facilitar manutenção e reutilização de código, além de exemplificar a abstração de acesso ao hardware.

## 🔧 Componentes  
- Raspberry Pi Pico W  

## ⚡ Pinagem  
| Componente        | Pino         |
|-------------------|--------------|
| LED Embutido Wi-Fi | Controlado pelo driver cyw43_arch interno |

## 🚀 Execução

1. Abra o projeto no VS Code com suporte ao SDK do Raspberry Pi Pico (CMake + compilador ARM);
2. Compile o projeto (Ctrl+Shift+B no VS Code ou via terminal com cmake e make);
3. Conecte a Pico via USB e coloque-a em modo de boot (pressione o botão *BOOTSEL* ao conectar);
4. Copie o arquivo .uf2 gerado para a unidade de armazenamento que aparecer (RPI-RP2);
5. A Pico reiniciará automaticamente e iniciará o programa;
6. Observe o LED embutido piscando, controlado pela função de abstração da HAL.

## 📋 Lógica do Programa

- A aplicação (`app/main.c`) chama apenas funções da HAL, sem lidar diretamente com detalhes do hardware;
- A HAL (`hal/hal_led.c`) fornece funções simples (como `hal_led_toggle()`) para manipular o LED;
- O driver (`drivers/led_embutido.c`) faz o controle real do LED, acessando diretamente o hardware via `cyw43_arch`;
- As interfaces (`include/*.h`) conectam essas camadas de forma organizada.

## 📁 Arquivos

- **app/main.c**: Contém a lógica principal da aplicação. Chama apenas funções da HAL, sem interagir diretamente com hardware.
- **hal/hal_led.c**: Implementa a camada de abstração de hardware (HAL). Oferece funções simples para controlar o LED, sem expor detalhes do hardware.
- **drivers/led_embutido.c**: Código que interage diretamente com o hardware (cyw43_arch), responsável por acessar o LED embutido.
- **include/**: Contém os cabeçalhos (`.h`) com as declarações de funções, permitindo a comunicação entre os diferentes módulos do projeto.
- **CMakeLists.txt**: Arquivo de configuração para compilar corretamente todo o projeto, organizando as dependências entre os módulos.

## 🖼 Imagens (opcional)

Caso deseje, adicione imagens demonstrando o LED embutido piscando na Pico W.

---

## 📜 Licença  
MIT License