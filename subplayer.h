#ifndef SUBPLAYER_H
#define SUBPLAYER_H

#include "player.h"

/*Spell objetives:
+10 1 enemigo
+20 todos enemigos
+30 es un hechizo que dura algunos turnos
+40 1 jugador
+50 todos jugadores
*/

class PlayerHero : public Player{
	public:
		PlayerHero(){}
		~PlayerHero(){}
		virtual void setSpellObjetive(int&);
};

void PlayerHero::setSpellObjetive(int &lay){
	Player::opc[1] += 30;
	lay = 4;
}

class PlayerStrong : public Player{
	public:
		PlayerStrong(){}
		~PlayerStrong(){}
		virtual void setSpellObjetive(int&);
};

void PlayerStrong::setSpellObjetive(int &lay){
	Player::opc[1] += 20;
}

class PlayerWizard : public Player{
	public:
		PlayerWizard(){}
		~PlayerWizard(){}
		virtual void setSpellObjetive(int&);
};

void PlayerWizard::setSpellObjetive(int &lay){
	Player::opc[1] += 20;
}

class PlayerSupport : public Player{
	public:
		PlayerSupport(){}
		~PlayerSupport(){}
		virtual void setSpellObjetive(int&);
};

void PlayerSupport::setSpellObjetive(int &lay){
	switch (opc[1]) {
		case 1:
			Player::opc[1] += 40; break;
		case 2:
			Player::opc[1] += 30;
			lay = 4; break;
		case 3:
			Player::opc[1] += 50;
	}
}

#endif
