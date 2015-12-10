#ifndef TIMERANGE_H_INCLUDED
#define TIMERANGE_H_INCLUDED

#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include <iostream>

namespace id {
namespace maths {

enum timeRangeState
{
    PAUSE = 0,
    PLAY = 1,
    REWIND = -1
};

class ITimeRange
{
    public:
        ITimeRange() = default;
        ~ITimeRange() = default;

        virtual auto _update(Uint32) -> void = 0;
};

template <typename T>
class TimeRange
:public ITimeRange
{
    public:
        TimeRange() = delete;
        
	TimeRange(T min, T max, Uint32 time, T* adress, int state)
	{
	    this->min = min;
	    this->max = max;
	    this->time = time;
	    this->adress = adress;
	    this->state = state;
	}
        ~TimeRange() = default;

	auto _update(Uint32 deltaTime) -> void
	{

	}

    private:
        T min;
        T max;
        Uint32 time;
        T* adress;
        int state;
};

class TimeRangeManager 
{
    public:
        TimeRangeManager() = default;
        ~TimeRangeManager()= default;

        TimeRangeManager(TimeRangeManager const&) = delete;
        TimeRangeManager(TimeRangeManager &&) = delete;
        auto operator=(TimeRangeManager const&) -> TimeRangeManager = delete;
        auto operator=(TimeRangeManager &&) -> TimeRangeManager = delete;

        auto _update() -> void;
        auto _updateDeltaTime() -> void;

        template <typename T>
        auto _add(T min, T max, Uint32 time, T* adress, int state = timeRangeState::PLAY) -> void
        {
            TimeRange<T> tr(min, max, time, adress, state);
            listTimeRange.push_back(&tr);
        }

    private:
        std::vector<ITimeRange*> listTimeRange;
        Uint32 oldTime = 0;
        Uint32 deltaTime;
};

} // namespace maths
} // namespace id

#endif //ANIMATOR_H_INCLUDED
