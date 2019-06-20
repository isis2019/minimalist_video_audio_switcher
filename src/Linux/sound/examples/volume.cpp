#include "mvas_mixer.h"
#include <iostream>
#include <alsa/asoundlib.h>

  namespace mvas
  {
	   mixer::mixer(){}

  void mixer::set_volume(const int volume)
    {
        snd_mixer_t* mixer = nullptr;
        snd_mixer_open(&mixer, 0);
        snd_mixer_attach(mixer, "default");
        snd_mixer_selem_register(mixer, NULL, NULL);
        snd_mixer_load(mixer);

        snd_mixer_selem_id_t* id = nullptr;
        snd_mixer_selem_id_alloca(&id);
        snd_mixer_selem_id_set_index(id,0);
        snd_mixer_selem_id_set_name(id,"Master");
        snd_mixer_elem_t* elem = snd_mixer_find_selem(mixer, id);

        long min, max;
        snd_strerror(snd_mixer_selem_get_playback_volume_range(elem,&min,&max));
        snd_mixer_selem_set_playback_volume_all(elem, volume * ((max-min)/100));
        snd_mixer_close(mixer);
    }
}
