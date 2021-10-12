#include<at89x52.h>
#include "LCD.h"

#define DHT  P0_6

unsigned char temp, humi;

void delay(unsigned int t){
	int i, j;
	for(i = 0; i < 123; i++)
		for(j = 0; j < t; j++);
}

void delay_20ms(){
	TMOD = 0x01;
	TH0 = 0xb8;
	TL0 = 0x0c;	
	TR0 = 1;		
	while(TF0 == 0);	
	TR0 = 0;		
	TF0 = 0;		
}

void delay_30us(){
	TMOD = 0x01;
	TH0 = 0xff;		
	TL0 = 0xf1;		
	TR0 = 1;		
	while(TF0 == 0);	
	TR0 = 0;		
	TF0 = 0;		
}

unsigned int get_micros(){
	return ((unsigned int) TH0 << 8) | TL0;
}

unsigned char dht11_getdata(){
	unsigned char buf[5];
	unsigned int i, j;
	// Send request signal to DHT11
	DHT = 0;
	delay_20ms();
	DHT = 1;
	// Receive response from DHT11
	while(DHT == 1);
	while(DHT == 0);
	while(DHT == 1);
	// Read bytes
	for(i = 0; i < 5; i++){
		for(j = 0; j < 8; j++){
			while(DHT == 0);
			delay_30us();
			if(DHT == 1)
				buf[i] = (buf[i] << 1) | 1;
			else
				buf[i] <<= 1;
			while(DHT == 1);
		}
	}
	temp = buf[2];
	humi = buf[0];
}

void main(){
	lcd_init();
	while(1){
		dht11_getdata();
		lcd_gotoxy(0, 0);
		lcd_putstring("Temp: ");
		lcd_putint(temp);
		lcd_putstring("oC  ");
		lcd_gotoxy(0, 1);
		lcd_putstring("Humi: ");
		lcd_putint(humi);
		lcd_putstring("%  ");
		delay(500);
	}
 }