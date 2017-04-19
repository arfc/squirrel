#include "ConservativeTemperatureAdvection.h"

template <>
InputParameters
validParams<ConservativeTemperatureAdvection>()
{
  InputParameters params = validParams<ConservativeAdvection>();
  return params;
}

ConservativeTemperatureAdvection::ConservativeTemperatureAdvection(
    const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapKernelInterface<ConservativeAdvection>>(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _d_rho_d_u(getMaterialPropertyDerivative<Real>("rho", _var.name())),
    _cp(getMaterialProperty<Real>("cp")),
    _d_cp_d_u(getMaterialPropertyDerivative<Real>("cp", _var.name()))
{
}

void
ConservativeTemperatureAdvection::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
ConservativeTemperatureAdvection::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * ConservativeAdvection::computeQpResidual();
}

Real
ConservativeTemperatureAdvection::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * ConservativeAdvection::computeQpJacobian() +
         _d_rho_d_u[_qp] * _phi[_j][_qp] * _cp[_qp] * ConservativeAdvection::computeQpResidual() +
         _rho[_qp] * _d_cp_d_u[_qp] * _phi[_j][_qp] * ConservativeAdvection::computeQpResidual();
}
