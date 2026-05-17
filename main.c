#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "vl53l5cx_api.h"

// I2C defines
// This example will use I2C0 on GPIO4 (SDA) and GPIO5 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5

int main()
{
    stdio_init_all();
    printf("UART stdout initialized on UART0 TX GP0 / RX GP1 at 115200 baud.\n");

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    VL53L5CX_Configuration dev;
    dev.platform.i2c = i2c0;
    dev.platform.address = VL53L5CX_I2C_ADDR;
    uint8_t status;
    status = vl53l5cx_init(&dev);
    printf("init status = %d\n", status);

    VL53L5CX_ResultsData Results;
    uint8_t isReady;
    uint8_t i;

    vl53l5cx_set_resolution(&dev, VL53L5CX_RESOLUTION_4X4);
    status = vl53l5cx_start_ranging(&dev);
    for (; true; sleep_ms(VL53L5CX_WaitMs(&(dev.platform), 5)))
    {
        status = vl53l5cx_check_data_ready(&dev, &isReady);
        if (isReady)
        {
            vl53l5cx_get_ranging_data(&dev, &Results);
            printf("Print data no : %3u\n", dev.streamcount);
            for (i = 0; i < 16; i++)
            {
                uint8_t sta = Results.target_status[VL53L5CX_NB_TARGET_PER_ZONE * i];
                int16_t dist = Results.distance_mm[VL53L5CX_NB_TARGET_PER_ZONE * i];
                uint32_t sign = Results.signal_per_spad[VL53L5CX_NB_TARGET_PER_ZONE * i];
                uint32_t amb = Results.ambient_per_spad[VL53L5CX_NB_TARGET_PER_ZONE * i];
                if ((sta == 5 || sta == 6) &&
                    (100 <= dist && dist <= 2500))
                {
                    printf("[*]");
                }
                else
                {
                    printf("[ ]");
                }
                if (((i + 1) % 4) == 0)
                {
                    printf("\n");
                }
            }
            printf("\n");
        }
    }
}
