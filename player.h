#ifndef PLAYER_H
#define PLAYER_H

#include "mapplayer.h"
#include "shortfunc.h"

void refreshActions(char**,short);
void actionDescriptions(string,int);

class Player {
	friend void adminfirststats(Player**);
	friend void drawPlayerHP(Player**);
	template <typename Obj>
	friend inline void ChangeHP(Obj**,short,int,int,char**,string&);
	private:
		int hp,mp;
		int maxhp,maxmp;
		int atk,def;
		int effatk, effspd; //ataque efectivo
		int spd,luck;
		short id, unmag; //unmag = cantidad de hechizos desbloqueados
		int spcs[4]; //spell cost
		bool critic;
		string name;
		string spell[5];
		short action[3];
		short potionEffect[4];
		short magicEffect[4];
		
		void selectaction();
		void verticalSelection(int);
		void selectenemy(int);
		void selectplayer();
		
		inline void drawMP(int,int,int);
		inline int criticChance();
	public:
		static int opc[3];
		Player(){}
		~Player(){}
		
		void setstats(int,MapPlayer);
		void resetStats(MapPlayer);
		
		void selectopc(int&, int&, int,Enemy**);
		
		void drawActions(string,Enemy**,int);
		void drawSpells(int);
		void drawEffects();
		
		void ejecutarAcciones(Player**,Enemy**,int,char**,short&);
		
		inline void setSpeed();
		
		inline string getName(){ return name;} //buena suerte entendiendo lo que escribí xd
		inline int getPlayer();
		inline int getSpeed() { return effspd;}
		inline int getHP(int aux = 0);
		virtual void setSpellObjetive(int&){}
};

inline int Player::getHP(int aux){
	if (aux == 0){
		return hp;
	} return maxhp;
}

inline int Player::getPlayer(){
	if (action[2] > 0 && action[2] < 5){
		return action[2]-1;
	} return 0;
}

inline int Player::criticChance(){
	int crit = (randnum(69420,1)%100);
	if (crit < (5+luck)){
		critic = true;
		return randnum(6,17);
	} return 0;
}

int Player::opc[] = {0,0,0};

void Player::resetStats(MapPlayer mapplayer){
	atk = mapplayer.atk[id];
	def = mapplayer.def[id];
	effspd = mapplayer.spd[id];
	luck = mapplayer.luck[id];
	action[0] = 0;
	action[1] = 0;
	action[2] = 0;
	for (register int i = 0; i < 4; i++){
		potionEffect[i]--;
		magicEffect[i]--;
		if (potionEffect[i] < 0) potionEffect[i] = 0;
		if (magicEffect[i] < 0) magicEffect[i] = 0;
	}
}

void Player::setstats(int z, MapPlayer mapplayer){
	hp = mapplayer.hp[z];
	mp = mapplayer.mp[z];
	maxhp = mapplayer.maxhp[z];
	maxmp = mapplayer.maxmp[z];
	atk = mapplayer.atk[z];
	def = mapplayer.def[z];
	spd = mapplayer.spd[z];
	effspd = spd;
	luck = mapplayer.luck[z];
	name = MapPlayer::name[z];
	unmag = mapplayer.unmag[z];
	for (register int i = 1; i < 5; i++){
		spell[i] = " ";
		potionEffect[i-1] = 0;
		magicEffect[i-1] = 0;
	}
	for (register int i = 0; i < unmag; i++){
		spell[i+1] = MapPlayer::spells[z][i];
		spcs[i] = mapplayer.spcs[z][i];
	}
	spell[0] = "[Missing Number 0 ~ Missigno Spell]";
	action[0] = 0;
	action[1] = 0;
	action[2] = 0;
	id = z;
}

