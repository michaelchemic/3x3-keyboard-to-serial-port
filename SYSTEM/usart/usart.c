/*=======================usart.c======================*/
#include "usart.h"
/**
 * 功能：串口初始化函数
 * 参数：None
 * 返回值：None
 */
void usart_init(void)
{
    GPIO_InitTypeDef GPIO_Init_Structure;   // 定义GPIO结构体
    USART_InitTypeDef USART_Init_Structure; // 定义串口结构体
    NVIC_InitTypeDef NVIC_Init_Structure;   // 定义中断结构体
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    RCC_APB2PeriphClockCmd(USART1_GPIO_CLK, ENABLE);       // 开启GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   // 开启APB2总线复用时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // 开启USART1时钟

    // 配置PA9  TX
    GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽
    GPIO_Init_Structure.GPIO_Pin = USART1_TX_GPIO_PIN;
    GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_GPIO_PORT, &GPIO_Init_Structure);

    // 配置PA10 RX
    GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 复用推挽
    GPIO_Init_Structure.GPIO_Pin = USART1_RX_GPIO_PIN;
    GPIO_Init(USART1_GPIO_PORT, &GPIO_Init_Structure);
    // 串口相关配置
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                   // 串口中断配置
    USART_Init_Structure.USART_BaudRate = 115200;                                    // 波特率设置为115200
    USART_Init_Structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控制为无
    USART_Init_Structure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 // 模式设为收和发
    USART_Init_Structure.USART_Parity = USART_Parity_No;                             // 无校验位
    USART_Init_Structure.USART_StopBits = USART_StopBits_1;                          // 一位停止位
    USART_Init_Structure.USART_WordLength = USART_WordLength_8b;                     // 字长为8位
    USART_Init(USART1, &USART_Init_Structure);                                       // 初始化
    USART_Cmd(USART1, ENABLE);                                                       // 串口使能

    // 中断结构体配置
    NVIC_Init_Structure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_Init_Structure);
}

void usart_init3(void)
{
    GPIO_InitTypeDef GPIO_Init_Structure;   // 定义GPIO结构体
    USART_InitTypeDef USART_Init_Structure; // 定义串口结构体
    NVIC_InitTypeDef NVIC_Init_Structure;   // 定义中断结构体
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    RCC_APB2PeriphClockCmd(USART3_GPIO_CLK, ENABLE);       // 开启GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   // 开启APB2总线复用时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); // 开启USART1时钟

    // 配置PB10 TX
    GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽
    GPIO_Init_Structure.GPIO_Pin = USART3_TX_GPIO_PIN;
    GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(USART3_GPIO_PORT, &GPIO_Init_Structure);

    // 配置PB11 RX
    GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 复用推挽
    GPIO_Init_Structure.GPIO_Pin = USART3_RX_GPIO_PIN;
    GPIO_Init(USART3_GPIO_PORT, &GPIO_Init_Structure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_Init_Structure.USART_BaudRate = 9600;                                      // 波特率设置为9600
    USART_Init_Structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控制为无
    USART_Init_Structure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 // 模式设为收和发
    USART_Init_Structure.USART_Parity = USART_Parity_No;                             // 无校验位
    USART_Init_Structure.USART_StopBits = USART_StopBits_1;                          // 一位停止位
    USART_Init_Structure.USART_WordLength = USART_WordLength_8b;                     // 字长为8位
    USART_Init(USART3, &USART_Init_Structure);
    USART_Cmd(USART3, ENABLE);

    // 中断结构体配置
    NVIC_Init_Structure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 3;
    NVIC_Init(&NVIC_Init_Structure);
}

// 三个串口初始化函数
void Init_Usart(void)
{
    usart_init();
    usart_init3();
}

/**
 * 功能：串口写字节函数
 * 参数1：USARTx ：串口号
 * 参数2：Data   ：需写入的字节
 * 返回值：None
 */
void USART_Send_Byte(USART_TypeDef *USARTx, uint16_t Data)
{
    USART_SendData(USARTx, Data);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        ;
}
/**
 * 功能：串口写字符串函数
 * 参数1：USARTx ：串口号
 * 参数2：str    ：需写入的字符串
 * 返回值：None
 */
void USART_Send_String(USART_TypeDef *USARTx, char *str)
{
    uint16_t i = 0;
    do
    {
        USART_Send_Byte(USARTx, *(str + i));
        i++;
    } while (*(str + i) != '\0');

    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        ;
}
/**
 * 功能：重定向
 */
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        ;
    return (ch);
}
/**
 * 功能：重定向
 */
int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        ;
    return (int)USART_ReceiveData(USART1);
}


