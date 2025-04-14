#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include <string.h>
#include "hardware/gpio.h"

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


float read_internal_temperature() {
    // Inicializa o ADC e seleciona o canal do sensor de temperatura interno
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);  // Canal 4 = sensor de temperatura interno

    // Lê o valor cru do ADC (12 bits)
    uint16_t raw = adc_read();

    // Converte o valor lido para voltagem
    float voltage = raw * (3.3f / (1 << 12));  // 12 bits = 4096 = 2^12

    // Converte para temperatura em Celsius
    float temperature_celsius = 27.0f - (voltage - 0.706f) / 0.001721f;

    return temperature_celsius;
}

float celsius_to_fahrenheit(float temp_celsius) {
    return temp_celsius * 9.0f / 5.0f + 32.0f;
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


    // Aguarda conexão USB (até 3 segundos)
    for (int i = 0; i < 30; i++) {
        if (stdio_usb_connected()) break;
        sleep_ms(100);
    }

    while (true) {
        float temperatureC = read_internal_temperature();
        float temperatureF = celsius_to_fahrenheit(temperatureC);

        printf("Internal Temperature: %.2f °C\n", temperatureC);
        printf("Internal Temperature: %.2f °F\n", temperatureF);

        //No display
        char buf[16];

        memset(ssd, 0, sizeof(ssd));  // Limpa o display
        
        snprintf(buf, sizeof(buf), "Temperatura");
        draw_centered_string(ssd, 16, buf); //linha 16
        
        snprintf(buf, sizeof(buf),"%.2f °C", temperatureC);
        draw_centered_string(ssd, 32, buf); //linha 32
        
        update_display();  // Atualiza o display com tudo já desenhado
        
        sleep_ms(1000);
        
    }

    return 0;
}

