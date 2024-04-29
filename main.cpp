#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using std::string;

/*
	enemydosomethig(int type, int enemy){
	int fulltype = 100 * type + enemy;
	} no sé para qué es esto pero lo vi en un sueño xd
*/

const string LANG = "ENG";

#include "shortfunc.h"
#include "mapplayer.h"
#include "drawpixel.h"
#include "loadstage.h"
#include "mapenemy.h"
#include "battle.h"

#define up 72
#define down 80
#define left 75
#define right 77
#define esc 27
#define enter 13

void inicio();
void game();

bool compzona(MapPlayer*);
void cargarzona(int,int,short*,MapPlayer*);
void cargarmapene(MapEnemy[],short);

void mostrarmapa();

unsigned long seed = 0;
int zona[25][26], zonaobj[25][25];
int mapa[100][104];
int xzone = 0,yzone = 0;
char tecla = 0;
short betabattleaux = 0;

/* zona referencias:
-1,1 = vacío
-2,2 = personajes
-10/-19,10/19 = enemigo
*/

int main(){
	inicio();
	
	start:
		game();
		timer();
	goto start;
	
	return 0;
}

void inicio(){
	CONSOLE_CURSOR_INFO cursor;
	HANDLE hCon;
	
	cursor.bVisible = false;
	cursor.dwSize = 01;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	
	COORD coord;
    coord.X = 84;
    coord.Y = 42;

    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = 83;
    Rect.Right = 41;
    
    HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 300, 0, Rect.Right, Rect.Bottom, TRUE);    
	SetConsoleCursorInfo(hCon, &cursor);
    system("mode 84,42");
    SetConsoleTitle("Moonlight Project ~ Hidden Dungeon Below the Surface");
}

void cargarzona(int x, int y,short* cantene, MapPlayer* mapplayer){
	bool flagplayer = false;
	x *= 25; y *= 25;
	zona[0][25] = mapa[0+x][100+yzone];
	for (register int i = 0; i < 25; i++){
		for (register int j = 0; j < 25; j++){
			zona[i][j] = mapa[i+x][j+y];
			zonaobj[i][j] = 0;
			if (zona[i][j] < 100 && zona[i][j] > 1){
				zonaobj[i][j] = zona[i][j];
				zona[i][j] = 1;
			}
			if (mapa[i+x][j+y] == 2){
				flagplayer = true;
				mapplayer->setpos(i,j);
				mapa[i+x][j+y] = 1;
			}
			if (zonaobj[i][j] == 3) zona[0][25]++;
			if (zonaobj[i][j] == 4) zona[0][25]++;
		}
	}
	if (!flagplayer) {
		xzone++;
		if (xzone > 3){xzone = 0; yzone++;}
		if (yzone > 3){yzone = 0; return;}
		cargarzona(xzone,yzone,cantene,mapplayer);
		return;
	}
	*cantene = zona[0][25];
	for (register int i = 0; i < 25; i++){
		zona[i][25] = mapa[i+x][100+yzone];
	}
}

void cargarmapene(MapEnemy mapenemy[], short cantene){
	int xe,ye;
	int type,dir;
	for (register int z = 0; z < cantene; z++){
		dir = randnum(4,0);
		type = zona[1+z][25];
		if (type == 10) type = randnum(10,0);
		for (register int i = 0; i < 25; i++){
			for (register int j = 0; j < 25; j++){
				if (zonaobj[i][j] == 3){
					xe = i; ye = j;
					zonaobj[i][j] = type+10;
					mapenemy[z].setpos(xe,ye,3,type+(zona[6+z][25]*10));
					goto endsearch;
				}
				if (zonaobj[i][j] == 4){
					xe = i; ye = j;
					zonaobj[i][j] = 21;
					mapenemy[z].setpos(xe,ye,69,99);
					goto endsearch;
				}
			}
		}
		endsearch:
		if (z >= (cantene-zona[0][25])){
			do {
				xe = randnum(22,2); ye = randnum(22,2);
			} while(zonaobj[xe][ye] != 0);
			zonaobj[xe][ye] = type+10;
			mapenemy[z].setpos(xe,ye,dir,type+(zona[6+z][25]*10));
		}
	}
}

