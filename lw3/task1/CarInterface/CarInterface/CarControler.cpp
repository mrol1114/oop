#include <map>
#include <string>

#include "CarControler.h"
#include "Car.h"

namespace
{
    const std::string EXIT_TEXT = "exit";
    const enum class COMMAND
    {
        info,
        engineOn,
        engineOff,
        setGear,
        setSpeed,
    };

    const std::map<std::string, COMMAND> STRING_TO_COMMAND
    {
        {"Info", COMMAND::info},
        {"EngineOn", COMMAND::engineOn},
        {"EngineOff", COMMAND::engineOff},
        {"SetGear", COMMAND::setGear},
        {"SetSpeed", COMMAND::setSpeed},
    };

    const std::map<Direction, std::string> DIRECTION_TO_STRING
    {
        {Direction::backward, "backward"},
        {Direction::forward, "forward"},
        {Direction::standingStill, "standing still"},
    };

    void PrintWrongCommandMessage(std::ostream& output)
    {
        output << "Wrong command, see avaible commands." << std::endl;
    }

    void PrintAvaibleCommandsMessage(std::ostream& output)
    {
        output << "Avaible commands: "
            "Info, EngineOn, EngineOff, SetGear, SetSpeed" << std::endl;
        output << "To end write 'exit'" << std::endl;
    }

    void PrintStartInputMessage(std::ostream& output)
    {
        output << "Input Command: ";
    }

    void ExecuteCommand(Car& car, const std::string& command,
        std::istream& input, std::ostream& output)
    {
        switch (STRING_TO_COMMAND.at(command))
        {
        case COMMAND::info:
            output << "Gear: " << car.GetGear() << std::endl;
            output << "Speed: " << car.GetSpeed() << std::endl;
            output << "Engine status: " << (car.isTurnedOn() ? "on" : "off") << std::endl;
            output << "Direction: " << DIRECTION_TO_STRING.at(car.GetDirection()) << std::endl;
            break;

        case COMMAND::engineOn:
            car.TurnOnEngine();
            break;

        case COMMAND::engineOff:
            car.TurnOffEngine();
            break;

        case COMMAND::setGear:
            int gear;

            input >> gear;
            car.SetGear(gear);
            break;

        case COMMAND::setSpeed:
            int speed;

            input >> speed;
            car.SetSpeed(speed);
            break;
        }
    }
}

void RunControler(std::istream& input, std::ostream& output)
{
    Car car;
    std::string command;

    PrintAvaibleCommandsMessage(output);
    PrintStartInputMessage(output);
    while (input >> command && command != EXIT_TEXT)
    {
        if (STRING_TO_COMMAND.find(command) != STRING_TO_COMMAND.end())
        {
            ExecuteCommand(car, command, input, output);
        }
        else
        {
            PrintWrongCommandMessage(output);
        }

        output << std::endl << std::endl;
        PrintAvaibleCommandsMessage(output);
        PrintStartInputMessage(output);
    }
}