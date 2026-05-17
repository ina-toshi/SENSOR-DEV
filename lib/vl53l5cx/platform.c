#include "platform.h"
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

uint8_t VL53L5CX_RdByte(
    VL53L5CX_Platform *p_platform,
    uint16_t RegisterAdress,
    uint8_t *p_value)
{
    return VL53L5CX_RdMulti(p_platform, RegisterAdress, p_value, 1);

}

uint8_t VL53L5CX_WrByte(
    VL53L5CX_Platform *p_platform,
    uint16_t RegisterAdress,
    uint8_t value)
{
    return VL53L5CX_WrMulti(p_platform, RegisterAdress, &value, 1);
}

uint8_t VL53L5CX_WrMulti(
    VL53L5CX_Platform *p_platform,
    uint16_t RegisterAdress,
    uint8_t *p_values,
    uint32_t size)
{
    uint8_t buffer[2 + size];

    buffer[0] = (RegisterAdress >> 8) & 0xFF;
    buffer[1] = RegisterAdress & 0xFF;
    memcpy(&buffer[2], p_values, size);
    int ret = i2c_write_blocking(
        p_platform->i2c,
        p_platform->address,
        buffer,
        size + 2,
        false);
    return (ret < 0) ? 1 : 0;
}

uint8_t VL53L5CX_RdMulti(
    VL53L5CX_Platform *p_platform,
    uint16_t RegisterAdress,
    uint8_t *p_values,
    uint32_t size)
{
    uint8_t reg[2];
    int ret;
    reg[0] = (RegisterAdress >> 8) & 0xFF;
    reg[1] = RegisterAdress & 0xFF;
    ret = i2c_write_blocking(p_platform->i2c, p_platform->address, reg, 2, true);
    if (ret < 0) return 1;
    ret = i2c_read_blocking(p_platform->i2c, p_platform->address, p_values, size, false);
    if (ret < 0) return 1;
    return 0;
}

uint8_t VL53L5CX_WaitMs(
    VL53L5CX_Platform *p_platform,
    uint32_t TimeMs)
{
    (void)p_platform;
    sleep_ms(TimeMs);
    return 0;
}

void VL53L5CX_SwapBuffer(
    uint8_t *buffer,
    uint16_t size)
{
    uint8_t tmp;

    for (uint16_t i = 0; i < size; i += 4) {
        tmp = buffer[i];
        buffer[i] = buffer[i + 3];
        buffer[i + 3] = tmp;

        tmp = buffer[i + 1];
        buffer[i + 1] = buffer[i + 2];
        buffer[i + 2] = tmp;
    }
}
