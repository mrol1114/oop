#pragma once

#include <vector>
#include <iostream>

#include "CBody.h"

using Body = std::shared_ptr<CBody>;
using Bodies = std::vector<std::shared_ptr<CBody>>;

// to vector, возвращать bodies
void ReadCBodiesInVector(std::istream& input, Bodies& bodies);
void PrintInfoAboutBodies(std::ostream& output, const Bodies& bodies);
// проверка на пустоту
Body GetBodyWithBiggestMass(const Bodies& bodies);
Body GetLightestBodyInWater(const Bodies& bodies);