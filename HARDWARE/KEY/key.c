#include "key.h"
#include "delay.h"
#include "stm32f10x.h"

u8 KEY_Scan(void)
{
    u8 i = 0, j = 0;        // 局部变量i和j用来记录按键所在的行和列
    RCC->APB2ENR |= 1 << 3; // 使能时钟

    GPIOB->CRH &= 0XFF000000; // 1111 1111 0000 0000 0000 0000 0000 0000 初始化6个GPIO寄存器
    GPIOB->CRH |= 0X00333888; // 0000 0000 0011 0011 0011 1000 1000 1000
    // PB8 mode输入模式，cnf上下拉输入模式。
    // PB9 mode输入模式，cnf上下拉输入模式。
    // PB10 mode输入模式，cnf上下拉输入模式。
    // PB11 mode输出模式，cnf通用推挽输出模式。
    // PB12 mode输出模式，cnf通用推挽输出模式。
    // PB13 mode输出模式，cnf通用推挽输出模式。

    GPIOB->ODR &= 0X00000000; // 将PB8-PB10设置为输入下拉

    PBout(11) = 1; // PB11-PB13推挽输出高电平
    PBout(12) = 1;
    PBout(13) = 1;

    PBin(8) = 0; // PB8-PB9设置低电平
    PBin(9) = 0;
    PBin(10) = 0;
    if (PBin(8) == 1 || PBin(9) == 1 || PBin(10) == 1) // 第一次条件或判断，其中任意一个为真就为真
    {
        delay_ms(10);     // 去抖动
        if (PBin(8) == 1) // 再次判断
        {
            i = 1;
        }
        else if (PBin(9) == 1)
        {
            i = 2;
        }
        else if (PBin(10) == 1)
        {
            i = 3;
        }
        else
        {
            return 0;
        }
    }

    // 同上改变行列引脚状态
    GPIOB->CRH &= 0XFF000000; // 1111 1111 0000 0000 0000 0000 0000 0000
    GPIOB->CRH |= 0X00888333; // 0000 0000 1000 1000 1000 0011 0011 0011
    // PB8 mode输出模式，cnf通用推挽输出模式。
    // PB9 mode输出模式，cnf通用推挽输出模式。
    // PB10 mode输出模式，cnf通用推挽输出模式。

    // PB11 mode输入模式，cnf上下拉输入模式。
    // PB12 mode输入模式，cnf上下拉输入模式。
    // PB13 mode输入模式，cnf上下拉输入模式。

    GPIOB->ODR &= 0X00000000;

    PBout(8) = 1;
    PBout(9) = 1;
    PBout(10) = 1;

    PBin(11) = 0;
    PBin(12) = 0;
    PBin(13) = 0;
    if (PBin(11) == 1 || PBin(12) == 1 || PBin(13) == 1)
    {
        delay_ms(10);      // 去抖动
        if (PBin(11) == 1) // 行
        {
            j = 1;
        }
        else if (PBin(12) == 1)
        {
            j = 2;
        }
        else if (PBin(13) == 1)
        {
            j = 3;
        }
        else
        {
            return 0;
        }
    }

    // 根据行列判断按键位置
    if (j == 1 && i == 1)
        return 7;
    else if (j == 1 && i == 2)
        return 8;
    else if (j == 1 && i == 3)
        return 9;
    else if (j == 2 && i == 1)
        return 4;
    else if (j == 2 && i == 2)
        return 5;
    else if (j == 2 && i == 3)
        return 6;
    else if (j == 3 && i == 1)
        return 1;
    else if (j == 3 && i == 2)
        return 2;
    else if (j == 3 && i == 3)
        return 3;
    else
        return 0;
}
