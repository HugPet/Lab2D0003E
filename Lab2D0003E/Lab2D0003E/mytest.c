#include "tinythreads.h"
#include <stdbool.h>

void writeChar(char ch, int pos); // from lab 1


bool is_prime(long i); // from lab 1

void printAt(long num, int pos) {
    int pp = pos;
    writeChar( (num % 100) / 10 + '0', pp);
    pp++;
    writeChar( num % 10 + '0', pp);
}

void computePrimes(int pos) {
    long n;

    for(n = 1; ; n++) {
        if (is_prime(n)) {
            printAt(n, pos);
			yield();
        }
    }
}

//int main() {
//    spawn(computePrimes, 0);
//    computePrimes(3);
//}

bool is_prime(long i) {
	int n = 2;
	while (i % n != 0 && i > 1){	// uses an inefficient but standard way of looking for primes.
		if (i - 1 == n) return true;
		n++;
	}
	return false;
	
}


void writeChar(char ch, int pos){
	int SCC_X_0 = 0, SCC_X_1 = 0, SCC_X_2 = 0, SCC_X_3 = 0;
		
	switch (ch)					/* a switch statement for which character is to be printed on the display.
								   sets various bytes of SCC_X to certain values, depending on which areas
								   should light up. These values are derived from the documentation.    */
	{
	case '0' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x5;
		SCC_X_2 = 0x5;
		SCC_X_3 = 0x1;
		
		break;
	case '1' :
		SCC_X_0 = 0x0;
		SCC_X_1 = 0x1;
		SCC_X_2 = 0x1;
		SCC_X_3 = 0x0;
		break;
	case '2' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x1;
		SCC_X_2 = 0xE;
		SCC_X_3 = 0x1;
		break;
	case '3' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x1;
		SCC_X_2 = 0xb;
		SCC_X_3 = 0x1;
		break;
	case '4' :
		SCC_X_0 = 0x0;
		SCC_X_1 = 0x5;
		SCC_X_2 = 0xb;
		SCC_X_3 = 0x0;
		break;
	case '5' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x4;
		SCC_X_2 = 0xb;
		SCC_X_3 = 0x1;
		break;
	case '6' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x4;
		SCC_X_2 = 0xf;
		SCC_X_3 = 0x1;
		break;
	case '7' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x1;
		SCC_X_2 = 0x1;
		SCC_X_3 = 0x0;
		break;
	case '8' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x5;
		SCC_X_2 = 0xf;
		SCC_X_3 = 0x1;
		break;
	case '9' :
		SCC_X_0 = 0x1;
		SCC_X_1 = 0x5;
		SCC_X_2 = 0xb;
		SCC_X_3 = 0x1;
		break;
	default:
		return;
	}
	
	switch(pos){										/* a switch statement for the position of the digit. Depending on the position 
														   we will write to different registers. We use a boolean value to show if 
														   the lower byte of the register or not, since the positions are paired up 
														   per register. */
	case 0:
		LCDDR0=writeReg(SCC_X_0, LCDDR0, false);
		LCDDR5=writeReg(SCC_X_1, LCDDR5, false);
		LCDDR10=writeReg(SCC_X_2, LCDDR10, false);
		LCDDR15=writeReg(SCC_X_3, LCDDR15, false);		
		break;
	case 1:
		LCDDR0=writeReg(SCC_X_0, LCDDR0, true);
		LCDDR5=writeReg(SCC_X_1, LCDDR5, true);
		LCDDR10=writeReg(SCC_X_2, LCDDR10, true);
		LCDDR15=writeReg(SCC_X_3, LCDDR15, true);
		break;
	case 2:
		LCDDR1 = writeReg(SCC_X_0, LCDDR1, false);
		LCDDR6 = writeReg(SCC_X_1, LCDDR6, false);
		LCDDR11 = writeReg(SCC_X_2, LCDDR11, false);
		LCDDR16 = writeReg(SCC_X_3, LCDDR16, false);
		break;
	case 3:
		LCDDR1 = writeReg(SCC_X_0, LCDDR1, true);
		LCDDR6 = writeReg(SCC_X_1, LCDDR6, true);
		LCDDR11 = writeReg(SCC_X_2, LCDDR11, true);
		LCDDR16 = writeReg(SCC_X_3, LCDDR16, true);
		break;
	case 4:
		LCDDR2 = writeReg(SCC_X_0, LCDDR2, false);
		LCDDR7 = writeReg(SCC_X_1, LCDDR7, false);
		LCDDR12 = writeReg(SCC_X_2, LCDDR12, false);
		LCDDR17 = writeReg(SCC_X_3, LCDDR17, false);
		break;
	case 5:
		LCDDR2 = writeReg(SCC_X_0, LCDDR2, true);
		LCDDR7 = writeReg(SCC_X_1, LCDDR7, true);
		LCDDR12 = writeReg(SCC_X_2, LCDDR12, true);
		LCDDR17 = writeReg(SCC_X_3, LCDDR17, true);
		break;
	default:
		return;
	}
	return;
}


/* A function for writing to a register, specifically the registers for 
   lighting up areas of the display. **/
int writeReg(int num, int reg, bool shift){
	if(!shift){
		reg &= 0xF0;
		reg |= num;
	}
	else{
		reg &= 0x0F;
		reg |= (num<<4);
	}
	return reg;
}