void Player::selectopc(int &lay, int &_opc, int cantene, Enemy** enemy){
	if (lay == 0){
		if (tecla == 27){
			for (register int i = 0; i < 3; i++){
				action[i] = 0;
				Player::opc[i] = 0;
			}
		}
		return;
	}
	int auxmp;
	extern int curpos[2][2];
	switch (lay) {
		case 1:
			this->selectaction(); break;
		case 2:
			switch(opc[0]){
				case 1: case 2: case 5:
					lay++; break;
				case 3:
					verticalSelection(unmag-1);
					break;
				case 4:
					verticalSelection(5); break;
				case 6:
					lay = 4; break;
			} break;
		case 3:
			switch(opc[0]){
				case 3: auxmp = mp-spcs[ (opc[1]-1) ];
					if (auxmp < 0 && tecla == 13){
						lay--;
						curpos[0][0] = curpos[0][1];
						curpos[1][0] = curpos[1][1];
						break;
					}
					if (opc[1] < 10) this->setSpellObjetive(lay);
					switch(opc[1]){
						case 11: case 12: case 13:
							selectenemy(cantene); break;
						case 41: case 42: case 43:
							selectplayer(); break;
					} break;
				case 1:
				case 5:
					selectenemy(cantene); break;
				case 2:
				case 4:
					selectplayer(); break;
			}
	}
	if (lay >= 4){
		for (register int i = 2; i >= 0; i--){
			action[i] = Player::opc[i];
			Player::opc[i] = 0;
			if (action[0] == 5) {
				enemy[ action[2]-1 ][0].drawDescription();
				action[i] = 0;
			}
		}
		lay = 0; return;
	}
	_opc = (curpos[0][0]*2) + curpos[1][0];
	Player::opc[lay-1] = _opc+1;
}

void Player::selectaction(){
	extern int curpos[2][2];
	switch (tecla) {
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
			if (curpos[0][0] < 0) {
				curpos[0][0] = 2;
			} break;
		case right:
			curpos[0][0]++;
			if (curpos[0][0] > 2) {
				curpos[0][0] = 0;
			} break;
	}
}

void Player::verticalSelection(int length){
	extern int curpos[2][2];
	switch (tecla) {
		case up:
			curpos[1][0]--;
			if (curpos[1][0] < 0) {
				curpos[1][0] = length;
			} break;
		case down:
			curpos[1][0]++;
			if (curpos[1][0] > length) {
				curpos[1][0] = 0;
			} break;
	}
}

void Player::selectenemy(int cantene){
	extern int curpos[2][2];
	switch (tecla) {
		case left:
			curpos[1][0]--;
			if (curpos[1][0] < 0) {
				curpos[1][0] = cantene-1;
			} break;
		case right:
			curpos[1][0]++;
			if (curpos[1][0] >= cantene) {
				curpos[1][0] = 0;
			} break;
		case up:
			curpos[1][0]-=4;
			if (curpos[1][0] < 0) {
				curpos[1][0] += 4;
			} break;
		case down:
			curpos[1][0]+=4;
			if (curpos[1][0] >= cantene) {
				curpos[1][0] -= 4;
			} break;
	}
}

void Player::selectplayer(){
	extern int curpos[2][2];
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
			if (curpos[0][0] < 0) {
				curpos[0][0] = 1;
			} break;
		case right:
			curpos[0][0]++;
			if (curpos[0][0] > 1) {
				curpos[0][0] = 0;
			} break;
	}
}

void Player::drawActions(string Pobjetive, Enemy **enemy, int cantene){
	extern char items[8][20];
	string Eobjetive = "Default";
	
	if (action[2] <= cantene && action[2] > 0){
		Eobjetive = enemy[action[2]-1][0].getName();
	}
	
	string stringaux[10];
	
	loadtext(stringaux,"Texto//"+LANG+"//Battle//Actions.txt");
	
	string actionname[7][2] = {
		"",name+" no hace nada",
		"",name+" ataca a "+Eobjetive,
		"",name+" defiende a "+Pobjetive,
		name+" utiliza","[Missing Number ~ Missigno Spell]",
		name+" utiliza "+items[ (action[1]%10) ],"en "+Pobjetive,
		"Hmmm...","Esto no debería mostrarse",
		name+" no puede huir","trabajo en progreso..."
		//"",name+" huye"
	};
	
	actionname[0][1] = name+stringaux[0]; //no hace nada
	actionname[1][1] = name+stringaux[1]+Eobjetive; // ataca a
	actionname[2][1] = name+stringaux[2]+Pobjetive; // defiende a
	actionname[3][0] = name+stringaux[3]; //usa una spell card
	actionname[4][0] = name+stringaux[4]+items[ (action[1]%10) ]; //usa un item
	actionname[4][1] = stringaux[5]+Pobjetive; //en el objetivo
	actionname[6][0] = name+stringaux[8]; //no puede huir
	actionname[6][1] = stringaux[9]; //esta accion sera añadida en la secuela
	//actionname[6][0] = stringaux[12];
	//actionname[6][1] = name+stringaux[13];
	
	if (action[1] > 10){
		actionname[3][1] = spell[ (action[1]%10) ];
	}
	
	for (register int i = 0; i < 2; i++){
		printtext(5,37+i,15,0,actionname[ action[0] ][i]);
	}
	
}

