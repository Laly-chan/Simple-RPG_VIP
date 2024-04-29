#ifndef LOADBATTLEUI_H
#define LOADBATTLEUI_H

void loadimage(int);
void transform();
void transformbg(int);

void loadsprite(string, short sprite[][16][8],short);

extern short uimap[84][42];
char uimapchar[42][84];

void loadimage(int bgzone){
	std::ifstream archivo;
	string path = "Imagenes//UI//Battle.ui";
	
	archivo.open(path.c_str(), std::ios::in);
	
	if (archivo.fail()){
		printp(0,0,15,0); std::cout<<"esto necesita un failsafe";
		getch();
		return;
	}
	
	archivo.getline(uimapchar[false],3529);
	
	archivo.close();
	transform();
	
	char aux[] = {'Z','o','n','e',bgzone+48};
	string zone = aux;
	path = "Imagenes//BGBattle//"+zone+".bg";
	
	archivo.open(path.c_str(), std::ios::in);
	
	if (archivo.fail()){
		printp(0,0,15,0); std::cout<<"esto necesita un failsafe";
		getch();
		return;
	}
	
	archivo.getline(uimapchar[false],3529);
	
	archivo.close();
	transformbg(bgzone);
}

void transform(){
	for (register int i = 0; i < 84; i++){
		for (register int j = 0; j < 42; j++){
			switch (uimapchar[j][i]){
				case 'q': uimap[i][j] = 201; break;
				case 'z': uimap[i][j] = 200; break;
				case 'e': uimap[i][j] = 187; break;
				case 'c': uimap[i][j] = 188; break;
				case 'w': uimap[i][j] = 205; break;
				case 'a': uimap[i][j] = 186; break;
				case '|': uimap[i][j] = 2; break;
				default: uimap[i][j] = 0;
			}
		}
	}
}

void transformbg(int palette){
	extern short background[80][26];
	switch (palette){
		case 1:
			for (register int i = 2; i < 82; i++){
				for (register int j = 9; j < 35; j++){
					background[i-2][j-9] = uimapchar[j][i]-32;
				}
			}	
	}
}

void loadsprite(string _path, short sprite[][16][8], short frame){
	std::ifstream archivo;
	string path = "Imagenes//"+_path;
	char _sprite[49][16];
	
	archivo.open(path.c_str(), std::ios::in);
	
	if (archivo.fail()){
		printp(0,0,15,0); std::cout<<"esto necesita un failsafe";
		getch();
		return;
	}
	
	archivo.getline(_sprite[false],769);
	
	archivo.close();
	
	for (register int i = 0; i < 16; i++){
		for (register int j = 0; j < 8; j++){
			sprite[frame][i][j] = _sprite[ j+(frame*8) ][i]-32;
		}
	}
}

#endif
