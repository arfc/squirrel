#include "NonConservativeAdvection.h"

registerMooseObject("SquirrelApp", NonConservativeAdvection);

InputParameters
NonConservativeAdvection::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<RealVectorValue>("velocity", "Velocity Vector");
  return params;
}

NonConservativeAdvection::NonConservativeAdvection(const InputParameters & parameters)
  : Kernel(parameters), _velocity(getParam<RealVectorValue>("velocity"))
{
}

Real
NonConservativeAdvection::computeQpResidual()
{
  return _test[_i][_qp] * (_velocity * _grad_u[_qp]);
}

Real
NonConservativeAdvection::computeQpJacobian()
{
  return _test[_i][_qp] * (_velocity * _grad_phi[_j][_qp]);
}
