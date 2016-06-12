#include "fxlib.h"

#define PLL_28x /*0011011*/ 27 // 101.5 MHz
#define PLL_26x /*0011001*/ 25 // 94.3 MHz 
#define PLL_24x /*0010111*/ 23 // 87 MHz 
#define PLL_20x /*0010011*/ 19 // 72.5 MHz 
#define PLL_18x /*0010001*/ 17 // 65.25 MHz 
#define PLL_16x /*0001111*/ 15 // 58 MHz (NORMAL SPEED) 
#define PLL_15x /*0001110*/ 14 // 54.37 MHz 
#define PLL_12x /*0001011*/ 11 // 43.5 MHz 
#define PLL_8x  /*0000111*/ 7 // 29 MHz 
#define PLL_6x  /*0000101*/ 5 // 21.75 MHz 
#define PLL_4x  /*0000011*/ 3 // 14.5 MHz 
#define PLL_3x  /*0000010*/ 2 // 10.8 MHz 
#define PLL_2x  /*0000001*/ 1 // 7.25 MHz 
#define PLL_1x  /*0000000*/ 0 // 3.6 MHz

#define ICLK_2 /*00000*/ 0
#define ICLK_3 /*00001*/ 1
#define ICLK_4 /*00010*/ 2
#define ICLK_6 /*00011*/ 3
#define ICLK_8 /*00100*/ 4
#define ICLK_12 /*00101*/ 5
#define ICLK_16 /*00110*/ 6
#define ICLK_24 /*00111*/ 7
#define ICLK_32 /*01000*/ 8
#define ICLK_36 /*01001*/ 9
#define ICLK_48 /*01010*/ 10
#define ICLK_72 /*01011*/ 11

const int PLLs[] = {PLL_1x, PLL_2x, PLL_3x, PLL_4x, PLL_6x, PLL_8x, PLL_12x, PLL_15x, PLL_16x, PLL_18x, PLL_20x, PLL_24x, PLL_26x, PLL_28x};
const int DIVs[] = {ICLK_2, ICLK_3, ICLK_4, ICLK_6, ICLK_8, ICLK_12, ICLK_16, ICLK_24, ICLK_32, ICLK_36, ICLK_48, ICLK_72};

int key = 0;
char*cur = 0x00000000;
volatile unsigned int*FRQCR = (unsigned int*) 0xA4150000;

void printXY(int x, int y, char *text, int useless)
{
	PrintMini(x * 6,y * 6, text, MINI_OVER);
}

