#include "CtrlConservativeTemperatureAdvection.h"

registerMooseObject("SquirrelApp", CtrlConservativeTemperatureAdvection);

template <>
InputParameters
validParams<CtrlConservativeTemperatureAdvection>()
{
  InputParameters params = validParams<CtrlConservativeAdvection>();
  return params;
}

CtrlConservativeTemperatureAdvection::CtrlConservativeTemperatureAdvection(
    const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapKernelInterface<CtrlConservativeAdvection>>(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _d_rho_d_u(getMaterialPropertyDerivative<Real>("rho", _var.name())),
    _cp(getMaterialProperty<Real>("cp")),
    _d_cp_d_u(getMaterialPropertyDerivative<Real>("cp", _var.name()))
{
}

void
CtrlConservativeTemperatureAdvection::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
CtrlConservativeTemperatureAdvection::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * CtrlConservativeAdvection::computeQpResidual();
}

Real
CtrlConservativeTemperatureAdvection::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * CtrlConservativeAdvection::computeQpJacobian() +
         _d_rho_d_u[_qp] * _phi[_j][_qp] * _cp[_qp] *
             CtrlConservativeAdvection::computeQpResidual() +
         _rho[_qp] * _d_cp_d_u[_qp] * _phi[_j][_qp] *
             CtrlConservativeAdvection::computeQpResidual();
}