void Player::drawEffects(){
	string stringaux[10];
	
	loadtext(stringaux,"Texto//"+LANG+"//Battle//Effects.txt");
	
	char auxchar[3] = {0,0,0};
	static short auxcur = 0;
	short maxcur = 0;
	
	string effects[10];
	
	for (register int i = 0; i < 4; i++){
		if (potionEffect[i] > 0){
			auxchar[0] = numtochar(potionEffect[i],10);
			auxchar[1] = numtochar(potionEffect[i],1);
			if (potionEffect[i] < 10) {
				auxchar[0] = auxchar[1];
				auxchar[1] = 0;
			}
			effects[maxcur] = stringaux[i]+stringaux[4]+auxchar+stringaux[9];
			maxcur++;
		}
		if (magicEffect[i] > 0){
			auxchar[0] = numtochar(magicEffect[i],10);
			auxchar[1] = numtochar(magicEffect[i],1);
			if (potionEffect[i] < 10) {
				auxchar[0] = auxchar[1];
				auxchar[1] = 0;
			}
			effects[maxcur] = spell[i+1]+": "+auxchar+stringaux[9];
			maxcur++;
		}
	}
	
	switch (tecla){
		case 'w': case 'W':
			auxcur--; if (auxcur < 0) auxcur = 0; break;
		case 's': case 'S':
			auxcur++; if (auxcur+3 > maxcur) auxcur--; break;
		case 0: break;
		case up: case down: case left: case right: case 13: case 27:
			auxcur = 0;
	}
	
	if (maxcur > 3 && auxcur+3 < maxcur) printp(13,7,15,0,'s');
	if (auxcur > 0) printp(13,1,15,0,'w');
	
	for (register int i = 0; i < 3; i++){
		if (auxcur+i >= maxcur) break;
		printtext(5,2+i*2,15,0,effects[auxcur+i]);
	}
}

void Player::drawSpells(int page){
	printtext(6,37,15,0,spell[(page*2)+1]);
	printtext(6,39,15,0,spell[(page*2)+2]);
	
	int aux = mp-spcs[ (opc[1]-1) ];
	
	printtext(11,36,15,0,"/   MP"); printtext(31,36,15,0,"->");
	
	drawMP(9,36,mp); drawMP(12,36,maxmp);
	drawMP(28,36,mp); drawMP(34,36,aux);
	
	
	if (page == 1) {
		printp(21,36,15,0,94); return;
	}
	
	if (unmag > 2) printp(21,40,15,0,118);
}

inline void Player::drawMP(int xmp, int ymp, int _aux){
	char auxtext[3] = {numtochar(_aux,10),numtochar(_aux,1),0};
	if (_aux < 10 && (xmp == 12 || xmp == 34)){
		auxtext[0] = auxtext[1];
		auxtext[1] = 32;
	}
	if (_aux < 10 && (xmp == 9 || xmp == 28)){
		auxtext[0] = 32;
	}
	if (_aux < 0){
		printtext(xmp,ymp,4,0,"0"); return;
	}
	printtext(xmp,ymp,15,0,auxtext);
}

