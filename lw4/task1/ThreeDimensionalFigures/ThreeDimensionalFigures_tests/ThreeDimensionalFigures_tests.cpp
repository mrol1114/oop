#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../libs/catch2/catch.hpp"

#include "../ConsoleApplication1/CBodyUtils.h"
#include "../ConsoleApplication1/CCompound.h"
#include "../ConsoleApplication1/CCone.h"
#include "../ConsoleApplication1/CParallelepiped.h"
#include "../ConsoleApplication1/CSphere.h"
#include "../ConsoleApplication1/CCylinder.h"

SCENARIO("checking body cone")
{
	WHEN("Initializing")
	{
		CCone cone{18, 14, 14};

		REQUIRE(cone.GetDensity() == 18);
		REQUIRE(cone.GetHeight() == 14);
		REQUIRE(cone.GetBaseRadius() == 14);
	}

	WHEN("Initializing with zeroes")
	{
		CCone cone{0, 0, 0};

		REQUIRE(cone.GetDensity() == 0);
		REQUIRE(cone.GetHeight() == 0);
		REQUIRE(cone.GetBaseRadius() == 0);
		REQUIRE(cone.GetMass() == 0);
		REQUIRE(cone.GetVolume() == 0);
	}

	WHEN("Trying initialize with negatives")
	{
		REQUIRE_THROWS(CCone{-18, 14, 14});
		REQUIRE_THROWS(CCone{18, -14, 14});
		REQUIRE_THROWS(CCone{18, 14, -14});
	}
}

SCENARIO("checking body cylinder")
{
	WHEN("Initializing")
	{
		CCylinder cylinder{ 18, 14, 14 };

		REQUIRE(cylinder.GetDensity() == 18);
		REQUIRE(cylinder.GetHeight() == 14);
		REQUIRE(cylinder.GetBaseRadius() == 14);
	}

	WHEN("Initializing with zeroes")
	{
		CCylinder cylinder{0, 0, 0};

		REQUIRE(cylinder.GetDensity() == 0);
		REQUIRE(cylinder.GetHeight() == 0);
		REQUIRE(cylinder.GetBaseRadius() == 0);
		REQUIRE(cylinder.GetMass() == 0);
		REQUIRE(cylinder.GetVolume() == 0);
	}

	WHEN("Trying initialize with negatives")
	{
		REQUIRE_THROWS(CCylinder{-18, 14, 14});
		REQUIRE_THROWS(CCylinder{18, -14, 14});
		REQUIRE_THROWS(CCylinder{18, 14, -14});
	}
}

SCENARIO("checking body parallelepiped")
{
	WHEN("Initializing")
	{
		CParallelepiped parallelepiped{18, 14, 14, 14};

		REQUIRE(parallelepiped.GetDensity() == 18);
		REQUIRE(parallelepiped.GetHeight() == 14);
		REQUIRE(parallelepiped.GetWidth() == 14);
		REQUIRE(parallelepiped.GetDepth() == 14);
	}

	WHEN("Initializing with zeroes")
	{
		CParallelepiped parallelepiped{0, 0, 0, 0};

		REQUIRE(parallelepiped.GetDensity() == 0);
		REQUIRE(parallelepiped.GetHeight() == 0);
		REQUIRE(parallelepiped.GetWidth() == 0);
		REQUIRE(parallelepiped.GetDepth() == 0);
		REQUIRE(parallelepiped.GetMass() == 0);
		REQUIRE(parallelepiped.GetVolume() == 0);
	}

	WHEN("Trying initialize with negatives")
	{
		REQUIRE_THROWS(CParallelepiped{-18, 14, 14, 14});
		REQUIRE_THROWS(CParallelepiped{-18, -14, 14, 14});
		REQUIRE_THROWS(CParallelepiped{-18, 14, -14, 14});
		REQUIRE_THROWS(CParallelepiped{-18, 14, 14, -14});
	}
}

SCENARIO("checking body sphere")
{
	WHEN("Initializing")
	{
		CSphere sphere{18, 14};

		REQUIRE(sphere.GetDensity() == 18);
		REQUIRE(sphere.GetRadius() == 14);
	}

	WHEN("Initializing with zeroes")
	{
		CSphere sphere{0, 0};

		REQUIRE(sphere.GetDensity() == 0);
		REQUIRE(sphere.GetRadius() == 0);
		REQUIRE(sphere.GetMass() == 0);
		REQUIRE(sphere.GetVolume() == 0);
	}

	WHEN("Trying initialize with negatives")
	{
		REQUIRE_THROWS(CSphere{-18, 14});
		REQUIRE_THROWS(CSphere{18, -14});
	}
}

SCENARIO("checking compound")
{
	WHEN("Initializing with bodies")
	{
		CCompound bodies{{
			std::shared_ptr<CBody>(new CSphere{20, 12}),
			std::shared_ptr<CBody>(new CCylinder{20, 13, 13})
		}};

		REQUIRE(bodies.GetChilds().size() == 2);
	}

	WHEN("Trying initialize without bodies")
	{
		REQUIRE_THROWS(CCompound{{}});
	}

	WHEN("Trying to add itself")
	{
		Bodies bodies;

		std::shared_ptr<CBody> cylinder(new CCylinder{20, 13, 13});
		std::shared_ptr<CBody> parallelepiped(new CParallelepiped{18, 14, 14, 14});
		std::shared_ptr<CBody> cone(new CCone{18, 14, 14});

		std::shared_ptr<CCompound> externalCompound(new CCompound{ {cylinder} });
		REQUIRE(externalCompound->GetChilds().size() == 1);

		std::shared_ptr<CCompound> internalCompound(new CCompound{ {cone, externalCompound} });
		REQUIRE(internalCompound->GetChilds().size() == 2);

		REQUIRE(externalCompound->AddChildBody(parallelepiped));
		REQUIRE(externalCompound->GetChilds().size() == 2);

		REQUIRE(!externalCompound->AddChildBody(externalCompound));
		REQUIRE(!externalCompound->AddChildBody(internalCompound));

		REQUIRE(externalCompound->GetChilds().size() == 2);
	}
}

