/*

* Ce programme permet de lire et d'écrire  depuis la carte son par défaut pendant 5 secondes

*/

/* Utilisation de la nouvelle API ALSA*/
#define ALSA_PCM_NEW_HW_PARAMS_API

#include <alsa/asoundlib.h>

int main() {
  long loops;
  int rc;
  int size;
  snd_pcm_t *handle;
  snd_pcm_hw_params_t *params;
  unsigned int val;
  int dir;
  snd_pcm_uframes_t frames;
  char *buffer;

  /* Ouvrir la carte pour l'enregistrement */
  rc = snd_pcm_open(&handle, "default",
                    SND_PCM_STREAM_CAPTURE, 0);
  if (rc < 0) {
    fprintf(stderr,
            "unable to open pcm device: %s\n",
            snd_strerror(rc));
    exit(1);
  }

  /* Allouer les paramètres à la carte */
  snd_pcm_hw_params_alloca(&params);

  /* Attribuer les valeurs par défaut */
  snd_pcm_hw_params_any(handle, params);

  /* Configuration des paramètres hardware*/

  /* Mode entrelacé */
  snd_pcm_hw_params_set_access(handle, params,
                      SND_PCM_ACCESS_RW_INTERLEAVED);

  /*  Choix du format 16 bits little-endian*/
  snd_pcm_hw_params_set_format(handle, params,
                              SND_PCM_FORMAT_S16_LE);

  /* Choix du nombre de cannaux: 2 stéréo */
  snd_pcm_hw_params_set_channels(handle, params, 2);

  /* Choix de la fréquence d'échantillonage 44100 bits */
  val = 44100;
  snd_pcm_hw_params_set_rate_near(handle, params,
                                  &val, &dir);

  /*  Définir la taille de la periode à 32 frames. */
  frames = 32;
  snd_pcm_hw_params_set_period_size_near(handle,
                              params, &frames, &dir);

  /* Ecriture des paramètres du pilote*/
  rc = snd_pcm_hw_params(handle, params);
  if (rc < 0) {
    fprintf(stderr,
            "unable to set hw parameters: %s\n",
            snd_strerror(rc));
    exit(1);
  }

  /* Utiliser un buffer assez large pour une période*/
  snd_pcm_hw_params_get_period_size(params,
                                      &frames, &dir);
  size = frames * 4; /* 2 bytes/sample, 2 channels */
  buffer = (char *) malloc(size);

  /*Boucler pendant 5 secondes */
  snd_pcm_hw_params_get_period_time(params,
                                         &val, &dir);
  loops = 5000000 / val;

  while (loops > 0) {
    loops--;
    rc = snd_pcm_readi(handle, buffer, frames);
    if (rc == -EPIPE) {
     
      fprintf(stderr, "overrun occurred\n");
      snd_pcm_prepare(handle);
    } else if (rc < 0) {
      fprintf(stderr,
              "error from read: %s\n",
              snd_strerror(rc));
    } else if (rc != (int)frames) {
      fprintf(stderr, "short read, read %d frames\n", rc);
    }
    rc = write(1, buffer, size);
    if (rc != size)
      fprintf(stderr,
              "short write: wrote %d bytes\n", rc);
  }

  snd_pcm_drain(handle);
  snd_pcm_close(handle);
  free(buffer);

  return 0;
}

