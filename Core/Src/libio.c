#include "libio.h"
#include "btn_matrix.h"

void println(char* str)
{
    char row1[LCD_LEN] = {};
    char row2[LCD_LEN] = {};
    init_arr(row1, LCD_LEN, ' ');
    init_arr(row2, LCD_LEN, ' ');
    unsigned char len = 0;
    while ((*str) != '\0')
    {
        if (len < LCD_LEN)
        {
            row1[len] = *str++; 
        } else {
            row2[len - 16] = *str++;
        }
        ++len;
    }
    cls();
    move_cursor(0,0);
    print(row1);
    move_cursor(1,0);
    print(row2);
}

void print (char* str)
{
    lcd_send_string (str);
}

void move_cursor (int row, int col)
{
    lcd_put_cur(row, col);
}

void cls (void)
{
    lcd_clear();
}

unsigned int sleep (unsigned int seconds)
{
    HAL_Delay (seconds * 1000);
    return 0;
}

int getchar(void)
{
    char result = get_matrix_btn();
    while ('X' == result)
    {
        result = get_matrix_btn();
    }
    return (int)result;
}

int msleep (unsigned int msec)
{
    HAL_Delay(msec);
    return 0;
}

void init_arr (char* array, size_t len, char c)
{
    for (size_t i = 0; i < len; i++)
    {
        array[i] = c;
    }
}