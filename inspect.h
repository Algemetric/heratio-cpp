#pragma once

#include <NTL/ZZ.h>
#include <vector>

using namespace std;
using namespace NTL;

void Inspect(Heratio heratio)
{
  cout << "Heratio instance:\n\n";
  cout << "d = " << heratio.d << endl;
  cout << "t = " << heratio.t << endl;
  cout << "alpha = " << heratio.alpha << endl;
  cout << "beta = " << heratio.beta << endl;
  cout << "lambda = " << heratio.lambda << "\n\n";
  cout << "eta = " << heratio.eta << endl;
  cout << "mu = " << heratio.mu << endl;
  cout << "sigma = " << heratio.sigma << endl;
  cout << "gamma = " << heratio.gamma << "\n\n";
  cout << "q0_bits = " << NumBits(heratio.q0) << endl;
  cout << "p_bits = " << NumBits(heratio.p) << endl;
  cout << "q0_to_beta_bits = " << NumBits(heratio.q0_to_beta) << endl;
  cout << "p_to_alpha_bits = " << NumBits(heratio.p_to_alpha) << endl;
  cout << "p_star_bits = " << NumBits(heratio.p_star) << endl;
  cout << "x0_bits = " << NumBits(heratio.x0) << "\n\n";
}

void Inspect(vector<Rational> v)
{
  stringstream buffer;
  buffer << "<Vector ";
  for (long i = 0; i < v.size(); i++)
  {
    buffer << v[i].ToString();
    if (i < v.size() - 1)
    {
      buffer << ", ";
    }
  }
  buffer << ">";
  cout << buffer.str() << endl;
}

void Inspect(Vec<ZZ> v)
{
  stringstream buffer;
  buffer << "<Vector ";
  for (long i = 0; i < v.length(); i++)
  {
    buffer << v[i];
    if (i < v.length() - 1)
    {
      buffer << ", ";
    }
  }
  buffer << ">";
  cout << buffer.str() << endl;
}