void game(){
	MapPlayer mapplayer = MapPlayer();
	bool pmove = false;
	bool enterbattle = false, startingattack = true;
	short cantene = 0;
	short actcantene = 0;
	loadmap(mapa,"Beta",1);
	cargarzona(xzone,yzone,&cantene,&mapplayer);
	mapplayer.setper(0);
	mapplayer.setstats();
	MapEnemy *mapenemy;
	if (cantene == 1) mapenemy = new MapEnemy; if (cantene > 1) mapenemy = new MapEnemy[cantene];
	cargarmapene(mapenemy,cantene);
	actcantene = cantene;
	int auxtype = 0;
	
	startgame:
		press();
		mapplayer.mover(zona,zonaobj,tecla,&pmove,&enterbattle);
		if (pmove){
			for (register int i = 0; i < cantene; i++){
				
				if (betabattleaux != 0) mapenemy[i].mover(zona,zonaobj,&enterbattle);
				//mapenemy[i].mover(zona,zonaobj,&enterbattle);
				
				if (enterbattle) {
					if (mapplayer.getxpos() == mapenemy[i].getxpos() && mapplayer.getypos() == mapenemy[i].getypos()) {
						mapenemy[i].kill();
						auxtype = mapenemy[i].gettype();
						if (mapa[(xzone*25)+mapenemy[i].xorg][(yzone*25)+mapenemy[i].yorg] == 3){
							mapa[(xzone*25)+mapenemy[i].xorg][(yzone*25)+mapenemy[i].yorg] = 1;
							for (int j = i; j < cantene-1; j++){
								mapa[1+j+(xzone*25)][yzone+100] = mapa[2+j+(xzone*25)][yzone+100];
								mapa[6+j+(xzone*25)][yzone+100] = mapa[7+j+(xzone*25)][yzone+100];
							}
						} else {
							mapa[0+(xzone*25)][yzone+100]--;
						}
					}
				}
			}
			pmove = false;
		}
		if (enterbattle){
			zonaobj[mapplayer.getxpos()][mapplayer.getypos()] = 2;
			printp(0,0,15,0); system("cls");
			battle(&mapplayer,auxtype,betabattleaux);
			enterbattle = false;
			actcantene--;
			mapa[(xzone*25)+mapplayer.getxpos()][(yzone*25)+mapplayer.getypos()] = 2;
			cargarzona(xzone,yzone,&actcantene,&mapplayer);
		}
		if (actcantene == 0){
			actcantene--;
			for (register int i = 0; i < 25; i++){
				for (register int j = 0; j < 25; j++){
					if (zona[i][j] == 102){
						zona[i][j] = 1;
					}
				}
			}
		}
		if (compzona(&mapplayer)){
			for (register int i = 0; i < cantene; i++){
				mapenemy[i].~MapEnemy();
			}
			if (cantene > 1) delete[] mapenemy; if (cantene == 1) delete mapenemy;
			cargarzona(xzone,yzone,&cantene,&mapplayer);
			if (cantene == 1) mapenemy = new MapEnemy; if (cantene > 1) mapenemy = new MapEnemy[cantene];
			cargarmapene(mapenemy,cantene);
			actcantene = cantene;
		}
		mostrarmapa();
		timer();
	goto startgame;
}

bool compzona(MapPlayer *mapplayer){
	int xp,yp;
	xp = mapplayer->getxpos();
	yp = mapplayer->getypos();
	if (yp == 0) {
		mapplayer->setpos(xp,23);
		yzone--;
		goto trueend;
	}
	if (yp == 24) {
		mapplayer->setpos(xp,1);
		yzone++;
		goto trueend;
	}
	if (xp == 0) {
		mapplayer->setpos(23,yp);
		xzone--;
		goto trueend;
	}
	if (xp == 24) {
		mapplayer->setpos(1,yp);
		xzone++;
		goto trueend;
	}
	return false;
	trueend:
		betabattleaux++;
		xp = (mapplayer->getxpos())+(xzone*25);
		yp = (mapplayer->getypos())+(yzone*25);
		mapa[xp][yp] = 2;
	return true;
}

void mostrarmapa(){
	for (register int i = 0; i < 25; i++){
		for (register int j = 0; j < 25; j++){
			int aux = i*2;
			switch (zona[i][j]){
				case 1:
					printp(aux+16,j+8,6,6);
					printp(aux+17,j+8,6,6);
					zona[i][j] = -1;
					break;
				case 101:
					printp(aux+16,j+8,6, 14);
					printp(aux+17,j+8,14, 6);
					zona[i][j] += 100;
					break;
				case 102:
					printp(aux+16,j+8,8, 8);
					printp(aux+17,j+8,8, 8);
					zona[i][j] += 100;
					break;
			}
			switch (zonaobj[i][j]){
				case 2:
					printp(aux+16,j+8,11, 12);
					printp(aux+17,j+8,12, 11);
					zonaobj[i][j] = -2;
					break;
				case 10: case 11:
					printp(aux+16,j+8,13, 7);
					printp(aux+17,j+8,7, 13);
					zonaobj[i][j] *= -1;
					break;
				case 12: //golem
					printp(aux+16,j+8,14, 6);
					printp(aux+17,j+8,6, 14);
					zonaobj[i][j] *= -1;
					break;
				case 13: //Slime
					printp(aux+16,j+8,10, 10);
					printp(aux+17,j+8,10, 10);
					zonaobj[i][j] *= -1;
					break;
				case 14: //esqueleto
					printp(aux+16,j+8,15, 7);
					printp(aux+17,j+8,7, 15);
					zonaobj[i][j] *= -1;
					break;
				case 15: //murcielago
					printp(aux+16,j+8,9, 8);
					printp(aux+17,j+8,8, 9);
					zonaobj[i][j] *= -1;
					break;
				case 16: //clon
					printp(aux+16,j+8,11, 12);
					printp(aux+17,j+8,12, 11);
					zonaobj[i][j] *= -1;
					break;
				case 17: case 18: case 19:
					printp(aux+16,j+8,4, 2);
					printp(aux+17,j+8,2, 4);
					zonaobj[i][j] *= -1;
					break;
				case 21: //bosunaito
					printp(aux+16,j+8,7, 8);
					printp(aux+17,j+8,8, 7);
					zonaobj[i][j] *= -1;
					break;
			}
		}
	}
}
