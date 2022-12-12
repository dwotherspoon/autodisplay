#include <string.h>

#include <debug.h>
#include <gauges/gauge.h>
#include <gauges/gauge_test.h>
#include <gauges/gauge_dial.h>

/* Note, it is assumed number of gauge types is small, 8-bit ID is used. */
struct gauge_type_t gauge_table[] = {
    GAUGE_TABLE_DEF("Test Gauge", gauge_test),
    GAUGE_TABLE_DEF("Dial Gauge", gauge_dial),
    GAUGE_TABLE_END()
};

/** Find id of gauge in gauge table from name.
    @param name String, name of gauge to find.
    @return The id of the gauge in the table, or GAUGE_NOT_FOUND (0xFF) on failure.
*/
uint8_t gauge_find_id(char *name) {
    uint8_t id;
    ASSERT(name != NULL, "Null input gauge name specified.");

    for (id = 0; gauge_table[id].name[0] != 0; id++) {
        if (strcmp(name, gauge_table[id].name) == 0) {
            return id;
        }
    }

    return GAUGE_NOT_FOUND;
}

/** My function doing something...
    @param param1 first parameter
    @param param2 second parameter
    @return value return value
*/
void gauge_init() {
    /* We copy gauges from config space and build config table */

    /* Render gauge faces */

    /* For each display, we need to build a list of gauges, ordered by the draw order */

}