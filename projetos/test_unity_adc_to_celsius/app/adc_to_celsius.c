#include "adc_to_celsius.h"

float adc_to_celsius(uint16_t adc_val) {
    const float Vref = 3.3f;
    const float adc_max = 4095.0f;
    float voltage = (adc_val * Vref) / adc_max;
    float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
    // Limita a temperatura a uma faixa realista
    // if (temperature < -40.0f) return -40.0f;
    //if (temperature > 150.0f) return 150.0f;
    return temperature;
}