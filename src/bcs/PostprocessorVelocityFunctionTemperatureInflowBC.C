#include "PostprocessorVelocityFunctionTemperatureInflowBC.h"

registerMooseObject("SquirrelApp", PostprocessorVelocityFunctionTemperatureInflowBC);

InputParameters
PostprocessorVelocityFunctionTemperatureInflowBC::validParams()
{
  InputParameters params = PostprocessorVelocityFunctionInflowBC::validParams();
  params.addParam<MaterialPropertyName>("rho", "rho", "Density material property name");
  params.addParam<MaterialPropertyName>("cp", "cp", "Specific heat material property name");
  return params;
}

PostprocessorVelocityFunctionTemperatureInflowBC::PostprocessorVelocityFunctionTemperatureInflowBC(
    const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapIntegratedBCInterface<PostprocessorVelocityFunctionInflowBC>>(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _d_rho_d_u(getMaterialPropertyDerivative<Real>("rho", _var.name())),
    _cp(getMaterialProperty<Real>("cp")),
    _d_cp_d_u(getMaterialPropertyDerivative<Real>("cp", _var.name()))
{
}

void
PostprocessorVelocityFunctionTemperatureInflowBC::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
PostprocessorVelocityFunctionTemperatureInflowBC::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * PostprocessorVelocityFunctionInflowBC::computeQpResidual();
}

Real
PostprocessorVelocityFunctionTemperatureInflowBC::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * PostprocessorVelocityFunctionInflowBC::computeQpJacobian() +
         _d_rho_d_u[_qp] * _phi[_j][_qp] * _cp[_qp] * PostprocessorVelocityFunctionInflowBC::computeQpResidual() +
         _rho[_qp] * _d_cp_d_u[_qp] * _phi[_j][_qp] * PostprocessorVelocityFunctionInflowBC::computeQpResidual();
}
