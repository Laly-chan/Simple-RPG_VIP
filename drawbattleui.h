#ifndef DRAWBATTLEUI_H
#define DRAWBATTLEUI_H

#include "drawpixel.h"
#include "mapplayer.h"
#include "player.h"
#include "loadbattleui.h"

#define ushort unsigned short

/* colores:
0 negro
1 azul oscuro
2 verde oscuro
3 celeste oscuro
4 rojo oscuro
5 magenta oscuro
6 amarillo oscuro
7 gris claro
8 gris oscuro
9 azul claro
10 verde claro
11 celeste claro
12 rojo claro
13 magenta claro
14 amarillo claro
15 blanco
*/

/* paleta test: (arriba/abajo)
0: - (nada)
1: comprobante
2: 6/6
3: -/6
4: 6/-
5: 14/14
6: -/14
7: 14/-
8: 0/0
9: -/0
10: 0/-
14: 6/14
15: 14/6
16: 0/14
17: 14/0
18: 6/0
19: 0/6
20: 4/4
21: -/4
22: 4/-
23: 4/6
24: 6/4
25: 4/14
26: 14/4
*/

void drawbattleui(int);

void adminfirststats(Player**);
void drawfirststats(int*,int,int);
void drawPlayerHP(Player**);

void drawopc(int,int,int,int,int,int,Player**,Enemy**);
void admincursor(int,int,int,int,int);
void enemyCursor(ushort,ushort);

inline void drawAllCursor(bool);
inline void drawcursor(ushort,ushort,ushort,bool);
inline void startcursor(ushort,ushort);
inline void endcursor(ushort,ushort);
inline void middlecursor(ushort,ushort,ushort);
inline void erasecursor(ushort,ushort,ushort);

inline void refreshimage(ushort Hstart = 0, ushort Hend = 80, ushort Vstart = 0, ushort Vend = 26);

inline void loadenemysprite(string,short sprite[][16][8],short);
inline void drawimage(ushort Hstart = 0, ushort Hend = 80, ushort Vstart = 0, ushort Vend = 26);
inline short GetBackgroundColor(int,int,int);

void actionDescriptions(string,int);
inline void drawDesc(char*,short,short);
void drawDialogue(char**);

void refreshActions(char**,short);
void mostrarAcciones(short,char**);

short uimap[84][42];
short foreground[80][26];
short background[80][26];

inline void loadenemysprite(string enemyname, short sprite[][16][8], short frame){
	string enemypath = "Enemy//InBattle//"+enemyname+".spr";
	loadsprite(enemypath, sprite,frame);
}

void drawbattleui(int bgzone){
	loadimage(bgzone);
	for (register int i = 0; i < 84; i++){
		for (register int j = 0; j < 42; j++){
			if (uimap[i][j] >0){
				printp(i,j,8,8);
			}
			if (uimap[i][j] < 10) continue;
			
			printp(i,j,0,8,uimap[i][j]);
		}
	}
	for (register int i = 0; i < 80; i++){
		for (register int j = 0; j < 26; j++){
			foreground[i][j] = 0;
		}
	}
	drawimage();
	
}

