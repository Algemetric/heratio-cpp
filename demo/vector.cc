#include "include_helper.h"

void ReadInputVector(int index, int &size, std::vector<Rational> &vector)
{
  std::string string;
  Rational rational;

  std::cout << "\nDefininig vector #" << index << std::endl;
  for (int i = 0; i < size; i++)
  {
    std::cout << "Type rational number for unit basis e" << i + 1 << ": ";
    std::cin >> string;
    rational = StringToRational(string);
    vector.push_back(rational);
  }
}