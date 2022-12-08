#ifndef _STATE_H
#define _STATE_H

#include <stdint.h>
#include <stdbool.h>

#include <config.h>
#include <gauges/gauge.h>

/* Struct for storing whole system state */
struct state_t {
    uint32_t pin;

    struct gauge_t gauges[LIMIT_MAX_GAUGES];
};

#endif