inline void drawimage(ushort Hstart, ushort Hend, ushort Vstart, ushort Vend){
	short bgc[2] = {0,0};
	for (register int i = Hstart; i < Hend; i++){
		for (register int j = Vstart; j < Vend; j++){
			if (background[i][j] > 0) {
				switch(background[i][j]){
					case 1: printp(i+2,j+9,12,12); break;
					case 2: printp(i+2,j+9,14,12); break;
					case 3: printp(i+2,j+9,14,14); break;
					case 4: printp(i+2,j+9,14,7); break;
					case 5: printp(i+2,j+9,7,14); break;
					case 6: printp(i+2,j+9,7,7); break;
					case 7: printp(i+2,j+9,14,6); break;
					case 8: printp(i+2,j+9,6,14); break;
					case 9: printp(i+2,j+9,6,6); break;
					case 10: printp(i+2,j+9,14,8); break;
					case 11: printp(i+2,j+9,8,14); break;
					case 12: printp(i+2,j+9,8,8); break;
					case 13: printp(i+2,j+9,14,0); break;
					case 14: printp(i+2,j+9,0,14); break;
					case 15: printp(i+2,j+9,0,0); break;
					case 16: printp(i+2,j+9,7,6); break;
					case 17: printp(i+2,j+9,6,7); break;
					case 18: printp(i+2,j+9,7,8); break;
					case 19: printp(i+2,j+9,8,7); break;
					case 20: printp(i+2,j+9,7,0); break;
					case 21: printp(i+2,j+9,0,7); break;
					case 22: printp(i+2,j+9,6,8); break;
					case 23: printp(i+2,j+9,8,6); break;
					case 24: printp(i+2,j+9,6,0); break;
					case 25: printp(i+2,j+9,0,6); break;
					case 26: printp(i+2,j+9,8,0); break;
					case 27: printp(i+2,j+9,0,8); break;
				}
				background[i][j]*=-1;
			}
			if (foreground[i][j] < 0) continue;
			bgc[0] = GetBackgroundColor(i,j,0);
			bgc[1] = GetBackgroundColor(i,j,1);
			switch(foreground[i][j]){
				case 2: printp(i+2,j+9,6,6); break;
				case 3: printp(i+2,j+9,bgc[0],6); break;
				case 4: printp(i+2,j+9,6,bgc[1]); break;
				case 5: printp(i+2,j+9,14,14); break;
				case 6: printp(i+2,j+9,bgc[0],14); break;
				case 7: printp(i+2,j+9,14,bgc[1]); break;
				case 8: printp(i+2,j+9,0,0); break;
				case 9: printp(i+2,j+9,bgc[0],0); break;
				case 10: printp(i+2,j+9,0,bgc[1]); break;
				case 14: printp(i+2,j+9,6,14); break;
				case 15: printp(i+2,j+9,14,6); break;
				case 16: printp(i+2,j+9,0,14); break;
				case 17: printp(i+2,j+9,14,0); break;
				case 18: printp(i+2,j+9,6,0); break;
				case 19: printp(i+2,j+9,0,6); break;
				case 20: printp(i+2,j+9,4,4); break;
				case 21: printp(i+2,j+9,bgc[0],4); break;
				case 22: printp(i+2,j+9,4,bgc[1]); break;
				case 23: printp(i+2,j+9,4,6); break;
				case 24: printp(i+2,j+9,6,4); break;
				case 25: printp(i+2,j+9,4,14); break;
				case 26: printp(i+2,j+9,14,4); break;
			} 
			foreground[i][j]*=-1;
		}
	}
}

inline short GetBackgroundColor(int xb, int yb, int pos){
	if (pos = 0){
		switch(background[xb][yb]){
			case -2: case -3: case -4: case -7: case -10: case -13: return 14;
			case -5: case -6: case -16: case -18: case -20: return 7;
			case -8: case -9: case -17: case -22: case -24: return 6;
			case -11: case -12: case -19: case -23: case -26: return 8;
		}
	}
	switch(background[xb][yb]){
		case -3: case -5: case -8: case -11: case -14: return 14;
		case -4: case -6: case -17: case -19: case -21: return 7;
		case -7: case -9: case -16: case -23: case -25: return 6;
		case -10: case -12: case -18: case -22: case -27: return 8;
	}
	return 0;
}

