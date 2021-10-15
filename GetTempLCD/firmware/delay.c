#include "main.h"
#include "delay.h"
//#include "port.h"

/*****************Ham delay*********************/
 void delay_us(unsigned int t){
        unsigned int i;
        for(i=0;i<t;i++);
}
void delay_ms(unsigned int t){
        unsigned int i,j;
        for(i=0;i<t;i++)
        for(j=0;j<125;j++);
}