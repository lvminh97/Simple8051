#include <at89x52.h>
#include <stdio.h>
#include "LCD.h"
#include "keypad_matrix.h"

#define DOOR P2_7

#define PASSWORD "10102021"

unsigned char keybuf;
unsigned char buf[10];
int bufId;

void delay(unsigned int t){
	int i, j;
	for(i = 0; i < 123; i++)
		for(j = 0; j < t; j++);
}

void main(){
	P2_7 = 0;
	lcd_init();
	lcd_putstring("Enter password:");
	lcd_gotoxy(0, 1);
	bufId = 0;
	while(1){
		keybuf = check_key();
		if(keybuf >= '0' && keybuf <= '9'){
			if(bufId < 10){
				lcd_putchar('*');
				buf[bufId] = keybuf;
				bufId++;
			}
		}
		else if(keybuf == '*'){
			lcd_gotoxy(0, 1);
			lcd_putstring("            ");
			lcd_gotoxy(0, 1);
			bufId = 0;
		}
		else if(keybuf == '#'){
			if(strcmp(buf, PASSWORD) == 0){
				lcd_gotoxy(0, 1);
				lcd_putstring("Accessed         ");
				P2_7 = 1;
			}
			else{
				lcd_gotoxy(0, 1);
				lcd_putstring("Wrong password   ");
			}
			delay(2000);
			if(P2_7 == 1) P2_7 = 0;
			lcd_gotoxy(0, 1);
			lcd_putstring("                ");
			lcd_gotoxy(0, 1);
			bufId = 0;
		}
		if(keybuf != 0){ // delay 200ms for debounce
			delay(250);
		}
		else{
			delay(100);
		}
	}
 }