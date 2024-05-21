#include "buscom.h"

uint16_t recv_id = 0; //dummy
uint16_t recv_pass = 0; //dummy
int recv_line = 0;

void buscom_send_credentials (const struct Driver* driver)
{
    recv_id = driver->id; //dummy
    recv_pass = driver->passcode; //dummy
}

int buscom_get_credentials_resp ()
{
    return (recv_id == 1111 && recv_pass == 1111); //dummy
}

void buscom_send_line(int line, int dir)
{
    UNUSED(dir);
    recv_line = line; //dummy
}

int buscom_get_line()
{
    return recv_line == 111; //dummy
}