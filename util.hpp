#include <algorithm>

typedef unsigned long ul;


template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    out << '[';
    if (v.size())
    {
      out << v[0];
      for (ul i = 1; i < v.size(); i++)
        out << ", " << v[i];
    }
    out << "]";
  return out;
}

float collatz_wielandt(VectorXf v, VectorXf Mv)
{
  float m = std::numeric_limits<double>::max();
  for (int i = 0; i < v.size(); i++)
    if (v[i] > 1e-10)
      m = std::min(m, Mv[i]/v[i]);
  return m;
}

double powerit(MatrixXf M, float tol, VectorXf v)
{
  v /= v.norm();
  VectorXf nextv = M*v;
  double cw = collatz_wielandt(v, nextv);
  while (abs(1-cw/nextv.norm()) > tol)
  {
    v = nextv;
    v /= v.norm();
    nextv = M*v;
    cw = collatz_wielandt(v, nextv);
  }
  return cw;
}

double powerit(MatrixXf M, float tol)
{
  return powerit(M, tol, VectorXf::Ones(M.cols()));
}

