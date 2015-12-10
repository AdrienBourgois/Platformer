#ifndef TIMERANGE_H_INCLUDED
#define TIMERANGE_H_INCLUDED

#include <SDL2/SDL.h>
#include <vector>
#include <tuple>

namespace id {
namespace maths {

enum timeRangeState
{
    PAUSE = 0,
    PLAY = 1,
    REWIND = -1
};

template <typename T>
class ITimeRange
{
    public:
        ITimeRange() = delete;
        ITimeRange(T, T, Uint32, T*);
        ~ITimeRange() = default;

        auto _update() -> void;

    private:
        T min;
        T max;
        Uint32 time;
        T* adress;
};

class TimeRangeManager 
{
    public:
        TimeRangeManager();
        ~TimeRangeManager()= default;

        TimeRangeManager(TimeRangeManager const&) = delete;
        TimeRangeManager(TimeRangeManager &&) = delete;
        auto operator=(TimeRangeManager const&) -> TimeRangeManager = delete;
        auto operator=(TimeRangeManager &&) -> TimeRangeManager = delete;

        auto _update() -> void;
        auto _updateDeltaTime() -> void;

    private:
        std::vector<ITimeRange> listTimeRange;
        Uint32 oldTime = 0;
        Uint32 deltaTime;
};

/* template<>
class TimeRange<>
:public ITimeRange
{
    public:
        TimeRange() = delete;
        TimeRange()
        ~TimeRange();

        TimeRange(TimeRange const&) = delete;
        TimeRange(TimeRange &&) = delete;
        auto operator=(TimeRange const&) -> TimeRange = delete;
        auto operator=(TimeRange &&) -> TimeRange = delete;

        auto _update() -> void;

    private:
        
}; */

} // namespace maths
} // namespace id

#endif //ANIMATOR_H_INCLUDED
