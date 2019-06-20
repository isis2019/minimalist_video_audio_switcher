#include <iostream>
#include <alsa/asoundlib.h>

using namespace std;

int main()
{
	const char* result;
	result = snd_mixer_selem_has_capture_channel(1,1);
	cout << result;
}

