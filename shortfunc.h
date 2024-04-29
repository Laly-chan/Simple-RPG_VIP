#ifndef SHORTFUNC_H
#define SHORTFUNC_H

inline void press();
inline int randnum(int,int);
inline void timer();
inline char numtochar(int,int);

extern char tecla;
extern unsigned long seed;

inline void press(){
	timer();
	if (kbhit()) {
		tecla = getch(); return;
	} tecla = 0;
}
inline int randnum(int range, int min){
	return ( ( ( 47 * seed + rand() ) %range ) + min );
}
inline void timer(){
	seed++;
}

inline char numtochar(int num,int dec){
	num /= dec;
	return int(num%10)+48;
}

#endif
