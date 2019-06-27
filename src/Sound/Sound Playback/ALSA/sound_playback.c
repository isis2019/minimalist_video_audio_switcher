
/* 	Ce programme permet de lire un fichier son en se basant sur ALSA API, depuis une carte son qu'on définit dans PCM_DEVICE ci dessous.
	Pour compiler le programme : gcc -o lire sound_playback.c -lasound   
	Pour lancer la lecture./lire  44100 2 5   < Roland.wav  (lecture pendant du fichier WAV stéréo Roland.wav qui est fournit avec les fichiers, en 44100Hz pendant 5 secondes) 
*/


#include <alsa/asoundlib.h>
#include <stdio.h>

// Définir la carte son chargé de la lecture, on choisit de mettre "default" ou 0 (carte de l'ordinatreur) ou 1(Digi003+) ou carte par défaut qu'on a mis par défaut grâce à la commande
// pacmd "set-default-sink alsa_output.firewire-0x00a07e0000ab0000.multichannel-output"
// Nous avons aussi utilisé "003Rack" // Digi00x 003Rack PCM // alsa_output.firewire-0x00a07e0000ab0000.multichannel-output.monitor

#define PCM_DEVICE "default"

int main(int argc, char **argv) {
	
	
	unsigned int pcm, tmp, dir;
	int rate, channels, seconds;
	snd_pcm_t *pcm_handle;
	snd_pcm_hw_params_t *params;
	snd_pcm_uframes_t frames;
	char *buff;
	int buff_size, loops;
	

	if (argc < 4) {
		printf("Usage: %s <sample_rate> <channels> <seconds>\n",
								argv[0]);
		return -1;
	}

	rate 	 = atoi(argv[1]);
	channels = atoi(argv[2]);
	seconds  = atoi(argv[3]);

	/* Utiliser le PCM (carte son) en mode playback ou lecture */
	if (pcm = snd_pcm_open(&pcm_handle, PCM_DEVICE,
					SND_PCM_STREAM_PLAYBACK, 0) < 0) 
		printf("ERROR: Can't open \"%s\" PCM device. %s\n",
					PCM_DEVICE, snd_strerror(pcm));

	// Allouer les paramètres par défaut 
	snd_pcm_hw_params_alloca(&params);
	//Utiliser des paramètres pour la configuration de la carte 
	snd_pcm_hw_params_any(pcm_handle, params);

	/* Définir les paramètres de mode entrelacé, nombre de bits de codage, fréquence d'échantillonage, nombre de cannaux de lecture */
	if (pcm = snd_pcm_hw_params_set_access(pcm_handle, params,
					SND_PCM_ACCESS_RW_INTERLEAVED) < 0) 
		printf("ERROR: Can't set interleaved mode. %s\n", snd_strerror(pcm));

	if (pcm = snd_pcm_hw_params_set_format(pcm_handle, params,
						SND_PCM_FORMAT_S16_LE) < 0) 
		printf("ERROR: Can't set format. %s\n", snd_strerror(pcm));

	if (pcm = snd_pcm_hw_params_set_channels(pcm_handle, params, channels) < 0) 
		printf("ERROR: Can't set channels number. %s\n", snd_strerror(pcm));

	if (pcm = snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0) < 0) 
		printf("ERROR: Can't set rate. %s\n", snd_strerror(pcm));

	/* Ecriture des paramèters */
	if (pcm = snd_pcm_hw_params(pcm_handle, params) < 0)
		printf("ERROR: Can't set harware parameters. %s\n", snd_strerror(pcm));

	/* Afficher à l'utilisateur les caractéristiques de mode de lecture et de carte son cité ci-dessus */
	printf("PCM name: '%s'\n", snd_pcm_name(pcm_handle));

	printf("PCM state: %s\n", snd_pcm_state_name(snd_pcm_state(pcm_handle)));

	snd_pcm_hw_params_get_channels(params, &tmp);
	printf("channels: %i ", tmp);

	if (tmp == 1)
		printf("(mono)\n");
	else if (tmp == 2)
		printf("(stereo)\n");

	snd_pcm_hw_params_get_rate(params, &tmp, 0);
	printf("rate: %d bps\n", tmp);

	printf("seconds: %d\n", seconds);	

	// Choix de la taille du buffer convenable pour une période 
	snd_pcm_hw_params_get_period_size(params, &frames, 0);

	buff_size = frames * channels * 2; // 2 -> Taille de l'échantillon 
	buff = (char *) malloc(buff_size);

	snd_pcm_hw_params_get_period_time(params, &tmp, NULL);

	for (loops = (seconds * 1000000) / tmp; loops > 0; loops--) {

		if (pcm = read(0, buff, buff_size) == 0) {
			printf("Early end of file.\n");
			return 0;
		}

		if (pcm = snd_pcm_writei(pcm_handle, buff, frames) == -EPIPE) {
			printf("XRUN.\n");
			snd_pcm_prepare(pcm_handle);
		} else if (pcm < 0) {
			printf("ERROR. Can't write to PCM device. %s\n", snd_strerror(pcm));
		}

	}
	//Arrêter la lecture
	snd_pcm_drain(pcm_handle);
	snd_pcm_close(pcm_handle);
	free(buff);

	return 0;
}
