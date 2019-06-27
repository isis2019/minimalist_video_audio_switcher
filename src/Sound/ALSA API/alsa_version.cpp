#include <iostream>
#include <alsa/asoundlib.h>

using namespace std;

int main()
{
    const char* toto;
   
    toto = snd_asoundlib_version();
    cout << toto << '\n';
    
}

