#include "btn_matrix.h"
#include "stm32f3xx_hal.h"

GPIO_TypeDef *R_PORTS[MATRIX_SIZE] = {R1_PORT, R2_PORT, R3_PORT, R4_PORT};
GPIO_TypeDef *C_PORTS[MATRIX_SIZE] = {C1_PORT, C2_PORT, C3_PORT, C4_PORT};

uint16_t R_PINS[MATRIX_SIZE] = {R1_PIN, R2_PIN, R3_PIN, R4_PIN};
uint16_t C_PINS[MATRIX_SIZE] = {C1_PIN, C2_PIN, C3_PIN, C4_PIN};

char matrix[MATRIX_SIZE][MATRIX_SIZE] = MATRIX_CHARS;

void write_row(const int row)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		HAL_GPIO_WritePin(R_PORTS[i], R_PINS[i], row == i ? GPIO_PIN_RESET : GPIO_PIN_SET);
	}
}

char get_matrix_btn(void)
{

	for (int j = 0; j < MATRIX_SIZE; j++)
	{
		write_row(j);

		for (int i = 0; i < MATRIX_SIZE; i++)
		{
			if (!(HAL_GPIO_ReadPin(C_PORTS[i], C_PINS[i])))
			{
				while (!(HAL_GPIO_ReadPin(C_PORTS[i], C_PINS[i])));
				return matrix[j][i];
			}
		}
	}
	return UNKNWN_CHAR;
}