#ifndef SUBENEMY_H
#define SUBENEMY_H

#include "drawbattleui.h"
#include "enemy.h"
#include "shortfunc.h"
#include "battleactions.h"

class Boss : public Enemy{
	private:
		int type;
	public:
		Boss(){}
		~Boss(){}
		virtual void DeltaAttack(Player**,Enemy**,char**,short&,string&,unsigned short,short,unsigned short, int);
		virtual void setstats();
		//virtual void loadsprite();
		virtual inline void loadDesc(string*);
};

void Boss::DeltaAttack(Player** player,Enemy** enemy,char** actiontext,short& line,string &auxchar, unsigned short randact, short effatk, unsigned short obj1, int id){
}

void Boss::setstats(){
}

//void Boss::loadsprite(){}

inline void Boss::loadDesc(string* stringaux){
}

class ElectricWizard : public Enemy{
	public:
		ElectricWizard(){}
		~ElectricWizard(){}
		virtual void DeltaAttack(Player**,Enemy**,char**,short&,string&,unsigned short,short,unsigned short, int);
		virtual void setstats();
		virtual void loadsprite();
		virtual inline void loadDesc(string*);
};

void ElectricWizard::DeltaAttack(Player** player,Enemy** enemy,char** actiontext,short& line,string &auxchar, unsigned short randact, short effatk, unsigned short obj1, int id){
	const short RESTAR = -1, SUMAR = 1;
	switch(randact){
		case 0: case 1: case 17: case 12: case 8:
			if (critic) printtext(72,1,15,0,"Critic!");
			auxchar = name+actiontext[196]+player[obj1][0].getName()+", "+player[obj1][0].getName();
			ChangeHP(player,RESTAR,effatk,obj1,actiontext,auxchar); break;
			
		case 5: case 6: case 7: case 15: case 9:
			auxchar = name+actiontext[198]+"[Seiga's Necromancy ~Electric Corpse~]";
			auxchar = auxchar+". Action unfinished..."; break;
			
		case 10: case 11: case 4: case 13:
			auxchar = name+actiontext[198]+"[Raiko's Electric Drum ~DenDen Daiko~]";
			AllAttack(player,enemy,actiontext,line,auxchar,effatk+10); break;
			
		case 14: case 2: case 16: case 3:
			if (critic) printtext(72,1,15,0,"Critic!");
			auxchar = name+actiontext[198]+"[Gungeon's Electric Gun ~Shock Rifle~]"+actiontext[199]+player[obj1][0].getName();
			
			for (register int i = 0; i < 76; i++){
				actiontext[line][i] = auxchar[i];
			}
			refreshActions(actiontext,line);
			
			line++;
			actiontext[line] = new char[76];
			
			auxchar = player[obj1][0].getName();
			ChangeHP(player,RESTAR,effatk+43,obj1,actiontext,auxchar); break;
			
		case 18: case 19:
			auxchar = name+actiontext[198]+"[DDC Skies ~Thunderclouds of Magical Power~]";
			AllAttack(player,enemy,actiontext,line,auxchar,effatk+40); break;
	}
}

void ElectricWizard::loadsprite(){
	for (int i = 0; i < 4; i++){
		loadenemysprite("EWizard",sprite,i);
	}
	frame = 0;
	maxframe = 2;
}

void ElectricWizard::setstats(){
	name = "E-Wizard";
	maxhp = 300;
	hp = maxhp;
	atk = randnum(6,27);
	def = randnum(6,17);
	spd = randnum(7,7);
	luck = randnum(4,4);
}

inline void ElectricWizard::loadDesc(string *stringaux){
	loadtext(stringaux,"Texto//"+LANG+"//Battle//EnemyDesc//testenemy.txt");
}

class Golem : public Enemy{
	public:
		Golem(){}
		~Golem(){}
		virtual void DeltaAttack(Player**,Enemy**,char**,short&,string&,unsigned short,short,unsigned short, int);
		virtual void setstats();
		virtual void loadsprite();
		virtual inline void loadDesc(string*);
};

