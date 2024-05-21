#ifndef _BUSCOM_H
#define _BUSCOM_H

#include "Driver.h"

void buscom_send_credentials (const struct Driver* driver);
int buscom_get_credentials_resp ();

#endif /* _BUSCOM_H */