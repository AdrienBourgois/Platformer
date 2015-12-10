#include "maths/timeRange.h"

namespace id {
namespace maths {

auto TimeRangeManager::_update() -> void
{
    this->_updateDeltaTime();

    for (unsigned int i = 0; i < this->listTimeRange.size(); ++i)
    {
        this->listTimeRange[i]._update(this->deltaTime);
    }
}

auto TimeRangeManager::_updateDeltaTime() -> void
{
    if (this->oldTime == 0)
    {
        this->oldTime = SDL_GetTicks();
        return;
    }

    Uint32 currentTime = SDL_GetTicks();
    this->deltaTime = currentTime - this->oldTime;
}

} // namespace maths
} // namespace id
