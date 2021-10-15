#include "main.h"
#include "port.h"
#include "delay.h"
#include "lcd.h"
#include "ADC.h"
#include "simple_EOS.h"	

unsigned int t1_cnt = 10;

int main(){
 	LCD_Init();//Khoi tao LCD
  delay_ms(200);
	LCD_Puts("Do nhiet do...");//Gui chuoi len LCD
  delay_ms(500);
  LCD_Clear();//Xoa man hinh
	sEOS_Init_Timer0();
	sEOS_Init_Timer1();

	while(1){
		sEOS_getTemp();
	  sEOS_Go_To_Sleep();
	}					
}
	 
