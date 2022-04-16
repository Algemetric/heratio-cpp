#pragma once

#include "lib/include/heratio.h"
#include "lib/include/rational.h"
#include <NTL/ZZ.h>

std::string StringFromZZ(const NTL::ZZ &x);

std::string Inspect(Heratio heratio);

std::string Inspect(std::vector<Rational> v);

std::string Inspect(NTL::Vec<NTL::ZZ> v);