void drawopc(int lay, int prevlay, int cursor, int prevcurpos, int actplayer, int cantene, Player **player, Enemy **enemy){
	extern int curpos[2][2];
	extern char actions[6][8];
	extern char items[8][20];
	int auxobj;
	string playerName = "default";
	int page = 0;
	for (register int i = 36; i < 41; i++){
		printtext(3,i,15,0,"                                       ");
	}
	for (register int i = 1; i < 8; i++){
		printtext(4,i,15,0,"                                                                           ");
	}
	switch(lay){
		case 0:
			auxobj = player[cursor][0].getPlayer();
			playerName = player[auxobj][0].getName();
			
			player[cursor][0].drawActions(playerName,enemy,cantene);
			player[cursor][0].drawEffects();
			
			printtext(5,40,15,0,"Enter = select       Esc = end turn");
			break;
		case 1:
			for (register int i = 0; i < 3; i++){
				for (register int j = 0; j < 2; j++){
					int xm = 6 + (i*14); int ym = 37 + (j*2);
					int aux = (i*2)+j;
					printtext(xm,ym,15,0,actions[aux]);
				}
			}
			break;
		case 2:
			page = int(curpos[1][0]/2);
			switch (Player::opc[0]){
				case 3:
					player[actplayer][0].drawSpells(page);
					break;
				case 4:
					printtext(6,37,15,0,items[(page*2)+1]);
					printtext(6,39,15,0,items[(page*2)+2]);
					break;
			}
			break;
		case 3:
			switch(Player::opc[0]){
				case 3:
					if (Player::opc[1] > 20) break;
				case 1: case 5:
					printtext(5,38,15,0,enemy[cursor][0].getName());
					
					printtext(8,39,15,0,"/    HP");
					
					for (int i = 0 ; i < 2; i++){
						int enemyhp = enemy[cursor][0].getHP(i);
						
						char auxtext[4] = {numtochar(enemyhp,100),numtochar(enemyhp,10),numtochar(enemyhp,1),0};
						
						if (enemyhp < 100) auxtext[0] = 32;
						if (enemyhp < 10) auxtext[1] = 32;
						
						printtext(5+(i*4),39,15,0,auxtext);
					}
			}
	}
	admincursor(lay,prevlay,cursor,prevcurpos,page);
}

void admincursor(int lay, int prevlay, int cursor, int prevcursor, int page){
	extern int curpos[2][2];
	extern char actions[6][8];
	extern char items[8][20];
	ushort ycursor,xcursor;
	switch (prevlay){
		case 0:
			ycursor = 37+(curpos[1][1]*2);
			xcursor = 45+(curpos[0][1]*19);
			drawcursor(xcursor,ycursor,17,true);
			if (lay > prevlay) {
				printp(xcursor-1,ycursor,15,0,62);
			} break;
		case 3:
			refreshimage(1,79,5,6);
			refreshimage(1,79,14,15);
			refreshimage(1,79,23,24);
			drawimage(1,79,5,6);
			drawimage(1,79,14,15);
			drawimage(1,79,23,24);
			drawcursor(45,37,17,true);
			drawcursor(45,39,17,true);
			drawcursor(64,37,17,true);
			drawcursor(64,39,17,true);
			printp(63,36,15,0,' ');
			printp(63,40,15,0,' ');
	}
	switch (lay){
		case 0:
			ycursor = 37+(curpos[1][0]*2);
			xcursor = 45+(curpos[0][0]*19);
			drawcursor(xcursor,ycursor,17,false);
			printp(44,37,15,0,32); printp(63,37,15,0,32); printp(44,39,15,0,32); printp(63,39,15,0,32);
			break;
		case 1:
			ycursor = 37+(curpos[1][0]*2);
			xcursor = 4+(curpos[0][0]*14);
			drawcursor(xcursor,ycursor,strlen(actions[cursor])+1,false);
			break;
		case 2:
			ycursor = 37+((curpos[1][0]%2)*2);
			xcursor = 4+(curpos[0][0]*19);
			printp(xcursor-1,ycursor,15,0,62);
			break;
		case 3:
			switch (Player::opc[0]){
				case 3:
					switch (Player::opc[1]){
						case 11:
							ycursor = 14+(int(curpos[1][0]/4)*9);
							xcursor = 3+((curpos[1][0]%4)*20);
							enemyCursor(xcursor,ycursor);
							break;
						case 21: case 22: case 23:
							drawAllCursor(false);
							 break;
						case 41:
							ycursor = 37+(curpos[1][0]*2);
							xcursor = 45+(curpos[0][0]*19);
							drawcursor(xcursor,ycursor,17,false);
							break;
						case 52: case 53:
							drawAllCursor(true);
							break;
					} break;
				case 1: case 5:
					ycursor = 14+(int(curpos[1][0]/4)*9);
					xcursor = 3+((curpos[1][0]%4)*20);
					enemyCursor(xcursor,ycursor);
					break;
				case 2: case 4:
					ycursor = 37+(curpos[1][0]*2);
					xcursor = 45+(curpos[0][0]*19);
					drawcursor(xcursor,ycursor,17,false);
					break;
			}
			break;
		default: return;
	}
	
}

