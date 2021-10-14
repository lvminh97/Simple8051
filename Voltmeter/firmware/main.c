#include<at89x52.h>
#include "lcd.h"

#define ADDA		P2_0
#define ADDB		P2_1
#define ADDC		P2_2
#define CLK			P2_3
#define ST			P2_4
#define	EOC			P2_5
#define	OE			P2_6
#define ALE			P2_7
#define ADC			P1

unsigned char adc;
unsigned int volt;

void delay_ms(unsigned int t){
	int i;
	while(t--){
		for(i = 0; i < 123; i++);
	}
}

void getADC(){
	ADDA = ADDB = ADDC = 0;
	EOC = 1;
	ALE = 1; 
	ST = 1; 
	ALE = 0;
	ST = 0;
	while(EOC == 1); 
	while(EOC == 0);
	OE = 1; 
	adc = ADC;
	OE = 0;
}

void set_interrupt(){
	TMOD = 0x02; // timer mode
	TH0 = TL0 = 236;
	TR0 = 1;	// Khoi dong timer0
	ET0 = 1; // Ngat timer0
  EA = 1; // Cho phep ngat 
}

void interrupt_timer0() interrupt 1 {
	CLK = !CLK;
}

void main(){
	lcd_init();
	lcd_putstring("Volt: ");
	set_interrupt();
	while(1){
		EA = 1;
		getADC();
		EA = 0;
		volt = (adc / 255.0) * 25000;
		lcd_gotoxy(0, 1);
		lcd_putint(volt);
		lcd_putstring("V   ");
		delay_ms(500);
	}
 }
