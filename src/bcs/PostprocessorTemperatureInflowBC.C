#include "PostprocessorTemperatureInflowBC.h"

registerMooseObject("SquirrelApp", PostprocessorTemperatureInflowBC);

InputParameters
PostprocessorTemperatureInflowBC::validParams()
{
  InputParameters params = PostprocessorInflowBC::validParams();
  params.addParam<MaterialPropertyName>("rho", "rho", "Density material property name");
  params.addParam<MaterialPropertyName>("cp", "cp", "Specific heat material property name");
  return params;
}

PostprocessorTemperatureInflowBC::PostprocessorTemperatureInflowBC(
    const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapIntegratedBCInterface<PostprocessorInflowBC>>(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _d_rho_d_u(getMaterialPropertyDerivative<Real>("rho", _var.name())),
    _cp(getMaterialProperty<Real>("cp")),
    _d_cp_d_u(getMaterialPropertyDerivative<Real>("cp", _var.name()))
{
}

void
PostprocessorTemperatureInflowBC::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
PostprocessorTemperatureInflowBC::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * PostprocessorInflowBC::computeQpResidual();
}

Real
PostprocessorTemperatureInflowBC::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * PostprocessorInflowBC::computeQpJacobian() +
         _d_rho_d_u[_qp] * _phi[_j][_qp] * _cp[_qp] * PostprocessorInflowBC::computeQpResidual() +
         _rho[_qp] * _d_cp_d_u[_qp] * _phi[_j][_qp] * PostprocessorInflowBC::computeQpResidual();
}
