#include "stm32f10x.h"
#include "sys.h"
#include "lcd.h"
#include "delay.h"
#include "usart.h"
#include "key.h"

int main(void)
{
    vu8 t;
    Init_Usart();
    delay_init();

    while (1) {

        t = KEY_Scan();

        switch (t) {
            case KEY1_PRES:
                USART_Send_String(USART1, "1");
                delay_ms(250);
                break;
            case KEY2_PRES:
                USART_Send_String(USART1, "2");
                delay_ms(250);
                break;
            case KEY3_PRES:
                USART_Send_String(USART1, "3");
                delay_ms(250);
                break;
            case KEY4_PRES:
                USART_Send_String(USART1, "4");
                delay_ms(250);
                break;
            case KEY5_PRES:
                USART_Send_String(USART1, "5");
                delay_ms(250);
                break;
            case KEY6_PRES:
                USART_Send_String(USART1, "6");
                delay_ms(250);
                break;
            case KEY7_PRES:
                USART_Send_String(USART1, "7");
                delay_ms(250);
                break;
            case KEY8_PRES:
                USART_Send_String(USART1, "8");
                delay_ms(250);
                break;
            case KEY0_PRES:
                USART_Send_String(USART1, "0");
                delay_ms(250);
                break;
        }
    }
}

void USART1_IRQHandler(void)
{
    char temp;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        temp = USART_ReceiveData(USART1);
        if (temp == 'A') {
            USART_Send_String(USART1, "USART1 Send Successful\n");
        }
    }
}

void USART3_IRQHandler(void)
{
    char temp;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
        temp = USART_ReceiveData(USART3);
        if (temp == 'C') {

            USART_Send_String(USART1, "USART3 Send Successful\n");
        }
    }
}
