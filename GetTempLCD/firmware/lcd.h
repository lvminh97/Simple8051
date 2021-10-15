#ifndef _LCD_H_
#define _LCD_H_

void LCD_Enable(void);
void LCD_Send4Bit(unsigned char Data);
//void LCD_SendCommand(unsigned char command);
void LCD_Clear();
void LCD_Init();
void LCD_Gotoxy(unsigned char x, unsigned char y);
void LCD_PutChar();
void LCD_Puts(char *s);
void TempShow(unsigned char z);
void hienthi();
#endif