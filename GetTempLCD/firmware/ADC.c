#include "main.h"
#include "port.h"
#include "ADC.h"

unsigned char ADC0808_Read(unsigned char a){
	unsigned char kq;
 	ADC0808_A = a & 0x01;
	ADC0808_B = a & 0x02;
	ADC0808_C = a & 0x04;
	ADC0808_EOC = 1;
	ADC0808_ALE = 1;
	ADC0808_START = 1;
	ADC0808_ALE = 0;
	ADC0808_START = 0;
	while(ADC0808_EOC);
	while(!ADC0808_EOC);
	ADC0808_OE = 1;
	kq = ADC0808_DATA;
	ADC0808_OE = 0;
	return kq;
}