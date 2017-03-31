#include "TemperatureOutflowBC.h"

template<>
InputParameters validParams<TemperatureOutflowBC>()
{
  InputParameters params = validParams<OutflowBC>();
  return params;
}

TemperatureOutflowBC::TemperatureOutflowBC(const InputParameters & parameters) :
    DerivativeMaterialInterface<JvarMapIntegratedBCInterface<OutflowBC> >(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _d_rho_d_u(getMaterialPropertyDerivative<Real>("rho", _var.name())),
    _cp(getMaterialProperty<Real>("cp")),
    _d_cp_d_u(getMaterialPropertyDerivative<Real>("cp", _var.name()))
{
}

void
TemperatureOutflowBC::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
TemperatureOutflowBC::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * OutflowBC::computeQpResidual();
}

Real
TemperatureOutflowBC::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * OutflowBC::computeQpJacobian() +
         _d_rho_d_u[_qp] * _cp[_qp] * OutflowBC::computeQpResidual() +
         _rho[_qp] * _d_cp_d_u[_qp] * OutflowBC::computeQpResidual();
}
