#ifndef _DRIVER_H
#define _DRIVER_H

#include "libio.h"
#include "STRRES.h"

#define ID_LEN 4
#define BUS_LINE_LEN 4
#define SINGLE_CHOICE 1
#define VALID_UNLOCK 0
#define VALID_LOCK 1

struct Driver {
    uint16_t id;
    uint16_t passcode;
    uint8_t lock_status;
    void (*login_process)(struct Driver* driver);
    void (*enter_line_process)(struct Driver* driver);
    uint8_t (*toggle_valid_lock)(struct Driver* driver);
    void (*display_stop)(struct Driver* driver);
    void (*next_stop)(void);
};

void driver_init(struct Driver* driver);

#endif /* _DRIVER_H */