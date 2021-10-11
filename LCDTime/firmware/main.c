#include<at89x52.h>
#include "LCD.h"
#include "ds1307.h"

#define MODE  P1_1
#define UP 	  P1_2
#define DOWN  P1_3
#define SPK   P1_0

#define MIN_A  0x08
#define HOUR_A 0x09

unsigned char hour, min, sec, date, mon, year;
unsigned char hour_alarm, min_alarm;
unsigned char adjust = 0;

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
		delay_us(50);
		SPK = 1;
		delay_us(50);
	}
}
//------------------------------------------------

void fixTime(){
	// HMS
	if(sec == 60) sec=0;
	if(sec == -1) sec=59;
	if(min == 60) min=0;
	if(min == -1) min=59;
	if(hour == 24) hour=0;
	if(hour == -1) hour=23;
	// DMY
	if(mon == 0) mon = 12;
	if(mon == 13) mon = 1;
	if(mon == 2){
		if(year % 4 == 0){
			if(date == 0) date = 29;
			if(date == 30) date = 1;
		}
		else{
			if(date == 0) date = 28;
			if(date == 29) date = 1;
		}
	}
	else if(mon == 4 || mon == 6 || mon == 9 || mon == 11){
		if(date == 0) date = 30;
		if(date == 31) date = 1;
	}
	else{
		if(date == 0) date = 31;
		if(date == 32) date = 1;
	}
}
void fixAlarm(){
	if(min_alarm == 60) min_alarm = 0;
	if(min_alarm == -1) min_alarm = 59;
	if(hour_alarm == 24) hour_alarm = 0;
	if(hour_alarm == -1) hour_alarm = 23;
}
//-----------------------------------------------------------

void dispHMS(unsigned char x, unsigned char y){
	lcd_gotoxy(x,y);
	lcd_putnum(hour);
	lcd_putchar(':');
	lcd_putnum(min);
	lcd_putchar(':');
	lcd_putnum(sec);
	lcd_putchar(' ');
	lcd_putsf("     ");
}
void dispDMY(unsigned char x, unsigned char y){
	lcd_gotoxy(x,y);
	lcd_putnum(date);
	lcd_putchar('/');
	lcd_putnum(mon);
	lcd_putchar('/');
	lcd_putnum(20);
	lcd_putnum(year);
	lcd_putsf("      ");
}
void dispAlarm(unsigned char x, unsigned char y){
	lcd_gotoxy(x,y);
	lcd_putnum(hour_alarm);
	lcd_putchar(':');
	lcd_putnum(min_alarm);
	lcd_putsf("        ");
}
void dispTime(){
	dispHMS(0, 0);
	dispDMY(0, 1);
}

//----------------------------------------------

void keypad(){
	if(MODE == 0){
		MODE = 1;
		beep();
		adjust = (adjust + 1) % 9;
		lcd_gotoxy(0,0);
		if(!adjust)
			lcd_putsf("               ");
		else if(adjust == 1)
			lcd_putsf("Adjust hour    ");
		else if(adjust == 2)
			lcd_putsf("Adjust minute  ");
		else if(adjust == 3)
			lcd_putsf("Adjust second  ");
		else if(adjust == 4)
			lcd_putsf("Adjust date    ");
		else if(adjust == 5)
			lcd_putsf("Adjust month   ");
		else if(adjust == 6)
			lcd_putsf("Adjust year    ");
		else if(adjust == 7)
			lcd_putsf("Set alarm: hour");
		else if(adjust == 8)
			lcd_putsf("Set alarm: min ");
		delay(200);
	}	
	else if(UP == 0 && adjust){
		UP = 1;
		beep();
		// Time
		if(adjust == 1) hour++;
		else if(adjust == 2) min++;
		else if(adjust == 3) sec++;
		else if(adjust == 4) date++;
		else if(adjust == 5) mon++;
		else if(adjust == 6) year++;
		// Alarm
		else if(adjust == 7) hour_alarm++;
		else if(adjust == 8) min_alarm++;
		// Fix value
		fixTime(); 
		fixAlarm();
		// Write data to DS1307
		DS1307_write(SEC, sec);	
		DS1307_write(MIN, min);
		DS1307_write(HOUR, hour);
		DS1307_write(DATE, date);
		DS1307_write(MONTH, mon);
		DS1307_write(YEAR, year);
		DS1307_write(MIN_A, min_alarm);
		DS1307_write(HOUR_A, hour_alarm);
		delay(200);
	}
	else if(DOWN == 0 && adjust){
		DOWN = 1;
		beep();
		// Time
		if(adjust == 1) hour--;
		else if(adjust == 2) min--;
		else if(adjust == 3) sec--;
		else if(adjust == 4) date--;
		else if(adjust == 5) mon--;
		else if(adjust == 6) year--;
		// Alarm
		else if(adjust == 7) hour_alarm--;
		else if(adjust == 8) min_alarm--;
		// Fix value
		fixTime(); 
		fixAlarm();
		// Write data to DS1307
		DS1307_write(SEC, sec);	
		DS1307_write(MIN, min);
		DS1307_write(HOUR, hour);
		DS1307_write(DATE, date);
		DS1307_write(MONTH, mon);
		DS1307_write(YEAR, year);
		DS1307_write(MIN_A, min_alarm);
		DS1307_write(HOUR_A, hour_alarm);
		delay(200);	
	}
	if(1 <= adjust && adjust <= 3) dispHMS(0, 1);
	else if(4 <= adjust && adjust <= 6) dispDMY(0, 1);
	else if(7 <= adjust && adjust <= 8) dispAlarm(0, 1);
}

//-------------------------------------------------

void main(){
	int tmp = 0, cnt = 0;
	hour_alarm = DS1307_get(HOUR_A); 
	min_alarm = DS1307_get(MIN_A);
	lcd_init();
	lcd_clear();
	beep();	
	delay(100);
	beep(); 
	while(1){
		keypad();
		if(adjust == 0){
			hour = DS1307_get(HOUR);
			min  = DS1307_get(MIN);
			sec  = DS1307_get(SEC);
			date = DS1307_get(DATE);
			mon  = DS1307_get(MONTH);
			year = DS1307_get(YEAR);
			dispTime();
			if(tmp != sec){
				tmp = sec;
				cnt = 0;
			}
			else {
				cnt++;
			}
			if(hour == hour_alarm && min == min_alarm && sec < 10){
				beep();
			}
			else if(min == 0 && sec == 0 && (cnt == 0 || cnt == 4)) beep();
			delay(20);
		}
	}
 }