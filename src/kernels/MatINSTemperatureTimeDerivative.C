#include "MatINSTemperatureTimeDerivative.h"

template<>
InputParameters validParams<MatINSTemperatureTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  return params;
}


MatINSTemperatureTimeDerivative::MatINSTemperatureTimeDerivative(const InputParameters & parameters) :
    DerivativeMaterialInterface<JvarMapKernelInterface<TimeDerivative> >(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _d_rho_d_u(getMaterialPropertyDerivative<Real>("rho", _var.name())),
    _cp(getMaterialProperty<Real>("cp")),
    _d_cp_d_u(getMaterialPropertyDerivative<Real>("cp", _var.name()))
{}

void
MatINSTemperatureTimeDerivative::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
MatINSTemperatureTimeDerivative::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * TimeDerivative::computeQpResidual();
}

Real
MatINSTemperatureTimeDerivative::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * TimeDerivative::computeQpJacobian() +
         _d_rho_d_u[_qp] * _phi[_j][_qp] * _cp[_qp] * TimeDerivative::computeQpResidual() +
         _rho[_qp] * _d_cp_d_u[_qp] * _phi[_j][_qp] * TimeDerivative::computeQpResidual();
}
