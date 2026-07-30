#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/adc.h"
#include "max7219.h"

//for monitoring adc value on display
#define SPI_PORT spi0
#define SPI_BAUD_RATE 1*1000*1000 //1 MHz
#define SPI_CLK 2
#define SPI_MOSI 3
#define SPI_MISO 4
#define SPI_CS 5

uint16_t val;
bool adc_find(struct repeating_timer *t){
    val = adc_read();
    return true;
}

int main()
{
    stdio_init_all();

    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    spi_init(SPI_PORT, SPI_BAUD_RATE);

    gpio_set_function(SPI_CLK, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO, GPIO_FUNC_SPI);
    gpio_init(SPI_CS);
    gpio_set_dir(SPI_CS, GPIO_OUT);

    spi_set_format(SPI_PORT, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    //initialize max7219
    max7219_t mx;
    max7219_init(&mx, SPI_PORT, SPI_CS, 4);

    struct repeating_timer time;
    add_repeating_timer_ms(200, adc_find, NULL, &time);
    while (true) {
        // val = adc_read();
        // printf("Read : %d\n", val);
        // sleep_ms(250);
        max7219_display_char(mx, (val/1)%10 + '0', 0b0001);
        max7219_display_char(mx, (val/10)%10 + '0', 0b0010);
        max7219_display_char(mx, (val/100)%10 + '0', 0b0100);
        max7219_display_char(mx, (val/1000)%10 + '0', 0b1000);
        sleep_ms(200);
    }
}
