#include "InflowBC.h"

template <>
InputParameters
validParams<InflowBC>()
{
  InputParameters params = InflowBCBase<Real>::validParams();
  return params;
}

InflowBC::InflowBC(const InputParameters & parameters) : InflowBCBase<Real>(parameters) {}
