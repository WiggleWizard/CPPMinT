#pragma once

#include <chrono>


class SimpleBench
{
public:
    SimpleBench(bool startNow = false)
    {
        if(startNow)
			Start();
    }

    ~SimpleBench()
    {
        Stop();
    }

    void Start()
    {
        _startTimePoint = std::chrono::high_resolution_clock::now();
        _duration = 0;
        _bIsRunning = true;
    }

    /**
     * \brief Stops the benchmark and returns the duration in milliseconds.
     */
    double Stop()
    {
        auto endTimePoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(_startTimePoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

        _duration = end - start;

        _bIsRunning = false;

        return GetDurationInMs();
    }

    double GetDurationInMs() { return (double)_duration * (double)0.001f; }
    long long GetDurationInUs() { return _duration; }

    bool IsRunning() const { return _bIsRunning; }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _startTimePoint;
    long long _duration = 0;
    bool _bIsRunning = false;
};