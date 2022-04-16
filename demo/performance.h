#pragma once

void KeyGenPerformance(Heratio &heratio);

void PerformanceDemo(Heratio &heratio, HenselCode &hensel_code);

void HenselCodePerformance(HenselCode &hensel_code);

void EncryptionPerformance(Heratio &heratio, HenselCode &hensel_code);

void BasicHomomorphismPerformance(Heratio &heratio, HenselCode &hensel_code);

void CompositeHomomorphismPerformance(Heratio &heratio,
                                      HenselCode &hensel_code);

void PrintDuration(double miliseconds);