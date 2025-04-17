#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/time.h"

#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include <string.h>

// === Definições ===
#define BOTAO_A 5
#define BOTAO_B 6

#define FONT_WIDTH 8
#define I2C_SDA 14
#define I2C_SCL 15

uint8_t ssd[ssd1306_buffer_length];
struct render_area frame_area;

// === Variáveis globais ===
volatile int contador = 0;
volatile int cliques_botao_b = 0;
volatile bool contando = false;

// === Funções auxiliares para o display OLED ===
int get_text_width(const char* text) {
    return strlen(text) * FONT_WIDTH;
}

int get_centered_x(const char* text) {
    int text_width = get_text_width(text);
    return (128 - text_width) / 2;
}

void draw_centered_string(uint8_t *buffer, int y, const char *text) {
    int x = get_centered_x(text);
    ssd1306_draw_string(buffer, x, y, text);
}

void update_display_oled() {
    char buf[16];

    memset(ssd, 0, sizeof(ssd));  // Limpa o display

    snprintf(buf, sizeof(buf), "Contador: %d", contador);
    draw_centered_string(ssd, 16, buf);

    snprintf(buf, sizeof(buf), "Cliques B: %d", cliques_botao_b);
    draw_centered_string(ssd, 32, buf);

    render_on_display(ssd, &frame_area);  
}


// === Callback dos botões ===
void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == BOTAO_A && (events & GPIO_IRQ_EDGE_FALL)) {
        if (!contando) {
            contador = 9;
            cliques_botao_b = 0;
            contando = true;
            printf("[A] Iniciando contagem!\n");
        }
    } else if (gpio == BOTAO_B && (events & GPIO_IRQ_EDGE_FALL)) {
        if (contando) {
            cliques_botao_b++;
            printf("[B] Clique registrado! Total: %d\n", cliques_botao_b);
        }
    }
}

int main() {
    stdio_init_all();

    // === Inicialização I2C e Display ===
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init();

    frame_area.start_column = 0;
    frame_area.end_column   = ssd1306_width - 1;
    frame_area.start_page   = 0;
    frame_area.end_page     = ssd1306_n_pages - 1;
    calculate_render_area_buffer_length(&frame_area);
    memset(ssd, 0, sizeof(ssd));
    render_on_display(ssd, &frame_area);

    // === Configuração dos botões ===
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);

    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B);

    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled(BOTAO_B, GPIO_IRQ_EDGE_FALL, true);

    printf("Sistema iniciado. Pressione o Botão A para começar.\n");

    while (true) {
        if (contando) {
            // Mostra e imprime o valor atual
            update_display_oled();
            printf("Contagem: %d | Cliques B: %d\n", contador, cliques_botao_b);

            sleep_ms(1000); // espera 1 segundo

            contador--;

            if (contador < 0) {
                contando = false;
                contador = 0;
                printf("Contagem finalizada. Cliques B: %d\n", cliques_botao_b);
                update_display_oled(); // Atualiza para mostrar o zero final
            }
        } else {
            sleep_ms(100); // espera leve quando parado
        }
    }

    return 0;
}
