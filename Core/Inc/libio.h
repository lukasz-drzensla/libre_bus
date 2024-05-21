#ifndef _LIBIO_H
#define _LIBIO_H

#include "LCD1602.h"

#define LCD_LEN 16

void println(char* str);

void print (char* str);

void move_cursor (int row, int col);

void cls (void);

unsigned int sleep (unsigned int seconds);
int msleep (unsigned int msec);

int getchar(void);

void init_arr (char* array, size_t len, char c);

#endif /* _LIBIO_H */