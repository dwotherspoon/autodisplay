#include <string.h>

#include <debug.h>
#include <inputs/input.h>
#include <inputs/input_bme280.h>

struct input_type input_type_table[] = {
    INPUT_TABLE_DEF("BME280", input_bme280),
    INPUT_TABLE_END()
};

struct input_type *input_find_type(char *name) {
    uint8_t id;
    ASSERT(name != NULL, "Null input name specified.");

    for (id = 0; input_type_table[id].name[0] != 0; id++) {
        if (strcmp(name, input_type_table[id].name) == 0) {
            return &input_type_table[id];
        }
    }

    return NULL;
}
