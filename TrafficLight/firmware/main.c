#include<at89x52.h>

#define LED7			P0
#define GREEN 	  P1_0
#define YELLOW		P1_1
#define RED				P1_2
#define LED				P1

unsigned int time, ticks;

void delay_ms(unsigned int t){
	int i;
	while(t--){
		for(i = 0; i < 123; i++);
	}
}

void set_interrupt(){
	TMOD = 0x10; // timer1 mode 1
	TH1 = 0xec;
	TL1 = 0x77;
	ET1 = 1;	// enable timer1 interrupt	
	TR1 = 1;	// start timer1
	EA  = 1; // enable interrupt
}

void interrupt_timer1() interrupt 3 {
	TR1 = 0;
	TH1 = 0xec;
	TL1 = 0x77;
	ticks--;
	if(ticks == 0){
		if(GREEN == 0){
			ticks = 1000;
			LED = ~0x02;
		}
		else if(YELLOW == 0){
			ticks = 3000;
			LED = ~0x04;
		}
		else if(RED == 0){
			ticks = 2000;
			LED = ~0x01;
		}
	}
	TR1 = 1;
}

void main(){
	ticks = 3000;
	LED = ~0x04;
	set_interrupt();
	while(1){
		time = ticks / 200;
		LED7 = ((time / 10) << 4) + time % 10;
		delay_ms(100);
	}
 }
