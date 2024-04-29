#ifndef ENEMY_H
#define ENEMY_H

#include "mapenemy.h"

class Enemy{
	template <typename Obj>
	friend void ChangeHP(Obj**,short,int,int,char**,string&);
	protected:
		int maxhp, hp;
		int spd, atk, def;
		int luck;
		bool critic;
		unsigned short dead;
		
		short sprite[7][16][8];
		short xpos, ypos;
		
		static int bosshp[12];
		string name;
		inline int criticChance();
		short frame, maxframe;
	public:
		Enemy(){}
		~Enemy(){}
		virtual void DeltaAttack(Player**,Enemy**,char**,short&,string&,unsigned short,short,unsigned short, int){}
		void atacar(Player**,Enemy**,char**,short&, int);
		void AllAttack(Player**,Enemy**,char**,short&,string&,int);
		
		virtual void setstats(){}
		
		virtual void loadsprite(){}
		void setSpritePos();
		inline void drawsprite(short actframe = 0);
		
		void drawDescription();
		virtual inline void loadDesc(string*){}
		
		virtual inline void isdead(){}
		
		inline void changeFrame();
		string getName(){ return name;}
		int getHP(int aux = 0);
		int getSpeed() { return spd;}
};

int Enemy::bosshp[12] = {500,1,11,12,2,3,4,5,6,7,8,9};

int Enemy::getHP(int aux){
	if (aux == 0){
		return hp;
	} return maxhp;
}

inline void Enemy::changeFrame(){
	if (hp == 0) {
		frame = maxframe; 
		drawsprite();
		return;
	}
	if (randnum(5,0) == 2) return;
	frame++;
	if (frame == maxframe) frame = 0;
	drawsprite();
}

inline int Enemy::criticChance(){
	int crit = (randnum(69420,1)%100);
	if (crit < (1+luck)){
		critic = true;
		return randnum(6,17);
	} return 0;
}

#endif
