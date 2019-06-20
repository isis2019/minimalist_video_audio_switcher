
#include <alsa/asoundlib.h>

static char *device = "default";                        /* playback device: Ordinateur dans un premier temps */
snd_output_t *output = NULL;
int main(void)
{
        int err;
        snd_pcm_t *handle;
        if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
                printf("Playback open error: %s\n", snd_strerror(err));
                exit(EXIT_FAILURE);
        }
        if ((err = snd_pcm_set_params(handle,
                                      SND_PCM_FORMAT_U8,
                                      SND_PCM_ACCESS_RW_INTERLEAVED,
                                      1,
                                      48000,
                                      1,
                                      500000)) < 0) {   /* 0.5sec */
                printf("Playback open error: %s\n", snd_strerror(err));
                exit(EXIT_FAILURE);
        }

        snd_pcm_close(handle);
        return 0;
}
