#include<at89x52.h>

#define ALE 		P2_1
#define START 	P2_2
#define EOC			P2_3
#define OE			P2_4
#define CLK			P2_5
#define ADC			P1
#define MOTOR   P2_0

#define GETBIT(x, i) ((x & (1 << i)) ? 1 : 0)

unsigned char temp;
unsigned short pwm_duty_h, pwm_duty_l;

void delay_us(unsigned int t){
	while(t--);
}

void delay(unsigned int t){
	int i, j;
	for(i = 0; i < 123; i++)
		for(j = 0; j < t; j++);
}

unsigned char get_temp(){
	unsigned char res = 0, i;
	EOC = 1;
	ALE = 1; // giao tiep
	START = 1; // bat dau chuyen doi ADC
	ALE = 0;
	START = 0;
	while(EOC); // cho ket thuc chuyen doi ADC
	while(!EOC);
	OE = 1; // lay ket qua
	for(i = 0; i < 8; i++){
		res <<= 1;
		res |= GETBIT(ADC, i);
	}
	OE = 0;
  return res;
}

void INT_Timer0() interrupt 1 {
	// tao xung clock cho ADC0808
	CLK = !CLK;
}

void INT_Timer1() interrupt 3 {
  // tao xung PWM dieu khien motor
	TR1 = 0;
	if(MOTOR == 0){
		TH1 = pwm_duty_h >> 8;
		TL1 = pwm_duty_h & 0xff;
		if(pwm_duty_h < 0xffff)
			MOTOR = 1;
	}
	else{
		TH1 = pwm_duty_l >> 8;
		TL1 = pwm_duty_l & 0xff;
		MOTOR = 0;
	}
	TR1 = 1;
}

void main(){
	TMOD = 0x12; // timer mode
	TH0 = TL0 = 236;
	TH1 = TL1 = 0xff;
	TR0 = 1;	// Khoi dong timer0
	TR1 = 1; // Khoi dong timer1
	ET0 = 1; // Ngat timer0
  ET1 = 1; // Ngat timer1
  EA = 1; // Cho phep ngat 
	//
	MOTOR = 0;
	while(1){
		temp = get_temp();
		if(temp < 20){
			pwm_duty_h = 0xffff;
			pwm_duty_l = 0xffff - 1600;
		}
		else if(temp < 25){
			pwm_duty_h = 0xffff - 400;
			pwm_duty_l = 0xffff - 1200;
		}
		else if(temp < 30){
			pwm_duty_h = 0xffff - 800;
			pwm_duty_l = 0xffff - 800;
		}
		else if(temp < 40){
			pwm_duty_h = 0xffff - 1200;
			pwm_duty_l = 0xffff - 400;
		}
		else{ 
			pwm_duty_h = 0xffff - 1600;
			pwm_duty_l = 0xffff;
		}
		delay(100);
	}
 }