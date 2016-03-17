#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3
#define HT16K33_CMD_BRIGHTNESS 0xE0


#define DIGITS 8

void sevenSegmentInit();
void rawSetDigit(int,int);
void setDigit(int,char);
void setDisplayString(char *);
void setDisplayInt(int);
void displayColon(int);
void updateDisplay();
void closeDisplay();




