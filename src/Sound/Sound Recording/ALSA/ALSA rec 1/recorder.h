#ifndef __RECORDER_H__
#define __RECORDER_H__

#define ALSA_PCM_NEW_HW_PARAMS_API

#include <alsa/asoundlib.h>
#include <complex>
#include <memory.h>

using namespace std;

#define DSIZE	16			//Longeur des données
#define CH		2			//Nombre de cannaux
#define FS		44100		//Fréquence d'échantillonage
#define FRAME	32			// la taille du buffer en frame pour une période = FRAME * CH * (DSIZE/8)
#define HW		"default"	// "id"  L'identifiant de la carte qu'on veut utiliser

/* Cette fonction va allouer la mémoire pour pbuf*/
int record(int time_ms, char** pbuf);
complex<double>* extract(uint16_t* pbuf, int len_16);
#endif
