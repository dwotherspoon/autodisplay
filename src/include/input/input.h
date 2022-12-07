#ifndef _INPUT_H
#define _INPUT_H

struct input_config_t {
    uint8_t input_type_id;

    void *test;
    void *max_value;
    void *min_value;
    void *cur_value;
};

struct input_type_t {
    char *name;
    void *test;
    /* The maximum and minimum possible values for this input,
        Used for rendering dial faces and sanity checking. */
    void *max_value;
    void *min_value;
    void *cur_value;
};

extern input_type_t input_type_table[];

#endif