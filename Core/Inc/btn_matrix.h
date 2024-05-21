#ifndef _BTN_MATHIX_H
#define _BTN_MATHIX_H

#include "stm32f3xx_hal.h"

/* Configurable macros according to current matrix and connections */
#define R1_PORT GPIOA
#define R1_PIN GPIO_PIN_5

#define R2_PORT GPIOA
#define R2_PIN GPIO_PIN_6

#define R3_PORT GPIOA
#define R3_PIN GPIO_PIN_7

#define R4_PORT GPIOA
#define R4_PIN GPIO_PIN_2

#define C1_PORT GPIOA
#define C1_PIN GPIO_PIN_4

#define C2_PORT GPIOA
#define C2_PIN GPIO_PIN_3

#define C3_PORT GPIOA
#define C3_PIN GPIO_PIN_1

#define C4_PORT GPIOA
#define C4_PIN GPIO_PIN_0

#define MATRIX_SIZE 4
#define UNKNWN_CHAR 'X'

#define MATRIX_CHARS {{'7', '8', '9', 'M'}, {'4', '5', '6', '<'}, {'1', '2', '3', '>'}, {'B', '0', 'L', 'E'}}

/* Function prototypes */
char get_matrix_btn(void);

#endif /* _BTN_MATHIX_H */