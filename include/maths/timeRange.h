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
        virtual ~ITimeRange() = default;

        virtual auto _update(float) -> void = 0;
        virtual auto _play() -> void = 0;
        virtual auto _pause() -> void = 0;
        virtual auto _rewind() -> void = 0;
        virtual auto _inverse() -> void = 0;
};

template <typename T>
class TimeRange
:public ITimeRange
{
    public:
        TimeRange() = delete;
        
	TimeRange(T min, T max, float time, T* adress, int state = timeRangeState::PLAY)
	{
	    this->min = min;
	    this->max = max;
	    this->time = time;
	    this->adress = adress;

        *(this->adress) = this->min;

        this->value = *(this->adress);

        if (min < max)
            this->state = timeRangeState::PLAY;
        else if (min == max)
            this->state = timeRangeState::PAUSE;
        else
	        this->state = timeRangeState::REWIND;

        this->state *= state;
	}
        ~TimeRange() = default;

	auto _update(float deltaTime) -> void
	{
        if ((state == timeRangeState::PLAY && this->value >= max) || (state == timeRangeState::REWIND && this->value <= min))
            return;

        if (this->min < this->max)
            this->unit = (this->max - this->min) / this->time;
        else if (this->min > this->max)
            this->unit = (this->min - this->max) / this->time;

        this->value += this->unit * (deltaTime / 1000) * this->state;

        *(this->adress) = this->value;
	}

    auto _pause() -> void
    {
        this->state = timeRangeState::PAUSE;
    }

    auto _inverse() -> void
    {
        if (this->state == timeRangeState::PLAY)
            this->state = timeRangeState::REWIND;
        if (this->state == timeRangeState::REWIND)
            this->state = timeRangeState::PLAY;
    }

    auto _play() -> void
    {
        this->state = timeRangeState::PLAY;
    }

    auto _rewind() -> void
    {
        this->state = timeRangeState::REWIND;
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

        auto _play(unsigned int) -> void;
        auto _pause(unsigned int) -> void;
        auto _rewind(unsigned int) -> void;
        auto _inverse(unsigned int) -> void;

        template <typename T>
        auto _add(T min, T max, float time, T* adress, int state = timeRangeState::PLAY) -> unsigned int
        {
            listTimeRange.push_back(new TimeRange<T>(min, max, time, adress, state));
            return listTimeRange.size() - 1;
        }

        auto _erase(unsigned int) -> void;

    private:
        std::vector<ITimeRange*> listTimeRange;
        float oldTime = 0;
        float deltaTime;
};

} // namespace maths
} // namespace id

#endif //ANIMATOR_H_INCLUDED
