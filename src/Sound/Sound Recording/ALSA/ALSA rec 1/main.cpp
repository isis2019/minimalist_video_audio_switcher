
/* Ce prgramme permet d'enregistrer le son en utilisant l'API ALSA pendant 5 secondes, depuis une carte sn qu'on peut définir dans le fichier "recorder.h" 
/   Pour compiler le programme g++ -o rec main.cpp recorder.h recorder.cpp includes.h -lasound
/  ./rec >nom.wav 
/   Pour enregistrer en ligne de commande: "arecord -f S32_LE -r 44100 --device="default" testt.wav ou "arecord -f cd -D default essai.wav"
*/

#include "includes.h"

int main() {
	char* _pbuf = NULL;	
	int len = record(5000, &_pbuf);
	printf("_pbuf address: %lxH\n", (long unsigned int)_pbuf);
#if DEBUG
	if(len >= 0){
		for(int i = 0; i < len; i += 2){
			printf("%d\t", (int16_t)(_pbuf[i]));
			if(i % (2*5) == 0) printf("\n");
		}
		printf("\n");
	}
#endif
	complex<double>* x1 = NULL;
	x1 = extract((uint16_t*)_pbuf, len / 2);
	free((void*)_pbuf);
	return 0;
}
