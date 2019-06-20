#include <iostream>
#include <alsa/asoundlib.h>

using namespace std;

int main()
{
    const char* version;
    int name;
    toto = snd_asoundlib_version();
    cout << version << '\n';

    name = snd_func_card_driver(0);
    cout << name;
}

