/*	Ce programme permet de lire un fichier son en se basant sur PulseAudio API, depuis une carte son qu'on définit dans les paramètres de la fonction "pa_simple_new" ci dessous.
	Pour compiler le programme : "gcc -o lire pulse_playback.c -lpulse -lpulse-simple" 
    Pour lancer la lecture: "./lire  <Roland.wav"  (lecture pendant du fichier WAV  Roland.wav qui est fournit avec les fichiers )
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#define BUFSIZE 1024

 #define PA_CHANNEL_POSITION_INVALID PA_CHANNEL_POSITION_INVALID
 #define PA_CHANNEL_POSITION_MONO PA_CHANNEL_POSITION_MONO
 #define PA_CHANNEL_POSITION_LEFT PA_CHANNEL_POSITION_LEFT
 #define PA_CHANNEL_POSITION_RIGHT PA_CHANNEL_POSITION_RIGHT
 #define PA_CHANNEL_POSITION_CENTER PA_CHANNEL_POSITION_CENTER
 #define PA_CHANNEL_POSITION_FRONT_LEFT PA_CHANNEL_POSITION_FRONT_LEFT
 #define PA_CHANNEL_POSITION_FRONT_RIGHT PA_CHANNEL_POSITION_FRONT_RIGHT



int main(int argc, char*argv[]) {
    /* Le format de codage, de fréquence d'échantillonnage, et nombre de cannaux utilisés  */
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 2
    };
    pa_simple *s = NULL;
    int ret = 1;
    int error;
    /* On peut remplacer STDIN par le fichier spécifique si besoin*/
    if (argc > 1) {
        int fd;
        if ((fd = open(argv[1], O_RDONLY)) < 0) {
            fprintf(stderr, __FILE__": open() failed: %s\n", strerror(errno));
            goto finish;
        }
        if (dup2(fd, STDIN_FILENO) < 0) {
            fprintf(stderr, __FILE__": dup2() failed: %s\n", strerror(errno));
            goto finish;
        }
        close(fd);
    }
    /* Lecture d'un flux sonore */
    if (!(s = pa_simple_new(NULL, argv[0] , PA_STREAM_PLAYBACK, "1", "playback", &ss, NULL , NULL, &error))) {   
		/* Les paramètres sont:
				  NULL, Utilisation du seveur par défaut .
                  argv[0]: Nom de l'application.
                  PA_STREAM_PLAYBACK: Mode lecture (playback)
                  NULL: Utilisation de la carte par défaut 
                  "playback": Description du flux sonore
                  &ss: Format de codage et échantillonage précisé ci-dessus
                  NULL: Utilisation du channel map par défaut 
                  NULL: Utilisation des attributs par défaut du buffer.
                  NULL: Ignorer le coe d'errreur
   */
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        goto finish;
    }
    for (;;) {
        uint8_t buf[BUFSIZE];
        ssize_t r;
#if 0
        pa_usec_t latency;
        if ((latency = pa_simple_get_latency(s, &error)) == (pa_usec_t) -1) {
            fprintf(stderr, __FILE__": pa_simple_get_latency() failed: %s\n", pa_strerror(error));
            goto finish;
        }
        fprintf(stderr, "%0.0f usec    \r", (float)latency);
#endif
        /* Lecture des données */
        if ((r = read(STDIN_FILENO, buf, sizeof(buf))) <= 0) {
            if (r == 0) /* EOF */
                break;
            fprintf(stderr, __FILE__": read() failed: %s\n", strerror(errno));
            goto finish;
        }
        /* Restitution des données */
        if (pa_simple_write(s, buf, (size_t) r, &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
            goto finish;
        }
    }
    /* S'assurer que chaque échantillon a été joué */
    if (pa_simple_drain(s, &error) < 0) {
        fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));
        goto finish;
    }
    ret = 0;
finish:
    if (s)
        pa_simple_free(s);
    return ret;
}
