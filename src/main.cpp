#include <SDL2/SDL_ttf.h>
#include <typeinfo>
#include <new>
#include <memory>
#include <string>
#include "maths/timeRange.h"

int main(int argc, char* argv[])
{
    char min = 0;
    char max = 10;
    Uint32 time = 10;
    char value = 0;

    id::maths::TimeRangeManager trmgr;

    trmgr._add(min, max, time, &value);

    while(1)
    {
        trmgr._update();
    }

	(void)argc;
	(void)argv;

	return EXIT_SUCCESS;
}
