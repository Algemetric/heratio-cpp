#pragma once

NTL::ZZ GenerateNonZeroRandomInteger(const NTL::ZZ upperbound);

std::vector<Rational> GenerateRandomVector(const int size, const NTL::ZZ upperbound);

NTL::Vec<NTL::ZZ> CreateVectorFromUniqueValue(long size, NTL::ZZ value);

Rational DotProduct(std::vector<Rational> v1, std::vector<Rational> v2);

NTL::ZZ DotProduct(NTL::Vec<NTL::ZZ> v1, NTL::Vec<NTL::ZZ> v2);

NTL::ZZ StringToZZ(const std::string &string);

void Clear();

std::string endln(const int n);