void Golem::DeltaAttack(Player** player,Enemy** enemy,char** actiontext,short& line,string &auxchar, unsigned short randact, short effatk, unsigned short obj1, int id){
	const short RESTAR = -1, SUMAR = 1;
	
	switch(randact){
		case 0: case 1: case 17: case 12: case 8: case 10: case 11:
			if (critic) printtext(72,1,15,0,"Critic!");
			auxchar = name+actiontext[196]+player[obj1][0].getName()+", "+player[obj1][0].getName();
			ChangeHP(player,RESTAR,effatk,obj1,actiontext,auxchar); break;
			
		case 5: case 6: case 7: case 15: case 9: case 4:
			auxchar = name+actiontext[198]+"[Yomad's Gathering of the Earth]";
			for (register int i = 0; i < 76; i++){
				actiontext[line][i] = auxchar[i];
			} refreshActions(actiontext,line);
			line++;
			actiontext[line] = new char[76];
			auxchar = name;
			ChangeHP(enemy,SUMAR,effatk+43,id,actiontext,auxchar); break;
			
		case 13: case 14: case 2: case 16: case 3:
			if (critic) printtext(72,1,15,0,"Critic!");
			
			auxchar = name+actiontext[198]+"[Himemushi's Piercing Stalagmite]"+actiontext[199]+player[obj1][0].getName();
			
			for (register int i = 0; i < 76; i++){
				actiontext[line][i] = auxchar[i];
			}
			refreshActions(actiontext,line);
			
			line++;
			actiontext[line] = new char[76];
			
			auxchar = player[obj1][0].getName();
			ChangeHP(player,RESTAR,effatk+43,obj1,actiontext,auxchar); break;
			
		case 18: case 19:
			auxchar = name+actiontext[198]+"[Uranus' World Shaking]";
			AllAttack(player,enemy,actiontext,line,auxchar,effatk+15); break;
	}
}

void Golem::loadsprite(){
	for (int i = 0; i < 4; i++){
		loadenemysprite("Golem",sprite,i);
	}
	frame = 0;
	maxframe = 2;
}

void Golem::setstats(){
	name = "Li'l Golem";
	maxhp = 500;
	hp = maxhp;
	atk = randnum(6,47);
	def = randnum(6,27);
	spd = randnum(5,5);
	luck = randnum(4,1);
}

inline void Golem::loadDesc(string *stringaux){
	loadtext(stringaux,"Texto//"+LANG+"//Battle//EnemyDesc//testenemy2.txt");
}

class Slime : public Enemy {
	public:
		Slime(){}
		~Slime(){}
		virtual void DeltaAttack(Player**,Enemy**,char**,short&,string&,unsigned short,short,unsigned short, int);
		virtual void setstats();
		virtual void loadsprite();
		virtual inline void loadDesc(string*);
		virtual inline void isdead();
};

void Slime::DeltaAttack(Player** player,Enemy** enemy,char** actiontext,short& line,string &auxchar, unsigned short randact, short effatk, unsigned short obj1, int id){
	const short RESTAR = -1, SUMAR = 1;
	//extern int maxenemy;
	randact = 0;
	switch(randact){
		case 0: case 1: case 17: case 12: case 8: case 10: case 11: case 18: case 19: case 13: case 14:
			if (critic) printtext(72,1,15,0,"Critic!");
			auxchar = name+actiontext[196]+player[obj1][0].getName()+", "+player[obj1][0].getName();
			ChangeHP(player,RESTAR,effatk,obj1,actiontext,auxchar); break;
			
		case 5: case 6: case 7: case 15: case 9: case 4: case 2: case 16: case 3:
			auxchar = name+actiontext[198]+"[Flandre's Half Spell ~Two of a Kind~]";
			for (register int i = 0; i < 76; i++){
				actiontext[line][i] = auxchar[i];
			} refreshActions(actiontext,line);
			line++;
			actiontext[line] = new char[76];
			//if (maxenemy == 8) break;
			//enemy[maxenemy] = new Slime;
	}
}

