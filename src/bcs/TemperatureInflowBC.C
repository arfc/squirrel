#include "TemperatureInflowBC.h"

template<>
InputParameters validParams<TemperatureInflowBC>()
{
  InputParameters params = validParams<InflowBC>();
  return params;
}

TemperatureInflowBC::TemperatureInflowBC(const InputParameters & parameters) :
  InflowBC(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _cp(getMaterialProperty<Real>("cp"))
{
}

Real
TemperatureInflowBC::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * InflowBC::computeQpResidual();
}

Real
TemperatureInflowBC::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * InflowBC::computeQpJacobian();
}
