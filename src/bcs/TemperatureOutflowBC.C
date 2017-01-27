#include "TemperatureOutflowBC.h"

template<>
InputParameters validParams<TemperatureOutflowBC>()
{
  InputParameters params = validParams<OutflowBC>();
  params.addClassDescription("DG upwinding for the convection");
  return params;
}

TemperatureOutflowBC::TemperatureOutflowBC(const InputParameters & parameters) :
    OutflowBC(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _cp(getMaterialProperty<Real>("cp"))
{
}

Real
TemperatureOutflowBC::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * OutflowBC::computeQpResidual();
}

Real
TemperatureOutflowBC::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * OutflowBC::computeQpJacobian();
}
