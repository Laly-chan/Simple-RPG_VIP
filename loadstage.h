#ifndef LOADSTAGE_H
#define LOADSTAGE_H

void loadmap(int mapa[][104],std::string);
void llenarmapa(int mapa[][104]);

char mapachar[104][100];

void llenarmapa(int mapa[100][104]){
	for ( register int i = 0; i < 100; i++){
		for (register int j = 0; j < 104; j++){
			switch(mapachar[j][i]){
				case 'n':
					mapa[i][j] = 1; break;
				case 'T':
					mapa[i][j] = 101; break;
				case 'D':
					mapa[i][j] = 102; break;
				case 'p':
					mapa[i][j] = 2; break;
				case '.':
					mapa[i][j] = 0; break;
				case 'e':
					mapa[i][j] = 3; break;
				case 'E':
					mapa[i][j] = 4; break;
				default:
					mapa[i][j] = mapachar[j][i] - 48; break;
			}
		}
	}
}

void loadmap(int mapa[100][104], std::string nivel, int slot){
	std::ifstream archivo;
	char aux[] = {'S','l','o','t',slot+48,0};
	std::string aux2 = aux;
	std::string path = "Mapas//"+aux2+"//"+nivel+".lvl";
	
	archivo.open(path.c_str(), std::ios::in);
	
	if (archivo.fail()){
		archivo.close();
		path = "Mapas//Default//"+nivel+".lvl";
		archivo.open(path.c_str(), std::ios::in);
		if (archivo.fail()){
			printp(0,0,15,0); std::cout<<"esto necesita un failsafe";
			getch();
			return;
		}
	}
	
	archivo.getline(mapachar[false],10401);
	
	archivo.close();
	llenarmapa(mapa);
}

#endif
