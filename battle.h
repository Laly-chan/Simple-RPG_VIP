#ifndef BATTLE_H
#define BATTLE_H
class Enemy;
class Player;
#include "shortfunc.h"
#include "loadtext.h"
#include "mapenemy.h"
#include "enemy.h"
#include "subenemy.h"
#include "mapplayer.h"
#include "player.h"
#include "subplayer.h"
#include "drawpixel.h"
#include "drawbattleui.h"

#define up 72
#define down 80
#define left 75
#define right 77
#define esc 27
#define enter 13

void battle(MapPlayer*, int, int);

void iniciarbatalla(MapPlayer,Player**,Enemy**,int);
void createenemy(Enemy**,int,int,int);

void selectplayer();
inline void changelay(int&, int&);

void setOrder(Player**,Enemy**,int order[][2],int,int start = 0);
void ejecutarAcciones(Player**, Enemy**,int);
void moverAcciones(char**,int);

int opc = 0, actplayer = 0, prevopc = 0;
int curpos[2][2] = {0,0,0,0};
char actions[6][8] = {'A','t','t','a','c','k',0,0,'D','e','f','e','n','s','e',0,'S','p','e','l','l',0,0,0,'I','t','e','m',0,0,0,0,'I','n','f','o',0,0,0,0,'R','u','n'};
char items[10][20] = {
"Mysterious Item",
"Healing Potion",
"Magic Potion",
"Attack Elixir",
"Defense Elixir", //cat's metal potion
"Reviving Orb Shield",
"Aya's Feathers"}; //tal vez cambie el nombre de los items

void battle(MapPlayer *mapplayer, int typeenemy, int zone){
	int maxenemy = randnum( 3 , typeenemy/10 );
	if (typeenemy == 99) maxenemy = 1;
	int lay = 0; int prevlay = lay;
	int frameadvance = time(0);
	int auxanim = 0;
	int cantenemy = maxenemy;
	Player *player[4];
	Enemy *enemy[cantenemy];
	
	createenemy(enemy,cantenemy,typeenemy%10,zone);
	iniciarbatalla(*mapplayer,player,enemy,cantenemy);
	drawimage();
	startbattle:
		do {
			if (frameadvance != time(0)){
				enemy[auxanim][0].changeFrame();
				auxanim++;
				if (auxanim == maxenemy){
					frameadvance = time(0);
					auxanim = 0;
				}
			}
			
			press();
			changelay(lay,prevlay);
			
			if (lay == 0 && prevlay == 0) selectplayer();
			
			if (lay == 2 || prevlay == 2){
				if (Player::opc[0] == 3){
					actionDescriptions("Texto//"+LANG+"//Battle//MagicDescriptions.txt", (curpos[1][0] + (actplayer*4) ) );
				}
				if (Player::opc[0] == 4){
					actionDescriptions("Texto//"+LANG+"//Battle//ItemDescriptions.txt", curpos[1][0]);
				}
			}
			
			if (tecla != 0){
				
				player[actplayer][0].selectopc(lay,opc,maxenemy,enemy);
				
				drawopc(lay,prevlay,opc,prevopc,actplayer,maxenemy,player,enemy);
			}
			
			if (lay < 0) break;
		} while (true);
		lay = 0;
		ejecutarAcciones(player,enemy,maxenemy);
		drawPlayerHP(player);
		for (int i = 0; i < 4; i++){
			player[i][0].resetStats(*mapplayer);
		}
		cantenemy = maxenemy;
		for (register int i = 0; i < maxenemy; i++){
			if (enemy[i][0].getHP(0) == 0) cantenemy--;
		}
		drawopc(lay,prevlay,opc,prevopc,actplayer,maxenemy,player,enemy);
		if (cantenemy == 0)goto endbattle;
	goto startbattle;
	endbattle: system("cls");
	printtext(0,0,15,0,"you win :D"); getch(); system("cls");
}

