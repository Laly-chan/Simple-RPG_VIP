#ifndef LOADTEXT_H
#define LOADTEXT_H

inline void loadtext(string*, string);

inline void loadtext(string *text, string path){
	std::ifstream archivo;
	
	char auxtext[76][69];
	
	archivo.open(path.c_str(), std::ios::in);
	
	if (archivo.fail()){
		text[0] = "Missingno 404 ~ Text not Found";
		return;
	}
	
	archivo.getline(auxtext[false],5245);
	
	for (register int i = 0; i < 69; i++){
		if (auxtext[i][0] == '1') break; //sale del bucle cuando detecta 1, es el final del archivo
		
		for (register int j = 0; j < 76; j++){
			
			if (auxtext[i][j] == 64) {
				auxtext[i][j] = 0;
				break;
			} //sale del bucle cuando detecta 0, es el final de la línea
			
		}
			text[i] = auxtext[i];
	}
	
	archivo.close();
}

#endif
