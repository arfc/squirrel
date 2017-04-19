#include "TemperatureInflowBC.h"

template <>
InputParameters
validParams<TemperatureInflowBC>()
{
  InputParameters params = validParams<InflowBC>();
  return params;
}

TemperatureInflowBC::TemperatureInflowBC(const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapIntegratedBCInterface<InflowBC>>(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _d_rho_d_u(getMaterialPropertyDerivative<Real>("rho", _var.name())),
    _cp(getMaterialProperty<Real>("cp")),
    _d_cp_d_u(getMaterialPropertyDerivative<Real>("cp", _var.name()))
{
}

void
TemperatureInflowBC::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
TemperatureInflowBC::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * InflowBC::computeQpResidual();
}

Real
TemperatureInflowBC::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * InflowBC::computeQpJacobian() +
         _d_rho_d_u[_qp] * _phi[_j][_qp] * _cp[_qp] * InflowBC::computeQpResidual() +
         _rho[_qp] * _d_cp_d_u[_qp] * _phi[_j][_qp] * InflowBC::computeQpResidual();
}
