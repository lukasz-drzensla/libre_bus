#ifndef _BUSCOM_H
#define _BUSCOM_H

#include "Driver.h"

void buscom_send_credentials (const struct Driver* driver);
int buscom_get_credentials_resp ();
void buscom_send_line(int line, int dir);
int buscom_get_line();

#endif /* _BUSCOM_H */