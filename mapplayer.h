#ifndef MAPPLAYER_H
#define MAPPLAYER_H

#define up 72
#define down 80
#define left 75
#define right 77
#define space 32

class MapPlayer{
	friend class Player;
	friend void ChangeHP(unsigned short,bool,int,int);
	private:
		int xmap,ymap;
		float x,y;
		int actp;
		//stats
		int hp[4],mp[4];
		int maxhp[4],maxmp[4];
		int atk[4],def[4];
		int spd[4],luck[4];
		int unmag[4]; //unlocked magic, cantidad de ataques mágicos desbloqueados
		int spcs[4][4]; //spell costs spcs[ player ] [ spell ]
	public:
		static string name[4];
		static string spells[4][4];
		MapPlayer(){}
		void mover(int zona[][26],int zonaobj[][25],char, bool*, bool*);
		void setpos(float,float);
		void setper(int);
		void setstats();
		int getper(){ return actp;}
		int getxpos(){ return xmap;}
		int getypos(){ return ymap;}
};
//std::string MapPlayer::name[4] = {"Flumf...","Momyo...","Mors....","Rika...."};
std::string MapPlayer::name[4] = {"Flumf","Momyo","Mors","Rika"};

std::string MapPlayer::spells[4][4] =
{"[High Damage ~ Thunder Sword]","[flumf spell 2]","[flumf spell 3]","[flumf spell 4]",
"[Rock Platform ~ Asteroid Belt]","[momyo spell 2]","[momyo spell 3]","[momyo spell 4]",
"[Sharp Leaf ~ Green Storm]","[Sun's Surface ~ Royal Flare]","[Icicle Fall ~ Diamond Blizzard]","[mors spell 4]",
"[Coconutter Dance ~ Healing Rain]","[E. Legacy ~ Reviving Orb Shield]","[Full Healing Storm]","[rika spell 4]"};

void MapPlayer::setpos(float _x, float _y){
	x = _x;
	y = _y;
	xmap = int(x);
	ymap = int(y);
}
void MapPlayer::setper(int p){
	actp = p;
}
void MapPlayer::setstats(){
	maxhp[0] = 200; maxmp[0] = 10;
	maxhp[1] = 300; maxmp[1] = 5;
	maxhp[2] = 150; maxmp[2] = 30;
	maxhp[3] = 100; maxmp[3] = 20;
	hp[0] = maxhp[0]; mp[0] = maxmp[0];
	hp[1] = maxhp[1]; mp[1] = maxmp[1];
	hp[2] = maxhp[2]; mp[2] = maxmp[2];
	hp[3] = maxhp[3]; mp[3] = maxmp[3];
	
	atk[0] = 25; def[0] = 30;
	atk[1] = 47; def[1] = 35;
	atk[2] = 20; def[2] = 25;
	atk[3] = 12; def[3] = 15;
	
	spd[0] = 16; luck[0] = 13;
	spd[1] = 10; luck[1] = 10;
	spd[2] = 13; luck[2] = 10;
	spd[3] = 16; luck[3] = 20;
	
	unmag[0] = 1;
	unmag[1] = 1;
	unmag[2] = 3;
	unmag[3] = 3;
	
	spcs[0][0] = 3; spcs[0][1] =69; spcs[0][2] = 69; spcs[0][3] = 69;
	spcs[1][0] = 2; spcs[1][1] =69; spcs[1][2] = 69; spcs[1][3] = 69;
	spcs[2][0] = 4; spcs[2][1] = 7; spcs[2][2] = 10; spcs[2][3] = 69;
	spcs[3][0] = 5; spcs[3][1] = 7; spcs[3][2] = 15; spcs[3][3] = 69;
}

void MapPlayer::mover(int zona[25][26], int zonaobj[25][25], char tecla, bool *pmove, bool *enterbattle){
	*pmove = true;
	switch (tecla){
		case up:
		case 'w':
		case 'W':
			if (zonaobj[xmap][ymap-1] <= -10) {*enterbattle = true; ymap--; return;}
			if (zona[xmap][ymap-1] < 100){
				zona[xmap][ymap] *= -1;
				zonaobj[xmap][ymap] = 0;
				ymap--;
				zonaobj[xmap][ymap] = 2;
				return;
			} break;
		case down:
		case 's':
		case 'S':
			if (zonaobj[xmap][ymap+1] <= -10) {*enterbattle = true; ymap++; return;}
			if (zona[xmap][ymap+1] < 100){
				zona[xmap][ymap] *= -1;
				zonaobj[xmap][ymap] = 0;
				ymap++;
				zonaobj[xmap][ymap] = 2;
				return;
			} break;
		case left:
		case 'a':
		case 'A':
			if (zonaobj[xmap-1][ymap] <= -10) {*enterbattle = true; xmap--; return;}
			if (zona[xmap-1][ymap] < 100){
				zona[xmap][ymap] *= -1;
				zonaobj[xmap][ymap] = 0;
				xmap--;
				zonaobj[xmap][ymap] = 2;
				return;
			} break;
		case right:
		case 'd':
		case 'D':
			if (zonaobj[xmap+1][ymap] <= -10) {*enterbattle = true; xmap++; return;}
			if (zona[xmap+1][ymap] < 100){
				zona[xmap][ymap] *= -1;
				zonaobj[xmap][ymap] = 0;
				xmap++;
				zonaobj[xmap][ymap] = 2;
				return;
			} break;
		case space: return;
	}
	*pmove = false;
}

#endif
