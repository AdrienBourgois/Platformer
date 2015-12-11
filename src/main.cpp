#include <SDL2/SDL_ttf.h>
#include <typeinfo>
#include <new>
#include <memory>
#include <string>
#include "maths/timeRange.h"

int main(int argc, char* argv[])
{
    int min = 5;
    int max = 50;
    Uint32 time = 5;
    int value = 500;

    id::maths::TimeRangeManager trmgr;

    trmgr._add(min, max, time, &value);

    while(1)
    {
        trmgr._update();

        std::cout << value << std::endl;
    }

	(void)argc;
	(void)argv;

	return EXIT_SUCCESS;
}
