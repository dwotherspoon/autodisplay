#ifndef _INPUT_BME280_H
#define _INPUT_BME280_H

#include <inputs/input.h>

struct input_bme280_data_t {
    uint8_t dummy;
};

void input_bme280_init(struct input_t *input);
void input_bme280_read(struct input_t *input);

#endif