void update(void) {
	int warning = 0;
	Bdisp_AllClr_VRAM();
	printXY(2, 1, "  Operating Frequency", MINI_OVER);
	printXY(3, 2, "  Freq:", MINI_OVER);
	printXY(3, 3, "  ICLK:", MINI_OVER);
	printXY(3, 4, "  PCLK:", MINI_OVER);
	printXY(3, 5, "  BCLK:", MINI_OVER);
	printXY(3, 6, "  SCLK:", MINI_OVER);
	printXY(1, 7, "  U/D - FRQ, L/R - ICLK", MINI_OVER);
	switch((*FRQCR & 0x3F000000) >> 24) {
		case PLL_28x:
			cur = "  101.5 MHz !!!";
			warning = 1;
			break;
		case PLL_26x:
			cur = "  94.3 MHz";
			break;
		case PLL_24x:
			cur = "  87 MHz";
			break;
		case PLL_20x:
			cur = "  72.5 MHz";
			break;
		case PLL_18x:
			cur = "  65.3 MHz";
			break;
		case PLL_16x:
			cur = "  58 MHz (NORM)";
			break;
		case PLL_15x:
			cur = "  54.4 MHz";
			break;
		case PLL_12x:
			cur = "  43.5 MHz";
			break;
		case PLL_8x:
			cur = "  29 MHz";
			break;
		case PLL_6x:
			cur = "  21.7 MHz";
			break;
		case PLL_4x:
			cur = "  14.5 MHz";
			break;
		case PLL_3x:
			cur = "  10.8 MHz";
			break;
		case PLL_2x:
			cur = "  7.25 MHz";
			break;
		case PLL_1x:
			cur = "  3.6 MHz";
			break;
		default:
			cur = "  INVALID";
			break;
	}
	printXY(9, 2, cur, MINI_OVER);
	switch((*FRQCR & 0x00F00000) >> 20) {
		case ICLK_72:
			cur = "  1/72";
			break;
		case ICLK_48:
			cur = "  1/48";
			break;
		case ICLK_36:
			cur = "  1/36";
			break;
		case ICLK_32:
			cur = "  1/32";
			break;
		case ICLK_24:
			cur = "  1/24";
			break;
		case ICLK_16:
			cur = "  1/16";
			break;
		case ICLK_12:
			cur = "  1/12";
			break;
		case ICLK_8:
			cur = "  1/8";
			break;
		case ICLK_6:
			cur = "  1/6";
			break;
		case ICLK_4:
			cur = "  1/4";
			break;
		case ICLK_3:
			cur = "  1/3 (NORM)";
			break;
		case ICLK_2:
			cur = "  1/2 !!!";
			warning += 2;
			break;
		default:
			cur = "  INVALID";
			break;
	}
	printXY(9, 3, cur, MINI_OVER);
	switch(*FRQCR & 0xF) {
		case ICLK_72:
			cur = "  1/72";
			break;
		case ICLK_48:
				cur = "  1/48";
		break;
		case ICLK_36:
			cur = "  1/36";
			break;
			case ICLK_32:
		cur = "  1/32";
				break;
		case ICLK_24:
			cur = "  1/24";
		break;
			case ICLK_16:
		cur = "  1/16";
			break;
		case ICLK_12:
				cur = "  1/12";
		break;
		case ICLK_8:
			cur = "  1/8";
				break;
		case ICLK_6:
			cur = "  1/6 (NORM)";
			break;
		case ICLK_4:
			cur = "  1/4";
			break;
		case ICLK_3:
			cur = "  1/3";
			break;
		case ICLK_2:
			cur = "  1/2";
			break;
		default:
			cur = "  INVALID";
			break;
	}
	printXY(9, 4, cur, MINI_OVER);
	switch((*FRQCR & 0xF00) >> 8) {
		case ICLK_72:
			cur = "  1/72";
			break;
		case ICLK_48:
			cur = "  1/48";
			break;
		case ICLK_36:
			cur = "  1/36";
			break;
		case ICLK_32:
			cur = "  1/32";
			break;
		case ICLK_24:
			cur = "  1/24";
			break;
		case ICLK_16:
			cur = "  1/16";
			break;
		case ICLK_12:
			cur = "  1/12";
			break;
		case ICLK_8:
			cur = "  1/8";
			break;
		case ICLK_6:
			cur = "  1/6";
			break;
		case ICLK_4:
			cur = "  1/4 (NORM)";
			break;
		case ICLK_3:
			cur = "  1/3";
			break;
		case ICLK_2:
			cur = "  1/2";
			break;
		default:
			cur = "  INVALID";
			break;
	}
	printXY(9, 5, cur, MINI_OVER);
	switch((*FRQCR & 0xF000) >> 12) {
		case ICLK_72:
			cur = "  1/72";
			break;
		case ICLK_48:
			cur = "  1/48";
			break;
		case ICLK_36:
			cur = "  1/36";
			break;
		case ICLK_32:
			cur = "  1/32";
			break;
		case ICLK_24:
			cur = "  1/24";
			break;
		case ICLK_16:
			cur = "  1/16";
			break;
		case ICLK_12:
			cur = "  1/12";
			break;
		case ICLK_8:
			cur = "  1/8";
			break;
		case ICLK_6:
			cur = "  1/6";
			break;
		case ICLK_4:
			cur = "  1/4 (NORM)";
			break;
		case ICLK_3:
			cur = "  1/3";
			break;
		case ICLK_2:
			cur = "  1/2";
			break;
		default:
			cur = "  INVALID";
		break;
		}
	printXY(9, 6, cur, MINI_OVER);
	if(warning == 1 || warning == 3) {
		printXY(1, 8, "  UNSAFE FREQ/DIV VALUE", MINI_OVER);
		} else if(warning == 2) {
		printXY(1, 8, "  TROUBLESOME DIV VALUE", MINI_OVER);
	}
	Bdisp_PutDisp_DD();
}

int AddIn_main(int isAppli, unsigned short OptionNum)
{
	int i;	
	while(1) {
		update();
		switch (key) {
			case KEY_CTRL_UP:
				for(i = 0; i < 13; i++) {
					if(((*FRQCR & 0x3F000000) >> 24) == PLLs[i]) {
						change_freq(PLLs[i+1]);
						update();
						break;
					}
				}
				break;
			case KEY_CTRL_DOWN:
				for(i = 1; i < 14; i++) {
					if(((*FRQCR & 0x3F000000) >> 24) == PLLs[i]) {
						change_freq(PLLs[i-1]);
						update();
						break;
					}
				}
				break;
			case KEY_CTRL_LEFT:
				for(i = 0; i < 2; i++) {
					if(((*FRQCR & 0x00F00000) >> 20) == DIVs[i]) {
						change_iclk(DIVs[i+1]);
						update();
						break;
					}
				}
				break;
			case KEY_CTRL_RIGHT:
				for(i = 1; i < 3; i++) {
					if(((*FRQCR & 0x00F00000) >> 20) == DIVs[i]) {
						change_iclk(DIVs[i-1]);
						update();
						break;
					}
				}
				break;
			default:
				break;
		}
		GetKey(&key);
		update();
	}
 
	return 0;
}

//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

