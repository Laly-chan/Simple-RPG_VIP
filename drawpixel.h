#ifndef DRAWPIXEL_H
#define DRAWPIXEL_H

#include <string.h>

inline void printp(int,int,unsigned short,unsigned short, int ch = 223);

inline void printp(int x1, int y1, unsigned short color, unsigned short bgcolor, int ch){
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.Y = y1;
	dwPos.X = x1;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
	SetConsoleTextAttribute(hCon,color);
	
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hCon, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	bgcolor &= 0x000f;
	bgcolor <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= bgcolor;

	SetConsoleTextAttribute(hCon, wAttributes);
	printf("%c",ch);
}

inline void printtext(int x1, int y1, unsigned short color, unsigned short bgcolor, string text){
	printp(x1-1,y1,color,bgcolor,0);
	
	std::cout<<text;
}

#endif
