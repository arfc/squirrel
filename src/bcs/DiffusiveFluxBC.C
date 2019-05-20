#include "DiffusiveFluxBC.h"

registerMooseObject("SquirrelApp", DiffusiveFluxBC);

template <>
InputParameters
validParams<DiffusiveFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<MaterialPropertyName>(
      "D_name", "D", "The name of the diffusivity, conductivity, or viscosity.");
  return params;
}

DiffusiveFluxBC::DiffusiveFluxBC(const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapIntegratedBCInterface<IntegratedBC>>(parameters),
    _D(getMaterialProperty<Real>("D_name")),
    _d_D_d_u(getMaterialPropertyDerivative<Real>("D_name", _var.name()))
{
}

void
DiffusiveFluxBC::initialSetup()
{
  validateNonlinearCoupling<Real>("D_name");
}

Real
DiffusiveFluxBC::computeQpResidual()
{
  return _normals[_qp] * -_D[_qp] * _grad_u[_qp];
}

Real
DiffusiveFluxBC::computeQpJacobian()
{
  return -_normals[_qp] *
         (_d_D_d_u[_qp] * _phi[_j][_qp] * _grad_u[_qp] + _D[_qp] * _grad_phi[_j][_qp]);
}
