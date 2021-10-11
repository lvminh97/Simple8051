#include<at89x52.h>

#define SPK   P1_0
#define CNT		P1_1
#define LED		P1_2
#define LED7_DAT	P0
#define LED7_POS	P2

unsigned char led7_code[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; // Ma hexa cua Led 7 doan
unsigned char led_index;
unsigned int count;

void delay(unsigned int t){
	int i, j;
	for(i = 0; i < 123; i++)
		for(j = 0; j < t; j++);
}

void delay_us(unsigned int t){
	while(t--);
}

void beep(){
	int i;
	for(i = 0; i < 100; i++){
		SPK = 0;
		delay_us(48);
		SPK = 1;
		delay_us(48);
	}
}

void set_interrupt(){
	TMOD = 0x01; // timer0 mode 1
	TH0 = 0xf8;
	TL0 = 0x2f;
	ET0 = 1; // enable timer0 interrupt
	TR0 = 1; // start timer0
	EA  = 1; // enable interrupt
}

void INT_Timer0() interrupt 1 {
	TR0 = 0;
	TH0 = 0xf8;
	TL0 = 0x2f;
	LED7_POS = 0x00;
	if(led_index == 0){
		LED7_DAT = led7_code[count / 1000];
		LED7_POS = 0x01;
	}
	else if(led_index == 1){
		LED7_DAT = led7_code[count % 1000 / 100];
		LED7_POS = 0x02;
	}
	else if(led_index == 2){
		LED7_DAT = led7_code[count % 100 / 10];
		LED7_POS = 0x04;
	}
	else{
		LED7_DAT = led7_code[count % 10];
		LED7_POS = 0x08;
	}
	led_index++;
	if(led_index == 4){
		led_index = 0;
	}
	TR0 = 1;
}

void main(){
	set_interrupt();
	count = 0;
	led_index = 0;
	while(1){
		if(CNT == 0){
			count = (count + 1) % 10000;
			LED = 0;
			beep(); 
			delay(150);
			beep();
			delay(150);
			LED = 1;
			CNT = 1;
		}
	}
 }
