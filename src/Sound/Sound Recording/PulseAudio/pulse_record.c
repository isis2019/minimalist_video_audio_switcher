/*
	Ce programme permet d'enregistrer du son en se basant sur PulseAudio API, depuis une carte son qu'on définit dans les paramètres de la fonction "pa_simple_new" ci dessous.
    Pour compiler le programme : gcc -o record pulse_record.c -lpulse -lpulse-simple 
    Pour lancer l'enregistrement: ./record   > nom_du_fichier.raw  ( Enregistremet en format raw qu'on pourra lire sur Audacity ou autre DAW)
*/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#define BUFSIZE 1024


/* Appeler à écrire en boucle */
static ssize_t loop_write(int fd, const void*data, size_t size) {
    ssize_t ret = 0;
    while (size > 0) {
        ssize_t r;
        if ((r = write(fd, data, size)) < 0)
            return r;
        if (r == 0)
            break;
        ret += r;
        data = (const uint8_t*) data + r;
        size -= (size_t) r;
    }
    return ret;
}
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
    /* Création de l'enregistrement du flux sonore */
    if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) 
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
    {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        goto finish;
    }
    for (;;) {
        uint8_t buf[BUFSIZE];
        /*  Lecture des données */ 
        if (pa_simple_read(s, buf, sizeof(buf), &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
            goto finish;
        }
        /* Restitution et écriture des données vers STDOUT */
        if (loop_write(STDOUT_FILENO, buf, sizeof(buf)) != sizeof(buf)) {
            fprintf(stderr, __FILE__": write() failed: %s\n", strerror(errno));
            goto finish;
        }
    }
    ret = 0;
finish:
    if (s)
        pa_simple_free(s);
    return ret;
}

