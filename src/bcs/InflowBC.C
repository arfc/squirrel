#include "InflowBC.h"

registerMooseObject("SquirrelApp", InflowBC);

template <>
InputParameters
validParams<InflowBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<Real>("uu", 0, "The x-component of the velocity");
  params.addParam<Real>("vv", 0, "The y-component of the velocity");
  params.addParam<Real>("ww", 0, "The z-component of the velocity");
  params.addRequiredParam<Real>("inlet_conc", "The inlet concentration");
  return params;
}

InflowBC::InflowBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _uu(getParam<Real>("uu")),
    _vv(getParam<Real>("vv")),
    _ww(getParam<Real>("ww")),
    _inlet_conc(getParam<Real>("inlet_conc"))
{
}

Real
InflowBC::computeQpResidual()
{
  RealVectorValue velocity(_uu, _vv, _ww);
  return _test[_i][_qp] * _inlet_conc * velocity * _normals[_qp];
}

Real
InflowBC::computeQpJacobian()
{
  return 0.;
}
