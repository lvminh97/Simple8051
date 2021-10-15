#include "main.h"
#include "port.h"
#include "lcd.h"
#include "delay.h"
#include "ADC.h"

unsigned char temp;
/**************Ctr giao tiep LCD 16x2 4bit**********************/
void LCD_Enable(void){
        LCD_EN =1;
        delay_us(3);
        LCD_EN=0;
        delay_us(50); 
}
//Ham Gui 4 Bit Du Lieu Ra LCD
void LCD_Send4Bit(unsigned char Data){
        LCD_D4=Data & 0x01;
        LCD_D5=(Data>>1)&1;
        LCD_D6=(Data>>2)&1;
        LCD_D7=(Data>>3)&1;
}
// Ham Gui 1 Lenh Cho LCD
void LCD_SendCommand(unsigned char command){
        LCD_Send4Bit(command >>4);/* Gui 4 bit cao */
        LCD_Enable();
        LCD_Send4Bit(command); /* Gui 4 bit thap*/
        LCD_Enable();
}
void LCD_Clear(){// Ham Xoa Man Hinh LCD
        LCD_SendCommand(0x01); 
        delay_us(10);
}
// Ham Khoi Tao LCD
void LCD_Init(){
        LCD_Send4Bit(0x00);
        delay_ms(20);
        LCD_RS=0;
        LCD_RW=0;
        LCD_Send4Bit(0x03);
        LCD_Enable();
        delay_ms(5);
        LCD_Enable();
        delay_us(100);
        LCD_Enable();
        LCD_Send4Bit(0x02);
        LCD_Enable();
        LCD_SendCommand( 0x28 ); // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
        LCD_SendCommand( 0x0c); // cho phep hien thi man hinh
        LCD_SendCommand( 0x06 ); // tang ID, khong dich khung hinh
        LCD_SendCommand(0x01); // xoa toan bo khung hinh
}
void LCD_Gotoxy(unsigned char x, unsigned char y){
        unsigned char address;
        if(!y)address=(0x80+x);
        else address=(0xc0+x);
        LCD_SendCommand(address);
}
void LCD_PutChar(unsigned char Data){//Ham Gui 1 Ki Tu
        LCD_RS=1;
        LCD_SendCommand(Data);
        LCD_RS=0 ;
}
void LCD_Puts(char *s){//Ham gui 1 chuoi ky tu
        while (*s){
                LCD_PutChar(*s);
                s++;
        }
}
/**************Show Temp***********************
unsigned char Temp(unsigned char adc){//Tinh nhiet do tu adc8bit
	 return ((VREF*adc)/2.56f); //Tinh nhiet do 
}  */
void TempShow(unsigned char z){ //Chuyen doi hien thi
		 LCD_Puts("Nhiet do: ");
     LCD_PutChar((z/100)+48);//Tram
     LCD_PutChar((z%100/10)+48);//Chuc
     LCD_PutChar((z%10)+48);//Don vi 
     LCD_Puts("'C");
}
void docADC(void){
   temp=ADC0808_Read(0);

}
void hienthi(void){
		LCD_Gotoxy(0,0);
		docADC();//Doc ADC0				
	TempShow(temp); //Hien thi nhiet do
	//delay_ms(500);//0.5s doc mot lan
}
