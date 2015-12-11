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

        virtual auto _update(float) -> void = 0;
};

template <typename T>
class TimeRange
:public ITimeRange
{
    public:
        TimeRange() = delete;
        
	TimeRange(T min, T max, float time, T* adress, int state = 1)
	{
	    this->min = min;
	    this->max = max;
	    this->time = time;
	    this->adress = adress;

        *(this->adress) = this->min;

        this->value = *(this->adress);

        if (min < max)
            this->state = 1;
        else if (min == max)
            this->state = 0;
        else
	        this->state = -1;

        this->state *= state;
	}
        ~TimeRange() = default;

	auto _update(float deltaTime) -> void
	{
        if ((state == 1 && this->value >= max) || (state == -1 && this->value <= max))
            return;

        if (this->min < this->max)
            this->unit = (this->max - this->min) / this->time;
        else if (this->min > this->max)
            this->unit = (this->min - this->max) / this->time;

        this->value += this->unit * (deltaTime / 1000) * this->state;

        *(this->adress) = this->value;
	}

    private:
        T min;
        T max;
        double value;
        float time;
        T* adress;
        int state;
        float unit = 0;

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
        auto _add(T min, T max, float time, T* adress, int state = timeRangeState::PLAY) -> void
        {
            TimeRange<T> tr(min, max, time, adress, state);
            listTimeRange.push_back(&tr);
        }

    private:
        std::vector<ITimeRange*> listTimeRange;
        float oldTime = 0;
        float deltaTime;
};

} // namespace maths
} // namespace id

#endif //ANIMATOR_H_INCLUDED
