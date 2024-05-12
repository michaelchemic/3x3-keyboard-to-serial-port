#ifndef _LCD_H
#define _LCD_H
#include "sys.h"
#include "delay.h"

#define RS PBout(0)
#define RW PBout(1)
#define EN PBout(10)

#define LINE1 0x80
#define LINE2 0x90
#define LINE3 0x88
#define LINE4 0x98

void IO_Init(void);
void CheckBusy(void);
void LCD_wdat(u8 dat);
void LCD_wcmd(u8 com);
void LCD_Init(void);
void LCD_Wmessage(u8 *message, u8 address);

#endif
