#pragma once

enum class Direction
{
    backward,
    standingStill,
    forward
};

class Car
{
public:
    bool isTurnedOn() const;
    bool TurnOnEngine();
    bool TurnOffEngine();
    Direction GetDirection() const;
    int GetSpeed() const;
    bool SetSpeed(int speed);
    int GetGear() const;
    bool SetGear(int gear);

private:
    struct Interval
    {
        int leftPoint;
        int rightPoint;
    };

    const int M_MIN_GEAR = -1;
    const int M_MAX_GEAR = 5;
    const int M_NEUTRAL_GEAR = 0;

    bool m_isEngineOn;
    int m_speed;
    int m_gear;

    const std::map<int, Interval> M_GEAR_INTERVALS
    {
        {-1, {-20, 0}},
        {1, {0, 30}},
        {2, {20, 50}},
        {3, {30, 60}},
        {4, {40, 90}},
        {5, {50, 150}},
    };

    bool isGearCanBeSet(int gear);
    bool isSpeedCanBeSet(int& speed);
    bool isEngineCanBeTurnedOff();
};