void selectplayer(){
	switch (tecla){
		case up:
			curpos[1][0]--;
			if (curpos[1][0] < 0) {
				curpos[1][0] = 1;
			} break;
		case down:
			curpos[1][0]++;
			if (curpos[1][0] > 1) {
				curpos[1][0] = 0;
			} break;
		case left:
			curpos[0][0]--;
			if (curpos[0][0] < 0) { //curpos[0][.] = posicion x del cursor
				curpos[0][0] = 1;   //curpos[1][.] = posicion y del cursor
			} break;                //curpos[.][0] = posicion acutal del cursor
		case right:                 //curpos[.][1] = posicion anterior del cursor
			curpos[0][0]++;         //me enoje e hice todo esto xd
			if (curpos[0][0] > 1) {
				curpos[0][0] = 0;
			} break;
	}
	opc = (curpos[0][0]*2) + curpos[1][0];
	actplayer = opc;
}

inline void changelay(int &lay, int &prevlay){
	curpos[0][1] = curpos[0][0]; curpos[1][1] = curpos[1][0];
	prevopc = opc;
	prevlay = lay;
	switch (tecla){
		case enter:
			lay++;
			break;
		case esc:
			lay--;
			if ((Player::opc[0] == 1 || Player::opc[0] == 2|| Player::opc[0] == 5) && lay >1) lay--;
			break;
		default:
			return;
	}
	curpos[0][0] = 0; curpos[1][0] = 0;
	for (register int i = 2; i > lay-1; i--){
		Player::opc[i] = 0;
	}
	opc = 0;
}

void iniciarbatalla(MapPlayer mapplayer, Player **player, Enemy **enemy, int cantenemy){
	player[0] = new PlayerHero;
	player[1] = new PlayerStrong;
	player[2] = new PlayerWizard;
	player[3] = new PlayerSupport;
	for (register int i=0; i < 4; i++){
		player[i][0].setstats(i,mapplayer);
	}
	drawbattleui(1);
	adminfirststats(player);
	for (register int i = 0; i < cantenemy; i++){
		enemy[i][0].setstats();
		enemy[i][0].loadsprite();
		enemy[i][0].setSpritePos();
	}
	drawopc(0,0,0,0,0,cantenemy,player,enemy);
}

void createenemy(Enemy **enemy, int cantenemy, int typeenemy, int zone){
	int randenemy = 1;//typeenemy;
	switch (zone){
		case 0:
			for (register int i = 0; i < cantenemy; i++){
				switch(randenemy){
					case 1: 
						enemy[i] = new ElectricWizard; break;
					case 2:
						enemy[i] = new Golem; break;
				}
				randenemy = (randnum(69,1)%2)+1;
			} break;
		case 1:
			for (register int i = 0; i < cantenemy; i++){
				switch(randenemy){
					case 1: 
						enemy[i] = new ElectricWizard; break;
					case 2:
						enemy[i] = new Golem; break;
				}
				randenemy = (randnum(69,1)%2)+1;
			} break;
		case 2:
			for (register int i = 0; i < cantenemy; i++){
				switch(randenemy){
					case 1: 
						enemy[i] = new ElectricWizard; break;
					case 2:
						enemy[i] = new Golem; break;
				}
				randenemy = (randnum(69,1)%2)+1;
			} break;
		case 3:
			for (register int i = 0; i < cantenemy; i++){
				switch(randenemy){
					case 1: 
						enemy[i] = new ElectricWizard; break;
					case 2:
						enemy[i] = new Golem; break;
				}
				randenemy = (randnum(69,1)%2)+1;
			} break;
		case 4:
			for (register int i = 0; i < cantenemy; i++){
				switch(randenemy){
					case 1: 
						enemy[i] = new ElectricWizard; break;
					case 2:
						enemy[i] = new Golem; break;
				}
				randenemy = (randnum(69,1)%2)+1;
			} break;
		default:
			for (register int i = 0; i < cantenemy; i++){
				switch(randenemy){
					case 1: 
						enemy[i] = new ElectricWizard; break;
					case 2:
						enemy[i] = new Golem; break;
				}
				randenemy = (randnum(69,1)%2)+1;
			}
	}
}

