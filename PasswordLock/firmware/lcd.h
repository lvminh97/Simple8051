#include<stdio.h>
#include<string.h>

#define RS P0_0
#define EN P0_1
#define D4 P0_2
#define D5 P0_3
#define D6 P0_4
#define D7 P0_5

void delay_lcd(unsigned int t){
	while(t--);
}	  

void send_4bit(unsigned char rs, unsigned char byte){
	if(rs)  RS = 1;			// select data register
	else    RS = 0;			// select instruction register
	EN = 1;					
	D7 = (byte & 0x80) ? 1:0;
	D6 = (byte & 0x40) ? 1:0;
	D5 = (byte & 0x20) ? 1:0;
	D4 = (byte & 0x10) ? 1:0;    
	EN = 0;
	delay_lcd(1);
}

void lcd_putchar(unsigned char byte){    
	send_4bit(1, (byte & 0xF0));
	send_4bit(1, (byte << 4) );
}

void lcd_sendcmd(unsigned char byte){    
	send_4bit(0, (byte & 0xF0));
	send_4bit(0, (byte << 4) );
}

void lcd_init(){
	delay_lcd(10);    
	send_4bit(0, 0x30);
	delay_lcd(10);    
	send_4bit(0, 0x30);
	delay_lcd(10);    
	send_4bit(0, 0x30);
	delay_lcd(10);    
	send_4bit(0, 0x20);    
	lcd_sendcmd(0x28);
	lcd_sendcmd(0x0C);
	lcd_sendcmd(0x06);
}
void lcd_clear() {
	lcd_sendcmd(1); 
	delay_lcd(10);
}

void lcd_putstring(unsigned char *s){
	unsigned char i;
	for(i = 0; s[i] != 0; i++){
		lcd_putchar(s[i]);
	}
}
void lcd_putint(int n){
	char num[10];
	sprintf(num, "%d", n);
	lcd_putstring((char*) num);
}
void lcd_gotoxy(unsigned char x,unsigned char y) {
	if(y == 0) lcd_sendcmd(128 + x); 
	if(y == 1) lcd_sendcmd(192 + x);  
}
