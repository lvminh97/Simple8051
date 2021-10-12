#define R1 P2_0
#define R2 P2_1
#define R3 P2_2
#define R4 P2_3
#define C1 P2_4
#define C2 P2_5
#define C3 P2_6

unsigned char R_find1(){
	C1 = 0;
	R1 = R2 = R3 = R4 = 1;
	if(R1 == 0) return '1';
	else if(R2 == 0) return '4';
	else if(R3 == 0) return '7';
	else if(R4 == 0) return '*';
	else return 0;
}

unsigned char R_find2(){
	C2 = 0;
	R1 = R2 = R3 = R4 = 1;
	if(R1 == 0) return '2';
	else if(R2 == 0) return '5';
	else if(R3 == 0) return '8';
	else if(R4 == 0) return '0';
	else return 0;
}

unsigned char R_find3(){
	C3 = 0;
	R1 = R2 = R3 = R4 = 1;
	if(R1 == 0) return '3';
	else if(R2 == 0) return '6';
	else if(R3 == 0) return '9';
	else if(R4 == 0) return '#';
	else return 0;
}

unsigned char check_key(){
	unsigned char tmp;
	C1 = C2 = C3 = 1;
	R1 = R2 = R3 = R4 = 1;
	C1 = 0;
	tmp = R_find1();
	if(tmp) return tmp;
	C1 = 1;
	C2 = 0;
	tmp = R_find2();
	if(tmp) return tmp;
	C2 = 1;
	C3 = 0;
	tmp = R_find3();
	return tmp;
}