void Slime::loadsprite(){
	for (int i = 0; i < 4; i++){
		loadenemysprite("Slime",sprite,i);
	}
	frame = 0;
	maxframe = 2;
}

void Slime::setstats(){
	name = "Slime";
	maxhp = 150;
	hp = maxhp;
	atk = randnum(6,27);
	def = randnum(6,27);
	spd = randnum(5,5);
	luck = randnum(4,1);
}

inline void Slime::loadDesc(string *stringaux){
	loadtext(stringaux,"Texto//"+LANG+"//Battle//EnemyDesc//testenemy2.txt");
}

inline void Slime::isdead(){
	if (dead == 2) return;
	if (dead == 1){
		dead++; return;
	}
	if (hp == 0) dead++;
}

/*class TestEnemy : public Enemy{
	public:
		TestEnemy(){}
		~TestEnemy(){}
		virtual void DeltaAttack(Player**,Enemy**,char**,short&,string&,unsigned short,short,unsigned short, int);
		virtual void setstats();
		virtual void loadsprite();
		virtual inline void loadDesc(string*);
};

void TestEnemy::DeltaAttack(Player** player,Enemy** enemy,char** actiontext,short& line,string &auxchar, unsigned short randact, short effatk, unsigned short obj1, int id){
	const short RESTAR = -1, SUMAR = 1;
	
	int aux = randnum(4,0);
	if (critic) printtext(72,1,15,0,"Critic!");
	auxchar = name+actiontext[196]+player[aux][0].getName()+", "+player[aux][0].getName();
	
	ChangeHP(player,RESTAR,effatk,aux,actiontext,auxchar);
}

void TestEnemy::loadsprite(){
	for (int i = 0; i < 4; i++){
		loadenemysprite("TestEnemy",sprite,i);
	}
	frame = 0;
	maxframe = 2;
}

void TestEnemy::setstats(){
	name = "Mushgoom";
	maxhp = 200;
	hp = maxhp;
	atk = randnum(6,27);
	def = randnum(6,17);
	spd = randnum(7,7);
	luck = randnum(4,2);
}

inline void TestEnemy::loadDesc(string *stringaux){
	loadtext(stringaux,"Texto//"+LANG+"//Battle//EnemyDesc//testenemy.txt");
}

class TestEnemy2 : public Enemy{
	public:
		TestEnemy2(){}
		~TestEnemy2(){}
		virtual void DeltaAttack(Player**,Enemy**,char**,short&,string&,unsigned short,short,unsigned short, int);
		virtual void setstats();
		virtual void loadsprite();
		virtual inline void loadDesc(string*);
};

void TestEnemy2::DeltaAttack(Player** player,Enemy** enemy,char** actiontext,short& line,string &auxchar, unsigned short randact, short effatk, unsigned short obj1, int id){
	const short RESTAR = -1, SUMAR = 1;
	
	int aux = randnum(4,0);
	if (critic) printtext(72,1,15,0,"Critic!");
	auxchar = name+actiontext[196]+player[aux][0].getName()+", "+player[aux][0].getName();
	
	ChangeHP(player,RESTAR,effatk,aux,actiontext,auxchar);
}

void TestEnemy2::loadsprite(){
	for (int i = 0; i < 6; i++){
		loadenemysprite("TestEnemy2",sprite,i);
	}
	frame = 0;
	maxframe = 4;
}

void TestEnemy2::setstats(){
	name = "Mad Plumber";
	maxhp = 400;
	hp = maxhp;
	atk = randnum(6,32);
	def = randnum(6,27);
	spd = randnum(7,13);
	luck = 0;
}

inline void TestEnemy2::loadDesc(string *stringaux){
	loadtext(stringaux,"Texto//"+LANG+"//Battle//EnemyDesc//testenemy2.txt");
}*/

void Enemy::setSpritePos(){
	xpos = 2, ypos = 6;
	
	while (foreground[xpos][ypos] == -1){
		xpos+=20;
		if (xpos > 80){
			xpos = 2;
			ypos += 9;
		}
		if (ypos > 26) break;
	}
	drawsprite();
}

