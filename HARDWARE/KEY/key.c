#include "key.h"
#include "delay.h"
#include "stm32f10x.h"

u8 KEY_Scan(void)
{
    u8 i = 0, j = 0;        // �ֲ�����i��j������¼�������ڵ��к���
    RCC->APB2ENR |= 1 << 3; // ʹ��ʱ��

    GPIOB->CRH &= 0XFF000000; // 1111 1111 0000 0000 0000 0000 0000 0000 ��ʼ��6��GPIO�Ĵ���
    GPIOB->CRH |= 0X00333888; // 0000 0000 0011 0011 0011 1000 1000 1000
    // PB8 mode����ģʽ��cnf����������ģʽ��
    // PB9 mode����ģʽ��cnf����������ģʽ��
    // PB10 mode����ģʽ��cnf����������ģʽ��
    // PB11 mode���ģʽ��cnfͨ���������ģʽ��
    // PB12 mode���ģʽ��cnfͨ���������ģʽ��
    // PB13 mode���ģʽ��cnfͨ���������ģʽ��

    GPIOB->ODR &= 0X00000000; // ��PB8-PB10����Ϊ��������

    PBout(11) = 1; // PB11-PB13��������ߵ�ƽ
    PBout(12) = 1;
    PBout(13) = 1;

    PBin(8) = 0; // PB8-PB9���õ͵�ƽ
    PBin(9) = 0;
    PBin(10) = 0;
    if (PBin(8) == 1 || PBin(9) == 1 || PBin(10) == 1) // ��һ���������жϣ���������һ��Ϊ���Ϊ��
    {
        delay_ms(10);     // ȥ����
        if (PBin(8) == 1) // �ٴ��ж�
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

    // ͬ�ϸı���������״̬
    GPIOB->CRH &= 0XFF000000; // 1111 1111 0000 0000 0000 0000 0000 0000
    GPIOB->CRH |= 0X00888333; // 0000 0000 1000 1000 1000 0011 0011 0011
    // PB8 mode���ģʽ��cnfͨ���������ģʽ��
    // PB9 mode���ģʽ��cnfͨ���������ģʽ��
    // PB10 mode���ģʽ��cnfͨ���������ģʽ��

    // PB11 mode����ģʽ��cnf����������ģʽ��
    // PB12 mode����ģʽ��cnf����������ģʽ��
    // PB13 mode����ģʽ��cnf����������ģʽ��

    GPIOB->ODR &= 0X00000000;

    PBout(8) = 1;
    PBout(9) = 1;
    PBout(10) = 1;

    PBin(11) = 0;
    PBin(12) = 0;
    PBin(13) = 0;
    if (PBin(11) == 1 || PBin(12) == 1 || PBin(13) == 1)
    {
        delay_ms(10);      // ȥ����
        if (PBin(11) == 1) // ��
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

    // ���������жϰ���λ��
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
