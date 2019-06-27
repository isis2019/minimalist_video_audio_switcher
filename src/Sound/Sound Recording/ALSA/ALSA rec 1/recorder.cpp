#include "recorder.h"

int record(int time_ms, char** pbuf){
    long loops;
    int rc;
    int size;
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    unsigned int val;
    int dir;
    snd_pcm_uframes_t frames;
    char* ptmpbuf;

    /* Ou_vrir l'équipement d'enregistrement */
    rc = snd_pcm_open(&handle, HW,
                      SND_PCM_STREAM_CAPTURE, 0);
    if (rc < 0) {
      fprintf(stderr,
              "unable to open pcm device: %s\n",
              snd_strerror(rc));
      return -1;
    }

    /* Allouer les paramètres hardware (hw) */
    snd_pcm_hw_params_alloca(&params);

    /* Utiliser les valeurs par défaut */
    snd_pcm_hw_params_any(handle, params);

    /* Configuration des paramètres hardware  */

    /* Mode entrelacé */
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

    /* Format de codage 16bits signé little-endian  */
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

    /* Choix des Cannaux (Stéréo) */
    snd_pcm_hw_params_set_channels(handle, params, CH);

    /* Fréquence d'achantillonage  */
    val = FS;
    snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);

    /* Mettre la taille de la période en frame */
    frames = FRAME;
    snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

    /* Mettre les paramètres pour le pilote */
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) {
      fprintf(stderr,
              "unable to set hw parameters: %s\n",
              snd_strerror(rc));
      return -1;
    }

    /* Utilisation d'une taille de buffer assez large pour contenir une période */
    snd_pcm_hw_params_get_period_size(params, &frames, &dir);
    size = frames * CH * (DSIZE/8); 
    ptmpbuf = (char *) malloc(size);

    /* Calcul de la boucle */
    snd_pcm_hw_params_get_period_time(params, &val, &dir);
    loops = time_ms*1000/val;

    /* Allouer de la mémoire pour pbuf*/
    int LENGTH = size * loops;
    *pbuf = new char[LENGTH];
    char* cp_pbuf = *pbuf;

    while (loops > 0) {
      loops--;
      rc = snd_pcm_readi(handle, ptmpbuf, frames);
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
      memcpy(cp_pbuf, ptmpbuf, size);
      printf("[%ld]\tbuffer[0]: 0x%2x, buffer frames: %ld\n",loops, (uint16_t)*cp_pbuf, frames);
      cp_pbuf += size;
    }
	/* Arrêter l'enregistrement*/
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(ptmpbuf);
    
    return LENGTH;
}

complex<double>* extract(uint16_t* pbuf, int len_16){
  if(!pbuf) return NULL;
  complex<double>* Xn = new complex<double>[len_16];
  complex<double>* pXn = Xn;
  for(int i = 0; i < len_16 / 2; ++i){
    (*pXn).real((double) pbuf[2 * i]);
    (*pXn).imag((double) 0);
    (*(pXn + len_16 / 2)).real((double) pbuf[2 * i + 1]);
    (*(pXn + len_16 / 2)).imag((double) 0);
    ++pXn;
  }

  return Xn;
}
