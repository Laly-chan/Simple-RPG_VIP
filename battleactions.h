#ifndef BATTLEACTIONS_H
#define BATTLEACTIONS_H

#include "player.h"
#include "subenemy.h"

template <typename Obj> inline void ChangeHP(Obj** object,short changeSign, int lives, int objective, char** actiontext, string &auxstring){
	lives *= changeSign;
	
	short effdef = ((changeSign-1)*-1)/2; //a changesign se le resta 1, si el resultado es 0 entonces saldrá 0, si el resultado es -2 entonces lo hace positivo y lo devuelve a 1
	
	int defense = object[objective][0].def * effdef; //lo que hace es guardar la defensa si se restan vidas, sino defense es 0
	
	lives += defense/4;
	
	char auxchar[] = {numtochar(lives*changeSign,100),numtochar(lives*changeSign,10),numtochar(lives*changeSign,1),0};
	
	if ((lives*changeSign) < 100) {
		auxchar[0] = auxchar[1];
		auxchar[1] = auxchar[2];
		auxchar[2] = 0;
	}
	
	if ((lives*changeSign) < 10) {
		auxchar[0] = auxchar[1];
		auxchar[1] = 0;
	}
	
	auxstring = auxstring+actiontext[ 191-(effdef*2) ]+auxchar+actiontext[ 192-(effdef*2) ]+".";
	
	object[objective][0].hp += lives;
	
	if (object[objective][0].hp > object[objective][0].maxhp){
		object[objective][0].hp = object[objective][0].maxhp; //básicamente comprueba si la vida supera el máximo
	}
	if (object[objective][0].hp < 0){
		object[objective][0].hp = 0;
	}
}

#endif