SCENARIO("checking insert")
{
	GIVEN("Two bodies")
	{
		Bodies bodies;

		CSphere sphere{20, 12};
		CCylinder cylinder{20, 13, 13};

		std::istringstream input(
			"[sphere]\n"
			"	radius=12\n"
			"	density=20\n"
			"[end_type]\n"
			""
			"[cylinder]\n"
			"	baseRadius=13\n"
			"	height=13\n"
			"	density=20\n"
			"[end_type]\n"
		);
		std::ostringstream output;

		ReadCBodiesInVector(input, bodies);
		REQUIRE(bodies.size() == 2);
		REQUIRE(bodies[0]->ToString() == sphere.ToString());
		REQUIRE(bodies[1]->ToString() == cylinder.ToString());
	}

	GIVEN("One compound body consits of 2 simple bodies and one compound of 1 simple body")
	{
		Bodies bodies;

		std::shared_ptr<CBody> cylinder(new CCylinder{20, 13, 13});
		std::shared_ptr<CBody> parallelepiped(new CParallelepiped{18, 14, 14, 14});
		std::shared_ptr<CBody> cone(new CCone{18, 14, 14});
		std::shared_ptr<CBody> internalCompound(new CCompound{{cone}});
		std::shared_ptr<CCompound> externalCompound(new CCompound{{cylinder}});

		REQUIRE(externalCompound->AddChildBody(parallelepiped));
		REQUIRE(externalCompound->AddChildBody(internalCompound));

		std::istringstream input(
			"[compound]\n" 
			"	[cylinder]\n"
			"		baseRadius=13\n"
			"		height=13\n"
			"		density=20\n"
			"	[end_type]\n"
			""
			"	[parallelepiped]\n"
			"		width=14\n"
			"		height=14\n"
			"		depth=14\n"
			"		density=18\n"
			"	[end_type]\n"
			""
			"	[compound]\n"
			"		[cone]\n"
			"			baseRadius=14\n"
			"			height=14\n"
			"			density=18\n"
			"		[end_type]\n"
			"	[end_type]\n"
			"[end_type]\n"
		);

		ReadCBodiesInVector(input, bodies);

		REQUIRE(bodies.size() == 1);
		REQUIRE(bodies[0].get()->ToString() == externalCompound->ToString());
	}
}

SCENARIO("finding body with biggest mass")
{
	GIVEN("Two bodies")
	{
		Bodies bodies = {
			std::shared_ptr<CBody>(new CSphere{20, 12}),
			std::shared_ptr<CBody>(new CCylinder{20, 13, 13})
		};

		REQUIRE(GetBodyWithBiggestMass(bodies)->GetMass() >= bodies[0]->GetMass());
		REQUIRE(GetBodyWithBiggestMass(bodies)->GetMass() >= bodies[1]->GetMass());
	}
}

SCENARIO("finding lightest body")
{
	GIVEN("1m3 of water and 1m3 of oxygen")
	{
		auto calculateWeightInWater = [](CBody* body) {
			const double DENSITY_OF_WATER = 1000;
			const double ACCELERATION_OF_GRAVITY = 9.81;

			return (body->GetDensity() - DENSITY_OF_WATER) * ACCELERATION_OF_GRAVITY * body->GetVolume();
		};

		Bodies bodies = {
			std::shared_ptr<CBody>(new CParallelepiped{1.4, 1, 1, 1}),
			std::shared_ptr<CBody>(new CParallelepiped{1000, 1, 1, 1})
		};

		Body lightestBody = GetLightestBodyInWater(bodies);

		REQUIRE(calculateWeightInWater(lightestBody.get()) <= calculateWeightInWater(bodies[0].get()));
		REQUIRE(calculateWeightInWater(lightestBody.get()) <= calculateWeightInWater(bodies[1].get()));
	}
}

SCENARIO("printing info about bodies")
{
	GIVEN("Two bodies")
	{
		Bodies bodies = {
			std::shared_ptr<CBody>(new CSphere{20, 12}),
			std::shared_ptr<CBody>(new CCylinder{20, 13, 13})
		};

		std::string expectedOutput(
			"[sphere]\n"
			"\tdensity = 20\n"
			"\tvolume = 7234.56\n"
			"\tmass = 144691.2\n"
			"\tradius = 12\n"
			"[end_type]\n"
			"\n"
			"[cylinder]\n"
			"\tdensity = 20\n"
			"\tvolume = 6898.58\n"
			"\tmass = 137971.6\n"
			"\tbaseRadius = 13\n"
			"\theight = 13\n"
			"[end_type]\n"
			"\n\n"
			"Body with biggest mass\n"
			"[sphere]\n"
			"\tdensity = 20\n"
			"\tvolume = 7234.56\n"
			"\tmass = 144691.2\n"
			"\tradius = 12\n"
			"[end_type]\n"
			"\n\n"
			"Lightest body in water\n"
			"[cylinder]\n"
			"\tdensity = 20\n"
			"\tvolume = 6898.58\n"
			"\tmass = 137971.6\n"
			"\tbaseRadius = 13\n"
			"\theight = 13\n"
			"[end_type]\n"
			"\n"
		);

		std::ostringstream output;

		PrintInfoAboutBodies(output, bodies);
		REQUIRE(output.str() == expectedOutput);
	}
}