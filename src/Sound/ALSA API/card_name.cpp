#include <iostream>
#include <alsa/asoundlib.h>

using namespace std;

int main()
{
    char* name;
    int result = 0;
	int i = 0;
	while (result == 0)
		{
			result = snd_card_get_longname(i,&name);
			if (result == 0)
			{
				cout << i << " : " << name << '\n';
				i++;
			}
		}

}
