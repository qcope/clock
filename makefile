clock:	clock.o sevenSegmentDisplay.o
	gcc clock.o sevenSegmentDisplay.o -o clock -lpigpio -lrt

clock.o: clock.c sevenSegmentDisplay.h
	gcc -c clock.c -o clock.o

sevenSegmentDisplay.o: sevenSegmentDisplay.c sevenSegmentDisplay.h	
	gcc -c -Wall -pthread sevenSegmentDisplay.c -o sevenSegmentDisplay.o
