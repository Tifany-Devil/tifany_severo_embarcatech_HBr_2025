#include "led_embutido.h"
#include "pico/cyw43_arch.h"

// Liga o LED usando acesso direto
void led_embutido_on(void) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
}

// Desliga o LED usando acesso direto
void led_embutido_off(void) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
}