inline void Enemy::drawsprite(short actframe){
	short auxsprite = frame;
	
	if (actframe > 0){
		auxsprite = maxframe+actframe; // 1 = recibir daño
	}
	
	for (register int i = 0; i < 16; i++){
		for (register int j = 0; j < 8; j++){
			foreground[i+xpos][j+ypos] = sprite[auxsprite][i][j];
		}
	}
	refreshimage(xpos,xpos+16,ypos,ypos+8);
	drawimage(xpos,xpos+16,ypos,ypos+8);
}

void Enemy::drawDescription(){
	char *desctext[5];
	string stringaux[5];
	char auxchar[] = {0,0,0};
	
	this->loadDesc(stringaux);
	
	auxchar[0] = numtochar(atk,10);
	auxchar[1] = numtochar(atk,1);
	
	if (atk < 10) {
		auxchar[0] = auxchar[1];
		auxchar[1] = 32;
	}
	
	stringaux[0] = "ATK: ";
	stringaux[0] = stringaux[0]+auxchar+"                   ";
	
	auxchar[0] = numtochar(def,10);
	auxchar[1] = numtochar(def,1);
	
	if (def < 10) {
		auxchar[0] = auxchar[1];
		auxchar[1] = 32;
	}
	
	stringaux[0] = stringaux[0]+"DEF: "+auxchar+"                   ";
	
	auxchar[0] = numtochar(spd,10);
	auxchar[1] = numtochar(spd,1);
	
	if (spd < 10) {
		auxchar[0] = auxchar[1];
		auxchar[1] = 32;
	}
	
	stringaux[0] = stringaux[0]+"SPD: "+auxchar;
	
	for (register int i = 0; i < 5; i++){
		desctext[i] = new char[76];
		for (register int j = 0; j < 76; j++){
			if (stringaux[i][j] == 0) {
				desctext[i][j] = 0;
				break;
			}
			desctext[i][j] = stringaux[i][j];
		}
		printtext(3,36+i,15,0,"                                       ");
	}
	
	drawDialogue(desctext);
	
	if (LANG == "ENG") printtext(8,38,15,0,"Press enter to continue...");
	
	if (LANG == "ESP") printtext(7,38,15,0,"Presiona enter para continuar");
	
	while (tecla != 13){
		press();
	}
}

void Enemy::AllAttack(Player** player,Enemy** enemy,char** actiontext,short& line,string &auxchar,int effatk){
	for (register int i = 0; i < 76; i++){
		actiontext[line][i] = auxchar[i];
	} refreshActions(actiontext,line);
	line++;
	actiontext[line] = new char[1];
	actiontext[line][0] = 0;
	for (register int i = 0; i < 4; i++){
		if (player[i][0].getHP() == 0) continue;
		line++;
		actiontext[line] = new char[76];
		auxchar = player[i][0].getName();
		ChangeHP(player,-1,effatk,i,actiontext,auxchar);
		for (register int j = 0; j < 76; j++){
			actiontext[line][j] = auxchar[j];
		}
		refreshActions(actiontext,line);
		Sleep(100);
	}auxchar = "";
	line++;
	actiontext[line] = new char[76];
	actiontext[line][0] = 0;
}

void Enemy::atacar(Player** player,Enemy** enemy,char** actiontext,short& line, int id){
	string auxchar = "";
	isdead();
	if (hp == 0 && dead != 1) return;
	critic = false;
	
	unsigned short randact = randnum(20,0);
	
	short effatk = atk+(randnum(6,1)*randnum(3,-1)) + criticChance();
	
	unsigned short obj1 = randnum(4,0);
	
	if (player[obj1][0].getHP() == 0){
		for (int i = 0; i < 5; i++){
			obj1 = i;
			if (player[i][0].getHP() > 0) break;
			if (i == 4) return;
		}
	}
	
	DeltaAttack(player,enemy,actiontext,line,auxchar,randact,effatk,obj1,id);
	
	for (register int i = 0; i < 76; i++){
		actiontext[line][i] = auxchar[i];
	}
	refreshActions(actiontext,line);
	line++;
}

#endif
