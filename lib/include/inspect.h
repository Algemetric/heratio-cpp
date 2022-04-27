#pragma once

#include "lib/include/heratio.h"
#include "lib/include/rational.h"
#include <NTL/ZZ.h>

std::string StringFromZZ(const NTL::ZZ &zz_);

std::string Inspect(const Heratio &heratio);

std::string Inspect(std::vector<Rational> vector);

std::string Inspect(NTL::Vec<NTL::ZZ> vector);