inline void drawAllCursor(bool cplayer){
	
	if (true) printtext(5,38,15,0,"Everyone");
	
	if (false) printtext(5,38,15,0,"Todos");
	
	if (cplayer){
		startcursor(45,37);
		startcursor(45,39);
		endcursor(81,37);
		endcursor(81,39);
		for (register int i = 0; i < 35; i++){
			printp(46+i,36,15,0,205);
			printp(46+i,40,15,0,205);
		}
		printp(45,38,15,0,186); printp(81,38,15,0,186);
		return;
	}
	
	for (register int i = 4; i < 80; i++){
		printp(i,32,15,0,205);
	}
	printp(3,32,15,0,200); printp(80,32,15,0,188);
}

void enemyCursor(ushort xcursor, ushort ycursor){
	for (register int i = 1; i < 17; i++){
		printp(xcursor+i,ycursor,15,0,205); 
		printp(xcursor+i,ycursor+9,15,0,205);
	}
	printp(xcursor,ycursor,15,0,201); printp(xcursor+17,ycursor,15,0,187);
	printp(xcursor,ycursor+9,15,0,200); printp(xcursor+17,ycursor+9,15,0,188);
}

inline void drawcursor(ushort xcursor, ushort ycursor, ushort length,bool erase){
	if (erase){
		erasecursor(xcursor,ycursor,length);
		return;
	}
	startcursor(xcursor,ycursor);
	endcursor(xcursor+length,ycursor);
	middlecursor(xcursor+1,ycursor,length-1);
}

inline void startcursor(ushort xcursor, ushort ycursor){
	printp(xcursor,ycursor-1,15,0,201);
	printp(xcursor,ycursor,15,0,186);
	printp(xcursor,ycursor+1,15,0,200);
}

inline void endcursor(ushort xcursor, ushort ycursor){
	printp(xcursor,ycursor-1,15,0,187);
	printp(xcursor,ycursor,15,0,186);
	printp(xcursor,ycursor+1,15,0,188);
}

inline void middlecursor(ushort xcursor, ushort ycursor, ushort length){
	for (register int i = 0; i < length; i++){
		printp(xcursor+i,ycursor-1,15,0,205);
		printp(xcursor+i,ycursor+1,15,0,205);
	}
}

inline void erasecursor(ushort xcursor, ushort ycursor, ushort length){
	for (register int i = 0; i < length+1; i++){
		printp(xcursor+i,ycursor-1,15,0,' ');
		printp(xcursor+i,ycursor+1,15,0,' ');
	}
	printp(xcursor,ycursor,15,0,' ');
	printp(xcursor+length,ycursor,15,0,' ');
}

void adminfirststats(Player **player){
	int aux[4];
	int xmp, ymp;
	const char barra = '/';
	
	drawPlayerHP(player);
	
	for (int i = 0; i < 4; i++){
		aux[i] = player[i][0].maxhp;
	}
	drawfirststats(aux,60,37);
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			xmp = 47+(i*19);
			ymp = 37+(j*2);
			printp(xmp+11,ymp,15,0,barra);
			printtext(xmp,ymp,15,0,MapPlayer::name[i*2+j]);
		}
	}
}

