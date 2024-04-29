#ifndef MAPENEMY_H
#define MAPENEMY_H

class MapEnemy {
	friend class Enemy;
	private:
		int type;
		int xmap, ymap, dir;
		bool dead;
	public:
		int xorg, yorg; //original position
		MapEnemy();
		~MapEnemy(){}
		void mover(int zona[][26], int zonaobj[][25], bool*);
		void setpos(int,int,int,int);
		inline void kill(){ dead = true;}
		int gettype(){ return type;}
		int getxpos(){ return xmap;}
		int getypos(){ return ymap;}
};

MapEnemy::MapEnemy(){
	dir = 0;
	xmap = 0;
	ymap = 0;
	type = 0;
}

void MapEnemy::setpos(int _x, int _y, int _dir, int _type){
	dir = _dir;
	xorg = _x;
	yorg = _y;
	xmap = _x;
	ymap = _y;
	type = _type;
	dead = false;
}

void MapEnemy::mover(int zona[25][26], int zonaobj[25][25], bool *enterbattle){
	if (*enterbattle) return;
	if (dead) return;
	switch (dir){
		case 2:
			if (zona[xmap][ymap-1] < 100 && ymap>0){
				if (zonaobj[xmap][ymap] <= -10){
					zona[xmap][ymap] *= -1;
					zonaobj[xmap][ymap] = 0;
				}
				ymap--;
				break;
			} dir++; break;
		case 0:
			if (zona[xmap][ymap+1] < 100 && ymap<24){
				if (zonaobj[xmap][ymap] <= -10){
					zona[xmap][ymap] *= -1;
					zonaobj[xmap][ymap] = 0;
				}
				ymap++;
				break;
			} dir++; break;
		case 1:
			if (zona[xmap-1][ymap] < 100 && xmap>0){
				if (zonaobj[xmap][ymap] <= -10){
					zona[xmap][ymap] *= -1;
					zonaobj[xmap][ymap] = 0;
				}
				xmap--;
				break;
			} dir++; break;
		case 3:
			if (zona[xmap+1][ymap] < 100 && xmap<24){
				if (zonaobj[xmap][ymap] <= -10){
					zona[xmap][ymap] *= -1;
					zonaobj[xmap][ymap] = 0;
				}
				xmap++;
				
				break;
			} dir = 0; break;
	}
	if (zonaobj[xmap][ymap] == -2 || zonaobj[xmap][ymap] == 2) *enterbattle = true;
	zonaobj[xmap][ymap] = (type%10)+10;
	if (type == 99) zonaobj[xmap][ymap] = 21;
}

#endif
