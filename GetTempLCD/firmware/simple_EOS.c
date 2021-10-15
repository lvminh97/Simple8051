#include "main.H"
#include "port.h"
#include "simple_EOS.H"
#include "LCD.h"

extern unsigned int t1_cnt;

void sEOS_Init_Timer0(){
	TMOD = (TMOD & 0xf0) | 0x02;
	TH0 = TL0 = 155;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
}

void sEOS_Init_Timer1(){
	TMOD = (TMOD & 0x0f) | 0x10;
	TR1 = 1;
}

void INT_Timer0(void)interrupt 1 {
  //ctr phuc vu ngat tao xung clock cho ADC0808
	ADC0808_CLK = !ADC0808_CLK; //Dao bit
}

void sEOS_getTemp() {
	TH1 = 0x4b;
	TL1 = 0xfd;
	while(TF1 == 0);
	t1_cnt--;
	if(t1_cnt == 0){
		hienthi();
		t1_cnt = 10;
	}
	TF1 = 0;
}

void sEOS_Go_To_Sleep(void){
PCON |= 0x01; 
}