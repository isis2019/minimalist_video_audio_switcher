#include <alsa/asoundlib.h>
#include <iostream>

using namespace std;
int main ()

{
int result = 0;
long value=100;
long* db_value;
snd_mixer_elem_t *handle;
 
result=snd_mixer_selem_ask_capture_vol_dB 	(handle, value, db_value);


return 0;
 		
}
