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

float collatz_wielandt_max(VectorXf v, MatrixXf M)
{
  VectorXf vz = v;
  for (int i = 0; i < vz.size(); i++)
    if (!(vz[i] > 1e-10))
      vz[i] = 1e-10;
  VectorXf Mvz = M*vz;
  float m = 0;
  for (int i = 0; i < vz.size(); i++)
      m = std::max(m, Mvz[i]/vz[i]);
  return m;
}

float collatz_wielandt_min(VectorXf v, MatrixXf M)
{
  VectorXf vz = v;
  for (int i = 0; i < vz.size(); i++)
    if (!(vz[i] > 1e-10))
      vz[i] = 0;
  VectorXf Mvz = M*vz;
  float m = std::numeric_limits<double>::max();
  for (int i = 0; i < vz.size(); i++)
    if (vz[i] > 1e-10)
      m = std::min(m, Mvz[i]/vz[i]);
  return m;
}

VectorXf powerit(MatrixXf M, float tol, VectorXf v)
{
  v = v.normalized();
  VectorXf nextv = M*v;
  double cwmax = collatz_wielandt_max(v, M);
  double cwmin = collatz_wielandt_min(v, M);
  while (abs(1-cwmax/cwmin) > tol)
  {
    v = nextv;
    v = v.normalized();
    nextv = M*v;
    cwmax = collatz_wielandt_max(v, M);
    cwmin = collatz_wielandt_min(v, M);
    std::cout << cwmin << " " << cwmax << std::endl;
  }
  return v;
}

VectorXf powerit(MatrixXf M, float tol)
{
  return powerit(M, tol, VectorXf::Ones(M.cols()));
}

