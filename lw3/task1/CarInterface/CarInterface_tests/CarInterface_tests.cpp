#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "../CarInterface/Car.h"
#include "../CarInterface/CarControler.h"

SCENARIO("turn engine on")
{
	
	GIVEN("A car with turned off engine")
	{
		Car car;

		REQUIRE(car.TurnOnEngine());
	}
}

SCENARIO("acceleration to top speed")
{
	GIVEN("A car with turned off engine")
	{
		Car car;

		car.TurnOnEngine();

		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetGear() == 1);
		REQUIRE(car.SetSpeed(30));
		REQUIRE(!car.SetSpeed(31));
		REQUIRE(!car.SetSpeed(-1));
		REQUIRE(car.GetSpeed() == 30);
		REQUIRE(car.SetSpeed(20));

		REQUIRE(car.SetGear(2));
		REQUIRE(car.GetGear() == 2);
		REQUIRE(car.SetSpeed(50));
		REQUIRE(!car.SetSpeed(51));
		REQUIRE(!car.SetSpeed(19));
		REQUIRE(car.GetSpeed() == 50);
		REQUIRE(car.SetSpeed(30));

		REQUIRE(car.SetGear(3));
		REQUIRE(car.GetGear() == 3);
		REQUIRE(car.SetSpeed(60));
		REQUIRE(!car.SetSpeed(61));
		REQUIRE(!car.SetSpeed(29));
		REQUIRE(car.GetSpeed() == 60);
		REQUIRE(car.SetSpeed(40));

		REQUIRE(car.SetGear(4));
		REQUIRE(car.GetGear() == 4);
		REQUIRE(car.SetSpeed(90));
		REQUIRE(!car.SetSpeed(91));
		REQUIRE(!car.SetSpeed(39));
		REQUIRE(car.GetSpeed() == 90);
		REQUIRE(car.SetSpeed(50));

		REQUIRE(car.SetGear(5));
		REQUIRE(car.GetGear() == 5);
		REQUIRE(car.SetSpeed(150));
		REQUIRE(!car.SetSpeed(151));
		REQUIRE(car.GetSpeed() == 150);
		REQUIRE(!car.SetSpeed(49));
	}
}

SCENARIO("moving with different speed")
{

	GIVEN("A car with turned off engine")
	{
		Car car;

		REQUIRE(car.TurnOnEngine());

		car.SetGear(1);
		car.SetSpeed(30);

		car.SetGear(0);
		REQUIRE(!car.SetSpeed(40));
	}
}

SCENARIO("moving backward")
{
	GIVEN("A car with turned off engine")
	{
		Car car;

		car.TurnOnEngine();
		REQUIRE(car.GetDirection() == Direction::standingStill);

		car.SetGear(1);
		REQUIRE(car.SetGear(-1));
		REQUIRE(car.GetGear() == -1);
		REQUIRE(car.SetSpeed(20));
		REQUIRE(car.GetDirection() == Direction::backward);
		REQUIRE(!car.SetSpeed(21));

		REQUIRE(!car.SetGear(-1));
		REQUIRE(!car.SetGear(1));
		REQUIRE(car.SetGear(0));
		REQUIRE(!car.SetGear(-1));
		REQUIRE(car.GetDirection() == Direction::backward);

		REQUIRE(car.SetSpeed(0));
		REQUIRE(car.SetGear(-1));
		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetDirection() == Direction::standingStill);
	}
}

SCENARIO("stop car")
{
	GIVEN("A car with turned on engine and not 0 speed")
	{
		Car car;
		car.TurnOnEngine();

		car.SetGear(1);
		car.SetSpeed(20);
		REQUIRE(!car.TurnOffEngine());

		car.SetSpeed(0);
		REQUIRE(!car.TurnOffEngine());

		car.SetGear(0);
		REQUIRE(car.TurnOffEngine());
	}
}