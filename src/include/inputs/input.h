#ifndef _INPUT_H
#define _INPUT_H

#include <stdint.h>
#include <stdbool.h>
#include <config.h>

union input_data {
    uint8_t dummy;
};

struct input {
    char type_name[LIMIT_TYPE_NAME_LEN];
    uint8_t type_id;
    union input_data data;
    void *test;
    void *max_value;
    void *min_value;
    void *cur_value;
    /* By default, all inputs are calculated in metric units. */
    bool imperial;
};

struct input_type {
    char name[LIMIT_TYPE_NAME_LEN];
    void (*init)(struct input *input);
    void (*read)(struct input *input);
};

#define INPUT_TABLE_DEF(NAME, PREFIX) {NAME, PREFIX##_init, PREFIX##_read}
#define INPUT_TABLE_END()             {"", NULL, NULL}
#define INPUT_NOT_FOUND 0xff

extern struct input_type input_type_table[];

#endif