void drawfirststats(int *aux, int x, int y){
	int aux2;
	int xm,ym;
	for (register int i = 0; i < 2; i++){
		for (register int j = 0; j < 2; j++){
			xm = x + (i*19);
			ym = y + (j*2);
			aux2 = aux[(i*2)+j];
			char auxtext[4] = {numtochar(aux2,100),numtochar(aux2,10),numtochar(aux2,1),0};
			if (aux2 < 100) auxtext[0] = 32;
			if (aux2 < 10) auxtext[1] = 32;
			printtext(xm,ym,15,0,auxtext);
		}
	}
}

void drawPlayerHP(Player** player){
	int aux[4];
	
	for (int i = 0; i < 4; i++){
		aux[i] = player[i][0].hp;
	}
	drawfirststats(aux,56,37);
}

inline void refreshimage(ushort Hstart, ushort Hend, ushort Vstart, ushort Vend){
	for (register int i = Hstart; i < Hend; i++){
		for (register int j = Vstart; j < Vend; j++){
			if (background[i][j] < 0) background[i][j]*=-1;
			if (foreground[i][j] < 0) foreground[i][j]*=-1;
		}
	}
}

void refreshActions(char** actiontext, short line){
	unsigned short middle = 5;
	printtext(4,6,15,0,"                                                                            ");
	
	for (register int i = 0; i < 4; i++){
		printtext(4,2+i,15,0,"                                                                            ");
		if (i+line-4 < 0) continue;
		middle = 42-(strlen(actiontext[i+line-4])/2);
		printtext(middle,2+i,15,0,actiontext[i+line-4]);
	}
	
	for (register int i = 0; i < 76; i++){
		if (line < 0) break;
		if (actiontext[line][i] == 0) break;
		middle = 42-(strlen(actiontext[line])/2);
		printp(middle-1+i,6,15,0,actiontext[line][i]);
		Sleep(1);
		press();
		if (tecla != 0){
			printtext(middle,6,15,0,actiontext[line]);
			tecla = 0;
			break;
		}
	}
	
}

void mostrarAcciones(short actcur, char **actiontext){
	unsigned short middle = 5;
	for (register int i = 0; i < 5; i++){
		printtext(4,2+i,15,0,"                                                                            ");
		if (i+actcur < 0) continue;
		middle = 42-(strlen(actiontext[i+actcur])/2);
		printtext(middle,2+i,15,0,actiontext[i+actcur]);
	}
}

void actionDescriptions(string descpath, int actcur){
	static short actchar = 0;
	string desctext[16];
	Sleep(1);
	loadtext(desctext,descpath);
	
	char chardesctext[76];
	
	for (register int i = 0; i < 76; i++){
		if (desctext[actcur][i] == 0){
			chardesctext[i] = 0; break;
		}
		chardesctext[i] = desctext[actcur][i];
	}
	
	drawDesc(chardesctext,4,actchar);
	
	if (actchar < strlen(chardesctext)) actchar++;
	
	if (tecla != 0){
		actchar = 0;
		printtext(4,4,15,0,"                                                                            ");
	}
	
}

inline void drawDesc(char* desctext,short y, short i){
	unsigned short middle =  42-(strlen(desctext)/2);
	printp(middle-1+i,y,15,0,desctext[i]);
}

void drawDialogue(char** dialoguetext){
	unsigned short middle = 0;
	tecla = 0;
	for (register int i = 0; i < 5; i++){
		middle = 42-(strlen(dialoguetext[i])/2);
		for (int j = 0; j < 76; j++){
			if (tecla != 0) break;
			if (dialoguetext[i][j] == 0) break;
			printp(middle-1+j,2+i,15,0,dialoguetext[i][j]);
			if (dialoguetext[i][j] != 32) Sleep(1);
			press();
		}
		if (tecla != 0){
			printtext(middle,2+i,15,0,dialoguetext[i]);
		}
	}
	tecla = 0;
}

#endif
