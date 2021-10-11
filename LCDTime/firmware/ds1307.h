// RTC DS1307

#define SCL P0_1
#define SDA P0_0
#define DS1307_ID 0xD0
#define SEC   0x00
#define MIN   0x01
#define HOUR  0x02
#define DAY   0x03
#define DATE  0x04
#define MONTH 0x05
#define YEAR  0x06

extern void delay_us(unsigned int t);

// For I2C

void I2C_start(void){
	SCL = 1;	
	SCL = 0;
	SDA = 1;
	SCL = 1;
	delay_us(2);
	SDA = 0;
	delay_us(2);
	SCL = 0;
	delay_us(2);	
}

void I2C_stop(void){
	SCL = 1;
	SCL = 0;
	SDA = 0;
	delay_us(2);
	SCL = 1;
	delay_us(2);
	SDA = 1;
}

bit I2C_write(unsigned char dat){
	int i;
	for(i = 0; i < 8; i++){
		SDA = (dat & 0x80) ? 1 : 0;
		SCL = 1;
		SCL = 0;
		dat <<= 1;
	}
	SCL = 1;
	delay_us(2);
	SCL = 0;
}

unsigned char I2C_read(void){
	bit read;
	unsigned char i, dat;
	dat = 0x00;
	for(i = 0; i < 8; i++){	// vong lap doc 1 Byte
		delay_us(2);
		SCL = 1;			// dat SCL
		delay_us(2);
		read = SDA;	  	// lay bit tu SDA
		dat <<= 1;
		dat |= read;		// Luu bit vao dat
		SCL = 0; 			// xoa sach SCL
	}
	return dat;
}

// For DS1307

unsigned char DS1307_get(unsigned char addr){
	unsigned int tmp, ret;
	I2C_start();  			// khoi tao I2C bus
	I2C_write(DS1307_ID);	// ket noi voi DS1307
	I2C_write(addr);
	I2C_start();
	I2C_write(DS1307_ID + 1);
	ret=I2C_read();
	I2C_stop();
	//------------------------------------------
	tmp = ret;
	ret = (((ret >> 4) * 10) + (tmp & 0x0f)); 	// BCD to HEX
	return ret;
}

void DS1307_write(unsigned char addr, unsigned char dat){
	unsigned int tmp;
	//-------------------------------------------
	tmp = dat;
	dat = (((dat / 10) << 4) | (tmp % 10));		// HEX to BCD
	//-------------------------------------------
	I2C_start();
	I2C_write(DS1307_ID);
	I2C_write(addr);
	I2C_write(dat);
	I2C_stop();
}