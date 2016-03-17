#include <stdio.h>
#include <string.h>
#include <pigpio.h>

#include "sevenSegmentDisplay.h"

int displayHandle=0;
int brightness=15;
unsigned short displayBuffer[DIGITS];

void sevenSegmentInit()
{
	if (gpioInitialise() < 0)
	{
		return;
	}
	displayHandle=i2cOpen(1,0x70,0);
	if (displayHandle<0)
	{
		fprintf(stderr,"Unable to open display\n");
		return;
	}
	i2cWriteByte(displayHandle,0x21);
	i2cWriteByte(displayHandle,HT16K33_BLINK_CMD |
		 HT16K33_BLINK_DISPLAYON | 
		(HT16K33_BLINK_OFF   << 1) );
	i2cWriteByte(displayHandle,HT16K33_CMD_BRIGHTNESS | brightness);
	updateDisplay(); // set everything off
}

void updateDisplay()
{
	int i;

 	i2cWriteByte(displayHandle,0x00);

	for(i=0;i<DIGITS;i++)
	{
		i2cWriteWordData(displayHandle,
			i*2,displayBuffer[i]);

	}
}

void rawSetDigit(int digit,int val)
{
	displayBuffer[digit]=val;
}

void setDigit(int digit,char val)
{
	if ( (digit<0) || (digit>=DIGITS))
	{
		return;
	}
	if (digit>1)
	{
		digit++; // skip over colon
	}
	switch (val)
	{
		case '0':
			displayBuffer[digit]=0x3F;
			break;
		case '1':
			displayBuffer[digit]=0x06;
			break;
		case '2':
			displayBuffer[digit]=0x5B;
			break;
		case '3':
			displayBuffer[digit]=0x4F;
			break;
		case '4':
			displayBuffer[digit]=0x66;
			break;
		case '5':
			displayBuffer[digit]=0x6D;
			break;
		case '6':
			displayBuffer[digit]=0x7D;
			break;
		case '7':
			displayBuffer[digit]=0x07;
			break;
		case '8':
			displayBuffer[digit]=0x7F;
			break;
		case '9':
			displayBuffer[digit]=0x6F;
			break;
		default:
			displayBuffer[digit]=0; // blank
			break;
	}
}

void setDisplayString(char *szString)
{
	char szDisplay[4];
	int i;

	strncpy(szDisplay,szString,4);
	for(i=0;i<4;i++)
	{
		setDigit(i,szDisplay[i]);
	}
	updateDisplay();
}

void setDisplayInt(int value)
{
	char szBuffer[10];
	sprintf(szBuffer,"%4.4d",value);
	setDisplayString(szBuffer);
}

void displayColon(int colon)
{
	if (colon)
	{
		displayBuffer[2]=0x2;
	}
	else
	{
		displayBuffer[2]=0x0;
	}
}

void closeDisplay()
{
	// close(displayHandle);
	displayColon(0);
	setDisplayString("    ");
	i2cClose(displayHandle);
	gpioTerminate();
}

