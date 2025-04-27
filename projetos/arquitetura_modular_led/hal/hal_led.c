#include "hal_led.h"
#include "led_embutido.h"

// Se state == 1, liga o LED; se state == 0, desliga
void hal_led_toggle(int state) {
    if (state) {
        led_embutido_on();   // Chama o driver
    } else {
        led_embutido_off();  // Chama o driver
    }
}
