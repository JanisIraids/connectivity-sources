#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Core>

using namespace Eigen;

#include "util.hpp"



int main(int argc, char** argv)
{
  ul maxi = 15;
  if (argc >= 2)
    sscanf(argv[1], "%lu", &maxi);
  ul d = 1;
  MatrixXf A00 = MatrixXf::Zero(d, d);
  MatrixXf A01 = MatrixXf::Zero(d, d);
  MatrixXf A10 = MatrixXf::Zero(d, d);
  MatrixXf A11 = MatrixXf::Identity(d, d);
  for (ul i = 1; i <= maxi; i++, d *= 2)
  {
    MatrixXf nA00 = MatrixXf::Zero(2*d, 2*d);
    MatrixXf nA01 = MatrixXf::Zero(2*d, 2*d);
    MatrixXf nA10 = MatrixXf::Zero(2*d, 2*d);
    MatrixXf nA11 = MatrixXf::Zero(2*d, 2*d);
    nA00.topLeftCorner(d, d) = A00+A11;
    nA00.topRightCorner(d, d) = A10+A11;
    nA00.bottomLeftCorner(d, d) = A01+A11;
    nA00.bottomRightCorner(d, d) = A00+A01+A10+A11;
    nA01.topRightCorner(d, d) = A00+A10+2*A11;
    nA01.bottomRightCorner(d, d) = A00+2*A01+A10+2*A11;    
    nA10.bottomLeftCorner(d, d) = A00+A01+2*A11;
    nA10.bottomRightCorner(d, d) = A00+A01+2*A10+2*A11;
    nA11.bottomRightCorner(d, d) = 2*A00+2*A01+2*A10+4*A11;
    A00 = nA00;
    A01 = nA01;
    A10 = nA10;
    A11 = nA11;
    MatrixXf Sprime = nA00+nA01+nA10+nA11;
    VectorXf eig = powerit(Sprime, 0.0001);
    std::cout << i << " " << pow(collatz_wielandt_max(eig, Sprime), 1.0/(4*i)) << std::endl;
  }
  return 0;
}
