#ifndef _STATE_H
#define _STATE_H

#include <stdint.h>
#include <stdbool.h>

#include <config.h>
#include <gauges/gauge.h>

/* Struct for storing whole system state */
struct state {
    uint32_t pin;

    struct gauge gauges[LIMIT_MAX_GAUGES];
};

#endif
