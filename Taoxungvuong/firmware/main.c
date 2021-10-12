#include<at89x52.h>

#define PULSE 		P2_0
#define UP_BTN		P3_2
#define DOWN_BTN	P3_3

unsigned int duty, tmp;

void EXT0_ISR() interrupt 0 { // Ngat ngoai 0 xu ly khi nhan UP
	if(duty < 2000)
		duty += 200;
	if(duty == 2000){
		PULSE = 1;
		TR0 = 0;
	}
	else if(TR0 == 0){
		TR0 = 1;
	}
}

void EXT1_ISR() interrupt 2 { // Ngat ngoai 1 xu ly khi nhan DOWN
	if(duty > 0)
		duty -= 200;
	if(duty == 0){
		PULSE = 0;
		TR0 = 0;
	}
	else if(TR0 == 0){
		TR0 = 1;
	}
}

void TIM0_ISR() interrupt 1 { // Ngat timer0 tao xung vuong
	TR0 = 0;
	if(PULSE == 0){
		tmp = 0xffff - duty;
		TH0 = tmp >> 8;
		TL0 = tmp & 0xff;
		if(duty > 0)
			PULSE = 1;
	}
	else{
		tmp = 0xffff + duty - 2000;
		TH0 = tmp >> 8;
		TL0 = tmp & 0xff;
		if(duty < 2000)
			PULSE = 0;
	}
	TR0 = 1;
}

void set_interrupt(){
	TMOD = 0x01; // timer0 mode 1
	TH0 = 0xff;
	TL0 = 0x00;
	TR0 = 1;	// Khoi dong timer0
	ET0 = 1;	// Ngat timer0
	EX0 = 1;	// Ngat ngoai 0
	IT0 = 1;	// Ngat ngoai 0 theo suon am
	EX1 = 1;	// Ngat ngoai 1
	IT1 = 1;	// Ngat ngoai 1 theo suon duong
  EA = 1; // Cho phep ngat 
}

void main(){
	duty = 0;
	set_interrupt();
	while(1){}
 }