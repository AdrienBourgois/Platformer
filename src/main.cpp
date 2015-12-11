#include <SDL2/SDL_ttf.h>
#include <typeinfo>
#include <new>
#include <memory>
#include <string>
#include "maths/timeRange.h"

int main(int argc, char* argv[])
{
    float min = 5.f;
    float max = 50.f;
    Uint32 time = 5;
    float value = 500.f;

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