void Player::ejecutarAcciones(Player** player,Enemy** enemy, int cantene, char** actiontext,short& line){
	extern char items[8][20];
	const short RESTAR = -1, SUMAR = 1;
	string auxchar = "";
	char numchar[4] = {0,0,0,0};
	critic = false;
	effatk = 0;
	
	if (hp == 0){
		if (potionEffect[2] == 0){
			line--; return;
		}
		hp = maxhp;
		potionEffect[2] = 0;
		auxchar = name+actiontext[187];
		for (register int i = 0; i < 76; i++){
			actiontext[line][i] = auxchar[i];
		}
		refreshActions(actiontext,line);
		line++; Sleep(300);
		actiontext[line] = new char[1];
		actiontext[line][0] = 0;
		refreshActions(actiontext,line);
		line++;
		actiontext[line] = new char[76];
		actiontext[line][0] = 0;
	}
	
	if (magicEffect[0] > 0) atk +=randnum(6,17);
	
	if (potionEffect[0] > 0) atk +=randnum(6,17);
	if (potionEffect[1] > 0) def +=randnum(6,17);
	//if (potionEffect[69] > 0) luck += randnum(6,7); //aun no existe una poción de suerte xd
	
	int objective = action[2]-1;
	
	/*
	printtext(6,36+id,15,0,name);
	for (int i = 0; i < 3; i++){
		printp(14+i,36+id,15,0,(action[i]%10)+48);
	}
	//*/
	
	effatk = atk+(randnum(6,1)*randnum(3,-1)) + criticChance();
	
	/*
	printtext(20,36+id,15,0,"      ");
	if (critic) printtext(20,36+id,15,0,"critic");
	//*/
	
	switch(action[0]){
		case 0:
			auxchar = name+actiontext[195];
			break;
		case 1:
			if (enemy[objective][0].getHP(0) == 0){
				objective = 0;
				while (enemy[objective][0].getHP(0) == 0){
					objective++;
					if (objective == cantene) {
						line--; return;
					}
				}
			} if (critic) printtext(72,1,15,0,"Critic!");
			auxchar = name+actiontext[196]+enemy[objective][0].getName()+", "+enemy[objective][0].getName();
			ChangeHP(enemy,RESTAR,effatk,objective,actiontext,auxchar);
			enemy[objective][0].drawsprite(1);
			break;
		case 2:
			player[objective][0].def+=10;
			auxchar = name+actiontext[197]+player[objective][0].getName();
			break;
		case 3:
			auxchar = name+actiontext[198]+spell[ (action[1]%10) ];
			mp -= spcs[(action[1]%10)-1];
			switch (action[1]){
				case 23: effatk += randnum(10,25);
				case 22: effatk += randnum(5,22);
				case 21: effatk = effatk - (atk/2) + randnum(4,18);
					for (register int i = 0; i < 76; i++){
						actiontext[line][i] = auxchar[i];
					} refreshActions(actiontext,line);
					line++;
					actiontext[line] = new char[1];
					actiontext[line][0] = 0;
					for (register int i = 0; i < cantene; i++){
						if (enemy[i][0].getHP(0) == 0) continue;
						line++;
						actiontext[line] = new char[76];
						auxchar = enemy[i][0].getName();
						ChangeHP(enemy,RESTAR,effatk,i,actiontext,auxchar);
						enemy[i][0].drawsprite(1);
						
						for (register int j = 0; j < 76; j++){
							actiontext[line][j] = auxchar[j];
						}
						refreshActions(actiontext,line);
						Sleep(100);
						enemy[i][0].drawsprite();
					} auxchar = "";
					line++;
					actiontext[line] = new char[76];
					actiontext[line][0] = 0;
					break;
				case 31: case 32:
					magicEffect[ action[1]-31 ] += 2; break;
				case 41:
					auxchar = auxchar+actiontext[199]+player[objective][0].getName();
					ChangeHP(player,SUMAR,randnum(10,55),objective,actiontext,auxchar);
					break;
				case 53:
					for (register int i = 0; i < 4; i++){
						player[i][0].hp = player[i][0].maxhp;
					} break;
			} break;
		case 4:
			auxchar = name+actiontext[198]+items[ action[1] ]+actiontext[199]+player[objective][0].getName();
			switch(action[1]){
				case 1:
					auxchar = auxchar+", "+player[objective][0].getName();
					ChangeHP(player,SUMAR,randnum(10,35),objective,actiontext,auxchar);
					break;
				case 2:
					numchar[0] = randnum(4,5)+48;
					auxchar = auxchar+", "+player[objective][0].getName()+actiontext[189]+numchar+actiontext[193];
					player[objective][0].mp += (numchar[0]-48);
					if (player[objective][0].mp > player[objective][0].maxmp) {
						player[objective][0].mp = player[objective][0].maxmp;
					}
					break;
				case 3: case 4: case 5: case 6:
					player[objective][0].potionEffect[ action[1]-3 ] += 3;
					numchar[0] = numtochar(player[objective][0].potionEffect[ action[1]-3 ],10);
					numchar[1] = numtochar(player[objective][0].potionEffect[ action[1]-3 ],1);
					if (player[objective][0].potionEffect[ action[1]-3 ] < 10) {
						numchar[0] = numchar[1];
						numchar[1] = 0;
					}
					auxchar = auxchar+"."+actiontext[194]+numchar;
			} break;
		case 6:
			auxchar = name+actiontext[195];
			break;
	}
	
	for (register int i = 0; i < 76; i++){
		actiontext[line][i] = auxchar[i];
	}
	refreshActions(actiontext,line);
	line++;
	if (action[0] == 1 && objective >= 0) enemy[objective][0].drawsprite();
}

inline void Player::setSpeed(){
	if (potionEffect[3] > 0){
		effspd = spd+randnum(2,3);
	}
}

#endif
