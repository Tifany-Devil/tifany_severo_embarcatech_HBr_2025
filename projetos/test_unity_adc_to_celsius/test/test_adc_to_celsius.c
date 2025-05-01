#include "unity.h"
#include "adc_to_celsius.h"
#include "pico/stdlib.h"

void setUp(void) {}
void tearDown(void) {}

void test_adc_to_celsius_known_value(void) {
    uint16_t adc_val = (uint16_t)((0.706f / 3.3f) * 4095.0f); // ~875, deve dar ~27°C
    float temp = adc_to_celsius(adc_val);
    TEST_ASSERT_FLOAT_WITHIN(0.5f, 27.0f, temp);
}

void test_adc_to_celsius_zero_adc(void) {
    uint16_t adc_val = 0; // Valor mínimo do ADC
    float temp = adc_to_celsius(adc_val);
    float expected = 27.0f - ((0.0f - 0.706f) / 0.001721f); // ~438°C (valor teórico)
    TEST_ASSERT_FLOAT_WITHIN(1.0f, expected, temp);
}

void test_adc_to_celsius_max_adc(void) {
    uint16_t adc_val = 4095; // Valor máximo do ADC
    float temp = adc_to_celsius(adc_val);
    float expected = 27.0f - ((3.3f - 0.706f) / 0.001721f); // ~-1478°C (valor teórico)
    TEST_ASSERT_FLOAT_WITHIN(1.0f, expected, temp);
}

void test_adc_to_celsius_mid_range(void) {
    uint16_t adc_val = (uint16_t)((0.856f / 3.3f) * 4095.0f); // ~1062, equivalente a ~0.856V
    float temp = adc_to_celsius(adc_val);
    float expected = 27.0f - ((0.856f - 0.706f) / 0.001721f); // ~-60°C (valor teórico)
    TEST_ASSERT_FLOAT_WITHIN(0.5f, expected, temp);
}

void test_adc_to_celsius_negative_temperature(void) {
    uint16_t adc_val = (uint16_t)((0.756f / 3.3f) * 4095.0f); // ~938, equivalente a ~0.756V
    float temp = adc_to_celsius(adc_val);
    float expected = 27.0f - ((0.756f - 0.706f) / 0.001721f); // ~-2°C (valor teórico)
    TEST_ASSERT_FLOAT_WITHIN(0.5f, expected, temp);
}

int main(void) {
    stdio_init_all();
    sleep_ms(5000); // Aguarda 5 segundos para garantir que a serial esteja pronta

    UNITY_BEGIN();

    printf("Iniciando os testes...\n");
    sleep_ms(2000);
    RUN_TEST(test_adc_to_celsius_known_value);
    RUN_TEST(test_adc_to_celsius_zero_adc);
    RUN_TEST(test_adc_to_celsius_max_adc);
    RUN_TEST(test_adc_to_celsius_mid_range);
    RUN_TEST(test_adc_to_celsius_negative_temperature);

    return UNITY_END();
}