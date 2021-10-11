#include<string.h>

#define RS P0_2
#define EN P0_3
#define D4 P0_4
#define D5 P0_5
#define D6 P0_6
#define D7 P0_7

void delay_lcd(unsigned int t){
	while(t--);
}	  

void send_4bit(unsigned char rs, unsigned char byte){
    if(rs)  RS=1;			// select data register
    else    RS=0;			// select instruction register
    EN = 1;					
    D7 = (byte & 0x80) ? 1:0;
    D6 = (byte & 0x40) ? 1:0;
    D5 = (byte & 0x20) ? 1:0;
    D4 = (byte & 0x10) ? 1:0;    
    EN = 0;
    delay_lcd(1);
}

void lcd_putchar(unsigned char byte){    
    send_4bit(1, (byte & 0xF0) );
    send_4bit(1, (byte << 4) );
}

void lcd_cmd(unsigned char byte){    
    send_4bit(0, (byte & 0xF0) );
    send_4bit(0, (byte << 4) );
}

void lcd_init(){
    //DDRA=255;
    delay_lcd(10);    
    send_4bit( 0, 0x30);
    delay_lcd(10);    
    send_4bit( 0, 0x30);
    delay_lcd(10);    
    send_4bit( 0, 0x30);
    delay_lcd(10);    
    send_4bit( 0, 0x20);    
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
	lcd_cmd(0x06);
}
void lcd_clear() {
	lcd_cmd(1); 
	delay_lcd(10);
}

void lcd_putsf(unsigned char *s)
 	{
		unsigned char data lens,count;
		lens=strlen(s);
		for(count=0;count<lens;count++)
		{
			lcd_putchar(*(s+count));
		}
 	}
void lcd_putnum(int z){
        unsigned int chuc,dv;
   		if(z<0)  {z=-z; lcd_putchar('-');} 
        chuc=z/10;
        dv  =z%10;
        lcd_putchar(chuc+48);		// ma ascii cua ki tu 0 la 48
        lcd_putchar(dv+48);
}
void lcd_gotoxy(unsigned char x,unsigned char y) {
       if(y==0) lcd_cmd(128+x); 
       if(y==1) lcd_cmd(192+x);  
}
