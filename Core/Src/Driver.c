#include "Driver.h"
#include "buscom.h"

void display_welcome (void);
void display_enter_ID (void);
void login_process (struct Driver* driver);
void enter_line_process(struct Driver* driver);
void gather_input(char* input_str, size_t input_len, unsigned int sleep_time);
uint8_t toggle_valid_lock(struct Driver* driver);
void display_stop(struct Driver* driver);
void next_stop(void);

char next_stop_str[LCD_LEN];

void driver_init(struct Driver* driver)
{
    driver->login_process = login_process;
    driver->enter_line_process = enter_line_process;
    driver->toggle_valid_lock = toggle_valid_lock;
    driver->lock_status = VALID_UNLOCK;
    driver->display_stop = display_stop;
    init_arr(next_stop_str, LCD_LEN, ' ');
    driver->next_stop = next_stop;
}

void display_welcome (void)
{
    println(WELCOME_STR);
}

void display_enter_ID (void)
{
    cls();
    move_cursor(0,0);
    print(ENTER_ID_STR);
}

void login_process (struct Driver* driver)
{
    unsigned char login_successful = 0;
    do {
        char input_ch = 'X';
        char input_str [LCD_LEN];
        char asterisks_str [LCD_LEN];
        display_welcome();
        sleep(3);
        display_enter_ID();
        init_arr(input_str, LCD_LEN, ' ');
        init_arr(asterisks_str, LCD_LEN, ' ');
        for (int i = 0; i < ID_LEN; i++)
        {
            input_str[i] = (char)getchar();
            if ('B' == input_str[i])
            {
                input_str[i] = ' ';
                if (i > 0)
                {
                    input_str[--i] = ' ';
                }
                --i;
            }
            move_cursor(1,0);
            print(input_str);
            msleep(200);
        }   
        while ((input_ch = (char)getchar()))
        {
            /* TODO: some cancel */
            if ('E' == input_ch)
            {
                break;
            }
        }
        if ('E' == input_ch)
        {
            driver->id = (input_str[0] - 48) * 1000 + (input_str[1] - 48) * 100 + (input_str[2] - 48) * 10 + (input_str[3] - 48);
        }
        println(ENTER_PASSCODE_STR);
        init_arr(input_str, LCD_LEN, ' ');
        for (int i = 0; i < ID_LEN; i++)
        {
            input_str[i] = (char)getchar();
            if ((input_str[i] >= '0' && input_str[i] <= '9') || input_str[i] == 'B')
            {                
                asterisks_str[i] = '*';
                if ('B' == input_str[i])
                {
                    input_str[i] = ' ';
                    asterisks_str[i] = ' ';
                    if (i > 0)
                    {
                        input_str[i-1] = ' ';
                        asterisks_str[i-1] = ' ';
                        --i;
                    }
                    --i;
                }
                move_cursor(1,0);
                print(asterisks_str);
                msleep(200);
            } else {
                --i;
            }
        }
        while ((input_ch = (char)getchar()))
        {
            /* TODO: some cancel */
            if ('E' == input_ch)
            {
                break;
            }
        }
        cls();
        driver->passcode = (input_str[0] - 48) * 1000 + (input_str[1] - 48) * 100 + (input_str[2] - 48) * 10 + (input_str[3] - 48);
        buscom_send_credentials(driver);
        int result = buscom_get_credentials_resp(); /* TODO: loop and timeout */
        if (result)
        {
            println(LOGIN_SUCCESS_STR);
            login_successful = 1;
        } else {
            println(LOGIN_FAILED_STR);
        }
    } while (!login_successful);
}

void gather_input(char* input_str, size_t input_len, unsigned int sleep_time)
{
    for (int i = 0; i < input_len; i++)
    {
        input_str[i] = (char)getchar();
        if ((input_str[i] >= '0' && input_str[i] <= '9') || input_str[i] == 'B' || input_str[i] == 'E')
        {
            if ('B' == input_str[i])
            {
                input_str[i] = ' ';
                if (i > 0)
                {
                    input_str[--i] = ' ';
                }
                --i;
            } else if ('E' == input_str[i])
            {
                for (int j = 0; j < input_len - i; j++)
                {
                    for (int k = input_len; k > 0; k--)
                    {
                        input_str[k]=input_str[k-1];
                        input_str[k-1] = '0';
                    }
                }
                break;
            }
            move_cursor(1,0);
            print(input_str);
            msleep(sleep_time);
        } else {
            --i;
        }
    }
}

void enter_line_process(struct Driver* driver)
{
    char input_str [LCD_LEN];

    cls();
    println(ENTER_LINE_STR);
    msleep(1000);
    init_arr(input_str, LCD_LEN, ' ');
    gather_input(input_str, BUS_LINE_LEN, 200);
    /* TODO: send function and receive reply */
    cls();
    println(CHOOSE_DIR_STR);
    msleep(3000);
    cls();
    move_cursor(0,0);
    print("0: Dir 0");
    move_cursor(1,0);
    print("1: Dir 1");

    char direction [SINGLE_CHOICE];

    gather_input (direction, SINGLE_CHOICE, 200);
    
    /* TODO: send result to master */

    cls();
}

uint8_t toggle_valid_lock(struct Driver* driver)
{
    driver->lock_status = !driver->lock_status;
    /* TODO: send to master */
    return driver->lock_status;
}

void display_stop(struct Driver* driver)
{
    println(DISP_STOP_STR);
    move_cursor(1,0);
    print(next_stop_str);
}

int stops = 0;
void next_stop(void)
{
    /* TODO: send request, gather reply */
    stops++;
    next_stop_str[0] = (char)(stops+48); /* dummy! */
}