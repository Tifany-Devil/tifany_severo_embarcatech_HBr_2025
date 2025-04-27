#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hal_led.h"  // Importa a HAL

int main() {
    stdio_init_all(); // Inicializa sistema de printf
    if (cyw43_arch_init()) { // Inicializa Wi-Fi (LED está nesse módulo)
        return -1; // Erro na inicialização
    }

    while (true) {
        hal_led_toggle(1); // Liga LED
        sleep_ms(500);     // Espera 500 ms
        hal_led_toggle(0); // Desliga LED
        sleep_ms(500);     // Espera 500 ms
    }
}
