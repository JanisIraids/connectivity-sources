#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace Eigen;

#include "util.hpp"

int main(int argc, char** argv)
{
  ul d = 4;
  if (argc >= 2)
    sscanf(argv[1], "%lu", &d);
  ul variables = 4*d;
  std::vector<std::vector<bool> > valid_inputs;
  for (ul i = 0; i < (1UL<<variables); i++)
  {
    std::vector<bool> input(variables, false);
    for (ul b = 0; b < variables; b++)
      input[b] = (1<<b)&i;
    bool failed = false;
    if (!((input[0] || input[1]) && (input[4*d-2] || input[4*d-1])))
      failed = true;
    for (ul k = 0; k < d - 1; k++)
      if ((input[4*k+2]||input[4*k+3]) != (input[4*k+4] || input[4*k+5]))
        failed = true;
    if (!failed)
      valid_inputs.push_back(input);
  }
  //std::cout << "valid inputs = " << valid_inputs.size() << std::endl;
  MatrixXf S = MatrixXf::Zero(valid_inputs.size(),valid_inputs.size());
  for (ul i = 0; i < valid_inputs.size(); i++)
  {
    for (ul j = 0; j < valid_inputs.size(); j++)
    {
      bool failed = false;
      for (ul k = 0; k < d; k++)
      {
        if ((valid_inputs[i][k*4+3] || valid_inputs[j][k*4+2]) != (valid_inputs[i][k*4+1] || valid_inputs[j][k*4]))
          failed = true;
      }
      if (!failed)
      {
        S(i,j) = 1;
      }
    }
  }
  VectorXf eig = powerit(S, 1e-6);
  std::cout << pow(collatz_wielandt_min(eig, S), 1.0/(4*d)) << std::endl;
  return 0;
}
