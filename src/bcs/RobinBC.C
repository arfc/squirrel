
#include "RobinBC.h"

registerMooseObject("SquirrelApp", RobinBC);

InputParameters
RobinBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addParam<Real>("velocity", 1, "The 1D velocity.");
  return params;
}

RobinBC::RobinBC(const InputParameters & parameters)
  : IntegratedBC(parameters), _velocity(getParam<Real>("velocity"))
{
}

Real
RobinBC::computeQpResidual()
{
  return _test[_i][_qp] * (1. + _velocity) * _u[_qp];
  // return _test[_i][_qp] * -2. * _grad_u[_qp] * _normals[_qp];
}

Real
RobinBC::computeQpJacobian()
{
  return _test[_i][_qp] * (1. + _velocity) * _phi[_j][_qp];
  // return _test[_i][_qp] * -2. * _grad_phi[_j][_qp] * _normals[_qp];
}