void ejecutarAcciones(Player **player, Enemy **enemy, int cantenemy){
	int order[12][2];
	
	int aux;
	short line = 0;
	
	char *actiontext[200];
	string stringaux[8];
	
	loadtext(stringaux,"Texto//"+LANG+"//Actions//Ui.txt");
	
	printtext(8,38,15,0,stringaux[0]);
	
	loadtext(stringaux,"Texto//"+LANG+"//Actions//Actions.txt");
	
	for (int i = 0; i < 5; i++){
		actiontext[195+i] = new char[17];
		for (int j = 0; j < 17; j++){
			if (stringaux[i][j] == 0) {
				actiontext[195+i][j] = 0;
				break;
			}
			actiontext[195+i][j] = stringaux[i][j];
		}
	}
	
	loadtext(stringaux,"Texto//"+LANG+"//Actions//Effects.txt");
	
	for (int i = 0; i < 8; i++){
		actiontext[187+i] = new char[19];
		for (int j = 0; j < 19; j++){
			if (stringaux[i][j] == 0) {
				actiontext[187+i][j] = 0;
				break;
			}
			actiontext[187+i][j] = stringaux[i][j];
		}
	}
	
	for (register int i = 0; i < cantenemy+4; i++){
		setOrder(player,enemy,order,cantenemy,i);
		actiontext[line] = new char[76];
		actiontext[line][0] = 0;
		
		printp(40,1,15,0,32);
		
		if (line > 5) printp(40,1,15,0,94);
		
		if (order[i][1] >= 8){
			aux = order[i][1]-8;
			player[aux][0].ejecutarAcciones(player,enemy,cantenemy,actiontext,line);
		}
		if (order[i][1] < 8){
			aux = order[i][1];
			enemy[aux][0].atacar(player,enemy,actiontext,line,aux);
			/*if (enemy[aux][0].getHP(0) > 0){
				refreshActions(actiontext,line);
				line+=2;
			} line--;*/
		}
		
		drawPlayerHP(player);
		
		moverAcciones(actiontext,line);
		
		printtext(72,1,15,0,"       ");
		
		actiontext[line] = new char[1];
		actiontext[line][0] = 0;
		refreshActions(actiontext,line);
		line++;
	}
	
	for (register int i = 1; i < 8; i++){
		printtext(4,i,15,0,"                                                                            ");
	}
}

void setOrder(Player **player, Enemy **enemy, int order[12][2], int cantenemy, int start){
	for (register int i = 0; i < 4; i++){
		player[i][0].setSpeed();
	}
	if (start == 0){
		for (register int i = 0; i < 8; i++){
			if (i < cantenemy){
				order[i][0] = enemy[i][0].getSpeed();
				order[i][1] = i;
			}
		}
		for (register int i = 0; i < 4; i++){
			order[i+cantenemy][0] = player[i][0].getSpeed();
			order[i+cantenemy][1] = i+8;
		}
	}
	int aux;
	for (register int i = start; i < cantenemy+4; i++){
		for (register int j = cantenemy+3; j > start; j--){
			if (order[j][1] > 8){
				order[j][0] = player[order[j][1]-8][0].getSpeed();
			}
			if (order[j][0] > order[j-1][0]){
				aux = order[j-1][0]; //se ordena según la velocidad
				order[j-1][0] = order[j][0];
				order[j][0] = aux;
				
				aux = order[j-1][1]; //cambia el índice de referencia junto con el orden de la velocidad
				order[j-1][1] = order[j][1];
				order[j][1] = aux;
			}
		}
	}
}

void moverAcciones(char **actiontext,int line){
	short actcur = line - 5;
	static short auxline = -1;
	
	do {
		press();
		if (auxline+1 == line || auxline == line) break;
		switch(tecla){
			case up:
				actcur--;
				if (actcur < 0){
					actcur++;
				} break;
			case down:
				actcur++;
				if (actcur+5 > line){
					actcur--;
				}
		}
		
		if (tecla != 0){
			printp(40,1,15,0,32); printp(40,7,15,0,32);
			
			if (actcur > 0) printp(40,1,15,0,94);
			if (actcur+5 < line) printp(40,7,15,0,118);
			
			mostrarAcciones(actcur,actiontext);
		}
		
	} while (tecla != enter);
	auxline = line;
	printp(40,1,15,0,32); printp(40,7,15,0,32);
}

#endif
