#include <iostream>
#include <string>
#include <map>
#include "Car.h"

bool Car::isTurnedOn() const
{
    return m_isEngineOn;
}

bool Car::TurnOnEngine()
{
    m_isEngineOn = true;
    m_gear = M_NEUTRAL_GEAR;
    m_speed = 0;

    return true;
}

bool Car::TurnOffEngine()
{
    if (!isEngineCanBeTurnedOff())
    {
        return false;
    }

    m_isEngineOn = false;
    return true;
}

Direction Car::GetDirection() const
{
    if (m_speed == 0)
    {
        return Direction::standingStill;
    }

    if (m_speed < 0)
    {
        return Direction::backward;
    }

    return Direction::forward;
}

int Car::GetSpeed() const
{
    return m_speed < 0 ? -m_speed : m_speed;
}

bool Car::SetSpeed(int speed)
{
    if (!isSpeedCanBeSet(speed))
    {
        return false;
    }

    m_speed = speed;
    return true;
}

int Car::GetGear() const
{
    return m_gear;
}

bool Car::SetGear(int gear)
{
    if (!isGearCanBeSet(gear))
    {
        return false;
    }

    m_gear = gear;
    return true;
}

bool Car::isGearCanBeSet(int gear)
{
    if (gear < M_MIN_GEAR || gear > M_MAX_GEAR)
    {
        return false;
    }

    if (m_speed < 0 && gear > M_NEUTRAL_GEAR)
    {
        return false;
    }

    if (gear == M_MIN_GEAR && m_speed != 0)
    {
        return false;
    }

    if (gear != M_NEUTRAL_GEAR
        && (M_GEAR_INTERVALS.at(gear).leftPoint > m_speed
            || M_GEAR_INTERVALS.at(gear).rightPoint < m_speed))
    {
        return false;
    }

    return true;
}

bool Car::isSpeedCanBeSet(int& speed)
{
    if (speed < 0)
    {
        return false;
    }

    if (m_gear == M_NEUTRAL_GEAR &&
        speed > (m_speed < 0 ? -m_speed : m_speed))
    {
        return false;
    }

    speed = (m_gear == M_MIN_GEAR && speed > 0) || m_speed < 0
        ? -speed
        : speed;

    if (m_gear != M_NEUTRAL_GEAR
        && (M_GEAR_INTERVALS.at(m_gear).leftPoint > speed
            || M_GEAR_INTERVALS.at(m_gear).rightPoint < speed))
    {
        return false;
    }

    return true;
}

bool Car::isEngineCanBeTurnedOff()
{
    if (m_speed != 0 ||
        m_gear != M_NEUTRAL_GEAR)
    {
        return false;
    }

    return true;
}