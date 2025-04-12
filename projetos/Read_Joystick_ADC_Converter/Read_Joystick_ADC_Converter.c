#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include <string.h>
#include "hardware/gpio.h"

#define vRx_PIN 26  // Pino ligado ao eixo X (ADC0)
#define vRy_PIN 27  // Pino ligado ao eixo Y (ADC1)
#define SW 22   // Pino do botão (Digital)

// Definições display OLED
#define FONT_WIDTH 8
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

uint8_t ssd[ssd1306_buffer_length];
struct render_area frame_area;

// Funções auxiliares para o display OLED
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

void update_display() {
    render_on_display(ssd, &frame_area);
}

int main() {
    stdio_init_all();

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


    adc_init();
    adc_gpio_init(vRx_PIN);
    adc_gpio_init(vRy_PIN);
    gpio_init(SW);
    gpio_set_dir(SW, GPIO_IN);
    gpio_pull_up(SW);
    
    while (1) {
        adc_select_input(0); // Seleciona o canal ADC0 (vRx)
        uint16_t x_value = adc_read();
        
        adc_select_input(1); // Seleciona o canal ADC1 (vRy)
        uint16_t y_value = adc_read();
        
        int button_state = gpio_get(SW);
        
        printf("X: %d, Y: %d, Button: %s\n", y_value, x_value, button_state == 0 ? "Pressionado" : "Solto");
        char buf[16];
        snprintf(buf, sizeof(buf), "X: %d, Y: %d, Button: %s\n", y_value, x_value, button_state == 0 ? "Pressionado" : "Solto");
        memset(ssd, 0, sizeof(ssd));
        draw_centered_string(ssd, 24, buf);
        update_display();
        sleep_ms(100);
    }
}